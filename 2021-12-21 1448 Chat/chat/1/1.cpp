#pragma comment(lib, "ws2_32.lib")  // ��� ��������� ������� � ��������� ��������
#include <iostream>
#include <string>
#include <winsock2.h>  // ���������� ��� ������ � �����
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // � ���� ���� ��� ������ ���������� �������� �� ����� (���������� ������� inet_addr())

static SOCKET connections[100];
int counter = 0;

namespace message
{
    void sendm(SOCKET newConnection, char * msg, int msg_size)
    {
        send(newConnection, (char*)&msg_size, sizeof(int), NULL);
        send(newConnection, msg, msg_size, NULL);
    }

    void ClientHandler(int index)
    {
        int msg_size;
        int count = 0;

        while (true)
        {
            recv(connections[index], (char*)&msg_size, sizeof(int), NULL);

            char* msg = new char[msg_size];
            msg[msg_size] = '\0';

            recv(connections[index], msg, msg_size, NULL);

            for (int i = 0; i < counter; i++) {
                if (i == index) {
                    continue;
                }

                sendm(connections[i], msg, msg_size);
            }

            delete [] msg;
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
            
            std::string msg = "Welcome to the chat! Press enter to start a dialogue.";
            int msg_size = msg.size();
            char* str = new char[msg_size];

            strcpy(str, msg.c_str());

            str[msg_size] = '\0';

            std::cout << str << std::endl;

            message::sendm(connections[i], str, msg_size);

            std::cout << "str2" << std::endl;

            delete[] str;

            std::cout << "str3" << std::endl;

            connections[i] = newConnection;
            counter++;

            std::cout << "str4" << std::endl;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::ClientHandler, (LPVOID)(i), NULL, NULL);

            std::cout << "str5" << std::endl;
        }
    }

    system("pause");

    return 0;
}
