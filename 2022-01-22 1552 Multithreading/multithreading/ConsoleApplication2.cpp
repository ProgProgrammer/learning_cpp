#include <iostream>
#include <thread>
#include <chrono>

const int threads = 100;  // количество потоков

void hello(int elem, int timeout)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));  // тайм аут для того, чтобы показать, что многопоточность работает
    std::cout << elem + 1 << ") Hello, world!" << std::endl;
}

int main()
{
    std::thread arr[threads];

    for (int i = 0; i < threads; i++)
    {
        arr[i] = std::thread(hello, i, threads - i);
    }

    for (int i = 0; i < threads; i++)
    {
        arr[i].join();
    }

    system("pause");

    return 0;
}