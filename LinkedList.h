#ifndef LINKED_LIST
#define LINKED_LIST
#include"List.h"
#include"Node.h"
#include<iostream>

using namespace std;
template <typename T>
class LinkedList:public List<T>{
	public:
		//�û���ֱ����Node����, NodeӦ�ñ���������, �û�ֻ��LinkedList����, �������
		LinkedList();//����ֻ��ͷ���Ŀ����� 
		LinkedList(T dataArray[], int number);//T����Ӧ����Node<T> , ��������봫������, ��Ϊ�Ҳ�֪�� 
		~LinkedList();
		virtual int getLength();
        virtual int locate(T data);
        virtual T get(int index);
        virtual void add(T data);
        virtual T deleteByIndex(int index);
        virtual bool isEmpty();
        virtual void printList();
        virtual Node<T>* getFirst(); 
    private:
    	Node<T> *first = nullptr;
    	Node<T> *tail = nullptr;
};

//�޲ι��캯��,����ֻ��һ��ͷ�ڵ��LinkedList,��ͷ���nextָ��nullptr, �����ָ
template <class T>
LinkedList<T>::LinkedList() {
	first = new Node<T>();
	first->setNext(nullptr);
	tail = first;
	//nullptr�ؼ������ڱ�ʶ��ָ�룬��std::nullptr_t���͵ģ�constexpr��������
	//������ת�����κ�ָ�����ͺ�bool�������ͣ���Ҫ��Ϊ�˼�����ָͨ�������Ϊ�����ж�����д���������ǲ��ܱ�ת��Ϊ������
	//����java��null 
}

//���в������캯��
template <class T>
LinkedList<T>::LinkedList(T data[], int number) {
	/*first = new Node<T>();
	Node<T>* pTemp = first;
	for(int i=0; i<number; i++) {
		Node<T>* node = new Node<T>(data[i], nullptr);
		pTemp->setNext(node);
		pTemp = node;
	}*/
	//ͷ�巨
	Node<T> *tail = new Node<T>();
	for(int i=0; i<number; i++) {
		first->setNext(new Node<T>(data[i], first->getNext()));
	}
}

//��������
template <class T>
LinkedList<T>::~LinkedList() {

}

//length
template <class T>
int LinkedList<T>::getLength() {
	Node<T>* p = first;
	int court = 0;
	while(p->getNext() != nullptr) {
		court++;
		p = p->getNext();
	}
	return court;
}

//locate
template <class T>
int LinkedList<T>::locate(T data) {
	Node<T>* p = first;
	int index = 0;
	while(p->getNext() != nullptr) {
		if(p->getNext()->getData() == data) {
			return index+1;
		}
		index++;
		p = p->getNext();
	}
	throw "function named \"locate\" : the data is not founded";
}

//get
template <class T>
T LinkedList<T>::get(int index) {
	Node<T>* p = first;
	int position = 0;//��ʾ��ǰ������
	while(p->getNext() != nullptr) {//�ж��Ƿ������һ�����
		position++;//������ ��ż�һ
		p = p->getNext(); //��ָ����Ӧ�ĺ���һλ
		if(position == index) {//�����ǰλ��position��index��ͬ,�򷵻�����
			return p->getData();
		}
	}
	throw "function named \"get\": invalid index";
}

//insert
//��ע������һ�ڵ�, �����ǵ�ǰ���, ����, ��һ�����ĵ�ַ�Ͷ�ʧ��
template <class T>
void LinkedList<T>::add(T data) {
	//Node<T>* p = first;//ָ��ָ��ͷ���
	//int position = 0;//��ʾ��ǰ����Ӧ���
	/*	while(p->getNext() != nullptr) {//�ж��Ƿ������һ�����
			position++;//������ ��ż�һ, ��ʾ��һ�ڵ��λ��
			if(position == index) {//�ж���һ�ڵ�λ���Ƿ���Ҫ�����λ��index
			//�������
				//new�½ڵ�, ����data��nextָ��p����һ�����,����ǰ������һ�����
				Node<T>* node = new Node<T>(data, p->getNext());
				//��ǰ���p��nextָ���½ڵ�
				p->setNext(node);
				//���Ƿ�����...
				return;
			}
			//�����ƶ�һλ
			p = p->getNext();
		}
		//��ʱpositionָ��β���, +1˵��Ҫ����Ҫβ������
		if(index == position+1) {
			p->setNext(new Node<T>(data, nullptr));
		}
		throw "function named \"insert\": invalid index, too biger";*/
	
	//new�½ڵ�, ����data��nextָ��p����һ�����,����ǰ������һ�����
	Node<T>* node = new Node<T>(data, nullptr);
	//��ǰ���p��nextָ���½ڵ�
	tail->setNext(node);
	tail = node;
	//���Ƿ�����...
	return;
}

//delete
//��ע������һ�ڵ� , �����ǵ�ǰ���, ����, ��һ�����ĵ�ַ�Ͷ�ʧ��
template <class T>
T LinkedList<T>::deleteByIndex(int index) {
	if(index==0) {
		throw "function named \"deleteByIndex\": invalid index, too smaller";
	}
	Node<T>* p = first;//ָ��ָ��ͷ���
	int position = 0;//��ʾ��ǰ����Ӧ���
	/*while(p->getNext() != nullptr) {//�ж��Ƿ������һ�����
		position++;//������ ��ż�һ, ��ʾ��һ�ڵ��λ��
		if(position == index) {//�ж���һ�ڵ�λ���Ƿ���Ҫɾ����λ��index
			//����ɾ��
			//��ǰ����nextֱ��ָ����һ�ڵ�p->getNext()��next
			T data = p->getNext()->getData();
			p->setNext(p->getNext()->getNext());
			return data;
		}
		//�����ƶ�һλ
		p = p->getNext();
	}
	throw "function named \"deleteByIndex\": invalid index, too biger";*/
	while(position < index-1) {
		if(p->getNext() == nullptr) {
			throw "function named \"insert\": invalid index, too biger";
		}
		p = p->getNext();
		position++;
	}
	T data = p->getNext()->getData();
	p->setNext(p->getNext()->getNext());
	return data;
}

//isEmpty
template <class T>
bool LinkedList<T>::isEmpty() {
	//ͷ����next�Ƿ�Ϊnull
	return first->getNext() == nullptr;
}

//printList
template <class T>
void LinkedList<T>::printList() {
	Node<T>* p = first;
	while(p->getNext() != nullptr) {
		//cout<<p->getNext()->getData()<<"\t";
		p = p->getNext();
	}
	cout<<endl;
}

//getFirst
template <class T>
Node<T>* LinkedList<T>::getFirst() {
	return first;
}
#endif
