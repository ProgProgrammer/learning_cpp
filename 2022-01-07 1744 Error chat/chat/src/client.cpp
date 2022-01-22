﻿#pragma comment(lib, "ws2_32.lib")  // для получения доступа к некоторым функциям
#include <iostream>
#include <winsock2.h>  // библиотека для работы с сетью
#include <string>

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

static SOCKET CONNECTION;

namespace message_namespace
{
    struct Message
    {
        std::string name;
        std::string message;
        std::string all_message;
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

        while (recv(CONNECTION, (char*)&msg_size, sizeof(int), NULL))  // функция для получения данных
        {
            count++;

            char* msg = new char[msg_size];
            msg[msg_size - 1] = '\0';

            recv(CONNECTION, msg, msg_size, NULL);  // функция для получения данных

            std::cout << msg << std::endl;

            delete[] msg;
        }
    }
}

int main(int argc, char* argv[])
{
    // WSAStartup - функция, для загрузки библиотеки

    WSAData wsaData;

    WORD DLLVersion = MAKEWORD(2, 1);
    int res = WSAStartup(DLLVersion, &wsaData);

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

    CONNECTION = socket(domain, SOCK_STREAM, NULL);

    if (connect(CONNECTION, (SOCKADDR*)&addr, sizeof(addr)) != 0)  // connect() - функция для соединения с сервером, где
                                                                   // connection - дескриптор сокета, возращенный функцией socket
                                                                   // (SOCKADDR*)&addr - указатель на структуру "sockaddr", содержащую в себе
                                                                   // адрес и порт удаленного узла с которым устанавливается соединение
                                                                   // sizeof(addr) - сообщает функции размер структуры sockaddr
    {
        std::cout << "Error: failed connect to server." << std::endl;
        closesocket(CONNECTION);  // удаление соединения
        WSACleanup();  // деинициализация библиотеки WINSOCK и освобождения используемых этим приложением ресурсов
        std::cin.get();

        return 1;
    }

    std::cout << "Connected." << std::endl;

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message_namespace::ClientHandler, NULL, NULL, NULL);

    std::cin.get();

    std::cout << "Enter your name: ";

    message_namespace::Message str_mes;

    std::getline(std::cin, str_mes.name);

    std::cout << "Start correspondence:" << std::endl;

    while (std::getline(std::cin, str_mes.message))
    {
        str_mes.all_message = "\t" + str_mes.name + "\n";
        str_mes.all_message = str_mes.all_message + "\t" + str_mes.message + "\n\a";

        message_namespace::sendm(CONNECTION, str_mes.all_message);

        std::cout << std::endl;

        Sleep(10);
    }

    system("pause");

    return 0;
}