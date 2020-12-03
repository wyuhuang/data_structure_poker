#ifndef LINKED_LIST
#define LINKED_LIST
#include"List.h"
#include"Node.h"
#include<iostream>

using namespace std;
template <typename T>
class LinkedList:public List<T>{
	public:
		//用户不直接与Node交互, Node应该被隐藏起来, 用户只跟LinkedList交互, 类似外观
		LinkedList();//建立只有头结点的空链表 
		LinkedList(T dataArray[], int number);//T而不应该是Node<T> , 传数组必须传来长度, 因为我不知道 
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

//无参构造函数,构造只有一个头节点的LinkedList,且头结点next指向nullptr, 免得乱指
template <class T>
LinkedList<T>::LinkedList() {
	first = new Node<T>();
	first->setNext(nullptr);
	tail = first;
	//nullptr关键字用于标识空指针，是std::nullptr_t类型的（constexpr）变量。
	//它可以转换成任何指针类型和bool布尔类型（主要是为了兼容普通指针可以作为条件判断语句的写法），但是不能被转换为整数。
	//很想java的null 
}

//所有参数构造函数
template <class T>
LinkedList<T>::LinkedList(T data[], int number) {
	/*first = new Node<T>();
	Node<T>* pTemp = first;
	for(int i=0; i<number; i++) {
		Node<T>* node = new Node<T>(data[i], nullptr);
		pTemp->setNext(node);
		pTemp = node;
	}*/
	//头插法
	Node<T> *tail = new Node<T>();
	for(int i=0; i<number; i++) {
		first->setNext(new Node<T>(data[i], first->getNext()));
	}
}

//析构函数
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
	int position = 0;//表示当前结点序号
	while(p->getNext() != nullptr) {//判断是否存在下一个结点
		position++;//存在则 序号加一
		p = p->getNext(); //且指针相应的后移一位
		if(position == index) {//如果当前位置position与index相同,则返回数据
			return p->getData();
		}
	}
	throw "function named \"get\": invalid index";
}

//insert
//关注的是下一节点, 而不是当前结点, 否则, 上一个结点的地址就丢失了
template <class T>
void LinkedList<T>::add(T data) {
	//Node<T>* p = first;//指针指向头结点
	//int position = 0;//表示当前结点对应序号
	/*	while(p->getNext() != nullptr) {//判断是否存在下一个结点
			position++;//存在则 序号加一, 表示下一节点的位置
			if(position == index) {//判断下一节点位置是否是要插入的位置index
			//是则插入
				//new新节点, 放入data且next指向p的下一个结点,即当前结点的下一个结点
				Node<T>* node = new Node<T>(data, p->getNext());
				//当前结点p的next指向新节点
				p->setNext(node);
				//忘记返回了...
				return;
			}
			//否则移动一位
			p = p->getNext();
		}
		//此时position指向尾结点, +1说明要插入要尾结点后面
		if(index == position+1) {
			p->setNext(new Node<T>(data, nullptr));
		}
		throw "function named \"insert\": invalid index, too biger";*/
	
	//new新节点, 放入data且next指向p的下一个结点,即当前结点的下一个结点
	Node<T>* node = new Node<T>(data, nullptr);
	//当前结点p的next指向新节点
	tail->setNext(node);
	tail = node;
	//忘记返回了...
	return;
}

//delete
//关注的是下一节点 , 而不是当前结点, 否则, 上一个结点的地址就丢失了
template <class T>
T LinkedList<T>::deleteByIndex(int index) {
	if(index==0) {
		throw "function named \"deleteByIndex\": invalid index, too smaller";
	}
	Node<T>* p = first;//指针指向头结点
	int position = 0;//表示当前结点对应序号
	/*while(p->getNext() != nullptr) {//判断是否存在下一个结点
		position++;//存在则 序号加一, 表示下一节点的位置
		if(position == index) {//判断下一节点位置是否是要删除的位置index
			//是则删除
			//当前结点的next直接指向下一节点p->getNext()的next
			T data = p->getNext()->getData();
			p->setNext(p->getNext()->getNext());
			return data;
		}
		//否则移动一位
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
	//头结点的next是否为null
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
