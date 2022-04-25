#include "classes_mover_interface.h"
#include <vector>

bool check_num(int num)
{
    if (num > 0)
        return true;
    else
        return false;
}

int main()
{
    int x = 1;
    int y = 3;
    int v = 2;
    int x2 = 2;
    int y2 = 4;
    int v2 = 3;

    std::vector<MoverInterface *> mi;
    mi.push_back(new LineMover(x, y, v));
    mi.push_back(new RandomMover(x2, y2, v2));

    std::cout << "x = " << mi[0]->GetX() << std::endl;
    std::cout << "y = " << mi[0]->GetY() << std::endl;

    std::cout << std::endl;

    std::cout << "x = " << mi[1]->GetX() << std::endl;
    std::cout << "y = " << mi[1]->GetY() << std::endl;

    std::cout << std::endl;

    int timeStamp = 1;

    mi[0]->Calculate(timeStamp);
    std::cout << "x = " << mi[0]->GetX() << std::endl;
    std::cout << "y = " << mi[0]->GetY() << std::endl;

    std::cout << std::endl;

    mi[1]->Calculate(timeStamp);
    std::cout << "x = " << mi[1]->GetX() << std::endl;
    std::cout << "y = " << mi[1]->GetY() << std::endl;

    std::cout << std::endl;

    std::cout << "Enter your number > 0: ";
    std::cin >> timeStamp;

    if (check_num(timeStamp))
    {

        mi[0]->Calculate(timeStamp);
        std::cout << "x = " << mi[0]->GetX() << std::endl;
        std::cout << "y = " << mi[0]->GetY() << std::endl;

        std::cout << std::endl;

        mi[1]->Calculate(timeStamp);
        std::cout << "x = " << mi[1]->GetX() << std::endl;
        std::cout << "y = " << mi[1]->GetY() << std::endl;

        std::cout << std::endl;
    }
    else
        return 0;

    return 0;
}