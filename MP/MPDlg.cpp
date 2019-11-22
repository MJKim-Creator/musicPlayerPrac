
// MPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP.h"
#include "MPDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h" // mci를 이용한 노래재생을 하고자 함

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMPDlg dialog

enum PlayFlag{
	FPLAY, FPAUSE, FRESUME,						//플레이 상태 (재생, 일시정지, 재개)
	FONSTOP, FOFFSTOP,							//정지 상태(정지버튼이 눌렸는지 여부)
	FNOREPEAT, FONEREPEAT, FALLREPEAT,			//반복 재생 종류(반복없음, 한곡반복, 전체반복)
	FSEQ, FRAN									//랜덤재생 상태(랜덤재생 여부
};

int dwID; // mci에서 사용
int g_playtime = 0; // 슬라이드바로 재생 저장
int g_tend = 0; // 현재 재생되는 노래의 총 플레이 시간을 저장
int g_stop = FOFFSTOP; // stop버튼이 눌렸는지의 유무를 저장. 기본은 눌리지 않음으로 둠
int g_random = FSEQ; // 랜덤모드가 on인지 off인지 확인. 기본은 off상태.
int g_repeat = FNOREPEAT; // 반복모드
int g_playbutt = FPLAY; // 재생버튼이 눌렸는지 여부. 기본은 눌리지 않은 상태 - play상태.
// 누르면 FPAUSE가 활성화되어, 일시정지가 가능하게 됨.

MCI_OPEN_PARMS mciOpen; // mci장치 초기화를 위한 구조체
MCI_PLAY_PARMS mciPlay; // MCI_OPEN_PARMS를 통해 초기화된 장치에 원하는 노래를 플레이하기 위한 구조체
MCI_GENERIC_PARMS mciGeneric;

CMPDlg::CMPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_BTN_PLAYPAUSE, m_playBtn);
	DDX_Control(pDX, IDC_LIST, m_nameListbox);
	DDX_Control(pDX, IDC_COMBO_PLAYSTYLE, m_playstyleCombo);
	DDX_Control(pDX, IDC_STATIC_PLAYTITLE, m_playtitle);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_STATIC_TIME, m_playtime);
	DDX_Control(pDX, IDC_CHECK_RANDOM, m_random);
	DDX_Control(pDX, IDC_CHECK_REPEATALL, m_repeatall);
	DDX_Control(pDX, IDC_CHECK_REPEATONE, m_repeatone);
}

