#include "Poker.h"
#include<iostream>

using namespace std;
Poker::Poker()
{
}

Poker::~Poker()
{
}

void Poker::setPointNumber(int pointNumber) {
	this->pointNumber = pointNumber;
}

int Poker::getPointNumber() {
	return this->pointNumber;
}

void Poker::setFlowerColor(char flowerColor) {
	this->flowerColor = flowerColor;
}
void Poker::print() {
	cout<<pointNumber;
	cout<<flowerColor<<endl;
}
