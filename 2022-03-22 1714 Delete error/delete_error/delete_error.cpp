#include <iostream>
#include "strngbad.h"

void callme1(StringBad& rsb)
{
    std::cout << "String passed by reference:" << std::endl;
    std::cout << "\"" << rsb << "\"" << std::endl;
}

void callme2(StringBad sb)
{
    std::cout << "String passed by value:" << std::endl;
    std::cout << "\"" << sb << "\"" << std::endl;
}

int main()
{
    {
        std::cout << "Strating an inner block." << std::endl;

        StringBad headlinel1("Celery Stalks at Midnight");
        StringBad headlinel2("Lettuce Prey");
        StringBad sports("Spinach Leaves Bowl for Dollars");

        std::cout << "headline1: " << headlinel1 << std::endl;
        std::cout << "headline2: " << headlinel2 << std::endl;
        std::cout << "sports: " << sports << std::endl;

        callme1(headlinel1);

        std::cout << "headline1: " << headlinel1 << std::endl;

        callme2(headlinel2);

        std::cout << "headline2: " << headlinel2 << std::endl;
        std::cout << "Initialize one object to another:" << std::endl;

        StringBad sailor(sports);

        std::cout << "sailor: " << sailor << std::endl;
        std::cout << "Initialize one object to another:" << std::endl;

        StringBad knot(headlinel1);

        std::cout << "knot: " << knot << std::endl;
        std::cout << "Exiting the block." << std::endl;
    }

    std::cout << "End of main()" << std::endl;

    return 0;
}