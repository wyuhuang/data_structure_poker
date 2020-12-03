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

	//cout<<"number is "<<number<<endl;
	//cout<<"swapPosition is "<<swapPosition<<endl;
	//打印
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
		//要移动的牌转移到temp临时表
		for(int i=0; i<number; i++) {
			temp[i] = pokers[swapPosition + i];//43
		}
		//牌堆顶的牌下移
		for(int i=swapPosition + number; i<52; i++) {
			pokers[i - number] = pokers[i]; //43 43+8
		}
		//临时表的扑克移到牌堆顶
		for(int i=0; i<number; i++) {
			pokers[52 - number + i] = temp[i];//43 + 8
		}
	}

	//打印
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

LinkedList<Player> ServerContext::getPlayerList() {
	return this->playerList;
}

string** ServerContext::settlementScore(){
	Node<Player> *p = playerList.getFirst()->getNext();
	Node<Player> *q;		//工作指针 
	q = p;					//初始化工作指针 
	HashTable HT;
	int PlayerLength = playerList.getLength();//获取玩家个数 
	string *(*RankingList) = new string*[PlayerLength];//返回的字符串数组 
	int sum[PlayerLength]; 
	int max = 22,min = 0,j=0,i=0,PNTotal; 
	string name;
	//初始化数组 
	for(i = 0; i<PlayerLength;i++){
		sum[i] = 0;
		RankingList[i] = new string[2];
		for(j= 0;j < 2;j++ ){
			RankingList[i][j] = " ";
		}
	}
	
	//测试 
	//cout<<PlayerLength;
	//cout<<q->getData().getPointNumberTotal();
	
	//将分值和名字装入哈希表中 
	while(q != nullptr){
		PNTotal = q->getData().getPointNumberTotal();
		name = q->getData().getName();
//		cout<<name<<endl;
//		cout<<PNTotal<<endl;
		if(PNTotal > 21){
			HT.Insert(22,name);
			
			//测试 
//			cout<<"超21插入HASH"<<endl;
		}
		else{
			HT.Insert(PNTotal,name);
			//测试 
//			cout<<"少于21插入成功"<<endl;
//			HT.SearchName(p->getData().getPointNumberTotal());
		}
		q = q->getNext();
	}
	
	//将分值排序
	for( i = 0;i < PlayerLength;i++){
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
	
	
	//测试：
//	for(i = 0;i < PlayerLength;i++){
//		cout<<sum[i]<<endl; 
//	}
	
	
	 
	//利用sum来写入字符串数组 
	j = 0;
	while(sum[j] != 0 && j < PlayerLength) {
		RankingList[j][0] = to_string(sum[j]);
		RankingList[j][1] = HT.SearchName(sum[j]);
		j++;
		
		//测试
//		cout<<RankingList[j][0]<<endl;
//		cout<<RankingList[j][1];
	}
	return RankingList;
}


