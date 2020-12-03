/*
*	纸牌游戏 
*	服务端 
* 	作者：郭龙涛、胡华浩、黄昌文、黄宏腾 
*/ 
#include <iostream>
#include <WinSock2.h> 
#include <WS2tcpip.h>
#include <Windows.h>
#include <cstdio>

#include "ServerContext.h" 

#pragma comment(lib,"ws2_32.lib")

using namespace std;

SOCKET server;
SOCKADDR_IN addr_server;

struct message {
	// 信息类型：1-上线信息 2-下线信息 3-操作信息 
	int type;
	char name[16];
	char text[200];
}; 

struct clientInfo {
	SOCKET client;
	SOCKADDR_IN addr_client;
	message msg;
};

struct cliNode {
	clientInfo info;
	Player *play;
	cliNode* next;
}; 

cliNode* head;
cliNode* p;

int num_cli = 0; 
int flag = 0;

/*
	洗牌  
*/ 
ServerContext* card = new ServerContext();

int serverInit() {
	
	// 28 
	cout << "****************************" << endl;
	cout << "**                        **" << endl;
	cout << "**    正在启动服务器！    **" << endl;
	cout << "**                        **" << endl;
	cout << "****************************" << endl;

	// 请求并绑定socket库
	WORD wsaVersion = MAKEWORD(2,2);
	WSADATA wsaData;
	if (WSAStartup(wsaVersion, &wsaData)) {
		cerr << "WSAStartup failed : " << GetLastError() << endl;
	}

	// 初始化服务器socket和地址信息
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	addr_server.sin_port = htons(8888);
	server = socket(AF_INET, SOCK_STREAM, 0);

	// 将服务器的socket与服务器地址信息绑定
	if (bind(server, (SOCKADDR*)&addr_server, sizeof(addr_server))) {
		cerr << "bind failed : " << GetLastError() << endl;
		WSACleanup();
	}

	// 服务器socket进入监听状态
	if (listen(server, SOMAXCONN)) {
		cerr << "listen failed : " << GetLastError() << endl;
		WSACleanup();
	}
	
	system("cls");
	cout << "****************************" << endl;
	cout << "**                        **" << endl;
	cout << "**      服务器已启动！    **" << endl;
	cout << "**                        **" << endl;
	cout << "****************************" << endl;
	
	
	return 0;
}

cliNode* Insert(cliNode* head, SOCKET client, SOCKADDR_IN addr_client, message msg) {
	
	cliNode* newNode = new cliNode();
	newNode->info.client = client;
	newNode->info.addr_client = addr_client;
	newNode->info.msg = msg;
	newNode->play = new Player();
	newNode->play->pointNumberTotal = 0;
	newNode->next = NULL;

	cliNode* p = head;

	// 链表中的客户端数量为0时
	if (p == NULL) {
		head = newNode;
	}
	// 链表中的客户端数量不为0时
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = newNode;
	}
	return head;
}

cliNode* Delete(cliNode* head, SOCKET client) {
	
	cliNode* p = head;
	
	// 链表中的客户端数量为0时
	if (p == NULL) {
		return head;
	}
	// 若要删除的结点是头结点时
	if (p->info.client == client) {
		head = p->next;
		delete p;
		return head;
	}
	// 若要删除的结点不是头结点时
	while (p->next != NULL && p->next->info.client != client) {
		p = p->next;
	}
	// 已经遍历到链表末尾，但没有找到目标
	if (p->next == NULL) {
		return head;
	}
	cliNode* deleteNode = p->next;
	p->next = deleteNode->next;
	delete deleteNode;
	return head;

}

void sendToOthers(cliNode* head, char buf[], clientInfo* info) {
	cliNode* p = head;
	while (p != NULL) {
		int i = strcmp(p->info.msg.name, "");
		int j = strcmp(p->info.msg.name, info->msg.name);
		//if (strcmp(p->info.msg.name, "") != 0 && strcmp(p->info.msg.name, info->msg.name) != 0) {
		if (i != 0 && j != 0) {
			send(p->info.client, buf, sizeof(info->msg), 0);
			int error_send = GetLastError();
			if (error_send != 0) {
				cout << "send failed : " << error_send << endl;
			}
		}
		p = p->next;
	}
} 

void sendToAll(cliNode* head, char buf[]) {
	cliNode* p = head;
	while (p != NULL) {
		send(p->info.client, buf, sizeof(p->info.msg), 0);
		if (GetLastError() != 0) {
			cout << "send failed : " << GetLastError() << endl;
		}
		p = p->next;
	}
}

void sendPoker(cliNode* pl, ServerContext* card) {
	// 接收发牌的返回值 
	cliNode* p = pl;
	Poker po;
	string str;
	message msg;
	char buf[1024] = { 0 };
	msg.type = 3;
	strcpy(msg.name, "系统");
	po = card->dealOnePoker();
	str = to_string(po.getPointNumber()) + po.getFlowerColor();
	strcpy(msg.text, str.c_str());
	cout << msg.text << endl;
	memcpy(buf, &msg, sizeof(msg));
	send(p->info.client, buf, sizeof(p->info.msg), 0);
	if (GetLastError() != 0) {
		cout << "send failed : " << GetLastError() << endl;
	}
}


