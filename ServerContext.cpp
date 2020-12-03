#include"ServerContext.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

//Լ��A:���� B:÷�� C������ D������ 
ServerContext::ServerContext() {
	//1. ��ʼ���ƶ�
	char flowerColers[] = {'A', 'B', 'C', 'D'};
	for(int i=0; i<52; i++) {
		pokers[i].setPointNumber(i % 13 + 1);
		pokers[i].setFlowerColor(flowerColers[i / 13]);
		//pokers[i].print();
	}
	shufflePokers();
}

void ServerContext::shufflePokers() {

	//cout<<"number is "<<number<<endl;
	//cout<<"swapPosition is "<<swapPosition<<endl;
	//��ӡ
	//for(int i=0; i<52; i++) {
		//pokers[i].print();
	//}
	//cout<<endl;
	unsigned seed = time(0);
	srand(seed);
	for(int i=0; i<100; i++) {
		int number = rand() % 32 + 8; //8-39
		int swapPosition = rand() % (52 - number - 1) + 1;//1-43
		//	cout<<"number is "<<number<<endl;
		//cout<<"swapPosition is "<<swapPosition<<endl;
		Poker temp[number];
		//Ҫ�ƶ�����ת�Ƶ�temp��ʱ��
		for(int i=0; i<number; i++) {
			temp[i] = pokers[swapPosition + i];//43
		}
		//�ƶѶ���������
		for(int i=swapPosition + number; i<52; i++) {
			pokers[i - number] = pokers[i]; //43 43+8
		}
		//��ʱ����˿��Ƶ��ƶѶ�
		for(int i=0; i<number; i++) {
			pokers[52 - number + i] = temp[i];//43 + 8
		}
	}

	//��ӡ
	//for(int i=0; i<52; i++) {
		//pokers[i].print();
//	}

}
ServerContext::~ServerContext() {

}

Poker* ServerContext::getPokers() {
	return pokers;
}

Poker ServerContext::dealOnePoker() {
	return pokers[pokersTop--];
}

int ServerContext::getPokersTop() {
	return pokersTop;
}

void ServerContext::setPokersTop(int pokersTop) {
	this->pokersTop = pokersTop;
}
LinkedList<Player> ServerContext::getPlayerList() {
	return this->playerList;
}

string** ServerContext::settlementScore(){
	Node<Player> *p = playerList.getFirst()->getNext();
	Node<Player> *q;		//����ָ�� 
	q = p;					//��ʼ������ָ�� 
	HashTable HT;
	int PlayerLength = playerList.getLength();//��ȡ��Ҹ��� 
	string *(*RankingList) = new string*[PlayerLength];//���ص��ַ������� 
	int sum[PlayerLength]; 
	int max = 22,min = 0,j=0,i=0,PNTotal; 
	string name;
	//��ʼ������ 
	for(i = 0; i<PlayerLength;i++){
		sum[i] = 0;
		RankingList[i] = new string[2];
		for(j= 0;j < 2;j++ ){
			RankingList[i][j] = " ";
		}
	}
	
	//���� 
	//cout<<PlayerLength;
	//cout<<q->getData().getPointNumberTotal();
	
	//����ֵ������װ���ϣ���� 
	while(q != nullptr){
		PNTotal = q->getData().getPointNumberTotal();
		name = q->getData().getName();
//		cout<<name<<endl;
//		cout<<PNTotal<<endl;
		if(PNTotal > 21){
			HT.Insert(22,name);
			
			//���� 
//			cout<<"��21����HASH"<<endl;
		}
		else{
			HT.Insert(PNTotal,name);
			//���� 
//			cout<<"����21����ɹ�"<<endl;
//			HT.SearchName(p->getData().getPointNumberTotal());
		}
		q = q->getNext();
	}
	
	//����ֵ����
	for( i = 0;i < PlayerLength;i++){
		q = p;
		while(q->getNext() != nullptr){
			if(q->getData().getPointNumberTotal() < max && q->getData().getPointNumberTotal() > min){
				min = q->getData().getPointNumberTotal();
			}
			q = q->getNext();
		}
		max = min;
		//��maxΪ0ʱ֤��21���µķ�ֵ�Ѿ��ź��� 
		if(max == 0){
			q = p;
			while(q->getNext() != nullptr){
				if(q->getData().getPointNumberTotal() > 21){
					sum[i] = 22;
					break;
				}
				q = q->getNext();
			}
			break;
		}
		sum[i] = min;
		min = 0;
	} 
	
	
	//���ԣ�
//	for(i = 0;i < PlayerLength;i++){
//		cout<<sum[i]<<endl; 
//	}
	
	
	 
	//����sum��д���ַ������� 
	j = 0;
	while(sum[j] != 0 && j < PlayerLength) {
		RankingList[j][0] = to_string(sum[j]);
		RankingList[j][1] = HT.SearchName(sum[j]);
		j++;
		
		//����
//		cout<<RankingList[j][0]<<endl;
//		cout<<RankingList[j][1];
	}
	return RankingList;
}


