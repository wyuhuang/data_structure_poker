/*
*	ֽ����Ϸ 
*	����� 
* 	���ߣ������Ρ������ơ��Ʋ��ġ��ƺ��� 
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
	// ��Ϣ���ͣ�1-������Ϣ 2-������Ϣ 3-������Ϣ 
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
	ϴ��  
*/ 
ServerContext* card = new ServerContext();

int serverInit() {
	
	// 28 
	cout << "****************************" << endl;
	cout << "**                        **" << endl;
	cout << "**    ����������������    **" << endl;
	cout << "**                        **" << endl;
	cout << "****************************" << endl;

	// ���󲢰�socket��
	WORD wsaVersion = MAKEWORD(2,2);
	WSADATA wsaData;
	if (WSAStartup(wsaVersion, &wsaData)) {
		cerr << "WSAStartup failed : " << GetLastError() << endl;
	}

	// ��ʼ��������socket�͵�ַ��Ϣ
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	addr_server.sin_port = htons(8888);
	server = socket(AF_INET, SOCK_STREAM, 0);

	// ����������socket���������ַ��Ϣ��
	if (bind(server, (SOCKADDR*)&addr_server, sizeof(addr_server))) {
		cerr << "bind failed : " << GetLastError() << endl;
		WSACleanup();
	}

	// ������socket�������״̬
	if (listen(server, SOMAXCONN)) {
		cerr << "listen failed : " << GetLastError() << endl;
		WSACleanup();
	}
	
	system("cls");
	cout << "****************************" << endl;
	cout << "**                        **" << endl;
	cout << "**      ��������������    **" << endl;
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

	// �����еĿͻ�������Ϊ0ʱ
	if (p == NULL) {
		head = newNode;
	}
	// �����еĿͻ���������Ϊ0ʱ
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
	
	// �����еĿͻ�������Ϊ0ʱ
	if (p == NULL) {
		return head;
	}
	// ��Ҫɾ���Ľ����ͷ���ʱ
	if (p->info.client == client) {
		head = p->next;
		delete p;
		return head;
	}
	// ��Ҫɾ���Ľ�㲻��ͷ���ʱ
	while (p->next != NULL && p->next->info.client != client) {
		p = p->next;
	}
	// �Ѿ�����������ĩβ����û���ҵ�Ŀ��
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
	// ���շ��Ƶķ���ֵ 
	cliNode* p = pl;
	Poker po;
	string str;
	message msg;
	char buf[1024] = { 0 };
	msg.type = 3;
	strcpy(msg.name, "ϵͳ");
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
	
	// ��ʼ���ͻ�������
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
    cout << "�������ѹرգ�" << endl;
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
			cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : ��������������һ��������" << endl;
			strcpy(msg.text, "��������������һ��������");
			memcpy(buf, &msg, sizeof(msg));
			sendToOthers(head, buf, info);
			head = Delete(head, info->client);
			return 1;
		}
		// �����ݴӴ����õ��ַ�������ʽת��Ϊ�����õĽṹ����ʽ 
		memcpy(&msg, buf, sizeof(buf));
		//cout << "2" << msg.text << endl;
		info->msg = msg;
		//cout << info->msg.name << endl;
		
		switch (info->msg.type) {
			// type = 1��������Ϣ 
			case 1:
				head = Insert(head, info->client, info->addr_client, info->msg);
				cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : �����ˣ�����" << endl;
				strcpy(msg.text, "�������ˣ��ֵ��ǣ�");
				// �����ݴӹ����õĽṹ����ʽת��Ϊ�����õ��ַ�������ʽ
				memcpy(buf, &msg, sizeof(msg));
				sendToOthers(head, buf, info);
				
				num_cli++;
				str = "��ǰ���������"+to_string(num_cli);
				strcpy(msg.name, "ϵͳ"); 
				strcpy(msg.text, str.c_str());
				memcpy(buf, &msg, sizeof(msg));
				sendToAll(head, buf);
				
				// �����Ҵﵽ��λ���ϣ�����Ϸ��δ��ʼ����ʼ��Ϸ������Ϸ״̬��ȡ�� 
				if (num_cli >=2 && flag == 0){
					strcpy(msg.text, "����������ˣ��Ƿ�ʼ��Ϸ��");
					memcpy(buf, &msg, sizeof(msg));
					send(info->client, buf, sizeof(info->msg), 0);
					recv(info->client, buf, sizeof(buf), 0);
					memcpy(&msg, buf, sizeof(buf));
					if (strcmp(msg.text, "Y") == 0 || strcmp(msg.text, "y") == 0)
					{
						flag = 1;
						cout << "��Ϸ��ʼ����ʼ���ƣ�" << endl;
						strcpy(msg.name, "ϵͳ"); 
						strcpy(msg.text, "��Ϸ��ʼ����ʼ���ƣ�");
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
			// type = 2��������Ϣ 	
			case 2:
				strcpy(msg.text, "�������ˣ��ֵ��ǣ�");
				memcpy(buf, &msg, sizeof(msg));
				sendToOthers(head, buf, info);
				cout << "[" << ip << ":" << ntohs(info->addr_client.sin_port) << "] " << msg.name << " : �����ˣ�����" << endl;
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





