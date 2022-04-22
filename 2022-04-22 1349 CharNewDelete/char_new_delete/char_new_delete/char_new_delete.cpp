#include "cd.h"

void Bravo(const Cd& disk)
{
    disk.Report();
}

int main()
{
    Cd c1("Beatles", "Capitol", 14, 35.5);
    Classic c2 = Classic("Piano Sonata in B flat, Fantasia in C", "Alfred Brendel", "Philips", 2, 57.17);

    Cd* pcd = &c1;

    std::cout << "Using object directly:" << std::endl;

    c1.Report();
    c2.Report();

    std::cout << "Using type cd * pointer to objects:" << std::endl;

    pcd->Report();
    pcd = &c2;
    pcd->Report();

    std::cout << "Calling a function with a Cd reference argument:" << std::endl;

    Bravo(c1);
    Bravo(c2);

    std::cout << "Testing assigment: " << std::endl;

    Classic copy;
    copy = c2;
    copy.Report();

    return 0;
}