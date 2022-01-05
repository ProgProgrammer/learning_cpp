#pragma comment(lib, "ws2_32.lib")  // для получения доступа к некоторым функциям
#include <iostream>
#include <winsock2.h>  // библиотека для работы с сетью
#include <string>

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

static SOCKET connection;

namespace message
{
    struct sendmessage
    {
        std::string name;
        std::string message;
        std::string all_t;
    };

    void sendm(SOCKET newConnection, std::string str)
    {
        int msg_size = str.size();
        send(newConnection, (char*)&msg_size, sizeof(int), NULL);
        send(newConnection, str.c_str(), str.length(), NULL);
    }

    void ClientHandler()
    {
        int msg_size;
        int count = -1;

        while (recv(connection, (char*)&msg_size, sizeof(int), NULL))
        {
            count++;

            char* msg = new char[msg_size];
            msg[msg_size - 1] = '\0';

            recv(connection, msg, msg_size, NULL);

            std::cout << msg << std::endl;

            delete[] msg;
        }
    }
}

int main(int argc, char* argv[])
{
    // WSAStartup - функция, для загрузки библиотеки

    WSAData wasData;

    WORD DLLVersion = MAKEWORD(2, 1);
    int res = WSAStartup(DLLVersion, &wasData);

    if (res != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;

    int domain = AF_INET;

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = domain;

    connection = socket(domain, SOCK_STREAM, NULL);

    if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)  // connect() - функция для соединения с сервером
    {
        std::cout << "Error: failed connect to server." << std::endl;

        return 1;
    }

    std::cout << "Connected." << std::endl;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message::ClientHandler, NULL, NULL, NULL);

    std::cin.get();

    std::cout << "Enter your name: ";

    message::sendmessage str_mes;

    std::getline(std::cin, str_mes.name);

    std::cout << "Start correspondence:" << std::endl;

    while (std::getline(std::cin, str_mes.message))
    {
        str_mes.all_t = "\t" + str_mes.name + "\n";
        str_mes.all_t = str_mes.all_t + "\t" + str_mes.message + "\n";

        message::sendm(connection, str_mes.all_t);

        str_mes.all_t = "";

        std::cout << std::endl;

        Sleep(10);
    }

    system("pause");

    return 0;
}