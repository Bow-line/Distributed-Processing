#include <Winsock2.h>
#include <conio.h>
#include <iostream>
#include <Ws2tcpip.h>
#define ST_PORT 5000
int main()
{
    WSADATA wsas;
    int result;
    WORD wersja;
    wersja = MAKEWORD(1, 1);
    result = WSAStartup(wersja, &wsas);
   
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    memset((void*)(&sa), 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(ST_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    result = bind(s, (struct sockaddr FAR*) & sa, sizeof(sa));
    result = listen(s, 5);
    SOCKET si;
    struct sockaddr_in sc;
    int lenc;
    for (;;)
    {
        lenc = sizeof(sc);
        si = accept(s, (struct sockaddr FAR*) & sc, &lenc)
}
