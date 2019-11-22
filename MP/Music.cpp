#include "StdAfx.h"
#include "Music.h"


CMusic::CMusic(void)
{
}


CMusic::~CMusic(void)
{
}

	// func : operator overloading, input된 값이 자신의 값으로 세팅됨.
	// pre : none
	// post : input의 title과 path가 자신의 값으로 세팅됨
void CMusic::operator =(CMusic& input){
	SetPath(input.GetPath());
	SetTitle(input.GetTitle());
}

	// func : title로 자신과 input의 값을 비교하여 같으면 0, input이 더 크면 0보다 큰 값, input이 더 작으면 0보다 작은 값을 리턴
	// pre : 자신의 값이 initialize
	// post : 비교된 결과값이 리턴
int CMusic::Compare(CMusic& input){
	return m_title.Compare(input.GetTitle());
}

	// func : 노래 제목을 리턴
	// pre : title이 initialize
	// post : 노래 제목을 리턴함
CString CMusic::GetTitle(){
	return m_title;
}

	// func : 노래파일의 경로를 리턴
	// pre : path가 initialize
	// post : 노래파일의 경로를 리턴함
CString CMusic::GetPath(){
	return m_path;
}

// func : 노래파일의 확장자를 리턴
	// pre : path가 initialize
	// post : 노래파일의 확장자를 리턴
CString CMusic::GetExtension(){
	return m_path.Right(3);
}
	
	
	// func : 입력받은 값으로 노래파일의 제목을 초기화
	// pre : none
	// post : 입력받은 값으로 title 세팅
void CMusic::SetTitle(CString& title){
	m_title = title;
}
	
	// func : 입력받은 값으로 노래파일의 경로를 초기화
	// pre : none
	// post : 입력받은 값으로 path 세팅
void CMusic::SetPath(CString& path){
	m_path = path;
}

	// func : 입력받은 값과 자신을 키값으로 비교하여 같은지 여부를 리턴
	// pre : 자신의 키값이 초기화
	// post : 입력받은 값과 자신의 값이 같으면 true, 다르면 false 리턴
bool CMusic::operator ==(CMusic& music){
	if(m_title.Compare(music.GetTitle()) == 0)
		return true;
	else
		return false;
}
