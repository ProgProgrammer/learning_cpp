#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

// �����:
enum colors
{
    Black,       // 0
    White,       // 1
    Red,         // 2
    Green,       // 3
    Blue,        // 4
    Yellow,      // 5
    Magenta,     // 6
    Cyan,        // 7
    Transparent  // 8
};

// ������ �������� �� �����:
enum Objects
{
    StatObj = 1,
    TankUser = 2,
    Gun = 3
};

struct ObjectStruct
{
    int weight;
    int height;
    int step;
    colors color;
};

struct MoverObject  // ��������� ��� �������� ���������� � ������������� �������
{
    int num_fig_width;   // ������ ������������� ������� � �����������
    int num_fig_height;  // ������ ������������� ������� � �����������
    int num_mover_obj;   // ����� ����������� �������������� �������
    int rotated_obj;     // ����� �������������� ����������� �������������� �������
};

struct WindowStruct
{
    int weight;
    int height;
    int color;
    std::string name_window;              // �������� ����
    std::vector<int> map;                 // ������ � ������ ��������
    std::vector<ObjectStruct> objsArray;  // ������ ��������
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
    virtual bool Calculate(sf::Event & event) = 0;
};