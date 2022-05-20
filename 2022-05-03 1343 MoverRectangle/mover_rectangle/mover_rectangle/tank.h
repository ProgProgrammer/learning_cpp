#pragma once
#include <iostream>
#include "class_mover_interface.h"

class Tank : public MoverInterface
{
private:
    WindowStruct * map;  // �����
    MoverObject * tank;  // ����
    int middle_horizontal_top;
    int middle_horizontal_down;
    int middle_id;
    int middle_vertical_left;
    int middle_vertical_right;
    int top_lines;  // �������� ����� ������ ������� ��� ���������� ������ �� ������ ������� �����
    int middle_line;  // ������ �� ������ ����� �� ��������
    int max_pixels_map;
    std::vector<int> nums_tank;  // ������ � ����������� � �������� �����
    std::vector<int> id_tank;    // ������ � ���������������� ����� �� �����
    bool tankDrawing();  // ��������� �����
    void copyArr(int & i, const int & length_arr, std::vector<int> & arr_id) const;
    void clearItems(std::vector<int> & arr_id);

public:
    Tank() {}  // �������� ������� ������� ��� ����, ����� ������� �������� ����� �� ��������������� � ��������� � ������� �� ������� ��� �������������� ���������
    Tank(WindowStruct & map, MoverObject & tank);
    virtual bool calculate(sf::Event & event) override;
};