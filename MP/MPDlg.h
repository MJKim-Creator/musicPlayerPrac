
// MPDlg.h : header file
//

#pragma once
//#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Music.h"
#include "afxwin.h"
#include "afxcmn.h"


// CMPDlg dialog
class CMPDlg : public CDialogEx
{
// Construction
public:
	CMPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void SearchMusicFile(CString dir);
private:
	DoublyLinkedList<CMusic> m_musicList; // 전체 노래 목록
	DoublyLinkedList<CString> m_playlistList; // 재생목록
	CQueue<CMusic> m_playQueue; // 현재 재생 중인 재생목록의 노래들
public:
	// Func : mci를 이용하여 노래를 재생시킴
	void OnPLAY(void);
	// 플레이 버튼
	CButton m_playBtn;
	// 재생중인 노래 시간을 보여주는 슬라이더
	CSliderCtrl m_playtimeSlider;
	// 플레이중인 노래를 정지시킴
	void OnSTOP(void);
	// mci를 닫기 위한 함수
	void OnCLOSE(void);
	afx_msg void OnLbnDblclkList();
	// 각종 목록을 보여줄 리스트박스
	CListBox m_nameListbox;
	// 현재 곡의 이전 노래 재생
	void OnPRE(void);
	// 다음 노래를 재생하게 하는 함수
	void OnNEXT(void);
	// 노래 제목으로 리스트에서 파일 경로를 찾아주는 함수
	CMusic FindMusicFilePath(CString name);
	// 재생목록에 추가된 노래를 삭제. 전체노래 리스트에는 계속 남아있게 됨.
	void OnDEL(void);
	afx_msg void OnCbnSelchangeComboPlaystyle();
	// 플레이하고자 하는 타입을 콤보박스에서 선택할 수 있음
	CComboBox m_playstyleCombo;
	// 랜덤한 순서로 곡을 재생할 수 있게 하는 함수
	int RandomPLAY(void);
	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnPlaypause();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnPost();
	// 현재 재생되는 노래 제목
	CStatic m_playtitle;
	// 리스트에 보여지는 내용을 선택할 수 있는 탭
	CTabCtrl m_tab;
	afx_msg void OnEnChangeEditSearchinput();
	// 플레이 시간을 보여주는 Static Text
	CStatic m_playtime;
	// 화면에 시간을 표시하는 함수
	void SetTimeStaticText(int time);
	// 플레이 방식을 랜덤으로 할 지 결정하는 변수
	CButton m_random;
	// 현재 재생목록을 무한반복할지 결정하는 변수
	CButton m_repeatall;
	// 현재 재생중인 노래를 무한반복할지 물어보는 변수
	CButton m_repeatone;
	afx_msg void OnBnClickedCheckRandom();
	afx_msg void OnBnClickedCheckRepeatall();
	afx_msg void OnBnClickedCheckRepeatone();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	// 사용자가 원하는 파일/폴더를 열어 그 안의(혹은 선택된) 음악파일을 리스트에 추가하는 함수
	void OpenWithModal(void);
	afx_msg void OnBnClickedBtnAdd();
};