BEGIN_MESSAGE_MAP(CMPDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST, &CMPDlg::OnLbnDblclkList)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAYSTYLE, &CMPDlg::OnCbnSelchangeComboPlaystyle)
	ON_BN_CLICKED(ID_BTN_PRE, &CMPDlg::OnBnClickedBtnPre)
	ON_BN_CLICKED(ID_BTN_PLAYPAUSE, &CMPDlg::OnBnClickedBtnPlaypause)
	ON_BN_CLICKED(ID_BTN_STOP, &CMPDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(ID_BTN_POST, &CMPDlg::OnBnClickedBtnPost)
	ON_EN_CHANGE(IDC_EDIT_SEARCHINPUT, &CMPDlg::OnEnChangeEditSearchinput)
	ON_BN_CLICKED(IDC_CHECK_RANDOM, &CMPDlg::OnBnClickedCheckRandom)
	ON_BN_CLICKED(IDC_CHECK_REPEATALL, &CMPDlg::OnBnClickedCheckRepeatall)
	ON_BN_CLICKED(IDC_CHECK_REPEATONE, &CMPDlg::OnBnClickedCheckRepeatone)
	ON_BN_CLICKED(ID_BTN_DEL, &CMPDlg::OnBnClickedBtnDel)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CMPDlg::OnTcnSelchangeTab)
	ON_BN_CLICKED(ID_BTN_ADD, &CMPDlg::OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CMPDlg message handlers

BOOL CMPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here
		
	m_tab.InsertItem(0, _T("All Songs"));
	m_tab.InsertItem(1, _T("Now Playing"));
	m_tab.InsertItem(2, _T("Playlists"));

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 찾는 디렉토리
void CMPDlg::SearchMusicFile(CString dir){
	dir+="\\*"; // 모든 파일
	CFileFind find;
	BOOL ls = find.FindFile(dir);

	if(ls == 0){
		//AfxMessageBox(_T("파일이 없습니다.")); // 메세지 박스
		m_nameListbox.AddString(_T("파일이 없습니다."));
	}

	while(ls){
		ls = find.FindNextFileW(); // 다음 파일 찾기

		if(find.IsDots()) continue; // . & ..라면 다시 위의 디렉토리로 올라가기
		if(find.IsDirectory()){ // 폴더라면
			CString newDir = find.GetFilePath(); // 폴더 경로를 newDir에 저장
			SearchMusicFile(newDir);
		}else{
			CString name = find.GetFileName(); // 파일 이름만 얻음
			CString extension = name.Mid(name.ReverseFind('.')+1, name.GetLength()); // 확장자 추출
			if(extension.Compare(_T("mp3")) == 0 || extension.Compare(_T("wma")) == 0 || extension.Compare(_T("wav")) == 0){ // 확장자가 음악파일 확장자인지 확인
				CMusic music; // 음악파일 확장자를 가졌다면 전체노래 목록에 해당 노래를 추가한다.
				music.SetTitle(name);
				music.SetPath(find.GetFilePath());
				m_musicList.Add(music, m_musicList.GetLength()+1);
			}
		}
	}
	find.Close();
}



// Func : mci를 이용하여 노래를 재생시킴
void CMPDlg::OnPLAY(void)
{
	int inx = m_nameListbox.GetCurSel(); // 리스트창에 선택되어진게 있어야만 해당 곡부터 플레이된다.
	if(inx == LB_ERR || m_nameListbox.GetCount() < 1){
		inx=0;
		m_nameListbox.SetCurSel(0);
	}

	CString str;
	CMusic music;
	m_nameListbox.GetText(inx, str);
	music = FindMusicFilePath(str);
	mciOpen.lpstrElementName = music.GetPath();
	m_playtitle.SetWindowTextW(music.GetTitle());

	switch(g_playbutt){
		case FPLAY:
			if(dwID && g_stop == FOFFSTOP){
				OnCLOSE();
			}

			m_playBtn.SetWindowTextW(_T("∥"));
			g_playbutt = FPAUSE;

			if(music.GetExtension() == "wav")
				mciOpen.lpstrDeviceType = _T("waveaudio");
			if(music.GetExtension() == "wma" || music.GetExtension() == "mp3")
				mciOpen.lpstrDeviceType = _T("mpegvideo");

			if(g_stop==FOFFSTOP){ // 정지 버튼이 눌리지 않았을 시에는 mci를 새로 open
				mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
				dwID = mciOpen.wDeviceID;
			}

			mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlay);
			MCI_STATUS_PARMS mciStatusParms;
			mciStatusParms.dwItem = MCI_FORMAT_HMS; // 재생시간을 밀리세컨드로 읽어옴
			mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

			g_tend = mciStatusParms.dwReturn/1000; // 노래의 총 플레이 시간을 셋팅
			g_playtime = 0;
			SetTimer(1, 1000, NULL); // 1초마다 OnTimer() 호출
			g_stop = FOFFSTOP; // 정지버튼 누른 후 시작 버튼을 눌렀을 떄를 위해 
			break;

		case FPAUSE: // 재생중이면 일시정지
			m_playBtn.SetWindowTextW(_T("▶"));
			g_playbutt = FRESUME;
			KillTimer(1);

			mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)&mciGeneric);
			break;

		case FRESUME: // 일시 정지가 된 부분부터 시작
			m_playBtn.SetWindowTextW(_T("∥"));
			g_playbutt = FPAUSE;

			MCI_PLAY_PARMS mciPlay;
			mciPlay.dwFrom = g_playtime*1000;
			SetTimer(1, 1000, NULL);

			mciSendCommand(dwID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID)&mciPlay);
			break;
	}
}



// 플레이중인 노래를 정지시킴
void CMPDlg::OnSTOP(void)
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlay); // 정지버튼을 누른 후 재생버튼 누를때를 위해 seek pointer만 처음으로 되돌림
	g_stop = FONSTOP;

	SetTimeStaticText(0);
	m_playBtn.SetWindowTextW(_T("▶"));
	g_playbutt = FPLAY; // 처음부터 재생하게 되돌림
	KillTimer(1);
}


// mci를 닫기 위한 함수
void CMPDlg::OnCLOSE(void)
{
	g_playbutt = FPLAY;
	mciSendCommand(dwID, MCI_CLOSE, NULL, (DWORD)(LPVOID)&mciPlay);
	KillTimer(1);
}



void CMPDlg::OnLbnDblclkList()
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("된다면..띄워보거라.."), NULL, NULL);
	if(dwID){
		OnCLOSE();
	}

	int inx = m_nameListbox.GetCurSel(); // 리스트박스에서 선택된 위치를 가져옴

	CString selname;
	m_nameListbox.GetText(inx, selname);
	CMusic music = FindMusicFilePath(selname);
	AfxMessageBox(selname);
	UpdateData(false);

	mciOpen.lpstrElementName = music.GetPath();

	OnPLAY();
}


