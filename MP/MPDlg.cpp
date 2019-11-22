
// MPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MP.h"
#include "MPDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h" // mci�� �̿��� �뷡����� �ϰ��� ��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMPDlg dialog

enum PlayFlag{
	FPLAY, FPAUSE, FRESUME,						//�÷��� ���� (���, �Ͻ�����, �簳)
	FONSTOP, FOFFSTOP,							//���� ����(������ư�� ���ȴ��� ����)
	FNOREPEAT, FONEREPEAT, FALLREPEAT,			//�ݺ� ��� ����(�ݺ�����, �Ѱ�ݺ�, ��ü�ݺ�)
	FSEQ, FRAN									//������� ����(������� ����
};

int dwID; // mci���� ���
int g_playtime = 0; // �����̵�ٷ� ��� ����
int g_tend = 0; // ���� ����Ǵ� �뷡�� �� �÷��� �ð��� ����
int g_stop = FOFFSTOP; // stop��ư�� ���ȴ����� ������ ����. �⺻�� ������ �������� ��
int g_random = FSEQ; // ������尡 on���� off���� Ȯ��. �⺻�� off����.
int g_repeat = FNOREPEAT; // �ݺ����
int g_playbutt = FPLAY; // �����ư�� ���ȴ��� ����. �⺻�� ������ ���� ���� - play����.
// ������ FPAUSE�� Ȱ��ȭ�Ǿ�, �Ͻ������� �����ϰ� ��.

MCI_OPEN_PARMS mciOpen; // mci��ġ �ʱ�ȭ�� ���� ����ü
MCI_PLAY_PARMS mciPlay; // MCI_OPEN_PARMS�� ���� �ʱ�ȭ�� ��ġ�� ���ϴ� �뷡�� �÷����ϱ� ���� ����ü
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
// ã�� ���丮
void CMPDlg::SearchMusicFile(CString dir){
	dir+="\\*"; // ��� ����
	CFileFind find;
	BOOL ls = find.FindFile(dir);

	if(ls == 0){
		//AfxMessageBox(_T("������ �����ϴ�.")); // �޼��� �ڽ�
		m_nameListbox.AddString(_T("������ �����ϴ�."));
	}

	while(ls){
		ls = find.FindNextFileW(); // ���� ���� ã��

		if(find.IsDots()) continue; // . & ..��� �ٽ� ���� ���丮�� �ö󰡱�
		if(find.IsDirectory()){ // �������
			CString newDir = find.GetFilePath(); // ���� ��θ� newDir�� ����
			SearchMusicFile(newDir);
		}else{
			CString name = find.GetFileName(); // ���� �̸��� ����
			CString extension = name.Mid(name.ReverseFind('.')+1, name.GetLength()); // Ȯ���� ����
			if(extension.Compare(_T("mp3")) == 0 || extension.Compare(_T("wma")) == 0 || extension.Compare(_T("wav")) == 0){ // Ȯ���ڰ� �������� Ȯ�������� Ȯ��
				CMusic music; // �������� Ȯ���ڸ� �����ٸ� ��ü�뷡 ��Ͽ� �ش� �뷡�� �߰��Ѵ�.
				music.SetTitle(name);
				music.SetPath(find.GetFilePath());
				m_musicList.Add(music, m_musicList.GetLength()+1);
			}
		}
	}
	find.Close();
}



// Func : mci�� �̿��Ͽ� �뷡�� �����Ŵ
void CMPDlg::OnPLAY(void)
{
	int inx = m_nameListbox.GetCurSel(); // ����Ʈâ�� ���õǾ����� �־�߸� �ش� ����� �÷��̵ȴ�.
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

			m_playBtn.SetWindowTextW(_T("��"));
			g_playbutt = FPAUSE;

			if(music.GetExtension() == "wav")
				mciOpen.lpstrDeviceType = _T("waveaudio");
			if(music.GetExtension() == "wma" || music.GetExtension() == "mp3")
				mciOpen.lpstrDeviceType = _T("mpegvideo");

			if(g_stop==FOFFSTOP){ // ���� ��ư�� ������ �ʾ��� �ÿ��� mci�� ���� open
				mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE|MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
				dwID = mciOpen.wDeviceID;
			}

			mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlay);
			MCI_STATUS_PARMS mciStatusParms;
			mciStatusParms.dwItem = MCI_FORMAT_HMS; // ����ð��� �и�������� �о��
			mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);

			g_tend = mciStatusParms.dwReturn/1000; // �뷡�� �� �÷��� �ð��� ����
			g_playtime = 0;
			SetTimer(1, 1000, NULL); // 1�ʸ��� OnTimer() ȣ��
			g_stop = FOFFSTOP; // ������ư ���� �� ���� ��ư�� ������ ���� ���� 
			break;

		case FPAUSE: // ������̸� �Ͻ�����
			m_playBtn.SetWindowTextW(_T("��"));
			g_playbutt = FRESUME;
			KillTimer(1);

			mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)&mciGeneric);
			break;

		case FRESUME: // �Ͻ� ������ �� �κк��� ����
			m_playBtn.SetWindowTextW(_T("��"));
			g_playbutt = FPAUSE;

			MCI_PLAY_PARMS mciPlay;
			mciPlay.dwFrom = g_playtime*1000;
			SetTimer(1, 1000, NULL);

			mciSendCommand(dwID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID)&mciPlay);
			break;
	}
}



