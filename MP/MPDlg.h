
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
	DoublyLinkedList<CMusic> m_musicList; // ��ü �뷡 ���
	DoublyLinkedList<CString> m_playlistList; // ������
	CQueue<CMusic> m_playQueue; // ���� ��� ���� �������� �뷡��
public:
	// Func : mci�� �̿��Ͽ� �뷡�� �����Ŵ
	void OnPLAY(void);
	// �÷��� ��ư
	CButton m_playBtn;
	// ������� �뷡 �ð��� �����ִ� �����̴�
	CSliderCtrl m_playtimeSlider;
	// �÷������� �뷡�� ������Ŵ
	void OnSTOP(void);
	// mci�� �ݱ� ���� �Լ�
	void OnCLOSE(void);
	afx_msg void OnLbnDblclkList();
	// ���� ����� ������ ����Ʈ�ڽ�
	CListBox m_nameListbox;
	// ���� ���� ���� �뷡 ���
	void OnPRE(void);
	// ���� �뷡�� ����ϰ� �ϴ� �Լ�
	void OnNEXT(void);
	// �뷡 �������� ����Ʈ���� ���� ��θ� ã���ִ� �Լ�
	CMusic FindMusicFilePath(CString name);
	// �����Ͽ� �߰��� �뷡�� ����. ��ü�뷡 ����Ʈ���� ��� �����ְ� ��.
	void OnDEL(void);
	afx_msg void OnCbnSelchangeComboPlaystyle();
	// �÷����ϰ��� �ϴ� Ÿ���� �޺��ڽ����� ������ �� ����
	CComboBox m_playstyleCombo;
	// ������ ������ ���� ����� �� �ְ� �ϴ� �Լ�
	int RandomPLAY(void);
	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnPlaypause();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnPost();
	// ���� ����Ǵ� �뷡 ����
	CStatic m_playtitle;
	// ����Ʈ�� �������� ������ ������ �� �ִ� ��
	CTabCtrl m_tab;
	afx_msg void OnEnChangeEditSearchinput();
	// �÷��� �ð��� �����ִ� Static Text
	CStatic m_playtime;
	// ȭ�鿡 �ð��� ǥ���ϴ� �Լ�
	void SetTimeStaticText(int time);
	// �÷��� ����� �������� �� �� �����ϴ� ����
	CButton m_random;
	// ���� �������� ���ѹݺ����� �����ϴ� ����
	CButton m_repeatall;
	// ���� ������� �뷡�� ���ѹݺ����� ����� ����
	CButton m_repeatone;
	afx_msg void OnBnClickedCheckRandom();
	afx_msg void OnBnClickedCheckRepeatall();
	afx_msg void OnBnClickedCheckRepeatone();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	// ����ڰ� ���ϴ� ����/������ ���� �� ����(Ȥ�� ���õ�) ���������� ����Ʈ�� �߰��ϴ� �Լ�
	void OpenWithModal(void);
	afx_msg void OnBnClickedBtnAdd();
};