// 현재 곡의 이전 노래 재생
void CMPDlg::OnPRE(void)
{
	int inx = m_nameListbox.GetCurSel();
	if(--inx < 0 && g_random == FSEQ){
		m_nameListbox.SetCurSel(m_nameListbox.GetCount());
	}else{
		m_nameListbox.SetCurSel(inx);
	}
	if(g_repeat == FONEREPEAT){
		inx++;
		m_nameListbox.SetCurSel(inx);
	}

	if(g_random == FRAN){
		if(RandomPLAY())
			return;
	}

	CString selname;
	m_nameListbox.GetText(inx, selname);
	CMusic music = FindMusicFilePath(selname);
	UpdateData(false);


	if(dwID)
		OnCLOSE();

	mciOpen.lpstrElementName = music.GetPath();
	OnPLAY();
}



// 현재 곡의 다음 노래를 재생하게 하는 함수
void CMPDlg::OnNEXT(void)
{
	int inx = m_nameListbox.GetCurSel();
	inx++;
	if(inx >= m_nameListbox.GetCount() && g_repeat == FNOREPEAT && g_random == FSEQ){ // 전체 재생이 아니며 랜덤곡도 아닐때
		if(g_playtime >= g_tend){
			KillTimer(1);
			OnCLOSE();
		}
		MessageBox(_T("다음 곡이 없습니다"), NULL, NULL);
		inx--;
	}else{
		if(g_repeat == FALLREPEAT && inx >= m_nameListbox.GetCount()){ // 전체 재생이며 마지막 곡일 떄는 첫 곡으로
			m_nameListbox.SetCurSel(0);
			inx = 0;
		}
		if(g_repeat == FONEREPEAT){ // 한곡 반복재생일때는 방금 전 재생했던 노래를 재생
			inx--;
		}
		if(g_repeat == FRAN) // 랜덤 재생일 떄는 랜덤재생
			if(RandomPLAY())
				return;
		
		CString selname;
		m_nameListbox.SetCurSel(inx);
		m_nameListbox.GetText(inx, selname);
		CMusic music = FindMusicFilePath(selname);
		UpdateData(FALSE);

		if(dwID)
			OnCLOSE();
		
		SetTimeStaticText(0);

		mciOpen.lpstrElementName = music.GetPath();
		OnPLAY();
	}
}


// 노래 제목으로 리스트에서 파일 경로를 찾아주는 함수
CMusic CMPDlg::FindMusicFilePath(CString name)
{
	CMusic lookingfor, result;
	lookingfor.SetTitle(name);

	for(int i=1; i<=m_musicList.GetLength(); i++){ // Doubly Linked List에서 해당 제목을 가진 노래를 찾음
		m_musicList.Get(result, i);
		if(result.Compare(lookingfor) == 0){
			break;
		}
	}
	return result;
}






void CMPDlg::OnCbnSelchangeComboPlaystyle()
{
	// TODO: Add your control notification handler code here
}



// 랜덤한 순서로 곡을 재생할 수 있게 하는 함수
int CMPDlg::RandomPLAY(void)
{
	if(m_nameListbox.GetCount() == 1 && g_repeat == FNOREPEAT){
		MessageBox(_T("한개의 노래만 추가되어 있습니다."), NULL, NULL);
		return 1;
	}else if(m_nameListbox.GetCount() == 1){
		m_nameListbox.SetCurSel(0);
	}
	if(m_nameListbox.GetCount() >= 2){
		int temp = 0;
		while(1){
			temp = rand()%m_nameListbox.GetCount();

			if((m_nameListbox.GetCurSel()-1) != temp){
				m_nameListbox.SetCurSel(temp);
				break;
			}
		}
	}
	return 0;
}


void CMPDlg::OnBnClickedBtnPre()
{
	// TODO: Add your control notification handler code here
	OnPRE();
}


void CMPDlg::OnBnClickedBtnPlaypause()
{
	// TODO: Add your control notification handler code here
	OnPLAY();
}


void CMPDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	OnSTOP();
}


void CMPDlg::OnBnClickedBtnPost()
{
	// TODO: Add your control notification handler code here
	OnNEXT();
}


void CMPDlg::OnEnChangeEditSearchinput()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


// 화면에 시간을 표시하는 함수
void CMPDlg::SetTimeStaticText(int time)
{
	CString str;
	int min, sec;
	min = (int)time/60;
	sec = time%60;
	if(min < 10 && sec < 10){
		str.Format(_T("0%d:0%d"), min, sec);
	}else if(min < 10){
		str.Format(_T("0%d:%d"), min, sec);
	}else if(sec < 10){
		str.Format(_T("%d:0%d"), min, sec);
	}else{
		str.Format(_T("%d:%d"), min, sec);
	}

	m_playtime.SetWindowTextW(str);
}


void CMPDlg::OnBnClickedCheckRandom()
{
	// TODO: Add your control notification handler code here
	if(m_random.GetCheck())
		g_random = FRAN;
	else
		g_random = FSEQ;
}


