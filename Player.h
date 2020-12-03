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
		string getName();
		void setName(string name);
		bool getActive();
		void setActive(bool active);
		bool operator==(Player player);
	private:
		int pointNumberTotal;//����֮��
		int pokerNumber;//���������ܻ��õ�
		int ip[4];//�洢��ʽ�ɷ���˾��� 
		string name;
		bool active;
};

#endif
