#include <iostream>

std::string* buildstr() // �������, ����������� ���������
{
    std::string* pstr = new std::string; // ��������� �� ����, ������� ����� ���������

    *pstr = "Hello, world!";

    return pstr; // ������� ���������
}

int main()
{
    std::string* ps = buildstr(); // �������� ��������� �� ������� � ���������� ��� ������������� �������� ���������

    std::cout << *ps << std::endl;

    delete[] ps; // ������������ ������

    return 0;
}