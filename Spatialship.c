#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Spatialship.h"

#define _Pi 3.1415927


void draw_Ship( sfWindow* window, sfRectangleShape* Ship){

	sfRenderWindow_drawRectangleShape(window, Ship, NULL);
}

void Move(struct Spatialship ship, int delta) {
    float dirx = cos(ship.angle * _Pi / 180);
    float diry = sin(ship.angle * _Pi / 180);

    if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) {
        ship.angle += (float)delta/4.0;

    }
    if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) {
        ship.angle -= (float)delta/4.0;

    }
    if (ship.angle >= 360 || ship.angle <= -360) {
        ship.angle = 0;
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        if (fabs(ship.power.x + ship.speed * dirx * delta) < fabs(0.5 * dirx * delta)) {
            ship.power.x += ship.speed * dirx * delta;
        }
        if (fabs(ship.power.y + ship.speed * diry * delta) < fabs(0.5 * diry * delta)) {
            ship.power.y += ship.speed * diry * delta;
        }

    }
    if (sfKeyboard_isKeyPressed(sfKeyDown) || sfKeyboard_isKeyPressed(sfKeyS)) {
        ship.power.x *= 0.99;
        ship.power.y *= 0.99;
    }

    ship.Position_X += ship.power.x;
    ship.Position_Y += ship.power.y;

    float deceleration = 0.01;

    float a_length = sqrt(ship.power.x * ship.power.x + ship.power.y * ship.power.y);
    if (a_length != 0) {
        float normalized_x = ship.power.x / a_length;
        float normalized_y = ship.power.y / a_length;
        if (fabs(ship.power.x) - fabs(normalized_x * deceleration) > 0) {
            ship.power.x -= (delta) * normalized_x * deceleration;
        }
        else {
            ship.power.x = 0;
        }
        if (fabs(ship.power.y) - fabs(normalized_y * deceleration) > 0) {
            ship.power.y -= (delta) * normalized_y * deceleration;
        }
        else {
            ship.power.y = 0;
        }
    }

    sfRectangleShape_setPosition(ship.Shape, (sfVector2f) { ship.Position_X, ship.Position_Y });
    sfRectangleShape_setRotation(ship.Shape, ship.angle + 90);
}