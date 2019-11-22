#pragma once
#include "DoublyLinkedList.h"
template <class DataType>
class CQueue
{
private:
	DoublyLinkedList<DataType> m_list;
	int m_location;
public:
	CQueue(void); // 기본 생성자
	~CQueue(void); // 기본 소멸자

	// func : queue에 data를 넣음
	// pre : none
	// post : queue에 data가 들어감. 성공하면 true, 그렇지 않으면 false 리턴
	bool Enqueue(DataType& data);

	// func : queue에서 맨 첫번째에 들어갔던 데이터를 제거
	// pre : 데이터가 존재
	// post : queue에서 맨 첫번째에 들어갔던 데이터가 제거됨. 성공하면 true, 실패하면(queue에 데이터가 없는 경우, 그외 기타) false return
	bool Dequeue();

	// func : queue를 비움
	// pre : none
	// post : queue의 모든 데이터 삭제
	void MakeEmpty();

	// func : queue에 더 값이 들어갈 수 있는지 확인
	// pre : none
	// post : queue가 꽉 찼다면 true, 그렇지 않다면 false 리턴
	bool IsFull();

	// func : queue가 비어 있는지 확인
	// pre : none
	// post : queue가 비어 있다면 true, 그렇지 않다면 false 리턴
	bool IsEmpty();

	// func : queue에 들어있는 데이터의 개수를 리턴
	int GetLength();

	// func : queue의 맨 처음에 들어온 데이터를 리턴
	DataType GetData();

	// queue에서 특정 데이터를 가리키는 변수인 location의 위치를 초기화시키는 함수
	void ResetQueue(void);
};


template <class DataType>
CQueue<DataType>::CQueue(void)
{
	m_location = 1;
}

template <class DataType>
CQueue<DataType>::~CQueue(void)
{
}

template <class DataType>
bool CQueue<DataType>::Enqueue(DataType& data){
	// func : queue에 data를 넣음
	// pre : none
	// post : queue에 data가 들어감. 성공하면 true, 그렇지 않으면 false 리턴
	m_list.Add(data, m_list.GetLength()+1);

	return true;
}

template <class DataType>
bool CQueue<DataType>::Dequeue(){
	// func : queue에서 맨 첫번째에 들어갔던 데이터를 제거
	// pre : 데이터가 존재
	// post : queue에서 맨 첫번째에 들어갔던 데이터가 제거됨. 성공하면 true, 실패하면(queue에 데이터가 없는 경우, 그외 기타) false return
	DataType deldata;
	m_list.Get(deldata, 1);
	m_list.Del(deldata);

	return true;
}

template <class DataType>
void CQueue<DataType>::MakeEmpty(){
	// func : queue를 비움
	// pre : none
	// post : queue의 모든 데이터 삭제
	m_list.MakeEmpty();
}

template <class DataType>
bool CQueue<DataType>::IsFull(){
	// func : queue에 더 값이 들어갈 수 있는지 확인
	// pre : none
	// post : queue가 꽉 찼다면 true, 그렇지 않다면 false 리턴
	return m_list.IsFull();
}

template <class DataType>
bool CQueue<DataType>::IsEmpty(){
	// func : queue가 비어 있는지 확인
	// pre : none
	// post : queue가 비어 있다면 true, 그렇지 않다면 false 리턴
	return m_list.IsEmpty();
}

template <class DataType>
int CQueue<DataType>::GetLength(){
	// func : queue에 들어있는 데이터의 개수를 리턴
	return m_list.GetLength();
}

template <class DataType>
DataType CQueue<DataType>::GetData(){
	// func : queue에서 location의 위치에 있는 데이터를 리턴
	DataType d;
	m_list.Get(d, m_location);
	m_location++;

	return d;
}

template <class DataType>
void CQueue<DataType>::ResetQueue(void)
{
	m_location = 1;
}
