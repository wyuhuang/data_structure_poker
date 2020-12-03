#include"SeqList.h"
#include<iostream>
#include<stack>
using namespace std;


//无参构造函数
template <class T>
SeqList<T>::SeqList() {
	this->length = 0;
}

//所有参数构造函数
template <class T>
SeqList<T>::SeqList(T data[], int len) {
	if(len > MAX_SIZE) {
		throw "length is longer than MAX_SIZE";
	}
	//this->data = data;//不能是简单的传地址, 要自己开辟内存, 实现封装
	for(int i=0; i<len; i++) {
		this->data[i] = data[i];
	}
	length = len;

}

//析构函数
template <class T>
SeqList<T>::~SeqList() {

}

//length
template <class T>
int SeqList<T>::getLength() {
	return length;
}

//locate
template <class T>
int SeqList<T>::locate(T data) {
	for(int i=0; i<length; i++) {
		if(this->data[i] == data)
			return i+1;
	}
	return 0;
}

//get
template <class T>
T SeqList<T>::get(int index) {
	if(index >0 && index <= length) {
		return data[index-1];
	}
	throw "function named \"get\": invalid index";
}

//insert
template <class T>
void SeqList<T>::insert(T data, int index) {
	if(length == MAX_SIZE) {
		throw "seqList`s length is equal MAX_SIZE";
	}
	if(index <=0 || index > length+1) {
		throw "function named \"insert\": invalid index";
	}
	//从后面开始, 逐个元素 后退一位直到index
	for(int i=length; i >= index; i--) {
		this->data[i] = this->data[i-1];
	}
	this->data[index-1] = data;
	//length同步+1
	length++;
}

//delete
template <class T>
T SeqList<T>::deleteByIndex(int index) {
	if(index < 1 || index > length) {
		throw "function named \"ideleteByIndex\": nvalid index";
	}
	//删除前先保存
	T data = this->data[index-1];
	//删除然后每个元素向前移动一个位置
	for(int i=index-1; i < length-1; i++) {
		this->data[i] = this->data[i+1];
	}
	//length同步-1
	length--;
	return data;
}

//isEmpty
template <class T>
bool SeqList<T>::isEmpty() {
	return length == 0;
}

//printList
template <class T>
void SeqList<T>::printList() {
	for(int i=0; i<length; i++) {
		cout<<data[i]<<"\t";
	}
	cout<<endl;
}

template <class T>
void SeqList<T>::quickSwapList() {
	int i = 0;
	int j = length - 1;
	stack<int> zeroI;//记录I移动过程遇到的0
	stack<int> zeroJ;//记录j扫描到的0
	while(i < j) {
		while(data[i] <= 0 && i != j) {
			if(data[i] == 0) zeroI.push(i);
			i++;
		}
		while(data[j] >= 0 && i != j) {
			if(data[j] == 0) zeroJ.push(j);
			j--;
		}
		data[j] ^= data[i] ^= data[j] ^= data[i];
	}
	//当i == j时，i，j回溯，遇到非0的都交换
	if(data[i] >0) {
		j++;
	} else if(data[i] < 0) {
		i--;
	} else {
		i--;
		j++;
	}
	while(!zeroI.empty()) {
		if(data[i] != 0) {
			data[i] ^= data[zeroI.top()] ^= data[i] ^= data[zeroI.top()];
		}
		i--;
		zeroI.pop();
	}
	while(!zeroJ.empty()) {
		if(data[j] != 0) {
			data[j] ^= data[zeroJ.top()] ^= data[j] ^= data[zeroJ.top()];
		}
		j++;
		zeroJ.pop();
	}
}

void merge(SeqList<int> list1, SeqList<int> list2) {
	
}
/*int main() {
	int data[] = {30,20,19,18,17,4,3,2,1};
	SeqList<int> seqList1(data, 9);
	SeqList<int> seqList2(data, 9);
	merge(seqList1, seqList2); 
	/*list->insert(11, 1);
	list->printList();
	int deletedData = list->deleteByIndex(1);
	//		list->deleteByIndex(1);
	//		list->deleteByIndex(1);
	//		list->deleteByIndex(1);
	//		list->deleteByIndex(1);
	//		list->deleteByIndex(1);
	list->printList();
	cout<<"the data deleted: "<<deletedData<<endl;
	cout<<"list is empty?"<<list->isEmpty()<<endl;
	list->printList();
	int getedData = list->get(3);
	cout<<"get the data which index is "<<list->locate(getedData)<<" :"<<getedData<<endl;
	cout<<"length is "<<list->getLength()<<endl;
	} catch (const char* e) {
	cout<<endl<<e;
	}
	return 0;
}*/
