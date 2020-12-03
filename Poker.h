#ifndef POKER_H
#define POKER_H

class Poker
{
	public:
		Poker();
		~Poker();
		int getPointNumber();
		void setPointNumber(int pointNumber);
		char getFlowerColor();
		void setFlowerColor(char flowerColor);
		void print();
	private:
		int pointNumber;
		char flowerColor;
};

#endif
