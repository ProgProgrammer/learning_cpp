#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct objectStruct
{
    int weight;
    int height;
    int step;
    int color;
};

struct moverObject  // ��������� ��� �������� ���������� � ������������� �������
{
    int num_fig_width;   // ������ ������������� ������� � �����������
    int num_fig_height;  // ������ ������������� ������� � �����������
    int num_mover_obj;   // ����� ����������� �������������� �������
    int rotated_obj;     // ����� �������������� ����������� �������������� �������
};

struct windowStruct
{
    int weight;
    int height;
    int color;
    std::string name_window;              // �������� ����
    std::vector<int> map;                 // ������ � ������ ��������
    std::vector<objectStruct> objsArray;  // ������ ��������
    int length_window;
};

class Map
{
public:
    virtual bool createWindow(sf::RenderWindow * window) = 0;
    virtual bool updateWindow() = 0;
};

class MoverInterface
{
public:
    virtual bool CalculateXU() = 0;
    virtual bool CalculateXD() = 0;
    virtual bool CalculateYL() = 0;
    virtual bool CalculateYR() = 0;
};