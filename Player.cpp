#include "Player.h"

Player::Player() {
	this.
}

Player::~Player() {
	
}

bool Player::operator==(Player player) {
	return false;
}

int Player::getPointNumberTotal() {
	return this->pointNumberTotal;
}
void Player::setPointNumberTotal(int pointNumberTotal) {
	this->pointNumberTotal = pointNumberTotal;
}
int Player::getPokerNumber() {
	return this->pokerNumber;
}
void Player::setPokerNumber(int pokerNumber) {
	this->pokerNumber = pokerNumber;
}
bool Player::getActive() {
	return this->active;
}
void Player::setActive(bool active) {
	this->active = active;
}
