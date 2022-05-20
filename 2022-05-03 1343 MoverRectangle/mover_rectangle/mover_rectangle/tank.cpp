#include "tank.h"

Tank::Tank(WindowStruct & m, MoverObject & t) : map(&m), tank(&t) 
{
    int top_lines;  // половина строк сверху матрицы для вычисления высоты до начала матрицы танка

    if (tank->num_fig_height % 2 == 0)
    {
        top_lines = tank->num_fig_height / 2 - 1;  // если высота делится на 2 без остатка, то она должна быть на 1 меньше, чтобы уместить орудие в размере танка при повороте башни
    }
    else
    {
        top_lines = tank->num_fig_height / 2;  // иначе орудие будет иметь нормальную длину
    }

    int middle_line = tank->num_fig_width / 2;  // отступ от центра танка по середине
    int start_pixel = tank->center_obj - middle_line - map->width_window * top_lines;  // начальный пиксель танка
    max_pixels_map = map->width_window * map->height_window - 1;
    int a;
    int id;

    for (int i = 0; i < tank->num_fig_height; i++)  // создание танка в массивах-посредниках
    {
        a = 0;
        id = 0;

        for (; a < tank->num_fig_width; a++)
        {
            if (i > id)
            {
                start_pixel += map->width_window;  // переход на следующую строку матрицы
                id = i;
            }

            if (start_pixel + a != tank->center_obj)  // установка номера клетки и идентификатора танка
            {
                nums_tank.push_back(TankUser);
                id_tank.push_back(start_pixel + a);
            }
            
            if (a == middle_line && start_pixel + a <= tank->center_obj)  // установка номера клетки и идентификатора орудия танка
            {
                nums_tank.push_back(Gun);
                id_tank.push_back(start_pixel + a);
            }
        }
    }

    bool result = checkMap();  // проверка танка на соприкосновение с другими объектами на карте

    if (result == false)
        throw std::runtime_error("CONTACT WITH OBJECT!");
    else
    {
        copyMap();
    }
}

bool Tank::checkMap() const
{
    for (int i = 0; i < id_tank.size(); i++)
    {
        if (map->map[id_tank[i]] == StatObj || map->map[id_tank[i]] == TankUser ||
            map->map[id_tank[i]] == Gun)
            return false;
    }

    return true;
}

void Tank::copyMap()
{
    for (int i = 0; i < id_tank.size(); i++)
    {
        map->map[id_tank[i]] = nums_tank[i];  // копирование копии карты в оригинальную карту
    }
}

bool Tank::calculate(sf::Event & event)
{
    if (event.key.code == sf::Keyboard::W)  // поворот орудия вперед
    {
        if (nums_tank[middle_horizontal_top + 1] != tank->rotated_obj)
        {
            for (int i = 0; i < nums_tank.size(); i++)
            {
                if (nums_tank[i] == tank->rotated_obj && i != middle_id)
                {
                    nums_tank[i] = tank->num_mover_obj;  // замена в копии карты всех значений, отвечающих за орудие танка на его обычные значения,кроме среднего значения
                }
            }

            nums_tank[middle_horizontal_top] = tank->rotated_obj;  // замена в копии карты обычного значения на значение орудия
        }
        else
            return false;

        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];  // копирование копии карты в оригинальную карту
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::S)  // поворот орудия назад
    {
        if (nums_tank[middle_horizontal_down + 1] != tank->rotated_obj)
        {
            for (int i = 0; i < nums_tank.size(); i++)
            {
                if (nums_tank[i] == tank->rotated_obj && i != middle_id)
                {
                    nums_tank[i] = tank->num_mover_obj;  // замена в копии карты всех значений, отвечающих за орудие танка на его обычные значения
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
    if (event.key.code == sf::Keyboard::A)  // поворот орудия влево
    {
        if (nums_tank[middle_vertical_left] != tank->rotated_obj)
        {
            for (int i = 0; i < nums_tank.size(); i++)
            {
                if (nums_tank[i] == tank->rotated_obj && i != middle_id)
                {
                    nums_tank[i] = tank->num_mover_obj;  // замена в копии карты всех значений, отвечающих за орудие танка на его обычные значения
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
    if (event.key.code == sf::Keyboard::D)  // поворот орудия вправо
    {
        if (nums_tank[middle_vertical_right] != tank->rotated_obj)
        {
            for (int i = 0; i < nums_tank.size(); i++)
            {
                if (nums_tank[i] == tank->rotated_obj && i != middle_id)
                {
                    nums_tank[i] = tank->num_mover_obj;  // замена в копии карты всех значений, отвечающих за орудие танка на его обычные значения
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
    if (event.key.code == sf::Keyboard::Up)  // движение вперед
    {
        for (int i = 0; i < tank->num_fig_width; i++)
        {
            if (id_tank[i] - map->width_window < 0)
                return false;

            if (map->map[id_tank[i] - map->width_window] == StatObj)
                return false;
        }

        for (int i = 0; i < nums_tank.size(); i++)
        {
            map->map[id_tank[i]] = EmptyObject;
            id_tank[i] = id_tank[i] - map->width_window;
        }

        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::Down)  // движение назад
    {
        int id_down = tank->num_fig_width * tank->num_fig_height - tank->num_fig_width;
        int length = tank->num_fig_width * tank->num_fig_width;

        for (int i = id_down; i < length; i++)
        {
            if (id_tank[i] + map->width_window >= map->width_window * map->width_window)
                return false;

            if (map->map[id_tank[i] + map->width_window] == StatObj)
                return false;
        }

        for (int i = 0; i < nums_tank.size(); i++)
        {
            map->map[id_tank[i]] = EmptyObject;
            id_tank[i] = id_tank[i] + map->width_window;
        }

        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];
        }

        return true;
    }
    /*if (event.key.code == sf::Keyboard::Left)  // движение влево
    {
        for (int i = 0; i < tank->num_fig_height; i + tank->num_fig_width)
        {
            /*if (id_tank[i] - 1 >= map->width_window * map->width_window)
                return false;*/

                /*if (id_tank[i] - 1 == StatObj)
                return false;
        }

        for (int i = 0; i < nums_tank.size(); i++)
        {
            map->map[id_tank[i]] = EmptyObject;
            id_tank[i] = id_tank[i] + map->width_window;
        }

        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];
        }

        return true;
    }*/

    return false;
}