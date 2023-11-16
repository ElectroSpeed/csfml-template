#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Spatialship.h"
#include "Lazer.h"
#define _Pi 3.1415927

int speed_bullet = 15;

void LazerSpawn(struct Spatialship ship, struct lazer lazer_list[], int size[], int nb_lazer) {
    for (int i = 0; i < nb_lazer; i++) {
        if (!lazer_list[i].is_visible) {
            lazer_list[i].x = ship.Position_X;
            lazer_list[i].y = ship.Position_Y;
            lazer_list[i].angle = ship.angle;
            lazer_list[i].vitesse = speed_bullet;
            lazer_list[i].is_visible = 1;
            sfClock_restart(lazer_list[i].lifetime);
            sfCircleShape_setRadius(lazer_list[i].shape, size[0] * 15 / 1920);
            sfCircleShape_setOrigin(lazer_list[i].shape, (sfVector2f) { size[0] * 7.5 / 1920, size[0] * 7.5 / 1920 });
            sfCircleShape_setRotation(lazer_list[i].shape, lazer_list[i].angle);
            sfCircleShape_setPosition(lazer_list[i].shape, (sfVector2f) { lazer_list[i].x, lazer_list[i].y });
            break;
        }
    }
}

void LazerMove(struct lazer lazer_list[], int nb_lazer, int delta) {
    for (int i = 0; i < nb_lazer; i++) {
        if (lazer_list[i].is_visible) {
            float dirx = cos(lazer_list[i].angle * _Pi / 180);
            float diry = sin(lazer_list[i].angle * _Pi / 180);

            lazer_list[i].x += lazer_list[i].vitesse * dirx * delta/10;
            lazer_list[i].y += lazer_list[i].vitesse * diry * delta/10;

            if (sfTime_asMicroseconds(sfClock_getElapsedTime(lazer_list[i].lifetime)) >= ((sfVideoMode_getDesktopMode().height / 2.5) / speed_bullet) * 10000) {
                lazer_list[i].is_visible = 0;
            }
        }
        sfCircleShape_setPosition(lazer_list[i].shape, (sfVector2f) { lazer_list[i].x, lazer_list[i].y });
    }
}