#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include <string>
using namespace std;


struct HashNode
{
	string data;
	HashNode *next;
};	

const int MaxSize = 22;

class HashTable
{
	public:
		HashTable( ); //构造函数，初始化开散列表
		~HashTable( ); //析构函数，释放同义词子表结点
		void Insert(int k,string name); //插入
		int Delete(int k); //删除
		string SearchName(int k); //查找名字 
		HashNode * Search(int k); //查找位置 
	private:
		int H(int k); //散列函数
		HashNode * ht[MaxSize]; //开散列表
};



#endif