void CMPDlg::OnBnClickedCheckRepeatall()
{
	// TODO: Add your control notification handler code here
	if(m_repeatall.GetCheck()){
		g_repeat = FALLREPEAT;
		m_repeatone.SetCheck(false);
	}else
		g_repeat = FNOREPEAT;
}


void CMPDlg::OnBnClickedCheckRepeatone()
{
	// TODO: Add your control notification handler code here
	if(m_repeatone.GetCheck()){
		g_repeat = FONEREPEAT;
		m_repeatall.SetCheck(false);
	}else
		g_repeat = FNOREPEAT;
}


void CMPDlg::OnBnClickedBtnDel()
{
	// TODO: Add your control notification handler code here
	int inx = m_nameListbox.GetCurSel();
	CMusic music;
	CString str;
	m_nameListbox.GetText(inx, str);
	music = FindMusicFilePath(str);
	m_nameListbox.DeleteString(inx);
	m_musicList.Del(music);

}


void CMPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	SetTimeStaticText(++g_playtime);

	if(g_playtime >= g_tend){ // 노래의 총 플레이시간보다 현재 재생중인 시간이 크면, 한 곡의 재생이 끝났음을 의미하므로
		OnNEXT();
		g_playbutt = FPLAY;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMPDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CMusic music;
	CString str;
	m_nameListbox.ResetContent();
	switch(m_tab.GetCurFocus()){
		case 0: for(int i=0; i<m_musicList.GetLength(); i++){
					m_musicList.Get(music, i);
					m_nameListbox.AddString(music.GetTitle());
				}
				break;
		case 1: m_playQueue.ResetQueue();
				for(int i=0; i<m_playQueue.GetLength(); i++){
					music = m_playQueue.GetData();
					m_nameListbox.AddString(music.GetTitle());
				}
				break;
		case 2: for(int i=0; i<m_playlistList.GetLength(); i++){
					m_playlistList.Get(str, i);
					m_nameListbox.AddString(str);
				}
				break;
	}
}


// 사용자가 원하는 파일/폴더를 열어 그 안의(혹은 선택된) 음악파일을 리스트에 추가하는 함수
void CMPDlg::OpenWithModal(void)
{
	WCHAR buffer[10000] = {0,};
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
		_T("음악파일/폴더 (*.mp3, *wma, *wav) | *.mp3, *.wma, *wav;|"));

	fDlg.m_ofn.lpstrFile = buffer;
	fDlg.m_ofn.nMaxFile = sizeof(buffer)-1;

	if(fDlg.DoModal() != IDOK){
		return;
	}

	POSITION pos = fDlg.GetStartPosition();

	while(pos){
		CMusic music;
		music.SetPath(fDlg.GetNextPathName(pos));
		music.SetTitle(music.GetPath().Right(music.GetPath().GetLength()-fDlg.GetPathName().GetLength()-1));

		if(music.GetTitle() == ""){
			music.SetPath(fDlg.GetPathName());
			music.SetTitle(fDlg.GetFileName());
			m_musicList.Add(music, 0);

			break;
		}
		//
	}
}


void CMPDlg::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	int inx = m_playstyleCombo.GetCurSel();
	CString str;
	m_playstyleCombo.GetLBText(inx, str);
	if(str == "New File"){
		OpenWithModal();
	}else if(str == "New Forder"){
		ITEMIDLIST *idbrowse;
		TCHAR pathname[1000];
		BROWSEINFO binfo;
		memset(&binfo, 0, sizeof(binfo));
		binfo.hwndOwner = GetSafeHwnd();
		binfo.pidlRoot = NULL;
		binfo.pszDisplayName = pathname;
		binfo.lpszTitle = _T("디렉토리를 선택하세요.");
		binfo.ulFlags = BIF_RETURNONLYFSDIRS;
		binfo.lpfn = NULL;
		binfo.lParam = (LPARAM)(LPCTSTR)"C:\\";
		binfo.lParam = (LPARAM)NULL;
		idbrowse = ::SHBrowseForFolderW(&binfo);
		if(idbrowse){
			SHGetPathFromIDListW(idbrowse, pathname);
			CMusic music;
			music.SetPath();
		}
		if(bDlg.DoModal() == IDOK){
			CString str;
			bDlg.GetSelectStr(str);
			SearchMusicFile(str);
		}
	}else if(str == "To Now Playing"){
		if(m_tab.GetCurFocus() == 0){
			int sinx = m_nameListbox.GetCurSel();
			CString name;
			m_nameListbox.GetText(sinx, name);
			CMusic music;
			music = FindMusicFilePath(name);
			m_playQueue.Enqueue(music);
		}else{
			MessageBox(_T("목록에 목록을 추가하거나, 이미 목록에 있는 노래를 넣을 수 없습니다."), NULL, NULL);
		}
	}

}
