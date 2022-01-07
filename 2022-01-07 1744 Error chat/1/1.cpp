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
        send(newConnection, (char*)&msg_size, sizeof(int), NULL);  // ������� ��� �������� ������
        send(newConnection, msg, msg_size, NULL);                  // ������� ��� �������� ������
    }

    void ClientHandler(int index)
    {
        int msg_size;

        while (recv(connections[index], (char*)&msg_size, sizeof(int), NULL))  // ������� ��� ��������� ������
        {
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';

            recv(connections[index], msg, msg_size, NULL);  // ������� ��� ��������� ������

            for (int i = 0; i < counter; i++) {
                if (i == index) 
                {
                    continue;
                }

                sendm(connections[i], msg, msg_size + 1);
            }

            delete [] msg;
        }
    }

    void closeAllSockets()
    {
        std::cout << "Connections:" << std::endl;

        for (int i = 0; i < counter; i++)
        {
            if (connections[i] > 0)
            {
                std::cout << "1. " << connections[i] << std::endl;
                closesocket(connections[i]);
                std::cout << "2. " << connections[i] << std::endl;
            }
        }
    }

    void actions(int n)
    {
        std::string str;
        int num;

        while (std::getline(std::cin, str))
        {
            if (str == "cl_all_cons")
            {
                closeAllSockets();

                std::cout << "All connections are closed." << std::endl;

                str = "";
            }
            else if (str == "cl_con")
            {
                std::cout << "Enter the connection number: ";
                std::cin >> num;

                if (num > 0 && closesocket(connections[num - 1]) == 0)
                {
                    std::cout << "Connection #" << num << " is closed." << std::endl;

                    str = "";
                }
                else
                {
                    std::cout << "There is no such connection." << std::endl;
                }
            }
            else if (str == "close_app")
            {
                if (counter > 0)
                {
                    closeAllSockets();
                }
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

    int domain = AF_INET;  // ��������� ������������ ����������. � ������ ������, AF_INET.
    //unsigned char buf[sizeof(struct in6_addr)];

    //addr.sin_addr.s_addr = inet_pton(domain, "127.0.0.1", buf);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // sin_addr - ��������� SOCKADDR_IN, ������� ������ ip-�����
    addr.sin_port = htons(1111);  // sin_port - ������ ���� ������������� ��������� ������������ �������
    addr.sin_family = domain;  // sin_family - ������ ��������� ����������. ��� ��������-���������� ����������� �������� AF_INET

    SOCKET sListen = socket(domain, SOCK_STREAM, NULL);   // �������� ������ � � ��������� sListen, �������� ��������� ���������
                                                          // ���������� ������ socket � �����������: AF_INET - ��������� ���������� AF_INET
                                                          // SOCK_STREAM - ��������, ��������������� ���������� (��������� ��� ������������ ������)
                                                          // NULL - ��� ����� �������� ����� ������������� ��������� ���������� �� ���������.
                                                          // TCP - ��� ��������� �������, ��� �����.
    
    int size_addr = sizeof(addr);

    bind(sListen, (SOCKADDR*)&addr, size_addr);  // �������, ��� �������� ������ ������.
                                                 // sListen - ��������������
                                                 // ��������� �����
                                                 // (SOCKADDR*)&addr - ��������� �� ��������� SOCKADDR
                                                 // sf_addr - ������ ��������� SOCKADDR

    listen(sListen, SOMAXCONN);  // listen() - ������� �������� �����������.
                                 // sListen - �����, �� �������� ������� ���������, �� ����� ����� ����� ������ �������������.
                                 // SOMAXCONN - ������������ ���������� ��������, ��������� ���������. ��-���������, ����� 128.
                                 // ����� �������� ������ ���������� ��������, �������� 3. � ���� ������ ������� � ������� 3 �������, � ��������� ������� ������

    SOCKET newConnection;  // ������ ����� �����

    std::cout << "To close all connections, type the word \"cl_all_cons\" and \"Enter\" keys." << std::endl;
    std::cout << "To close all connections, type the word \"cl_con\" and \"Enter\", and then enter the connection number." << std::endl;
    std::cout << "To exit the application, type the word \"close_app\" and press the \"Enter\" key." << std::endl << std::endl;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::actions, (LPVOID)(0), NULL, NULL);

    for (int i = 0; i < 100; i++)
    {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &size_addr);  // ���������� �������� �� ���������� �� �������

        if (newConnection == 0)
        {
            std::cout << "Error connection." << std::endl;
        }
        else
        {
            std::cout << "Client #" << i + 1 << " connected." << std::endl; 
            
            std::string msg = "Welcome to the chat! Press enter twice to start a dialogue.\n";
            int msg_size = msg.size();
            char* str = new char[msg_size + 1];
            str[msg_size] = '\0';

            strcpy(str, msg.c_str());

            message::sendm(newConnection, str, msg_size + 1);

            delete [] str;

            connections[i] = newConnection;
            counter++;

            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::ClientHandler, (LPVOID)(i), NULL, NULL);
        }
    }

    system("pause");

    return 0;
}
