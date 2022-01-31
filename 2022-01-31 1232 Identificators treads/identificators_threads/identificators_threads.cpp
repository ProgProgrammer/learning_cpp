#include <iostream>
#include <thread>
#include <vector>

template <class T>
void output(T i)
{
    std::cout << i + 1 << ") " << std::this_thread::get_id << std::endl;
}

int main()
{
    unsigned long const hardware_threads = std::thread::hardware_concurrency();  // функция std::thread::hardware_concurrency() возвращает количество аппаратных потоков

    if (hardware_threads != 0)
    {
        std::cout << hardware_threads << std::endl;  // 12

        std::vector<std::thread> threads(hardware_threads);  // создание массива для потоков в динамической памяти

        for (int i = 0; i < hardware_threads; i++)
        {
            threads[i] = std::thread(output, i);

            if (threads[i].joinable())  // проверка того, что поток создан
            {
                threads[i].join();  // ожидание завершения потока перед продолжением работы родительского потока
            }
        }
    }
    else
    {
        std::vector<std::thread> threads(2);

        for (int i = 0; i < 2; i++)
        {
            threads[i] = std::thread(output, i);

            if (threads[i].joinable())
            {
                threads[i].join();
            }
        }
    }

    return 0;
}
