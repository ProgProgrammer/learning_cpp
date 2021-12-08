#include <iostream>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

const free_throws& clone1(free_throws& ft)  // НЕВЕРНО
{
    free_throws newguy;
    newguy = ft;    // копирование структуры по ссылке в локальную структуру
    return newguy;  // невозможно вернуть временную переменную со значением локальной переменной (со ссылкой), которая была уничтожена после завершения работы функции
}

int main()
{
    free_throws ft = { "Sasha", 1, 2, 3.1 };

    std::cout << clone1(ft).name << std::endl; // ошибка получения ссылочной переменной

    return 0;
}