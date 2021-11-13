#include <iostream>
#include <array>
#include <string>

void fill(const int* Seasons, std::array<double, *Seasons>* pa, const std::array<std::string, *Seasons>* sn) 
{ 
    std::cout << *Seasons << " " << (*pa)[0] << (*sn)[0] << std::endl;
}

int main()
{
    const int Seasons = 4;

    const std::array<std::string, Seasons> Snames = { "Spring", "Summer", "Fall", "Winter" };
    std::array<double, Seasons> expenses;

    fill(&Seasons, &expenses, &Snames);
}
