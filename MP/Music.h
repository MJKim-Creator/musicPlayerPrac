#pragma once
class CMusic
{
public:
	CMusic(void); // �⺻ ������
	~CMusic(void); // �⺻ �Ҹ���

	// func : operator overloading, input�� ���� �ڽ��� ������ ���õ�.
	// pre : none
	// post : input�� title�� path�� �ڽ��� ������ ���õ�
	void operator =(CMusic& input);

	// func : title�� �ڽŰ� input�� ���� ���Ͽ� ������ 0, input�� �� ũ�� 0���� ū ��, input�� �� ������ 0���� ���� ���� ����
	// pre : �ڽ��� ���� initialize
	// post : �񱳵� ������� ����
	int Compare(CMusic& input);

	// func : �뷡 ������ ����
	// pre : title�� initialize
	// post : �뷡 ������ ������
	CString GetTitle();

	// func : �뷡������ ��θ� ����
	// pre : path�� initialize
	// post : �뷡������ ��θ� ������
	CString GetPath();

	// func : �뷡������ Ȯ���ڸ� ����
	// pre : path�� initialize
	// post : �뷡������ Ȯ���ڸ� ����
	CString GetExtension();
	
	// func : �Է¹��� ������ �뷡������ ������ �ʱ�ȭ
	// pre : none
	// post : �Է¹��� ������ title ����
	void SetTitle(CString& title);
	
	// func : �Է¹��� ������ �뷡������ ��θ� �ʱ�ȭ
	// pre : none
	// post : �Է¹��� ������ path ����
	void SetPath(CString& path);

	// func : �Է¹��� ���� �ڽ��� Ű������ ���Ͽ� ������ ���θ� ����
	// pre : �ڽ��� Ű���� �ʱ�ȭ
	// post : �Է¹��� ���� �ڽ��� ���� ������ true, �ٸ��� false ����
	bool operator ==(CMusic& music);

private:
	CString m_title; // key��, �뷡����
	CString m_path; // �뷡����
	CString m_extent; // Ȯ����
};

