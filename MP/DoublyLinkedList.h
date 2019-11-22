#pragma once
#include <iostream>
using namespace std;

template <class TYPE>
struct Node{
	TYPE data;
	Node<TYPE>* next;
	Node<TYPE>* prev;
};

template <class DataType>
class DoublyLinkedList
{
private:
	Node<DataType>* m_head;
	Node<DataType>* m_tail;
	int m_length; // 해당 리스트의 길이
public:
	 // 기본 생성자. Head와 Tail을 초기화함
	DoublyLinkedList(void);
	 // 기본 소멸자. 리스트의 모든 데이터를 지우고 소멸
	virtual ~DoublyLinkedList(void);

	// func : 입력받은 데이터를 inx에 따른 위치에 넣음
	// pre : head와 tail이 initialize
	// post : 입력받은 inx의 위치에 data를 넣는다.
	//		  input에 실패했을 경우(데이터를 더 넣을 수 없거나, 존재하지 않는 인덱스가 input되었을 경우) false, 성공했을 경우 true를 리턴한다.
	bool Add(DataType& data, int inx);

	// func : 입력받은 데이터를 찾아 제거한다.
	// pre : head와 tail의 initialize
	// post : 입력받은 Data를 찾아 삭제한다.
	bool Del(DataType& data);

	// func : 입력받은 위치의 데이터를 data에 저장한다. 데이터가 존재하지 않을 시에는 false, 존재할 시에는 true를 리턴
	// pre : head와 tail이 initialize
	// post : 입력받은 위치의 데이터가 data에 저장된다. 데이터의 존재유무에 따라 true나 false가 리턴된다.
	bool Get(DataType& data, int inx);

	// func : 메모리 공간이 데이터를 더 넣어도 되는건지 확인한다.
	// pre : none
	// post : 메모리 공간에 데이터를 더 넣을 수 있으면 false, 넣을 수 없다면 true 리턴
	bool IsFull();

	// func : 리스트가 비어있는지 확인한다.
	// pre : none
	// post : 리스트가 비어 있으면(head와 tail만 존재한다면) return true, 그렇지 않다면 return false
	bool IsEmpty();

	// func : 리스트를 비운다.
	// pre : none
	// post : 리스트에 존재하는 모든 데이터를 지운다.(head와 tail을 제외하고)
	void MakeEmpty();

	// func : 리스트의 길이를 리턴한다.
	// pre : none
	// post : 리스트의 길이가 리턴된다.
	int GetLength();
};

template <class DataType>
DoublyLinkedList<DataType>::DoublyLinkedList(void)
{
	m_head = new Node<DataType>;
	m_tail = new Node<DataType>;
	m_head->next = m_tail;
	m_head->prev = NULL;
	m_tail->prev = m_head;
	m_tail->next = NULL;
	m_length = 0;
}

template <class DataType>
DoublyLinkedList<DataType>::~DoublyLinkedList(void)
{
	MakeEmpty();
	delete m_head;
	delete m_tail;
}

template <class DataType>
bool DoublyLinkedList<DataType>::Add(DataType& data, int inx){
	// func : 입력받은 데이터를 inx에 따른 위치에 넣음
	// pre : head와 tail이 initialize
	// post : 입력받은 inx의 위치에 data를 넣는다.
	//		  input에 실패했을 경우(데이터를 더 넣을 수 없거나, 존재하지 않는 인덱스가 input되었을 경우) false, 성공했을 경우 true를 리턴한다.

	if(inx < 1 || inx > m_length+1){ // index가 0 이하의 위치이거나, 현재 리스트의 길이+1보다 클 때
		AfxMessageBox(_T("List에 잘못된 값이 입력되었습니다."));
		return false;
	}else if(inx == m_length+1){ // index가 현재 리스트의 길이+1과 같을 때(즉, 맨 뒤에 값이 삽입되어야 할 때)
		if(IsFull()){ // 리스트에 더는 값을 넣을 수 없을 때
			AfxMessageBox(_T("List가 꽉 찼습니다."));
			return false;
		}else{ // 리스트의 맨 뒤에 값을 삽입
			Node<DataType>* newNode = new Node<DataType>;
			newNode->data = data;

			newNode->next = m_tail;
			newNode->prev = m_tail->prev;
			m_tail->prev->next = newNode;
			m_tail->prev = newNode;

			m_length++;
			return true;
		}
	}else{ // index값에 따라 리스트에서 중간의 위치를 파악하여 저장하려고 할 떄
		Node<DataType>* location = m_head;

		for(int i=0; i<inx; i++){
			location = location->next;
		}

		Node<DataType>* newNode = new Node<DataType>;
		newNode->data = data;

		newNode->next = location;
		newNode->prev = location->prev;
		location->prev->next = newNode;
		location->prev = newNode;

		m_length++;
		return true;
	}
}

