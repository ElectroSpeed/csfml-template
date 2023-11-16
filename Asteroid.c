#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Asteroid.h"

#define _Pi 3.1415927

int speed_asteroid = 1;

void AsteroidSpawn(struct Asteroid asteroid_list[], int size[], int Nb_Asteroids) {
    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    for (int i = 0; i < Nb_Asteroids; i++) {
        if (!asteroid_list[i].is_visible) {
            asteroid_list[i].x = (rand() % WINDOW_X);
            asteroid_list[i].y = (rand() % WINDOW_Y);
            asteroid_list[i].angle = rand() % 360;
            asteroid_list[i].vitesse = speed_asteroid;
            asteroid_list[i].is_visible = 1;
            asteroid_list[i].shape = sfCircleShape_create();
            sfCircleShape_setRadius(asteroid_list[i].shape, size[0] * 120 / 1920);
            sfCircleShape_setOrigin(asteroid_list[i].shape, (sfVector2f) { size[0] * 7.5 / 1920, size[0] * 7.5 / 1920 });
            sfCircleShape_setRotation(asteroid_list[i].shape, asteroid_list[i].angle);
            sfCircleShape_setPosition(asteroid_list[i].shape, (sfVector2f) { asteroid_list[i].x, asteroid_list[i].y });
            break;
        }
    }
}

void AsteroidMove(struct Asteroid asteroid_list[], int Nb_Asteroids, int delta) {
    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    for (int i = 0; i < Nb_Asteroids; i++) {
        if (asteroid_list[i].is_visible) {
            float dirx = cos(asteroid_list[i].angle * _Pi / 180);
            float diry = sin(asteroid_list[i].angle * _Pi / 180);

            asteroid_list[i].x += asteroid_list[i].vitesse * dirx * delta / 10;
            asteroid_list[i].y += asteroid_list[i].vitesse * diry * delta / 10;

        }
        sfCircleShape_setPosition(asteroid_list[i].shape, (sfVector2f) { asteroid_list[i].x, asteroid_list[i].y });
    }
}


