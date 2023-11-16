#pragma once

struct lazer {
    float x;
    float y;
    float vitesse;
    float angle;
    int is_visible;
    sfClock* lifetime;
    sfCircleShape* shape;
};

void LazerSpawn(ship, lazer_list, size, nb_lazer);

void LazerMove(lazer_list, nb_lazer, delta);