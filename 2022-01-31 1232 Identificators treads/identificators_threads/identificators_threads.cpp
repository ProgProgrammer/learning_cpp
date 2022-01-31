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
    unsigned long const hardware_threads = std::thread::hardware_concurrency();  // ������� std::thread::hardware_concurrency() ���������� ���������� ���������� �������

    if (hardware_threads != 0)
    {
        std::cout << hardware_threads << std::endl;  // 12

        std::vector<std::thread> threads(hardware_threads);  // �������� ������� ��� ������� � ������������ ������

        for (int i = 0; i < hardware_threads; i++)
        {
            threads[i] = std::thread(output, i);

            if (threads[i].joinable())
            {
                threads[i].join();
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
