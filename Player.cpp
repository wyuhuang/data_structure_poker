#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::operator==(Player player) {
	return false;
}

int Player::getPointNumberTotal(){
	return pointNumberTotal;
}

void Player::setPointNumberTotal(int pointNumberTotal) {
	this->pointNumberTotal = pointNumberTotal;
}

int Player::getPokerNumber(){
	return pokerNumber;
}

void Player::setPokerNumber(int pokerNumber) {
	this->pokerNumber = pokerNumber;
}

string Player::getName(){
	return name;
}

void Player::setName(string name){
	this->name = name;
}

bool Player::getActive(){
	return active;
}

void Player::setActive(bool active){
	this->active = active;
}

