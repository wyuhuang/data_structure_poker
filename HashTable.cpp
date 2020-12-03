#include"HashTable.h"

#include<iostream>
using namespace std;

HashTable::HashTable()
{
	for (int i = 0; i < MaxSize; i++)
	{
		ht[i] = nullptr;
	}
}


HashTable :: ~HashTable( )
{
	HashNode *p = nullptr, *q = nullptr;
	for (int i = 0; i < MaxSize; i++)
	{
		p = q = ht[i];
		while (p != nullptr)
		{
			p = p->next;
			delete q;
			q = p;
		}
	}
}


int HashTable :: H(int k)
{

	return k % 22;
}


string HashTable :: SearchName(int k)
{
	int j = H(k); //计算散列地址
	string name = " ";
	HashNode *p = ht[j]; //工作指针p初始化
	if(p != nullptr){
		while (p != nullptr)
		{
//			cout<<p->data<<endl;
			name += p->data;
			if(p->next != nullptr){
				name += " & " ;
			}
			p = p->next;
		}
		return name; 
	}
	else{
		return "无名字";
	}
}


void HashTable :: Insert(int k,string name)
{
	int j = H(k); //计算散列地址
//	cout<<j<<endl;
	HashNode *p = ht[j]; //工作指针p初始化
	p = new HashNode;
	p->data = name;
//	cout<<p->data<<endl;
	p->next = ht[j];
	ht[j] = p;

}

