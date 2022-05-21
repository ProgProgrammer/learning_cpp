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
    max_pixels_map = map->width_window * map->height_window - 1;  // максимальный пиксель карты

    if (tankDrawing() == false)
        throw std::runtime_error("CONTACT WITH OBJECT OR TO GOING OUT OF THE MAP!");
}

bool Tank::tankDrawing()
{
    int start_pixel = tank->center_obj - middle_line - map->width_window * top_lines;  // начальный пиксель танка
    int end_pixel = start_pixel + (tank->num_fig_height - 1) * map->width_window + tank->num_fig_width - 1;  // последний пиксель танка
    int top_tank_pixels = tank->center_obj - tank->num_fig_height / 2 * map->width_window; // отступ от центра танка до края по вертикали
    int top_lines_window = top_tank_pixels / map->width_window;
    int top_pixels_window = top_lines_window * map->width_window;
    int down_pixels_window = (top_lines_window + tank->num_fig_height) * map->width_window - 1;
    int a;
    int id;
    std::vector<int> nt;
    std::vector<int> it;
    std::vector<int> copy_id_tank;
    
    if (start_pixel >= 0 && end_pixel <= max_pixels_map && 
        !(top_pixels_window > start_pixel && top_pixels_window < end_pixel) &&
        !(down_pixels_window < end_pixel))
    {
        nt = nums_tank;
        it = id_tank;

        if (id_tank.size() > 0)
        {
            copy_id_tank = id_tank;
        }

        nums_tank.clear();  // очистка массива с прошлым расположением танка, чтобы не дублироват танк
        id_tank.clear();    // очистка массива с прошлым расположением танка, чтобы не дублироват танк

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
        if (copy_id_tank.size() > 0)
        {
            for (int i = 0; i < copy_id_tank.size(); i++)
            {
                map->map[copy_id_tank[i]] = EmptyObject;  // чистит прошлое расположение танка
            }
        }

        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];  // копирование копии карты в оригинальную карту
        }

        return true;
    }
    else
        return false;
}

bool Tank::calculate(sf::Event & event)
{
    if (event.key.code == sf::Keyboard::Up)  // движение вперед
    {
        tank->center_obj -= map->width_window;

        if (!tankDrawing())
        {
            tank->center_obj += map->width_window;

            return false;
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::Down)  // движение назад
    {
        tank->center_obj += map->width_window;

        if (!tankDrawing())
        {
            tank->center_obj -= map->width_window;

            return false;
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::Left)  // движение влево
    {
        tank->center_obj -= 1;

        if (!tankDrawing())
        {
            tank->center_obj += 1;

            return false;
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::Right)  // движение вправо
    {
        tank->center_obj += 1;

        if (!tankDrawing())
        {
            tank->center_obj -= 1;

            return false;
        }

        return true;
    }
    if (event.key.code == sf::Keyboard::W)  // поворот орудия вперед
    {        

        return true;
    }
    if (event.key.code == sf::Keyboard::S)  // поворот орудия назад
    {

        return true;
    }
    if (event.key.code == sf::Keyboard::A)  // поворот орудия влево
    {

        return true;
    }
    if (event.key.code == sf::Keyboard::D)  // поворот орудия вправо
    {

        return true;
    }

    return false;
}