#include <iostream>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

const free_throws& cloneStruct(free_throws& ft)  // �������
{
    free_throws newguy;
    newguy = ft;    // ����������� ������
    return newguy;  // ���������� ������� ��������� ���������� �� ��������� ��������� ����������, ������� ���� ���������� ����� ���������� ������ �������
}

int main()
{
    free_throws ft = { "Sasha", 1, 2, 3.1 };

    const free_throws& ft2 = cloneStruct(ft);      // ��������� ������ �� ����� ���������

    std::cout << ft2.name << std::endl;        // ����� �������� ����� name ���������

    return 0;
}
