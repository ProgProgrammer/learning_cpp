#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class iDrawable
{
    public:
        virtual void draw() = 0;
};