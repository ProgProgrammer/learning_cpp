#include "create_map.h"

CreateMap::CreateMap(WindowStruct & ws) : weight(ws.weight), height(ws.height), color(colors[ws.color]), 
name_window(ws.name_window), map(ws.map), objsArray(ws.objsArray), winSct(ws) {}

bool CreateMap::updateWindow(sf::RenderWindow & window)
{
    int x, y, id_objs, x_module;
    float id_x, id_y;       // идентификатор смещения объекта по оси "x"
    id_x = id_y = 0.5;       // идентификатор смещения объекта по оси "y"
    id_objs = 0;   // идентификатор массива объектов для отображения
    x_module = 0;  // переменная для условия деления по модулю

    if (window.isOpen())
    {
        window.clear(color);

        for (int i = 0; i < map.size(); i++)
        {
            if (map[i] != 0)
            {
                renderedObjects.push_back(sf::RectangleShape(sf::Vector2f(objsArray[map[i] - 1].weight, objsArray[map[i] - 1].height)));  // добавление в массив объектов для отображения
                renderedObjects[id_objs].setFillColor(colors[objsArray[map[i] - 1].color]);  // добавление цвета объектам массива
                x = objsArray[map[i] - 1].weight * id_x;       // вычисление смещения объекта по оси "x"
                y = objsArray[map[i] - 1].height * id_y;       // вычисление смещения объекта по оси "y"
                renderedObjects[id_objs].setPosition(x, y);
                renderedObjects[id_objs].setOrigin(renderedObjects[id_objs].getSize().x / 2, renderedObjects[id_objs].getSize().y / 2);
                window.draw(renderedObjects[id_objs]);
                id_objs++;
            }

            if ((x_module + 1) % winSct.length_window == 0)  // сброс смещения по оси "x" при достижении конца строки матрицы
            {
                id_x = 0.5;
                id_y += 1;  // переключение на следующую строку матрицы внизу
                x_module = 0;
            }
            else
            {
                id_x += 1; // увеличение смещения по оси "x" на один шаг
                x_module += 1;
            }
        }

        window.display();

        return true;
    }
}