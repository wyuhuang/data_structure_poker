#include "Player.h"

#include<iostream>
using namespace std;
Player::Player()
{

}

Player::~Player() {
}

bool Player::operator==(Player player) {
	return false;
}


int Player::getPointNumberTotal(){
	return pointNumberTotal;
}

void Player::setPointNumberTotal(int pointNumberTotal) {
	
	this->pointNumberTotal = pointNumberTotal;
//	cout<<this->pointNumberTotal<<"sss";
}

int Player::getPokerNumber(){
	return pokerNumber;
}

void Player::setPokerNumber(int pokerNumber) {
	this->pokerNumber = pokerNumber;
}

string Player::getName(){
//	cout<<"getName: "<<name<<endl;
	return this->name;
}

void Player::setName(string name){
	this->name = name;
//	cout<<this->name<<endl;
}

bool Player::getActive(){
	return active;
}

void Player::setActive(bool active){
	this->active = active;
}