DWORD WINAPI threadToHandle(LPVOID lpParameter);

int main() {
	
	serverInit();
	
	// 初始化客户端链表
	head = NULL;
	p = head;

	while (true) {
		clientInfo* info = new clientInfo();
		int addr_len = sizeof(SOCKADDR);
		info->client = accept(server, (SOCKADDR*)&info->addr_client, &addr_len);
		
		HANDLE h_thread = CreateThread(0, 0, threadToHandle, info, 0, 0);
		if (h_thread == NULL) { 
			cerr << "CreateThread failed : " << GetLastError() << endl; 
		}
		CloseHandle(h_thread);
		
	}

	closesocket(server);
    WSACleanup();
    cout << "服务器已关闭！" << endl;
	return 0;
}

DWORD WINAPI threadToHandle(LPVOID lpParameter) {
	
	clientInfo* info = (clientInfo*)lpParameter;
	
	char buf[1024];
	memset(buf, 1024, 0);
	// string str; ???
	
	while (true) {
		
		message msg;
		//cout << "1" << msg.text << endl;
		string str;

		char ip[20];
		strcpy(ip, inet_ntoa(info->addr_client.sin_addr));
		
		Poker po;
		
		int addr_len = sizeof(SOCKADDR);
		
		int ret = recv(info->client, buf, sizeof(buf), 0);
		if (ret <= 0) {
			cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : 人有三急，先走一步！！！" << endl;
			strcpy(msg.text, "人有三急，先走一步！！！");
			memcpy(buf, &msg, sizeof(msg));
			sendToOthers(head, buf, info);
			head = Delete(head, info->client);
			return 1;
		}
		// 将数据从传输用的字符数组形式转换为功能用的结构体形式 
		memcpy(&msg, buf, sizeof(buf));
		//cout << "2" << msg.text << endl;
		info->msg = msg;
		//cout << info->msg.name << endl;
		
		switch (info->msg.type) {
			// type = 1，上线信息 
			case 1:
				head = Insert(head, info->client, info->addr_client, info->msg);
				cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : 上线了！！！" << endl;
				strcpy(msg.text, "我上线了，兄弟们！");
				// 将数据从功能用的结构体形式转换为传输用的字符数组形式
				memcpy(buf, &msg, sizeof(msg));
				sendToOthers(head, buf, info);
				
				num_cli++;
				str = "当前玩家数量："+to_string(num_cli);
				strcpy(msg.name, "系统"); 
				strcpy(msg.text, str.c_str());
				memcpy(buf, &msg, sizeof(msg));
				sendToAll(head, buf);
				
				// 如果玩家达到三位以上，且游戏仍未开始，则开始游戏，将游戏状态量取反 
				if (num_cli >=2 && flag == 0){
					strcpy(msg.text, "玩家已满两人，是否开始游戏？");
					memcpy(buf, &msg, sizeof(msg));
					send(info->client, buf, sizeof(info->msg), 0);
					recv(info->client, buf, sizeof(buf), 0);
					memcpy(&msg, buf, sizeof(buf));
					if (strcmp(msg.text, "Y") == 0 || strcmp(msg.text, "y") == 0)
					{
						flag = 1;
						cout << "游戏开始！开始发牌！" << endl;
						strcpy(msg.name, "系统"); 
						strcpy(msg.text, "游戏开始！开始发牌！");
						memcpy(buf, &msg, sizeof(msg));
						sendToAll(head, buf);
						
						cliNode* p = head;
						while (p != NULL) {
							po = card->dealOnePoker();
							cout << p->play->pointNumberTotal << endl;
							cout << po.getPointNumber() << endl;
							p->play->pointNumberTotal += po.getPointNumber();
							cout << p->play->pointNumberTotal << endl;
							str = to_string(po.getPointNumber()) + po.getFlowerColor();
							str += " ";
							po = card->dealOnePoker();
							p->play->pointNumberTotal += po.getPointNumber();
							cout << p->play->pointNumberTotal << endl;
							str += to_string(po.getPointNumber()) + po.getFlowerColor();
							strcpy(msg.text, str.c_str());
							memcpy(buf, &msg, sizeof(msg));
							send(p->info.client, buf, sizeof(p->info.msg), 0);
							p = p->next;
						}
					}
				}
				break;
			// type = 2，下线信息 	
			case 2:
				strcpy(msg.text, "我下线了，兄弟们！");
				memcpy(buf, &msg, sizeof(msg));
				sendToOthers(head, buf, info);
				cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : 下线了！！！" << endl;
				head = Delete(head, info->client);
				return 0;
			case 3:
				cout << "[" << ip << " : " << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : " << info->msg.text << endl; 
				memcpy(buf, &msg, sizeof(msg));
				sendToOthers(head, buf, info);
				break;
		}
	}
}





