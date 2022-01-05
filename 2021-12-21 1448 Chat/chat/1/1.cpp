#pragma comment(lib, "ws2_32.lib")  // для получения доступа к некоторым функциям
#include <iostream>
#include <string>
#include <winsock2.h>  // библиотека для работы с сетью
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

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

        while (recv(connections[index], (char*)&msg_size, sizeof(int), NULL))
        {
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';

            recv(connections[index], msg, msg_size, NULL);

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
}

int main(int argc, char * argv[] )
{
    // WSAStartup - функция, для загрузки библиотеки
    WSAData wasData; // создание структуры

    WORD DLLVersion = MAKEWORD(2, 1);  // запрашиваемая версия библиотеки winsock - нужна для того, чтобы загрузить библиотеку
    int res = WSAStartup(DLLVersion, &wasData);  // загружаем библиотеку

    if (res != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;  // нужна для хранения интернет протоколов и адреса

    int domain = AF_INET;
    //unsigned char buf[sizeof(struct in6_addr)];

    //addr.sin_addr.s_addr = inet_pton(domain, "127.0.0.1", buf);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // sin_addr - структура SOCKADDR_IN, которая хранит ip-адрес
    addr.sin_port = htons(1111);  // sin_port - хранит порт ижентификации программы поступающими данными
    addr.sin_family = domain;  // sin_family - хранит семейство протоколов. Для интернет-протоколов указывается контанта AF_INET

    SOCKET sListen = socket(domain, SOCK_STREAM, NULL);  // создание сокета и с названием sListen, которому присовоен результат
                                                          // выполнения фунции socket с параметрами: AF_INET - семейство протоколов AF_INET
                                                          // SOCK_STREAM - протокол, устанавливающий соединение
                                                          // NULL - третий параметр не нужен.
    
    int size_addr = sizeof(addr);

    bind(sListen, (SOCKADDR*)&addr, size_addr);  // функция, для привязки адреса сокету.
                                               // sListen - предварительно
                                               // созданный сокет
                                               // (SOCKADDR*)&addr - указатель на структуру SOCKADDR
                                               // sf_addr - размер структуры SOCKADDR

    listen(sListen, SOMAXCONN);  // sListen - сокет, по которому функция определит, по каком порту нужно начать прослушивание
                                 // SOMAXCONN - максимальное количество запросов, ожидающих обработки
                                 // можно написать точное количество запросов, например 3. В этом случае встанут в очередь 3 запроса, а остальные получат ошибку

    SOCKET newConnection;  // создан новый сокет

    for (int i = 0; i < 100; i++)
    {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &size_addr);  // это функция, которая используется сервером для принятия связи на сокет

        if (newConnection == 0)
        {
            std::cout << "Error connection." << std::endl;
        }
        else
        {
            std::cout << "Client #" << i + 1 << " connected." << std::endl; 
            
            std::string msg = "Welcome to the chat! Press enter twice to start a dialogue.";
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
