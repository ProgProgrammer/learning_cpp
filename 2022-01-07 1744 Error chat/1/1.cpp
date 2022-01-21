#pragma comment(lib, "ws2_32.lib")  // ��� ��������� ������� � ��������� �������� (��������)
#include <iostream>
#include <string>
#include <winsock2.h>  // ���������� ��� ������ � �����
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // � ���� ���� ��� ������ ���������� �������� �� ����� (���������� ������� inet_addr())

static HANDLE CLIENT_THREADS[100];  // ������ �������
static SOCKET CLIENT_CONNECTIONS[100];   // ������ �������
int CLIENT_COUNTER = 0;

namespace message_namespace
{
    struct ConnectionParams
    {
        SOCKET sListen;
        SOCKADDR_IN addr;
        int size_addr;
    };

    void sendm(SOCKET newConnection, const char * msg, int msg_size)
    {
        send(newConnection, (char*)&msg_size, sizeof(int), NULL);  // ������� ��� �������� ������ (������ ������)
        send(newConnection, msg, msg_size, NULL);                  // ������� ��� �������� ������ (���� ���������)
    }

    void ClientHandler(int client_index)
    {
        int msg_size;

        while (recv(CLIENT_CONNECTIONS[client_index], (char*)&msg_size, sizeof(int), NULL))  // ������� ��� ��������� ������
        {
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';

            recv(CLIENT_CONNECTIONS[client_index], msg, msg_size, NULL);  // ������� ��� ��������� ������

            for (int i = 0; i < CLIENT_COUNTER; i++) 
            {
                if (i == client_index) 
                {
                    continue;
                }

                sendm(CLIENT_CONNECTIONS[i], msg, msg_size + 1);
            }

            delete [] msg;
        }
    }

    void createConnections(ConnectionParams & params)
    {
        SOCKET newConnection;  // ������ ����� �����

        while ((newConnection = accept(params.sListen, (SOCKADDR*)&params.addr, &params.size_addr)) && CLIENT_COUNTER < 100)
        {
            if (newConnection == 0)
            {
                std::cout << "Error connection." << std::endl;
            }
            else
            {
                std::cout << "Client #" << CLIENT_COUNTER + 1 << " connected." << std::endl;

                std::string msg = "Welcome to the chat! Press enter twice to start a dialogue.\n";

                message_namespace::sendm(newConnection, msg.c_str(), msg.size() + 1);

                CLIENT_CONNECTIONS[CLIENT_COUNTER] = newConnection;

                CLIENT_THREADS[CLIENT_COUNTER] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message_namespace::ClientHandler, (LPVOID)(CLIENT_COUNTER), NULL, NULL);

                CLIENT_COUNTER++;
            }
        }
    }

    void closeAllSockets()
    {
        for (int i = 0; i < CLIENT_COUNTER; i++)
        {
            if (CLIENT_CONNECTIONS[i] > 0 && closesocket(CLIENT_CONNECTIONS[i]) == 0)
            {
                CLIENT_CONNECTIONS[i] = 0;
            }
        }
    }

    void closeHandles()
    {
        for (int i = 0; i < CLIENT_COUNTER; i++)
        {
            CloseHandle(CLIENT_THREADS[i]);
        }
    }
}

int main(int argc, char * argv[] )
{
    // WSAStartup - �������, ��� �������� ����������
    WSAData wsaData; // �������� ���������

    WORD DLLVersion = MAKEWORD(2, 1);  // ������������� ������ ���������� winsock - ����� ��� ����, ����� ��������� ����������
    int res = WSAStartup(DLLVersion, &wsaData);  // ��������� ����������

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

    SOCKET sListen = socket(domain, SOCK_STREAM, NULL);   // �������� ������ � � ��������� sListen, �������� �������� ���������
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

    std::cout << "To close all connections, type the word \"cl_all_cons\" and \"Enter\" keys." << std::endl;
    std::cout << "To close all connections, type the word \"cl_con\" and \"Enter\", and then enter the connection number." << std::endl;
    std::cout << "To exit the application, type the word \"close_app\" and press the \"Enter\" key." << std::endl << std::endl;

    message_namespace::ConnectionParams params;
    
    params.sListen = sListen;
    params.addr = addr;
    params.size_addr = size_addr;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message_namespace::createConnections, &params, NULL, NULL);

    std::string command;
    int connection_num;

    while (std::getline(std::cin, command))
    {
        if (command == "cl_all_cons")
        {
            message_namespace::closeAllSockets();
            message_namespace::closeHandles();

            CLIENT_COUNTER = 0;

            std::cout << "All connections are closed." << std::endl;
        }
        else if (command == "cl_con")
        {
            std::cout << "Enter the connection number: ";
            std::cin >> connection_num;

            if (connection_num > 0 && closesocket(CLIENT_CONNECTIONS[connection_num - 1]) == 0)
            {
                CloseHandle(CLIENT_THREADS[connection_num - 1]);
            }
            else
            {
                std::cout << "There is no such connection." << std::endl;
            }
        }
        else if (command == "close_app")
        {
            if (CLIENT_COUNTER > 0)
            {
                message_namespace::closeAllSockets();
                message_namespace::closeHandles();
            }

            std::cout << "The program has ended." << std::endl;
            WSACleanup();
        }
    }

    system("pause");

    return 0;
}
