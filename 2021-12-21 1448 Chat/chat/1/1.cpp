#pragma comment(lib, "ws2_32.lib")  // ��� ��������� ������ � ��������� ��������
#include <iostream>
#include <string>
#include <winsock2.h>  // ���������� ��� ������ � �����
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // � ���� ���� ��� ������ ���������� �������� �� ����� (���������� ������� inet_addr())

SOCKET connections[100];
int counter = 0;

namespace message
{
    struct sendmessage
    {
        std::string name;
        std::string message;
    };

    void sendm(SOCKET newConnection, std::string str)
    {
        send(newConnection, str.c_str(), str.length(), NULL);
    }

    void ClientHandler(int index)
    {
        char msg[256] = "";
        int count = 0;

        while (recv(connections[index], msg, sizeof(msg), NULL))
        {
            for (int i = 0; i < counter; i++) {
                if (i == index) {
                    continue;
                }

                send(connections[i], msg, sizeof(msg), NULL);
                memset(msg, 0, 255);
            }
        }
    }
}

int main(int argc, char * argv[] )
{
    // WSAStartup - �������, ��� �������� ����������
    WSAData wasData; // �������� ���������

    WORD DLLVersion = MAKEWORD(2, 1);  // ������������� ������ ���������� winsock - ����� ��� ����, ����� ��������� ����������
    int res = WSAStartup(DLLVersion, &wasData);  // ��������� ����������

    if (res != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;  // ����� ��� �������� �������� ���������� � ������

    int domain = AF_INET;
    //unsigned char buf[sizeof(struct in6_addr)];

    //addr.sin_addr.s_addr = inet_pton(domain, "127.0.0.1", buf);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // sin_addr - ��������� SOCKADDR_IN, ������� ������ ip-�����
    addr.sin_port = htons(1111);  // sin_port - ������ ���� ������������� ��������� ������������ �������
    addr.sin_family = domain;  // sin_family - ������ ��������� ����������. ��� ��������-���������� ����������� �������� AF_INET

    SOCKET sListen = socket(domain, SOCK_STREAM, NULL);  // �������� ������ � � ��������� sListen, �������� ��������� ���������
                                                          // ���������� ������ socket � �����������: AF_INET - ��������� ���������� AF_INET
                                                          // SOCK_STREAM - ��������, ��������������� ����������
                                                          // NULL - ������ �������� �� �����.
    
    int size_addr = sizeof(addr);

    bind(sListen, (SOCKADDR*)&addr, size_addr);  // �������, ��� �������� ������ ������.
                                               // sListen - ��������������
                                               // ��������� �����
                                               // (SOCKADDR*)&addr - ��������� �� ��������� SOCKADDR
                                               // sf_addr - ������ ��������� SOCKADDR

    listen(sListen, SOMAXCONN);  // sListen - �����, �� �������� ������� ���������, �� ����� ����� ����� ������ �������������
                                 // SOMAXCONN - ������������ ���������� ��������, ��������� ���������
                                 // ����� �������� ������ ���������� ��������, �������� 3. � ���� ������ ������� � ������� 3 �������, � ��������� ������� ������

    SOCKET newConnection;  // ������ ����� �����

    for (int i = 0; i < 100; i++)
    {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &size_addr);  // ��� �������, ������� ������������ �������� ��� �������� ����� �� �����

        if (newConnection == 0)
        {
            std::cout << "Error connection." << std::endl;
        }
        else
        {
            std::cout << "Client #" << i + 1 << " connected." << std::endl; 
            
            char msg[256] = "Welcome to the chat! Press enter to start a dialogue.";
            send(newConnection, msg, sizeof(msg), NULL);

            connections[i] = newConnection;
            counter++;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::ClientHandler, (LPVOID)(i), NULL, NULL);
        }
    }

    system("pause");

    return 0;
}
