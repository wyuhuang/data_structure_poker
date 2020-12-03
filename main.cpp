#include"ServerContext.h"
#include"Player.h"
int main() {
	ServerContext a;
	Player *p1 = new Player();
	Player *p2 = new Player();
	Player *p3 = new Player();
	Player *p4 = new Player();
	Player *p5 = new Player();
	p1->setPointNumberTotal(24);
	p1->setName("p1");
	p2->setPointNumberTotal(18);
	p2->setName("p2");
	p3->setPointNumberTotal(18);
	p3->setName("p3");
	p4->setPointNumberTotal(21);
	p4->setName("p4");
	p5->setPointNumberTotal(26);
	p5->setName("p5");
	return 0;
}
