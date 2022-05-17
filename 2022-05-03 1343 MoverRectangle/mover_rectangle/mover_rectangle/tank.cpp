#include "tank.h"

Tank::Tank(windowStruct & m, moverObject & t) : map(&m), tank(&t) { addedValues(); }

Tank::Tank(windowStruct * m, moverObject * t) : map(m), tank(t) { addedValues(); }

void Tank::addedValues()
{
    middle_horizontal_top = tank->num_fig_width / 2;  // ������� ����� �� ����� �����
    middle_horizontal_down = tank->num_fig_width * tank->num_fig_height - middle_horizontal_top - 1;  // ������� ����� ����� �����
    middle_id = tank->num_fig_width * tank->num_fig_height / 2;  // ���������� �������� �������� �����
    middle_vertical_left = tank->num_fig_width * middle_horizontal_top;   // ������� ����� ����� �����
    middle_vertical_right = tank->num_fig_width * (middle_horizontal_top * 2) - 1;  // ������� ����� ������ �����

    for (int i = 0; i < map->map.size(); i++)
    {
        if (map->map[i] == tank->num_mover_obj || map->map[i] == tank->rotated_obj)
        {
            nums_tank.push_back(map->map[i]);
            id_tank.push_back(i);
        }
    }
}

bool Tank::CalculateXU()
{

    if (nums_tank[middle_horizontal_top + 1] != tank->rotated_obj)
    {
        for (int i = 0; i < nums_tank.size(); i++)
        {
            if (nums_tank[i] == tank->rotated_obj && i != middle_id)
            {
                nums_tank[i] = tank->num_mover_obj;  // ������ � ����� ����� ���� ��������, ���������� �� ������ ����� �� ��� ������� ��������,����� �������� ��������
            }
        }

        nums_tank[middle_horizontal_top] = tank->rotated_obj;  // ������ � ����� ����� �������� �������� �� �������� ������
    }
    else
        return false;

    for (int i = 0; i < id_tank.size(); i++)
    {
        map->map[id_tank[i]] = nums_tank[i];  // ����������� ����� ����� � ������������ �����
    }

    return true;
}

bool Tank::CalculateXD()
{
    if (nums_tank[middle_horizontal_down + 1] != tank->rotated_obj)
    {
        for (int i = 0; i < nums_tank.size(); i++)
        {
            if (nums_tank[i] == tank->rotated_obj && i != middle_id)
            {
                nums_tank[i] = tank->num_mover_obj;  // ������ � ����� ����� ���� ��������, ���������� �� ������ ����� �� ��� ������� ��������
            }
        }

        nums_tank[middle_horizontal_down] = tank->rotated_obj;
    }
    else
        return false;

    for (int i = 0; i < id_tank.size(); i++)
    {
         map->map[id_tank[i]] = nums_tank[i];
    }

    return true;
}

bool Tank::CalculateYL()
{
    if (nums_tank[middle_vertical_left] != tank->rotated_obj)
    {
        for (int i = 0; i < nums_tank.size(); i++)
        {
            if (nums_tank[i] == tank->rotated_obj && i != middle_id)
            {
                nums_tank[i] = tank->num_mover_obj;  // ������ � ����� ����� ���� ��������, ���������� �� ������ ����� �� ��� ������� ��������
            }
        }

        nums_tank[middle_vertical_left] = tank->rotated_obj;
    }
    else
        return false;

    for (int i = 0; i < id_tank.size(); i++)
    {
        map->map[id_tank[i]] = nums_tank[i];
    }

    return true;
}

bool Tank::CalculateYR()
{
    if (nums_tank[middle_vertical_right] != tank->rotated_obj)
    {
        for (int i = 0; i < nums_tank.size(); i++)
        {
            if (nums_tank[i] == tank->rotated_obj && i != middle_id)
            {
                nums_tank[i] = tank->num_mover_obj;  // ������ � ����� ����� ���� ��������, ���������� �� ������ ����� �� ��� ������� ��������
            }
        }

        nums_tank[middle_vertical_right] = tank->rotated_obj;
    }
    else
        return false;

    for (int i = 0; i < id_tank.size(); i++)
    {
        map->map[id_tank[i]] = nums_tank[i];
    }

    return true;
}