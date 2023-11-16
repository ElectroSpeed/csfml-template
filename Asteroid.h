#pragma once


typedef struct Asteroid {
    float x;
    float y;
    float vitesse;
    float angle;
    int is_visible;
    sfCircleShape* shape;
};

void AsteroidSpawn(asteroid_list, size, Nb_Asteroids);

void AsteroidMove(asteroid_list, Nb_Asteroid, delta);