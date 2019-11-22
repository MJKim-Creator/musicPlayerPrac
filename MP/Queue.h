#pragma once
#include "DoublyLinkedList.h"
template <class DataType>
class CQueue
{
private:
	DoublyLinkedList<DataType> m_list;
	int m_location;
public:
	CQueue(void); // �⺻ ������
	~CQueue(void); // �⺻ �Ҹ���

	// func : queue�� data�� ����
	// pre : none
	// post : queue�� data�� ��. �����ϸ� true, �׷��� ������ false ����
	bool Enqueue(DataType& data);

	// func : queue���� �� ù��°�� ���� �����͸� ����
	// pre : �����Ͱ� ����
	// post : queue���� �� ù��°�� ���� �����Ͱ� ���ŵ�. �����ϸ� true, �����ϸ�(queue�� �����Ͱ� ���� ���, �׿� ��Ÿ) false return
	bool Dequeue();

	// func : queue�� ���
	// pre : none
	// post : queue�� ��� ������ ����
	void MakeEmpty();

	// func : queue�� �� ���� �� �� �ִ��� Ȯ��
	// pre : none
	// post : queue�� �� á�ٸ� true, �׷��� �ʴٸ� false ����
	bool IsFull();

	// func : queue�� ��� �ִ��� Ȯ��
	// pre : none
	// post : queue�� ��� �ִٸ� true, �׷��� �ʴٸ� false ����
	bool IsEmpty();

	// func : queue�� ����ִ� �������� ������ ����
	int GetLength();

	// func : queue�� �� ó���� ���� �����͸� ����
	DataType GetData();

	// queue���� Ư�� �����͸� ����Ű�� ������ location�� ��ġ�� �ʱ�ȭ��Ű�� �Լ�
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
	// func : queue�� data�� ����
	// pre : none
	// post : queue�� data�� ��. �����ϸ� true, �׷��� ������ false ����
	m_list.Add(data, m_list.GetLength()+1);

	return true;
}

template <class DataType>
bool CQueue<DataType>::Dequeue(){
	// func : queue���� �� ù��°�� ���� �����͸� ����
	// pre : �����Ͱ� ����
	// post : queue���� �� ù��°�� ���� �����Ͱ� ���ŵ�. �����ϸ� true, �����ϸ�(queue�� �����Ͱ� ���� ���, �׿� ��Ÿ) false return
	DataType deldata;
	m_list.Get(deldata, 1);
	m_list.Del(deldata);

	return true;
}

template <class DataType>
void CQueue<DataType>::MakeEmpty(){
	// func : queue�� ���
	// pre : none
	// post : queue�� ��� ������ ����
	m_list.MakeEmpty();
}

template <class DataType>
bool CQueue<DataType>::IsFull(){
	// func : queue�� �� ���� �� �� �ִ��� Ȯ��
	// pre : none
	// post : queue�� �� á�ٸ� true, �׷��� �ʴٸ� false ����
	return m_list.IsFull();
}

template <class DataType>
bool CQueue<DataType>::IsEmpty(){
	// func : queue�� ��� �ִ��� Ȯ��
	// pre : none
	// post : queue�� ��� �ִٸ� true, �׷��� �ʴٸ� false ����
	return m_list.IsEmpty();
}

template <class DataType>
int CQueue<DataType>::GetLength(){
	// func : queue�� ����ִ� �������� ������ ����
	return m_list.GetLength();
}

template <class DataType>
DataType CQueue<DataType>::GetData(){
	// func : queue���� location�� ��ġ�� �ִ� �����͸� ����
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
