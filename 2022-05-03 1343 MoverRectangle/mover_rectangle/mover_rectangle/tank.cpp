#include "tank.h"

Tank::Tank(WindowStruct & m, MoverObject & t) : map(&m), tank(&t) 
{
    if (tank->num_fig_height % 2 == 0)
    {
        top_lines = tank->num_fig_height / 2 - 1;  // если высота делится на 2 без остатка, то она должна быть на 1 меньше, чтобы уместить орудие в размере танка при повороте башни
    }
    else
    {
        top_lines = tank->num_fig_height / 2;  // иначе орудие будет иметь нормальную длину
    }

    middle_line = tank->num_fig_width / 2;  // отступ от центра танка до края по горизонтали
    max_pixels_map = map->width_window * map->height_window - 1;  // максимальный пиксель танка

    if (tankDrawing() == false)
        throw std::runtime_error("CONTACT WITH OBJECT OR TO GOING OUT OF THE MAP!");
}

bool Tank::tankDrawing()
{
    int start_pixel = tank->center_obj - middle_line - map->width_window * top_lines;  // начальный пиксель танка
    int end_pixels = start_pixel + tank->num_fig_height * map->width_window + tank->num_fig_width - 1;  // последний пиксель танка
    int top_tank_pixels = tank->center_obj - tank->num_fig_height / 2 * map->width_window; // отступ от центра танка до края по вертикали
    int top_lines_window = top_tank_pixels / map->width_window;
    int top_pixels_window = top_lines_window * map->width_window;
    int down_pixels_window = (top_lines_window + tank->num_fig_height + 1) * map->width_window - 1;
    int a;
    int id;
    std::vector<int> nt;
    std::vector<int> it;
    
    if (start_pixel >= 0 && end_pixels <= max_pixels_map && 
        !(top_pixels_window > start_pixel && top_pixels_window < end_pixels) &&
        !(down_pixels_window < end_pixels))
    {
        nt = nums_tank;
        it = id_tank;
        nums_tank.clear();
        id_tank.clear();

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

                if (a == middle_line && start_pixel + a <= tank->center_obj)  // установка номера клетки и идентификатора орудия танка
                {
                    nums_tank.push_back(Gun);
                    id_tank.push_back(start_pixel + a);
                }

                if (start_pixel + a != tank->center_obj)  // установка номера клетки и идентификатора танка
                {
                    if (a == middle_line && start_pixel + a <= tank->center_obj)
                        continue;

                    nums_tank.push_back(TankUser);
                    id_tank.push_back(start_pixel + a);
                }
            }
        }
    }
    else
        return false;

    bool check_drawing_tank = true;

    for (int i = 0; i < id_tank.size(); i++)
    {
        if (map->map[id_tank[i]] == StatObj /* || map->map[id_tank[i]] == TankUser ||
            map->map[id_tank[i]] == Gun*/)
        {
            check_drawing_tank = false;  // соприкосновение танка с другими объектами на карте есть
            nums_tank = nt;
            id_tank = it;
        }
    }

    if (check_drawing_tank == true)
    {
        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];  // копирование копии карты в оригинальную карту
        }

        return true;
    }
    else
        return false;
}

void Tank::copyArr(int & i, const int & length_arr, std::vector<int> & arr_id) const
{
    for (; i < length_arr; i++)
    {
        arr_id.push_back(id_tank[i]);  // копия массива для обнуления перемещенных пикселей
    }
}

void Tank::clearItems(std::vector<int> & arr_id)
{
    for (int i = 0; i < arr_id.size(); i++)
    {
        map->map[arr_id[i]] = 0;  // обнуление элементов карты, на котрых уже нет танка
    }
}

bool Tank::calculate(sf::Event & event)
{
    std::vector<int> arr_id;    // массив с обнуляемыми id

    if (event.key.code == sf::Keyboard::W)  // поворот орудия вперед
    {
        

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
        int i = tank->num_fig_width * (tank->num_fig_height - 1);
        int length_arr = tank->num_fig_width * tank->num_fig_height;

        copyArr(i, length_arr, arr_id);

        tank->center_obj -= map->width_window;

        if (!tankDrawing())
        {
            tank->center_obj += map->width_window;

            return false;
        }

        clearItems(arr_id);

        return true;
    }
    if (event.key.code == sf::Keyboard::Down)  // движение назад
    {
        int i = 0;
        int length_arr = tank->num_fig_width;

        copyArr(i, length_arr, arr_id);

        tank->center_obj += map->width_window;

        if (!tankDrawing())
        {
            tank->center_obj -= map->width_window;

            return false;
        }

        clearItems(arr_id);

        return true;
    }

    return false;
}