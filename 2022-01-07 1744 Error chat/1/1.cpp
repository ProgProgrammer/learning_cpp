#pragma comment(lib, "ws2_32.lib")  // ��� ��������� ������� � ��������� ��������
#include <iostream>
#include <string>
#include <winsock2.h>  // ���������� ��� ������ � �����
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // � ���� ���� ��� ������ ���������� �������� �� ����� (���������� ������� inet_addr())

static HANDLE hThreadArray[100];
static SOCKET connections[100];
int counter = 0;

namespace message
{
    struct mess
    {
        SOCKET sListen;
        SOCKADDR_IN addr;
        int size_addr;
    };

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

    void createConnections(mess * m1)
    {
        SOCKET newConnection;  // ������ ����� �����

        while ((newConnection = accept(m1->sListen, (SOCKADDR*)&m1->addr, &m1->size_addr)) && counter < 100)
        {
            if (newConnection == 0)
            {
                std::cout << "Error connection." << std::endl;
            }
            else
            {
                std::cout << "Client #" << counter + 1 << " connected." << std::endl;

                std::string msg = "Welcome to the chat! Press enter twice to start a dialogue.\n";
                int msg_size = msg.size();
                char* str = new char[msg_size + 1];
                str[msg_size] = '\0';

                strcpy(str, msg.c_str());

                message::sendm(newConnection, str, msg_size + 1);

                delete[] str;

                connections[counter] = newConnection;

                hThreadArray[counter] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::ClientHandler, (LPVOID)(counter), NULL, NULL);

                counter++;
            }
        }
    }

    void closeAllSockets()
    {
        for (int i = 0; i < counter; i++)
        {
            if (connections[i] > 0 && closesocket(connections[i]) == 0)
            {
                connections[i] = 0;
            }
        }
    }

    void closeHandles()
    {
        for (int i = 0; i < counter; i++)
        {
            CloseHandle(hThreadArray[i]);
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

    std::cout << "To close all connections, type the word \"cl_all_cons\" and \"Enter\" keys." << std::endl;
    std::cout << "To close all connections, type the word \"cl_con\" and \"Enter\", and then enter the connection number." << std::endl;
    std::cout << "To exit the application, type the word \"close_app\" and press the \"Enter\" key." << std::endl << std::endl;

    message::mess* m1 = new message::mess;
    
    m1->sListen = sListen;
    m1->addr = addr;
    m1->size_addr = size_addr;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::createConnections, m1, NULL, NULL);

    std::string str;
    int num;

    while (std::getline(std::cin, str))
    {
        if (str == "cl_all_cons")
        {
            message::closeAllSockets();
            message::closeHandles();

            counter = 0;

            std::cout << "All connections are closed." << std::endl;
        }
        else if (str == "cl_con")
        {
            std::cout << "Enter the connection number: ";
            std::cin >> num;

            if (num > 0 && closesocket(connections[num - 1]) == 0)
            {
                CloseHandle(hThreadArray[num - 1]);
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
                message::closeAllSockets();
                message::closeHandles();
            }

            std::cout << "The program has ended." << std::endl;
            WSACleanup();
        }
    }

    system("pause");

    return 0;
}
