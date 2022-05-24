#include "tank.h"
#include "bot_tank.h"

Tank::Tank(WindowStruct & m, MoverObject & t, sf::RenderWindow * w, CreateMap & cm, std::vector<BotTank*> bt) : map(&m), tank(&t), window(w), copy_map(&cm), bot_tanks(bt)
{
    if (tank->num_fig_height % 2 != 0 && tank->num_fig_width == tank->num_fig_height)
    {
        top_lines = tank->num_fig_height / 2;  // длина орудия
    }
    else
        throw std::runtime_error("WRONG PROPORTIONS!");

    middle_line = tank->num_fig_width / 2;  // отступ от центра танка до края по горизонтали
    gun_axis = tank->num_fig_width * tank->num_fig_height / 2;  // идентификатор оси орудия в массиве nums_tank
    max_pixels_map = map->width_window * map->height_window - 1;  // максимальный пиксель карты

    if (tankDrawing() == false)
        throw std::runtime_error("CONTACT WITH OBJECT OR TO GOING OUT OF THE MAP!");
}

bool Tank::tankDrawing(std::string obj)
{
    if (obj != gun)  // если двигается не орудие
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

            if (moving_gun == true)
            {
                nums_tank.clear();  // очистка массива с прошлым расположением танка, чтобы не дублироват танк
            }

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

                    if (moving_gun == true)
                    {
                        if (a == middle_line && start_pixel + a <= tank->center_obj)  // установка номера клетки и идентификатора орудия танка
                        {
                            nums_tank.push_back(tank->rotated_obj);
                            id_tank.push_back(start_pixel + a);
                        }

                        if (start_pixel + a != tank->center_obj)  // установка номера клетки и идентификатора танка
                        {
                            if (a == middle_line && start_pixel + a <= tank->center_obj)
                                continue;

                            nums_tank.push_back(tank->num_mover_obj);
                            id_tank.push_back(start_pixel + a);
                        }
                    }
                    else
                    {
                        id_tank.push_back(start_pixel + a);
                    }
                }
            }

            if (position_gun == 0)
            {
                position_gun = tank->center_obj - map->width_window * top_lines;
                direction_gun = DirectionsGun::top;
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
    else if (obj == gun)  // если двигается орудие
    {
        for (int i = 0; i < id_tank.size(); i++)
        {
            map->map[id_tank[i]] = nums_tank[i];  // копирование копии карты в оригинальную карту
        }

        return true;
    }
}

bool Tank::removeGun()
{
    for (int i = 0; i < nums_tank.size(); i++)
    {
        if (nums_tank[i] == Gun && i != gun_axis)
            nums_tank[i] = TankUser;
    }

    tankDrawing(gun);

    return true;
}

bool Tank::destroyedObj(int i)
{
    if (map->map[i] == StatObj)
    {
        map->map[i] = DestroyedObj;

        if (copy_map->updateWindow(window))
        {
            map->map[i] = EmptyObject;
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1000ms / 4);
        }

        return true;
    }
    else if (map->map[i] == TankUser || map->map[i] == Gun)
    {
        int num_tank;
        std::vector<int> id_tank;
        BotTank * bt;
        bool bal = true;

        for (int a = 0; a < bot_tanks.size(); a++)
        {
            if (bal == true)
            {
                id_tank = bot_tanks[a]->returnIdTank();
                bt = bot_tanks[a];

                for (int b = 0; b < id_tank.size(); b++)
                {
                    if (i == id_tank[b])
                    {
                        num_tank = a;

                        for (int c = 0; c < id_tank.size(); c++)
                        {
                            map->map[id_tank[c]] = DestroyedObj;
                        }

                        bal = false;

                        break;
                    }
                }
            }
        }

        if (copy_map->updateWindow(window))
        {
            for (int i = 0; i < id_tank.size(); i++)
            {
                map->map[id_tank[i]] = EmptyObject;
            }

            bot_tanks[num_tank]->destroy();
            bot_tanks[num_tank] = nullptr;

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1000ms / 4);
        }

        return true;
    }

    return false;
}

