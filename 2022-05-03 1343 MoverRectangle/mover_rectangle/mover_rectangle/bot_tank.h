#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "class_mover_interface.h"
#include "timer.h"
#include "create_map.h"
#include "tank.h"

class BotTank : public Tank
{
private:
    WindowStruct* map = nullptr;  // �����
    MoverObject* tank = nullptr;  // ����
    Tank* main_tank = nullptr;  // ������ �������� �����;
    sf::RenderWindow* window;
    CreateMap* copy_map;
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    int top_lines;  // �������� ����� ������ ������� ��� ���������� ������ �� ������ ������� �����
    int middle_line;  // ������ �� ������ ����� �� ��������
    int gun_axis;  // ������������� ��� ������ � ������� nums_tank
    int max_pixels_map;
    bool flag_ready_to_destroy = false;
    std::vector<int> nums_tank;  // ������ � ����������� � �������� �����
    std::vector<int> id_tank;    // ������ � ���������������� ����� �� �����
    std::string gun = "gun";
    bool moving_gun = true;  // �������� �� ��, ���� �� �������� ��������� ������ ��� ���
    bool destroyedObj(int i);  // ������ ����������� �������

public:
    BotTank(WindowStruct& map, MoverObject& tank, sf::RenderWindow* window, CreateMap& cm, Tank * main_tank, std::vector<BotTank*> & bot_tanks);
    virtual bool calculate(sf::Event & event) override;
};