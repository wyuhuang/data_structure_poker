#ifndef PLAYER_H
#define PLAYER_H
#include<string>

using namespace std;

class Player
{
	public:
		Player();
		~Player();
		int getPointNumberTotal();
		void setPointNumberTotal(int pointNumberTotal);
		int getPokerNumber();
		void setPokerNumber(int pokerNumber);
		int* getIp();
		void setIp(int ip[]);
		bool getActive();
		void setActive(bool active);
		bool operator==(Player player);
	private:
		int pointNumberTotal;//点数之和
		int pokerNumber;//牌数，可能会用到
		int ip[4];//存储方式由服务端决定 
		string name;
		bool active;
};

#endif
