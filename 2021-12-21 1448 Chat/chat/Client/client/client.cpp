#pragma comment(lib, "ws2_32.lib")  // для получения оступа к некоторым функциям
#include <iostream>
#include <winsock2.h>  // библиотека для работы с сетью

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

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

    SOCKET connection = socket(domain, SOCK_STREAM, NULL);

    int size_addr = sizeof(addr);

    if (connect(connection, (SOCKADDR*)&addr, size_addr) != 0)  // connect() - функция для соединения с сервером
    {
        std::cout << "Error: failed connect to server." << std::endl;

        return 1;
    }

    std::cout << "Connected." << std::endl;

    char msg[256] = "";
    int count = 0;

    /*recv(connection, msg, sizeof(msg), NULL);

    std::cout << msg << std::endl;

    memset(msg, 0, 255);*/

    while (recv(connection, msg, sizeof(msg), NULL))
    {
        count++;

        std::cout << msg << std::endl;

        memset(msg, 0, 255);

        if (count % 2 == 0)
        {
            std::cout << std::endl;
        }
    }

    system("pause");

    return 0;
}