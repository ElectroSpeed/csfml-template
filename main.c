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
#include "Asteroid.h"

#define _Pi 3.1415927
#define nb_lazer 1
#define Nb_Asteroids 4

int Score = 0;

sfTexture* ShipSpatial;
sfTexture* Galaxy;

typedef int bool;
#define true 1
#define false 0

int Delta(sfClock* deltaclock, int delta) {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
    return delta;
}

int main() {
    srand(time(0));
    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    int size[2] = { WINDOW_X,WINDOW_Y };
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    sfRenderWindow* window = sfRenderWindow_create(mode, "TEMPLATE", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    ShipSpatial = sfTexture_createFromFile("Ship.png", NULL);
    Galaxy = sfTexture_createFromFile("Galaxy.png", NULL);

    sfSprite* Background = sfSprite_create();

    struct Spatialship ship = {
         .Position_X = WINDOW_X / 2,
         .Position_Y = WINDOW_Y / 2,
         .power = {0,0},
         .angle = 0,
         .speed = 0.1,
         .Shape = sfRectangleShape_create(),
    };

    sfRectangleShape_setSize(ship.Shape, (sfVector2f) { WINDOW_Y / 20, WINDOW_Y / 20 });
    sfRectangleShape_setPosition(ship.Shape, (sfVector2f) { WINDOW_X / 2, WINDOW_Y / 2 });
    sfRectangleShape_setOrigin(ship.Shape, (sfVector2f) { WINDOW_Y / 40, WINDOW_Y / 40 });
    sfRectangleShape_setTexture(ship.Shape, ShipSpatial, NULL);
    sfSprite_scale(Background, (sfVector2f) { 9, 6});
    sfSprite_setTexture(Background, Galaxy, NULL);

    struct lazer lazer_list[1];
    struct Asteroid asteroid_list[4];


    for (int i = 0; i < nb_lazer; i++) {
        lazer_list[i].is_visible = 0;
        lazer_list[i].shape = sfCircleShape_create();
        lazer_list[i].lifetime = sfClock_create();
    }
    
    sfClock* deltaclock = sfClock_create();
    sfFont* font1 = sfFont_createFromFile("Font/Arial.ttf");

    int delta = 0;

    sfFont* font = sfFont_createFromFile("Font/Arial.ttf");
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    char str[30];

    for (int i = 0; i < Nb_Asteroids; ++i) {
        asteroid_list[i].is_visible = 0;
        AsteroidSpawn(asteroid_list, size, Nb_Asteroids);
    }

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        snprintf(str, 30, "Score: %d", Score);
        sfText_setString(text, str);

        delta = Delta(deltaclock, delta);

        Move(&ship, delta);
        LazerMove(lazer_list, nb_lazer, delta);
        AsteroidMove(asteroid_list, Nb_Asteroids, delta);
        if (sfKeyboard_isKeyPressed(sfKeySpace)) {
            LazerSpawn(ship, lazer_list, size, nb_lazer);
        }


        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit

        ////// DRAW /////
        sfRenderWindow_clear(window, sfTransparent);

        sfRenderWindow_drawSprite(window, Background, NULL);
        draw_Ship(window,ship.Shape);
        for (int i = 0; i < nb_lazer; ++i) {
            if (lazer_list[i].is_visible){ 
                sfRenderWindow_drawCircleShape(window, lazer_list[i].shape, NULL); 
            }
        }
        for (int i = 0; i < Nb_Asteroids; ++i) {
            if (asteroid_list[i].is_visible) {
                sfRenderWindow_drawCircleShape(window, asteroid_list[i].shape, NULL);
            }
        }

        sfRenderWindow_drawText(window, text, NULL);
        
        sfRenderWindow_display(window);
        /////////////////
    }
    return 0;
    sfClock_destroy(deltaclock);
    sfTexture_destroy(ShipSpatial);
    sfTexture_destroy(Galaxy);
    sfSprite_destroy(Background);
    sfRectangleShape_destroy(ship.Shape);
    sfFont_destroy(font1);
    sfFont_destroy(font);
    sfText_destroy(text);
    sfRenderWindow_destroy(window);
    for (int i = 0; i < nb_lazer; ++i) {
        sfCircleShape_destroy(lazer_list[i].shape);
    }
}