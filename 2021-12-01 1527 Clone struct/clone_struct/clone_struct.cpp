#include <iostream>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

const free_throws& cloneStruct(free_throws& ft)  // НЕВЕРНО
{
    free_throws newguy;
    newguy = ft;    // копирование ссылки
    return newguy;  // невозможно вернуть временную переменную со значением локальной переменной, которая была уничтожена после завершения работы функции
}

int main()
{
    free_throws ft = { "Sasha", 1, 2, 3.1 };

    const free_throws& ft2 = cloneStruct(ft);      // получение ссылки на копию структуры

    std::cout << ft2.name << std::endl;        // вывод значение члена name структуры

    return 0;
}
