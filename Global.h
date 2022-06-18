#pragma once

#include<SFML/Graphics.hpp>
#include<cmath>

sf::RenderWindow *window;

sf::Font *font;



float distance(float x1, float y1, float x2, float y2)//formula for findinf distance between two points(math!!!)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

bool isIntersects(sf::FloatRect a, sf::FloatRect b) { //when rectangles of players touch each other
    if (a.intersects(b)) {
        return true;
    }
    return false;
}
