#include "create_map.h"

CreateMap::CreateMap(windowStruct & ws) : weight(ws.weight), height(ws.height), color(colors[ws.color]), 
name_window(ws.name_window), map(ws.map), objsArray(ws.objsArray), winSct(&ws) {}

CreateMap::CreateMap(windowStruct * ws) : weight(ws->weight), height(ws->height), color(colors[ws->color]),
name_window(ws->name_window), map(ws->map), objsArray(ws->objsArray), winSct(ws) {}

bool CreateMap::createWindow(sf::RenderWindow * window)
{
    int x, y, id_objs, x_module;
    float id_x, id_y;       // ������������� �������� ������� �� ��� "x"
    id_x = id_y = 0.5;       // ������������� �������� ������� �� ��� "y"
    id_objs = 0;   // ������������� ������� �������� ��� �����������
    x_module = 0;  // ���������� ��� ������� ������� �� ������

    if (window->isOpen())
    {
        window->clear(color);

        for (int i = 0; i < map.size(); i++)
        {
            if (map[i] != 0)
            {
                renderedObjects.push_back(sf::RectangleShape(sf::Vector2f(objsArray[map[i] - 1].weight, objsArray[map[i] - 1].height)));  // ���������� � ������ �������� ��� �����������
                renderedObjects[id_objs].setFillColor(colors[objsArray[map[i] - 1].color]);  // ���������� ����� �������� �������
                x = objsArray[map[i] - 1].weight * id_x;       // ���������� �������� ������� �� ��� "x"
                y = objsArray[map[i] - 1].height * id_y;  // ���������� �������� ������� �� ��� "y"
                renderedObjects[id_objs].setPosition(x, y);
                renderedObjects[id_objs].setOrigin(renderedObjects[id_objs].getSize().x / 2, renderedObjects[id_objs].getSize().y / 2);
                window->draw(renderedObjects[id_objs]);
                id_objs++;
            }

            if ((x_module + 1) % winSct->length_window == 0)  // ����� �������� �� ��� "x" ��� ���������� ����� ������ �������
            {
                id_x = 0.5;
                id_y += 1;  // ������������ �� ��������� ������ ������� �����
                x_module = 0;
            }
            else
            {
                id_x += 1; // ���������� �������� �� ��� "x" �� ���� ���
                x_module += 1;
            }
        }

        window->display();

        return true;
    }
}