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
	int m_length; // �ش� ����Ʈ�� ����
public:
	 // �⺻ ������. Head�� Tail�� �ʱ�ȭ��
	DoublyLinkedList(void);
	 // �⺻ �Ҹ���. ����Ʈ�� ��� �����͸� ����� �Ҹ�
	virtual ~DoublyLinkedList(void);

	// func : �Է¹��� �����͸� inx�� ���� ��ġ�� ����
	// pre : head�� tail�� initialize
	// post : �Է¹��� inx�� ��ġ�� data�� �ִ´�.
	//		  input�� �������� ���(�����͸� �� ���� �� ���ų�, �������� �ʴ� �ε����� input�Ǿ��� ���) false, �������� ��� true�� �����Ѵ�.
	bool Add(DataType& data, int inx);

	// func : �Է¹��� �����͸� ã�� �����Ѵ�.
	// pre : head�� tail�� initialize
	// post : �Է¹��� Data�� ã�� �����Ѵ�.
	bool Del(DataType& data);

	// func : �Է¹��� ��ġ�� �����͸� data�� �����Ѵ�. �����Ͱ� �������� ���� �ÿ��� false, ������ �ÿ��� true�� ����
	// pre : head�� tail�� initialize
	// post : �Է¹��� ��ġ�� �����Ͱ� data�� ����ȴ�. �������� ���������� ���� true�� false�� ���ϵȴ�.
	bool Get(DataType& data, int inx);

	// func : �޸� ������ �����͸� �� �־ �Ǵ°��� Ȯ���Ѵ�.
	// pre : none
	// post : �޸� ������ �����͸� �� ���� �� ������ false, ���� �� ���ٸ� true ����
	bool IsFull();

	// func : ����Ʈ�� ����ִ��� Ȯ���Ѵ�.
	// pre : none
	// post : ����Ʈ�� ��� ������(head�� tail�� �����Ѵٸ�) return true, �׷��� �ʴٸ� return false
	bool IsEmpty();

	// func : ����Ʈ�� ����.
	// pre : none
	// post : ����Ʈ�� �����ϴ� ��� �����͸� �����.(head�� tail�� �����ϰ�)
	void MakeEmpty();

	// func : ����Ʈ�� ���̸� �����Ѵ�.
	// pre : none
	// post : ����Ʈ�� ���̰� ���ϵȴ�.
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
	// func : �Է¹��� �����͸� inx�� ���� ��ġ�� ����
	// pre : head�� tail�� initialize
	// post : �Է¹��� inx�� ��ġ�� data�� �ִ´�.
	//		  input�� �������� ���(�����͸� �� ���� �� ���ų�, �������� �ʴ� �ε����� input�Ǿ��� ���) false, �������� ��� true�� �����Ѵ�.

	if(inx < 1 || inx > m_length+1){ // index�� 0 ������ ��ġ�̰ų�, ���� ����Ʈ�� ����+1���� Ŭ ��
		AfxMessageBox(_T("List�� �߸��� ���� �ԷµǾ����ϴ�."));
		return false;
	}else if(inx == m_length+1){ // index�� ���� ����Ʈ�� ����+1�� ���� ��(��, �� �ڿ� ���� ���ԵǾ�� �� ��)
		if(IsFull()){ // ����Ʈ�� ���� ���� ���� �� ���� ��
			AfxMessageBox(_T("List�� �� á���ϴ�."));
			return false;
		}else{ // ����Ʈ�� �� �ڿ� ���� ����
			Node<DataType>* newNode = new Node<DataType>;
			newNode->data = data;

			newNode->next = m_tail;
			newNode->prev = m_tail->prev;
			m_tail->prev->next = newNode;
			m_tail->prev = newNode;

			m_length++;
			return true;
		}
	}else{ // index���� ���� ����Ʈ���� �߰��� ��ġ�� �ľ��Ͽ� �����Ϸ��� �� ��
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
	// func : �Է¹��� �����͸� ã�� �����Ѵ�.
	// pre : head�� tail�� initialize
	// post : �Է¹��� Data�� ã�� �����Ѵ�. �����ϸ� true, �����ϸ� false�� �����Ѵ�.
	Node<DataType>* location = m_head->next;
	int i;
	
	for(i=1; i<m_length; i++){
		if(location->data == data){
			break;
		}
		location = location->next;
	}

	if(i == m_length){ // for���� ���� ���Ҵٴ� ���� ����Ʈ�� �����Ͱ� �������� �ʴ´ٴ� ���̹Ƿ� �����̴�.
		AfxMessageBox(_T("�ش� �����Ͱ� �������� �ʽ��ϴ�."));
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
	// func : �Է¹��� ��ġ�� �����͸� data�� �����Ѵ�. �����Ͱ� �������� ���� �ÿ��� false, ������ �ÿ��� true�� ����
	// pre : head�� tail�� initialize
	// post : �Է¹��� ��ġ�� �����Ͱ� data�� ����ȴ�. �������� ���������� ���� true�� false�� ���ϵȴ�.
	Node<DataType>* location = m_head->next;
	int i;
	
	for(i=1; i<inx; i++){
		location = location->next;
	}

	if(i == m_length){ // for���� ����Ʈ�� ���� ���Ҵٴ� ���� ����Ʈ�� �����Ͱ� �������� �ʴ´ٴ� ���̹Ƿ� �����̴�.
		AfxMessageBox(_T("�ش� �����Ͱ� �������� �ʽ��ϴ�."));
		return false;
	}else{
		data = location->data;
		return true;
	}
}

template <class DataType>
bool DoublyLinkedList<DataType>::IsFull(){
	// func : �޸� ������ �����͸� �� �־ �Ǵ°��� Ȯ���Ѵ�.
	// pre : none
	// post : �޸� ������ �����͸� �� ���� �� ������ false, ���� �� ���ٸ� true ����
	Node<DataType>* temp;

	try{
		temp = new Node<DataType>;
	}catch(std::bad_alloc){ // �� �̻� �߰��� �� ������
		return true;
	}

	delete temp; // �߰��Ǿ��� ��� Ȯ�εǾ����Ƿ� �ٽ� ����

	return false;
}

template <class DataType>
bool DoublyLinkedList<DataType>::IsEmpty(){
	// func : ����Ʈ�� ����ִ��� Ȯ���Ѵ�.
	// pre : none
	// post : ����Ʈ�� ��� ������(head�� tail�� �����Ѵٸ�) return true, �׷��� �ʴٸ� return false
	if(m_head->next == m_tail) return true; // head�� tail�� ����Ų�ٸ� ����Ʈ�� ��� �ִ� ������ �����Ѵ�.
	else return false;
}

template <class DataType>
void DoublyLinkedList<DataType>::MakeEmpty(){
	// func : ����Ʈ�� ����.
	// pre : none
	// post : ����Ʈ�� �����ϴ� ��� �����͸� �����.(head�� tail�� �����ϰ�)
	DataType getdata;
	
	for(int i=1; i<m_length; i++){
		Get(getdata, 1);
		Del(getdata);
	}
}

template <class DataType>
int DoublyLinkedList<DataType>::GetLength(){
	// func : ����Ʈ�� ���̸� �����Ѵ�.
	return m_length;
}
