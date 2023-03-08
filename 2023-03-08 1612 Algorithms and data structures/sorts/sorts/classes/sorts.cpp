#include "sorts.h";
#include <iostream>
#include <vector>

int sorts::RadixSort::velichRazr(int num, int id, const int count)
{
    while (id > 1)
    {
        num /= count;
        id--;
    }
    return num % count;
}

void sorts::RadixSort::startLoop(std::vector<int> arr, const int count)
{
    std::vector<std::vector<int>> dop_arr;
    std::vector<int> arr_row(count);
    std::vector<int> arr_col(count);
    
    for (int i = 0; i < count; ++i)
    {
        dop_arr.push_back(arr_row);
    }

    for (int id = 1; id < 4; ++id)
    {
        for (int i = 0; i < count; ++i)
        {
            arr_col[i] = 0;
        }

        for (int i = 0; i < count; ++i)
        {
            int a = velichRazr(arr[i], id, count);
            dop_arr[arr_col[a]][a] = arr[i];
            arr_col[a]++;
        }

        int temp = 0;

        for (int i = 0; i < count; ++i)
        {
            for (int j = 0; j < arr_col[i]; ++j)
            {
                arr[temp] = dop_arr[j][i];
                temp++;
            }
        }
    }
}

void sorts::SelectionSort::startLoop(std::vector<int> arr, const int count)
{
    int min = 0; // для записи минимального значения
    int buf = 0; // для обмена значениями 

    for (int i = 0; i < count; i++)
    {
        min = i; // запомним номер текущей ячейки, как ячейки с минимальным значением
        
        for (int j = i + 1; j < count; ++j)  // в цикле найдем реальный номер ячейки с минимальным значением
        {
            min = (arr[j] < arr[min]) ? j : min;
        }

        if (i != min)  // cделаем перестановку этого элемента, поменяв его местами с текущим
        {
            buf = arr[i];
            arr[i] = arr[min];
            arr[min] = buf;
        }
    }
}

void sorts::HeapSort::heapify(std::vector<int> arr, int count, int id)
{
    int largest = id;   // Инициализируем наибольший элемент как корень    
    int l = 2 * id + 1; // левый = 2*i + 1
    int r = 2 * id + 2; // правый = 2*i + 2
        
    if (l < count && arr[l] > arr[largest])  // Если левый дочерний элемент больше корня
        largest = l;

    if (r < count && arr[r] > arr[largest])  // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
        largest = r;
        
    if (largest != id)                       // Если самый большой элемент не корень
    {
        std::swap(arr[id], arr[largest]);        
        heapify(arr, count, largest);        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
    }
}

void sorts::HeapSort::startLoop(std::vector<int> arr, const int count)
{    
    for (int i = count / 2 - 1; i >= 0; i--)  // Построение кучи (перегруппируем массив)
        heapify(arr, count, i);
    
    for (int i = count - 1; i >= 0; i--)  // Один за другим извлекаем элементы из кучи
    {        
        std::swap(arr[0], arr[i]);  // Перемещаем текущий корень в конец        
        heapify(arr, i, 0);         // вызываем процедуру heapify на уменьшенной куче
    }
}