#pragma comment(lib, "ws2_32.lib")  // для получения доступа к некоторым функциям (линковка)
#include <iostream>
#include <string>
#include <winsock2.h>  // библиотека для работы с сетью
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

static HANDLE CLIENT_THREADS[100];  // массив потоков
static SOCKET CLIENT_CONNECTIONS[100];   // массив сокетов
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
        send(newConnection, (char*)&msg_size, sizeof(int), NULL);  // функция для отправки данных (размер данных)
        send(newConnection, msg, msg_size, NULL);                  // функция для отправки данных (само сообщение)
    }

    void ClientHandler(int client_index)
    {
        int msg_size;

        while (recv(CLIENT_CONNECTIONS[client_index], (char*)&msg_size, sizeof(int), NULL))  // функция для получения данных
        {
            char* msg = new char[msg_size + 1];
            msg[msg_size] = '\0';

            recv(CLIENT_CONNECTIONS[client_index], msg, msg_size, NULL);  // функция для получения данных

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
        SOCKET newConnection;  // создан новый сокет

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
    // WSAStartup - функция, для загрузки библиотеки
    WSAData wsaData; // создание структуры

    WORD DLLVersion = MAKEWORD(2, 1);  // запрашиваемая версия библиотеки winsock - нужна для того, чтобы загрузить библиотеку
    int res = WSAStartup(DLLVersion, &wsaData);  // загружаем библиотеку

    if (res != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;  // нужна для хранения интернет протоколов и адреса

    int domain = AF_INET;  // семейство используемых протоколов. В данном случае, AF_INET.
    //unsigned char buf[sizeof(struct in6_addr)];

    //addr.sin_addr.s_addr = inet_pton(domain, "127.0.0.1", buf);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // sin_addr - структура SOCKADDR_IN, которая хранит ip-адрес
    addr.sin_port = htons(1111);  // sin_port - хранит порт ижентификации программы поступающими данными
    addr.sin_family = domain;  // sin_family - хранит семейство протоколов. Для интернет-протоколов указывается контанта AF_INET

    SOCKET sListen = socket(domain, SOCK_STREAM, NULL);   // создание сокета и с названием sListen, которому присвоен результат
                                                          // выполнения фунции socket с параметрами: AF_INET - семейство протоколов AF_INET
                                                          // SOCK_STREAM - протокол, устанавливающий соединение (потоковый тип создаваемого сокета)
                                                          // NULL - при таком значении выбор транспортного протокола происходит по умолчанию.
                                                          // TCP - для потоковых сокетов, как здесь.

    int size_addr = sizeof(addr);

    bind(sListen, (SOCKADDR*)&addr, size_addr);  // функция, для привязки адреса сокету.
                                                 // sListen - предварительно
                                                 // созданный сокет
                                                 // (SOCKADDR*)&addr - указатель на структуру SOCKADDR
                                                 // sf_addr - размер структуры SOCKADDR

    listen(sListen, SOMAXCONN);  // listen() - функция ожидания подключений.
                                 // sListen - сокет, по которому функция определит, по каком порту нужно начать прослушивание.
                                 // SOMAXCONN - максимальное количество запросов, ожидающих обработки. По-умолчанию, равен 128.
                                 // можно написать точное количество запросов, например 3. В этом случае встанут в очередь 3 запроса, а остальные получат ошибку

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
