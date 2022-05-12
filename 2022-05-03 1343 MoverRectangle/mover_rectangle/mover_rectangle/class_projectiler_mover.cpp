#include "class_projectiler_mover.h"
#include "timer.h"

ProjectilerMover::ProjectilerMover(sf::RenderWindow & wd, sf::RectangleShape & prj, sf::RectangleShape & rct,
    const int & c_x, const int & c_y, const int & tS, const int & speed,
    const int & x_scr, const int & y_scr, const float & w, const float & h)
    : x(c_x), y(c_y), v(speed), timeStamp(tS), x_screen(x_scr), y_screen(y_scr), weight(w), height(h),
    window(wd), projectiler(prj), rectangle(rct)
{
    half_weight = weight / 2;
    half_height = height / 2;

    if (x - half_weight < 0 || x + half_weight > x_screen)
        throw std::logic_error("wrong coordinate 'x'");

    if (y - half_height < 0 || y + half_height > y_screen)
        throw std::logic_error("wrong coordinate 'y'");
}

bool ProjectilerMover::CheckScreenY(const int & timeStamp)
{
    int num = y + v * timeStamp;

    if (num - half_height < 0 || num + half_height > y_screen)
        return false;

    return true;
}

void ProjectilerMover::CalculateYU()
{
    while (timeStamp != 0 && CheckScreenY(-timeStamp))
    {
        if (getMilliseconds() % 5 == 0)
        {
            y = y + v * (-timeStamp);

            projectiler.setPosition(x, y);
            projectiler.setOrigin(projectiler.getSize().x / 2, projectiler.getSize().y / 2);
            window.clear(sf::Color::Blue);
            window.draw(projectiler); // Drawing our shape.
            window.draw(rectangle); // Drawing our shape.
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