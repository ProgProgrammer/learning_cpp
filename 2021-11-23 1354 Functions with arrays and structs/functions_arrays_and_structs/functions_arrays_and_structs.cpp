#include <iostream>
#include <string>

const int SLEN = 30;

struct student {
    char fullname[SLEN];
    char hobby[SLEN];
    int ooplevel;
};

int getinfo(student pa[], int n) // pa - имя не очень - не читаемо, проходится смотреть вниз в код метода, чтобы понять, что значит эта переменная
{                                // лушче, чтобы по названию переменной сразу было понятно что это такое, я бы назвал studentsArray или просто students
    std::string str;
    int i;

    for (i = 0; i < n; i++)
    {
        std::cout << i + 1 << " student." << std::endl;
        std::cout << "Entered full name student: ";

        if (std::getline(std::cin, str) && str.length() != 0)
        {
            strcpy_s(pa[i].fullname, 30, str.c_str());  // на заметку - тут ограничение в 30 символов. Наверное это нормально для твоей задачи, 
        }                                               // в другом коде может потребоваться неограниченное количество символов.
        else
        {
            break;
        }

        std::cout << "Entered hobby student: ";

        if (std::getline(std::cin, str))    // Что будет, если пользователь введет не верный hobby. Ветки else нет, программа продолжит дальше пытаться считывтать.
        {                                   // Это так и должно быть?
            strcpy_s(pa[i].hobby, 30, str.c_str());
        }

        std::cout << "Entered oop level: ";

        if (std::cin >> str)
        {
            pa[i].ooplevel = stoi(str);
        }

        std::cin.clear();
        std::cin.ignore();
    }

    return i;
}

void display1(student st)
{
    std::cout << "Name student: " << st.fullname << std::endl;
    std::cout << "Hobby: " << st.hobby << std::endl;
    std::cout << "Oop level: " << st.ooplevel << std::endl;
}

void display2(const student* st)
{
    std::cout << "Name student: " << st->fullname << std::endl;
    std::cout << "Hobby: " << st->hobby << std::endl;
    std::cout << "Oop level: " << st->ooplevel << std::endl;
}

void display3(const student pa[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Name student: " << pa[i].fullname << std::endl;
        std::cout << "Hobby: " << pa[i].hobby << std::endl;
        std::cout << "Oop level: " << pa[i].ooplevel << std::endl;
    }
}

int main()
{
    std::cout << "Enter class size: ";
    int class_size;
    std::cin >> class_size;

    while (std::cin.get() != '\n')
    {
        continue;
    }

    student* ptr_stu = new student[class_size];

    int entered = getinfo(ptr_stu, class_size);

    for (int i = 0; i < entered; i++)
    {
        display1(ptr_stu[i]);
        display2(&ptr_stu[i]);
    }

    display3(ptr_stu, entered);

    delete[] ptr_stu;

    std::cout << "Done" << std::endl;

    return 0;
}
