#include <iostream>
#include <omp.h>

int count;
int its_me;

void one_task()  // Написать многопоточную программу, используя директивы OpenMP
{
    std::cout << "10 threads:" << std::endl;
#pragma omp parallel num_threads(10)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "1 thread:" << std::endl;
#pragma omp parallel num_threads(1)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "5 threads:" << std::endl;
#pragma omp parallel num_threads(5)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
    std::cout << std::endl << "10 threads:" << std::endl;
#pragma omp parallel num_threads(10)
    {
        count = omp_get_num_threads();
        its_me = omp_get_thread_num();
        printf("Hello, OpenMP! I am %d of %d\n", its_me, count);
    }
}

int main()
{
    one_task();
    std::cout << std::endl << "Hello, world!" << std::endl;
}