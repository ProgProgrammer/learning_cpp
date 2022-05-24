#include "bot_tank.h"
#include <random>

int getRandomInt(int & min, int & max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

    auto random_integer = uni(rng);

    return random_integer;
}

BotTank::BotTank(WindowStruct& m, MoverObject& t, sf::RenderWindow* w, CreateMap& cm, Tank* mt, std::vector<BotTank*> & bt) : Tank(m, t, w, cm, bt),
                                                                                                                            map(&m), tank(&t), window(w), copy_map(&cm), main_tank(mt)
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

    //if (tankDrawing() == false)
        //throw std::runtime_error("CONTACT WITH OBJECT OR TO GOING OUT OF THE MAP!");
}

bool BotTank::destroyedObj(int i)
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
        std::vector<int> id_tank;
        Tank * bt;
        bool bal = true;

        id_tank = main_tank->returnIdTank();
        bt = main_tank;

        for (int b = 0; b < id_tank.size(); b++)
        {
            if (i == id_tank[b])
            {
                for (int c = 0; c < id_tank.size(); c++)
                {
                    map->map[id_tank[c]] = DestroyedObj;
                }

                bal = false;

                break;
            }
        }

        if (copy_map->updateWindow(window))
        {
            for (int i = 0; i < id_tank.size(); i++)
            {
                map->map[id_tank[i]] = EmptyObject;
            }

            main_tank->destroy();
            main_tank = nullptr;

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1000ms / 4);
        }

        return true;
    }

    return false;
}

bool BotTank::calculate(sf::Event & event)
{
    int min = 1;
    int max = 9;
    int res;
    nums_tank = numsTank();
    id_tank = idTank();
    
    while (true)
    {
        res = getRandomInt(min, max);

        if (res == 1)  // движение вперед
        {
            tank->center_obj -= map->width_window;

            if (!tankDrawing())
            {
                tank->center_obj += map->width_window;

                return false;
            }

            position_gun = returnPosition();
            position_gun -= map->width_window;

            return true;
        }
        if (res == 2)  // движение назад
        {
            tank->center_obj += map->width_window;

            if (!tankDrawing())
            {
                tank->center_obj -= map->width_window;

                return false;
            }

            position_gun = returnPosition();
            position_gun += map->width_window;

            return true;
        }
        if (res == 3)  // движение влево
        {
            tank->center_obj -= 1;

            if (!tankDrawing())
            {
                tank->center_obj += 1;

                return false;
            }

            position_gun = returnPosition();
            position_gun -= 1;

            return true;
        }
        if (res == 4)  // движение вправо
        {
            tank->center_obj += 1;

            if (!tankDrawing())
            {
                tank->center_obj -= 1;

                return false;
            }

            position_gun = returnPosition();
            position_gun += 1;

            return true;
        }
        if (res == 5)  // поворот орудия вперед
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
            position_gun = returnPosition();
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::top;

            if (tankDrawing(gun))
                return true;
        }
        if (res == 6)  // поворот орудия назад
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
            position_gun = returnPosition();
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::bottom;

            if (tankDrawing(gun))
                return true;
        }
        if (res == 7)  // поворот орудия влево
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
            position_gun = returnPosition();
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::left;

            if (tankDrawing(gun))
                return true;

            return true;
        }
        if (res == 8)  // поворот орудия вправо
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
            position_gun = returnPosition();
            position_gun = id_tank[a];
            direction_gun = DirectionsGun::right;

            if (tankDrawing(gun))
                return true;

            return true;
        }

        if (res == 9)
        {
            if (shot())
                return true;
        }
    }

    return false;
}