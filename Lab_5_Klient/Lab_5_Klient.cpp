#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <winsock2.h>
#include <string>
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

    if (connect(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("Failed to connect.\n");
        WSACleanup();
        return 1;
    }

    
    char sendbuf[32] = "";
    char recvbuf[32] = "";
    string text = "";
    

    while (sendbuf[0] != 'E' && sendbuf[1] != 'N' && sendbuf[2] != 'D')
    {
        strcpy_s(sendbuf, "                               ");
        strcpy_s(recvbuf, "                               ");

        cout << "Say sth: ";
        getline(cin, text);
        strcpy_s(sendbuf, text.c_str());
        send(mainSocket, sendbuf, strlen(sendbuf), 0);

        if (sendbuf[0] != 'E' && sendbuf[1] != 'N' && sendbuf[2] != 'D') {
            recv(mainSocket, recvbuf, 32, 0);
            cout << "Server said: " << recvbuf << endl;
        }
        
    }

    
    closesocket(mainSocket);
    WSACleanup();
    
}