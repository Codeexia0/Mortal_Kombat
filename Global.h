#pragma once

#include<SFML/Graphics.hpp>
#include<cmath>

sf::RenderWindow *window;

sf::Font *font;



float distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

bool isIntersects(sf::FloatRect a, sf::FloatRect b) {
    if (a.intersects(b)) {
        return true;
    }
    return false;
}
