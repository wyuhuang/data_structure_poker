#ifndef SERVER_CONTEXT
#define SERVER_CONTEXT

#include"LinkedList.h"
#include"Poker.h"
#include"Player.h"
class ServerContext {
	public:
		ServerContext();
		~ServerContext(); 
		Poker* getPokers();
		//���ṩsetPokers����ΪgetPokers�Ϳ��Ի�ȡָ�룬Ȼ��set
		LinkedList<Player> getPlayerList();
		//ͬ�� 
		void shufflePokers();//ϴ��
		Poker dealOnePoker();//����һ���� 
		void settlementScore();
	private:
		Poker pokers[52];
		LinkedList<Player> playerList;
		//��ǰ��Ծ����ֶ������ɷ���˾���
		//int activeIP[4]; 
		int PokersTop = 52;
};

#endif