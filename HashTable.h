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
		HashTable( ); //���캯������ʼ����ɢ�б�
		~HashTable( ); //�����������ͷ�ͬ����ӱ���
		void Insert(int k,string name); //����
		int Delete(int k); //ɾ��
		string SearchName(int k); //�������� 
		HashNode * Search(int k); //����λ�� 
	private:
		int H(int k); //ɢ�к���
		HashNode * ht[MaxSize]; //��ɢ�б�
};



#endif