template <class DataType>
bool DoublyLinkedList<DataType>::Del(DataType& data){
	// func : 입력받은 데이터를 찾아 제거한다.
	// pre : head와 tail의 initialize
	// post : 입력받은 Data를 찾아 삭제한다. 성공하면 true, 실패하면 false를 리턴한다.
	Node<DataType>* location = m_head->next;
	int i;
	
	for(i=1; i<m_length; i++){
		if(location->data == data){
			break;
		}
		location = location->next;
	}

	if(i == m_length){ // for문이 전부 돌았다는 것은 리스트에 데이터가 존재하지 않는다는 뜻이므로 실패이다.
		AfxMessageBox(_T("해당 데이터가 존재하지 않습니다."));
		return false;
	}else{
		location->prev->next = location->next;
		location->next->prev = location->prev;

		delete location;
		m_length--;
		return true;
	}
}

template <class DataType>
bool DoublyLinkedList<DataType>::Get(DataType& data,int inx){
	// func : 입력받은 위치의 데이터를 data에 저장한다. 데이터가 존재하지 않을 시에는 false, 존재할 시에는 true를 리턴
	// pre : head와 tail이 initialize
	// post : 입력받은 위치의 데이터가 data에 저장된다. 데이터의 존재유무에 따라 true나 false가 리턴된다.
	Node<DataType>* location = m_head->next;
	int i;
	
	for(i=1; i<inx; i++){
		location = location->next;
	}

	if(i == m_length){ // for문이 리스트를 전부 돌았다는 것은 리스트에 데이터가 존재하지 않는다는 뜻이므로 실패이다.
		AfxMessageBox(_T("해당 데이터가 존재하지 않습니다."));
		return false;
	}else{
		data = location->data;
		return true;
	}
}

template <class DataType>
bool DoublyLinkedList<DataType>::IsFull(){
	// func : 메모리 공간이 데이터를 더 넣어도 되는건지 확인한다.
	// pre : none
	// post : 메모리 공간에 데이터를 더 넣을 수 있으면 false, 넣을 수 없다면 true 리턴
	Node<DataType>* temp;

	try{
		temp = new Node<DataType>;
	}catch(std::bad_alloc){ // 더 이상 추가할 수 없으면
		return true;
	}

	delete temp; // 추가되었을 경우 확인되었으므로 다시 제거

	return false;
}

template <class DataType>
bool DoublyLinkedList<DataType>::IsEmpty(){
	// func : 리스트가 비어있는지 확인한다.
	// pre : none
	// post : 리스트가 비어 있으면(head와 tail만 존재한다면) return true, 그렇지 않다면 return false
	if(m_head->next == m_tail) return true; // head가 tail을 가리킨다면 리스트는 비어 있는 것으로 간주한다.
	else return false;
}

template <class DataType>
void DoublyLinkedList<DataType>::MakeEmpty(){
	// func : 리스트를 비운다.
	// pre : none
	// post : 리스트에 존재하는 모든 데이터를 지운다.(head와 tail을 제외하고)
	DataType getdata;
	
	for(int i=1; i<m_length; i++){
		Get(getdata, 1);
		Del(getdata);
	}
}

template <class DataType>
int DoublyLinkedList<DataType>::GetLength(){
	// func : 리스트의 길이를 리턴한다.
	return m_length;
}