// �÷������� �뷡�� ������Ŵ
void CMPDlg::OnSTOP(void)
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&mciPlay); // ������ư�� ���� �� �����ư �������� ���� seek pointer�� ó������ �ǵ���
	g_stop = FONSTOP;

	SetTimeStaticText(0);
	m_playBtn.SetWindowTextW(_T("��"));
	g_playbutt = FPLAY; // ó������ ����ϰ� �ǵ���
	KillTimer(1);
}


// mci�� �ݱ� ���� �Լ�
void CMPDlg::OnCLOSE(void)
{
	g_playbutt = FPLAY;
	mciSendCommand(dwID, MCI_CLOSE, NULL, (DWORD)(LPVOID)&mciPlay);
	KillTimer(1);
}



void CMPDlg::OnLbnDblclkList()
{
	// TODO: Add your control notification handler code here
	MessageBox(_T("�ȴٸ�..������Ŷ�.."), NULL, NULL);
	if(dwID){
		OnCLOSE();
	}

	int inx = m_nameListbox.GetCurSel(); // ����Ʈ�ڽ����� ���õ� ��ġ�� ������

	CString selname;
	m_nameListbox.GetText(inx, selname);
	CMusic music = FindMusicFilePath(selname);
	AfxMessageBox(selname);
	UpdateData(false);

	mciOpen.lpstrElementName = music.GetPath();

	OnPLAY();
}


// ���� ���� ���� �뷡 ���
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



// ���� ���� ���� �뷡�� ����ϰ� �ϴ� �Լ�
void CMPDlg::OnNEXT(void)
{
	int inx = m_nameListbox.GetCurSel();
	inx++;
	if(inx >= m_nameListbox.GetCount() && g_repeat == FNOREPEAT && g_random == FSEQ){ // ��ü ����� �ƴϸ� ����� �ƴҶ�
		if(g_playtime >= g_tend){
			KillTimer(1);
			OnCLOSE();
		}
		MessageBox(_T("���� ���� �����ϴ�"), NULL, NULL);
		inx--;
	}else{
		if(g_repeat == FALLREPEAT && inx >= m_nameListbox.GetCount()){ // ��ü ����̸� ������ ���� ���� ù ������
			m_nameListbox.SetCurSel(0);
			inx = 0;
		}
		if(g_repeat == FONEREPEAT){ // �Ѱ� �ݺ�����϶��� ��� �� ����ߴ� �뷡�� ���
			inx--;
		}
		if(g_repeat == FRAN) // ���� ����� ���� �������
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


// �뷡 �������� ����Ʈ���� ���� ��θ� ã���ִ� �Լ�
CMusic CMPDlg::FindMusicFilePath(CString name)
{
	CMusic lookingfor, result;
	lookingfor.SetTitle(name);

	for(int i=1; i<=m_musicList.GetLength(); i++){ // Doubly Linked List���� �ش� ������ ���� �뷡�� ã��
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



// ������ ������ ���� ����� �� �ְ� �ϴ� �Լ�
int CMPDlg::RandomPLAY(void)
{
	if(m_nameListbox.GetCount() == 1 && g_repeat == FNOREPEAT){
		MessageBox(_T("�Ѱ��� �뷡�� �߰��Ǿ� �ֽ��ϴ�."), NULL, NULL);
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


// ȭ�鿡 �ð��� ǥ���ϴ� �Լ�
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

	if(g_playtime >= g_tend){ // �뷡�� �� �÷��̽ð����� ���� ������� �ð��� ũ��, �� ���� ����� �������� �ǹ��ϹǷ�
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


// ����ڰ� ���ϴ� ����/������ ���� �� ����(Ȥ�� ���õ�) ���������� ����Ʈ�� �߰��ϴ� �Լ�
void CMPDlg::OpenWithModal(void)
{
	WCHAR buffer[10000] = {0,};
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_OVERWRITEPROMPT,
		_T("��������/���� (*.mp3, *wma, *wav) | *.mp3, *.wma, *wav;|"));

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
		binfo.lpszTitle = _T("���丮�� �����ϼ���.");
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
			MessageBox(_T("��Ͽ� ����� �߰��ϰų�, �̹� ��Ͽ� �ִ� �뷡�� ���� �� �����ϴ�."), NULL, NULL);
		}
	}

}
