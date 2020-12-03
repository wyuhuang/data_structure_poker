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

int ServerContext::getPokersTop() {
	return pokersTop;
}

void ServerContext::setPokersTop(int pokersTop) {
	this->pokersTop = pokersTop;
}
LinkedList<Player> ServerContext::getPlayerList() {
	return this->playerList;
}
