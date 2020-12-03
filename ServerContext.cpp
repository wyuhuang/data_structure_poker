#include"ServerContext.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

//约定A:方块 B:梅花 C：红桃 D：黑桃 
ServerContext::ServerContext() {
	//1. 初始化牌堆
	char flowerColers[] = {'A', 'B', 'C', 'D'};
	for(int i=0; i<52; i++) {
		pokers[i].setPointNumber(i % 13 + 1);
		pokers[i].setFlowerColor(flowerColers[i / 13]);
		//pokers[i].print();
	}
	shufflePokers();
}

void ServerContext::shufflePokers() {
	unsigned seed = time(0);
	 srand(seed);
	 int number = rand() % 32 + 8; //8-39
	 int swapPosition = rand() % (52 - number) + 1;//1-44
	 
	 
}
ServerContext::~ServerContext() {

}

int ServerContext::settlementScore(){
	Node<Player> *p = playerList.getFirst();
	Node<Player> *q;		//工作指针 
	q = p;					//初始化工作指针 
	HashTable HT;
	int PlayerLength = playerList.getLength();//获取玩家个数 
	string RankingList[PlayerLength][2];//返回的字符串数组 
	int sum[PlayerLength] ={0}; 
	int max = 22,min = 0,j=0; 
	//将分值和名字装入哈希表中 
	while(q->getNext() != nullptr){
		if(q->getData().getPointNumberTotal() > 21){
			HT.Insert(22,p->getData().getName());
		}
		else{
			HT.Insert(p->getData().getPointNumberTotal(),p->getData().getName());
		}
		q = q->getNext();
	}
	//将分值排序
	for(int i = 0;i < PlayerLength;i++){
		q = p;
		while(q->getNext() != nullptr){
			if(q->getData().getPointNumberTotal() < max && q->getData().getPointNumberTotal() > min){
				min = q->getData().getPointNumberTotal();
			}
			q = q->getNext();
		}
		max = min;
		//当max为0时证明21以下的分值已经排好序 
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
	//利用sum来写入字符串数组 
	while(sum[j] != 0 && j < PlayerLength) {
		RankingList[j][0] = to_string(sum[j]);
		RankingList[j][1] = HT.SearchName(sum[j]);
		j++;
	}
}