bool Tank::shot()  // стрельба из орудия
{
    using namespace std::chrono_literals;
    int i;

    if (direction_gun == DirectionsGun::top)
    {
        i = position_gun - map->width_window;

        while (i >= 0)
        {
            if (map->map[i + map->width_window] == Projectile)
                map->map[i + map->width_window] = EmptyObject;

            if (destroyedObj(i))
                break;

            map->map[i] = Projectile;
            i -= map->width_window;
            copy_map->updateWindow(window);

            std::this_thread::sleep_for(1000ms / 24);
        }
    }
    else if (direction_gun == DirectionsGun::bottom)
    {
        i = position_gun + map->width_window;

        while (i < map->map.size())
        {
            if (map->map[i - map->width_window] == Projectile)
                map->map[i - map->width_window] = EmptyObject;

            if (destroyedObj(i))
                break;

            map->map[i] = Projectile;
            i += map->width_window;
            copy_map->updateWindow(window);

            std::this_thread::sleep_for(1000ms / 24);
        }
    }
    else if (direction_gun == DirectionsGun::left)
    {
        i = position_gun - 1;
        int border_pixel = position_gun / map->width_window * map->width_window;

        while (i >= 0 && i >= border_pixel)
        {
            if (map->map[i + 1] == Projectile)
                map->map[i + 1] = EmptyObject;

            if (destroyedObj(i))
                break;

            map->map[i] = Projectile;
            i -= 1;
            copy_map->updateWindow(window);

            std::this_thread::sleep_for(1000ms / 24);
        }
    }
    else if (direction_gun == DirectionsGun::right)
    {
        i = position_gun + 1;
        int border_pixel = position_gun / map->width_window * map->width_window + map->width_window;

        while (i < map->map.size() && i < border_pixel)
        {
            if (map->map[i - 1] == Projectile)
                map->map[i - 1] = EmptyObject;

            if (destroyedObj(i))
                break;

            map->map[i] = Projectile;
            i += 1;
            copy_map->updateWindow(window);

            std::this_thread::sleep_for(1000ms / 24);
        }
    }

    if (direction_gun == DirectionsGun::top && map->map[i + map->width_window] == Projectile)
        map->map[i + map->width_window] = EmptyObject;
    else if (direction_gun == DirectionsGun::bottom && map->map[i - map->width_window] == Projectile)
        map->map[i - map->width_window] = EmptyObject;
    else if (direction_gun == DirectionsGun::left && map->map[i + 1] == Projectile)
        map->map[i + 1] = EmptyObject;
    else if (direction_gun == DirectionsGun::right && map->map[i - 1] == Projectile)
        map->map[i - 1] = EmptyObject;

    return true;
}

bool Tank::calculate(sf::Event & event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)  // движение вперед
        {
            tank->center_obj -= map->width_window;

            if (!tankDrawing())
            {
                tank->center_obj += map->width_window;

                return false;
            }

            position_gun -= map->width_window;

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

            position_gun += map->width_window;

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

            position_gun -= 1;

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

            position_gun += 1;

            return true;
        }
        if (event.key.code == sf::Keyboard::W)  // поворот орудия вперед
        {
            int a;

            if (removeGun())
            {
                for (int i = gun_axis - tank->num_fig_width;
                    i < gun_axis && i > 0;
                    i -= tank->num_fig_width)
                {
                    nums_tank[i] = Gun;
                    a = i;
                }
            }

            moving_gun = false;
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::top;

            if (tankDrawing(gun))
                return true;
        }
        if (event.key.code == sf::Keyboard::S)  // поворот орудия назад
        {
            int a;

            if (removeGun())
            {
                for (int i = gun_axis + tank->num_fig_width;
                    i > gun_axis && i < nums_tank.size();
                    i += tank->num_fig_width)
                {
                    nums_tank[i] = Gun;
                    a = i;
                }
            }

            moving_gun = false;
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::bottom;

            if (tankDrawing(gun))
                return true;
        }
        if (event.key.code == sf::Keyboard::A)  // поворот орудия влево
        {
            int a;

            if (removeGun())
            {
                for (int i = gun_axis; i > gun_axis - middle_line - 1; i--)
                {
                    nums_tank[i] = Gun;
                    a = i;
                }
            }

            moving_gun = false;
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::left;

            if (tankDrawing(gun))
                return true;

            return true;
        }
        if (event.key.code == sf::Keyboard::D)  // поворот орудия вправо
        {
            int a;

            if (removeGun())
            {
                for (int i = gun_axis; i < gun_axis + middle_line + 1; i++)
                {
                    nums_tank[i] = Gun;
                    a = i;
                }
            }

            moving_gun = false;
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::right;

            if (tankDrawing(gun))
                return true;

            return true;
        }

        if (event.key.code == sf::Keyboard::Space)
        {
            if (shot())
                return true;
        }
    }

    return false;
}

void Tank::destroy()
{
    flag_ready_to_destroy = true;
}

bool Tank::isReadyToDestroy()
{
    return flag_ready_to_destroy;
}
