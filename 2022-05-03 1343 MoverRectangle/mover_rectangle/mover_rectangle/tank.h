#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "class_mover_interface.h"
#include "timer.h"
#include "create_map.h"

class Tank : public MoverInterface
{
private:
    enum DirectionsGun
    {
        top,    // 0
        left,   // 1
        right,  // 2
        bottom  // 3
    };
    WindowStruct * map;  // �����
    MoverObject * tank;  // ����
    sf::RenderWindow * window;
    CreateMap * copy_map;
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    int top_lines;  // �������� ����� ������ ������� ��� ���������� ������ �� ������ ������� �����
    int middle_line;  // ������ �� ������ ����� �� ��������
    int gun_axis;  // ������������� ��� ������ � ������� nums_tank
    int max_pixels_map;
    std::vector<int> nums_tank;  // ������ � ����������� � �������� �����
    std::vector<int> id_tank;    // ������ � ���������������� ����� �� �����
    std::string gun = "gun";
    int position_gun = 0;  // ������� ����� ������
    int direction_gun;
    bool moving_gun = true;  // �������� �� ��, ���� �� �������� ��������� ������ ��� ���
    bool tankDrawing(std::string obj = "");  // ��������� �����
    bool removeGun();
    bool destroyedObj(int i);  // ������ ����������� �������
    bool shot();  // �������� �� ������

public:
    Tank() {}  // �������� ������� ������� ��� ����, ����� ������� �������� ����� �� ��������������� � ��������� � ������� �� ������� ��� �������������� ���������
    Tank(WindowStruct & map, MoverObject & tank, sf::RenderWindow * window, CreateMap & cm);
    virtual bool calculate(sf::Event & event) override;
};