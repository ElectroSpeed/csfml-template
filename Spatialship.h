#pragma once


struct Spatialship {
    float Position_X;
    float Position_Y;
    sfVector2f power;
    float angle;
    float speed;
    sfRectangleShape* Shape;
};

void draw_Ship(window, Ship);

void Move(ship, delta);