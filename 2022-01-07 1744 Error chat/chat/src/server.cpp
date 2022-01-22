#pragma comment(lib, "ws2_32.lib")  // для получения доступа к некоторым функциям (линковка)
#include <iostream>
#include <string>
#include <winsock2.h>  // библиотека для работы с сетью
#include <ws2tcpip.h>

#pragma warning(disable: 4996)  // в этом коде эта ошибка компиляции выходить не будет (устаревшая функция inet_addr())

const int MAX_CLIENT_COUNT = 100;
static HANDLE CLIENT_THREADS[MAX_CLIENT_COUNT];   // массив потоков
static SOCKET CLIENT_SOCKETS[MAX_CLIENT_COUNT];   // массив сокетов
bool FLAG_STOP_CLIENT[MAX_CLIENT_COUNT] = {false};

namespace message_namespace
{
    struct ConnectionParams
    {
        SOCKET sListen;
        SOCKADDR_IN addr;
        int size_addr;
    };

    bool sendMessage(SOCKET newConnection, const char * msg, int msg_size)
    {
        int result = send(newConnection, (char*)&msg_size, sizeof(int), NULL);  // отправляем РАЗМЕР СООБЩЕНИЯ (в виде однобайтового числа)
        if(result < 0)
        {
            std::cout << "Thread " << __func__ << ": send(message size) returns error=" << result << "\n";
            return false;
        }

        result = send(newConnection, msg, msg_size, NULL);                  // затем отправляем САМО СООБЩЕНИЕ указанного на предыдущем шаге размера
        if(result < 0)
        {
            std::cout << "Thread " << __func__ << ": send(message data) returns error=" << result << "\n";
            return false;
        }

        return true;
    }

    void clientHandler(int client_index)
    {
        int msg_size;

        while (int result = recv(CLIENT_SOCKETS[client_index], (char*)&msg_size, sizeof(int), NULL))  // функция для получения РАЗМЕРА СООБЩЕНИЯ
        {
            if(FLAG_STOP_CLIENT[client_index] == true)
            {
                std::cout << "Thread " << __func__ << "Request to stop client #" << client_index << "\n";
                break;
            }

            if(result < 0)
            {
                std::cout << "Thread " << __func__ << " client_index=" << client_index << ": recv return error=" << result << "\n";
                break;
            }

            std::string msg_buffer(msg_size + 1, '\0');
            char* pRawString = &msg_buffer[0];
            
            result = recv(CLIENT_SOCKETS[client_index], pRawString, msg_size, NULL);  // функция для получения САМОГО СООБЩЕНИЯ размера полученного выше
            if(result < 0)
            {
                std::cout << "Thread " << __func__ << " client_index=" << client_index << ": recv return error=" << result << "\n";
                break;
            }
            
            // отправка сообщения всем клиентам кроме отправителя
            for (int i = 0; i < MAX_CLIENT_COUNT; i++)
            {
                if (i == client_index)
                {
                    continue;
                }

                bool success = sendMessage(CLIENT_SOCKETS[i], pRawString, msg_size + 1);
                if(!success)
                {
                    std::cout << "Thread " << __func__ << " client_index=" << client_index << ": sendMessage return false\n";
                    break;
                }
            }
        }

        FLAG_STOP_CLIENT[client_index] = false;
        CloseHandle(CLIENT_THREADS[client_index]); // BUG. It can be unsafe. But it is easiest way to implement.
        closesocket(CLIENT_SOCKETS[client_index]);
        CLIENT_SOCKETS[client_index] = 0;
    }

    void createConnections(ConnectionParams & params)
    {
        SOCKET newConnection;  // создан новый сокет
        
        while ((newConnection = accept(params.sListen, (SOCKADDR*)&params.addr, &params.size_addr)))
        {
            if (newConnection == 0)
            {
                std::cout << "Error connection." << std::endl;
            }
            else
            {
                int available_client_index = -1;
                for(int client_index = 0; client_index < MAX_CLIENT_COUNT; client_index++)
                {
                    if(CLIENT_SOCKETS[client_index] == 0)
                    {
                        available_client_index = client_index;
                        break;
                    }
                }

                if(available_client_index >= 0)
                {
                    std::cout << "Client #" << available_client_index << " connected." << std::endl;

                    std::string msg = "Welcome to the chat! Press enter twice to start a dialogue.\n";

                    bool success = sendMessage(newConnection, msg.c_str(), msg.size() + 1);
                    if(!success)
                    {
                        std::cout << "Thread " << __func__ << ": sendMessage return false\n";
                        break;                    
                    }
                    
                    CLIENT_SOCKETS[available_client_index] = newConnection;

                    CLIENT_THREADS[available_client_index] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler, (LPVOID)(available_client_index), NULL, NULL);
                }
                else
                {
                    std::cout << "Reached limit of connected clients\n";
                    closesocket(newConnection);
                }
            }
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

    const std::string cmd_close_all = "cl_all_cons";
    const std::string cmd_close_connection_by_num = "cl_con";
    const std::string cmd_close_app = "close_app";

    std::cout << "To close all connections, type the word \"" << cmd_close_all << "\" and \"Enter\" keys." << std::endl;
    std::cout << "To close all connections, type the word \"" << cmd_close_connection_by_num << "\" and \"Enter\", and then enter the connection number." << std::endl;
    std::cout << "To exit the application, type the word \"" << cmd_close_app << "\" and press the \"Enter\" key." << std::endl << std::endl;

    message_namespace::ConnectionParams params;

    params.sListen = sListen;
    params.addr = addr;
    params.size_addr = size_addr;

    HANDLE hCreateConnectionThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)message_namespace::createConnections, &params, NULL, NULL);

    std::string command;

    while (std::getline(std::cin, command))
    {
        if (command == cmd_close_all)
        {
            for(bool& client_index : FLAG_STOP_CLIENT)
            {
                client_index = true;
            }

            std::cout << "All connections are closed." << std::endl;
        }
        else if (command == cmd_close_connection_by_num)
        {
            std::cout << "Enter the client index[0.." << MAX_CLIENT_COUNT-1 << "]: ";
            int client_index;
            std::cin >> client_index;

            if (client_index > 0 && client_index < MAX_CLIENT_COUNT)
            {
                FLAG_STOP_CLIENT[client_index] = true;
            }
            else
            {
                std::cout << "There is no such connection." << std::endl;
            }
        }
        else if (command == cmd_close_app)
        {
            for(bool& client_index : FLAG_STOP_CLIENT)
            {
                client_index = true;
            }
            break;
        }
    }

    CloseHandle(hCreateConnectionThread);
    WSACleanup();
    std::cout << "The program has ended." << std::endl;
    system("pause");

    return 0;
}
