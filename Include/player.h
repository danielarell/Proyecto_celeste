//
// Created by marep on 27/04/2023.
//

#ifndef EXAMPLE_PLAYER_H
#define EXAMPLE_PLAYER_H

#include "raylib.h"
#include "platform.h"
#include "hazard.h"
#include "map.h"
#include "level.h"

typedef struct Player
{
    Texture2D text;
    Texture2D text_j;
    Rectangle recta;
    Rectangle collide;
    Vector2 position;
    float speed;
    bool canJump;
    bool onTop;
    bool isFalling;
    bool IsAlive;
    Vector2 velocity;
}Player;

void UpdatePlayer(Player *player, Platform *plats, Hazard  *hazs, Object *obs,float *delta, int *framew, int *deaths, Map *mapi, Rectangle camera, Level *lev);

#endif //EXAMPLE_PLAYER_H
