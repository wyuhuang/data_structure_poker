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
