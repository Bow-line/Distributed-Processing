#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <string>
#include <Windows.h>
using namespace std;
int main()
{
	WSADATA wsaData;

	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		printf("Initialization error.\n");

	SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET)
	{
		printf("Error creating socket: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);

	if (bind(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("bind() failed.\n");
		closesocket(mainSocket);
		return 1;
	}

	if (listen(mainSocket, 5) == SOCKET_ERROR)
		printf("Error listening on socket.\n");

	SOCKET acceptSocket = SOCKET_ERROR;
	printf("Waiting for a client to connect...\n");

	while (acceptSocket == SOCKET_ERROR)
	{
		acceptSocket = accept(mainSocket, NULL, NULL);
	}

	printf("Client connected.\n");
	mainSocket = acceptSocket;
	
	
	char sendbuf[32] = "";
	char recvbuf[32] = "";
	string text = "";
	
	while (recvbuf[0] != 'E' && recvbuf[1] != 'N' && recvbuf[2] != 'D') {

		strcpy_s(sendbuf, "                               ");
		strcpy_s(recvbuf, "                               ");

		recv(mainSocket, recvbuf, 32, 0);
		cout << "Client said: " << recvbuf << endl;

		if (recvbuf[0] != 'E' && recvbuf[1] != 'N' && recvbuf[2] != 'D') {
			cout << "Say sth: ";
			getline(cin, text);
			strcpy_s(sendbuf, text.c_str());
			send(mainSocket, sendbuf, strlen(sendbuf), 0);
		}
		
	}
	
	closesocket(mainSocket);
	WSACleanup();
}