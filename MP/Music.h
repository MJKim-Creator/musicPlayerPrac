#pragma once
class CMusic
{
public:
	CMusic(void); // 기본 생성자
	~CMusic(void); // 기본 소멸자

	// func : operator overloading, input된 값이 자신의 값으로 세팅됨.
	// pre : none
	// post : input의 title과 path가 자신의 값으로 세팅됨
	void operator =(CMusic& input);

	// func : title로 자신과 input의 값을 비교하여 같으면 0, input이 더 크면 0보다 큰 값, input이 더 작으면 0보다 작은 값을 리턴
	// pre : 자신의 값이 initialize
	// post : 비교된 결과값이 리턴
	int Compare(CMusic& input);

	// func : 노래 제목을 리턴
	// pre : title이 initialize
	// post : 노래 제목을 리턴함
	CString GetTitle();

	// func : 노래파일의 경로를 리턴
	// pre : path가 initialize
	// post : 노래파일의 경로를 리턴함
	CString GetPath();

	// func : 노래파일의 확장자를 리턴
	// pre : path가 initialize
	// post : 노래파일의 확장자를 리턴
	CString GetExtension();
	
	// func : 입력받은 값으로 노래파일의 제목을 초기화
	// pre : none
	// post : 입력받은 값으로 title 세팅
	void SetTitle(CString& title);
	
	// func : 입력받은 값으로 노래파일의 경로를 초기화
	// pre : none
	// post : 입력받은 값으로 path 세팅
	void SetPath(CString& path);

	// func : 입력받은 값과 자신을 키값으로 비교하여 같은지 여부를 리턴
	// pre : 자신의 키값이 초기화
	// post : 입력받은 값과 자신의 값이 같으면 true, 다르면 false 리턴
	bool operator ==(CMusic& music);

private:
	CString m_title; // key값, 노래제목
	CString m_path; // 노래제목
	CString m_extent; // 확장자
};

