#include "class_projectiler_mover.h"
#include "timer.h"

ProjectilerMover::ProjectilerMover(sf::RenderWindow & wd, sf::RectangleShape & prj, sf::RectangleShape & rct, std::vector<StaticObjects> & st_obs,
    std::vector<sf::RectangleShape> & rs_ob, const projMov & pm, const recMov & rm)
    : x(pm.x_projectiler), y(pm.y_projectiler), v(pm.speed_projectiler), timeStamp(rm.timeStamp), x_screen(rm.weight_screen), 
    y_screen(rm.height_screen), weight(pm.w_projectiler), height(pm.h_projectiler),
    window(wd), projectiler(prj), rectangle(rct), stat_objs(st_obs), rs_objs(rs_ob)
{
    half_weight = weight / 2;
    half_height = height / 2;

    if (x - half_weight < 0 || x + half_weight > x_screen)
        throw std::logic_error("wrong coordinate 'x'");

    if (y - half_height < 0 || y + half_height > y_screen)
        throw std::logic_error("wrong coordinate 'y'");
}

bool ProjectilerMover::CheckScreenY(const int & timeStamp) const
{
    int num = y + v * timeStamp;

    if (num - half_height < 0 || num + half_height > y_screen)
        return false;

    return true;
}

bool ProjectilerMover::checkDestroyed()
{
    for (int i = 0; i < stat_objs.size(); i++)
    {
        begin_x = x - weight / 2;
        end_x = x + weight / 2;
        begin_y = y - height / 2;
        end_y = y + height / 2;

        if (begin_x >= stat_objs[i].GetBX() && end_x <= stat_objs[i].GetEX() &&
            begin_y >= stat_objs[i].GetBY() && end_y <= stat_objs[i].GetEY())
        {
            stat_objs.erase(stat_objs.begin() + i);

            int milliseconds;

            if (getMilliseconds() + 300 > 1000)
                milliseconds = getMilliseconds() + 300 - 1000;
            else
                milliseconds = getMilliseconds() + 300;

            while (getMilliseconds() != milliseconds)
            {
                rs_objs[i].setFillColor(sf::Color::Yellow);
                window.clear(sf::Color::Blue);
                window.draw(rectangle); // Drawing our shape.

                for (int a = 0; a < rs_objs.size(); a++)
                {
                    window.draw(rs_objs[a]);
                }

                window.display();
            }

            rs_objs.erase(rs_objs.begin() + i);

            return false;
        }
    }

    return true;
}

void ProjectilerMover::CalculateYU()
{
    while (timeStamp != 0 && CheckScreenY(-timeStamp))
    {
        if (getMilliseconds() % 5 == 0)
        {
            y = y + v * (-timeStamp);

            if (!checkDestroyed())
                break;

            projectiler.setPosition(x, y);
            projectiler.setOrigin(projectiler.getSize().x / 2, projectiler.getSize().y / 2);
            window.clear(sf::Color::Blue);
            window.draw(projectiler); // Drawing our shape.
            window.draw(rectangle); // Drawing our shape.

            for (int i = 0; i < rs_objs.size(); i++)
            {
                window.draw(rs_objs[i]);
            }

            window.display();

            std::cout << "Y = " << y << std::endl;
        }
    }
}

int ProjectilerMover::GetX() const
{
    return x;
}

int ProjectilerMover::GetY() const
{
    return y;
}