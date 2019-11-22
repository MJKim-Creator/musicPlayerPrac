#include "StdAfx.h"
#include "Music.h"


CMusic::CMusic(void)
{
}


CMusic::~CMusic(void)
{
}

	// func : operator overloading, input�� ���� �ڽ��� ������ ���õ�.
	// pre : none
	// post : input�� title�� path�� �ڽ��� ������ ���õ�
void CMusic::operator =(CMusic& input){
	SetPath(input.GetPath());
	SetTitle(input.GetTitle());
}

	// func : title�� �ڽŰ� input�� ���� ���Ͽ� ������ 0, input�� �� ũ�� 0���� ū ��, input�� �� ������ 0���� ���� ���� ����
	// pre : �ڽ��� ���� initialize
	// post : �񱳵� ������� ����
int CMusic::Compare(CMusic& input){
	return m_title.Compare(input.GetTitle());
}

	// func : �뷡 ������ ����
	// pre : title�� initialize
	// post : �뷡 ������ ������
CString CMusic::GetTitle(){
	return m_title;
}

	// func : �뷡������ ��θ� ����
	// pre : path�� initialize
	// post : �뷡������ ��θ� ������
CString CMusic::GetPath(){
	return m_path;
}

// func : �뷡������ Ȯ���ڸ� ����
	// pre : path�� initialize
	// post : �뷡������ Ȯ���ڸ� ����
CString CMusic::GetExtension(){
	return m_path.Right(3);
}
	
	
	// func : �Է¹��� ������ �뷡������ ������ �ʱ�ȭ
	// pre : none
	// post : �Է¹��� ������ title ����
void CMusic::SetTitle(CString& title){
	m_title = title;
}
	
	// func : �Է¹��� ������ �뷡������ ��θ� �ʱ�ȭ
	// pre : none
	// post : �Է¹��� ������ path ����
void CMusic::SetPath(CString& path){
	m_path = path;
}

	// func : �Է¹��� ���� �ڽ��� Ű������ ���Ͽ� ������ ���θ� ����
	// pre : �ڽ��� Ű���� �ʱ�ȭ
	// post : �Է¹��� ���� �ڽ��� ���� ������ true, �ٸ��� false ����
bool CMusic::operator ==(CMusic& music){
	if(m_title.Compare(music.GetTitle()) == 0)
		return true;
	else
		return false;
}
