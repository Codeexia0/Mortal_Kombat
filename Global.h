#pragma once

#include<SFML/Graphics.hpp>
#include<cmath>

sf::RenderWindow *window;


float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
