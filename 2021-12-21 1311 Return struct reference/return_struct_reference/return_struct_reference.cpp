#include <iostream>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

const free_throws& clone1(free_throws& ft)  // �������
{
    free_throws newguy;
    newguy = ft;    // ����������� ��������� �� ������ � ��������� ���������
    return newguy;  // ���������� ������� ��������� ���������� �� ��������� ��������� ���������� (�� �������), ������� ���� ���������� ����� ���������� ������ �������
}

int main()
{
    free_throws ft = { "Sasha", 1, 2, 3.1 };

    std::cout << clone1(ft).name << std::endl; // ������ ��������� ��������� ����������

    return 0;
}