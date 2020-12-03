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
		//不提供setPokers，因为getPokers就可以获取指针，然后set
		LinkedList<Player> getPlayerList();
		//同上 
		void shufflePokers();//洗牌
		Poker dealOnePoker();//发出一张牌 
		void settlementScore();
		int getPokersTop();
		void setPokersTop(int pokerTop);
	private:
		Poker pokers[52];
		LinkedList<Player> playerList;
		//当前活跃玩家字段类型由服务端决定
		//int activeIP[4]; 
		int pokersTop = 51;
};

#endif
