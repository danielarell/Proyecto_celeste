//
// Created by marep on 27/04/2023.
//

#include "Include/player.h"

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 150.0f

unsigned frameDelay = 3;
unsigned frameindex = 0;
unsigned framecounter = 0;

void UpdatePlayer(Player *player, Platform *plats, Hazard  *hazs, Object  *obs, float *delta, int *framew, int *deaths, Map *mapi, Rectangle camera, Level *lev)
{

    player->speed += G * (*delta);

    if (player->position.y <= 16)
    {
        player->position.y = 17;
    }

    int hitObstacle = 0;
    int hitwall = 0;
    int hittop = 0;

    if (IsKeyDown(KEY_LEFT))
    {
        if (player->canJump)
        {
            if (player->recta.width > 0)
            {
                player->recta.width = -player->recta.width;
            }
            ++framecounter;
            if (framecounter > frameDelay)
            {
                framecounter = 0;
                ++frameindex;
                frameindex %= 4;
                player->recta.x = (float) (*framew) * frameindex;
            }
        }
        if (player->position.x > 16) player->position.x -= PLAYER_HOR_SPD * (*delta);
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        if(player->canJump)
        {
            if (player->recta.width < 0)
            {
                player->recta.width = -player->recta.width;
            }
            ++framecounter;
            if(framecounter > frameDelay)
            {
                framecounter = 0;
                ++frameindex;
                frameindex %= 4;
                player->recta.x = (float) (*framew) * frameindex;
            }
        }

        if (player->position.x < (1784)) player->position.x += PLAYER_HOR_SPD*(*delta);
    }
    if (IsKeyPressed(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }
    if (IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
    {
        player->recta.y = 0;
        player->recta.x = 32;
    }

    //bool onground = false;

    bool collision = false;
    bool collision_2 = false;

    for (int i = 0; i < mapi->numHazards; i++)
    {
        Hazard *ei = hazs + i;
        if (CheckCollisionRecs(camera, ei->coll))
        {
            collision = CheckCollisionRecs(ei->coll, player->collide);
            if ( collision )
            {
                (*deaths)++;
                Vector2 targetPosition = { 200, 150 };
                float speed = 2.0f; // Adjust this value to control the speed of the movement
                player->position.x = 150;
                player->position.y = 130;
            }
        }
    }

    for ( int i = 0; i < mapi->numObjects; i++)
    {
        Object *ei = obs + i;
        if (CheckCollisionRecs(camera, ei->colli))
        {
            collision = CheckCollisionRecs(ei->colli, player->collide);
            if ( collision && ei->isActive )
            {
                ei->isActive = false;
                if ( ei->type == star)
                {
                    lev->count_sp_obj++;
                } else
                {
                    lev->count_n_obj++;
                }
            }
        }
    }

    for (int i = 0; i < mapi->numPlatforms; i++)
    {
        Platform *ei = plats + i;
        Vector2 *p = &(player->position);
        if (CheckCollisionRecs(camera, ei->rect))
        {

            float player_top = player->position.y;
            float player_left = player->position.x;
            float player_right = player->position.x + (*framew);
            float player_bottom = player->position.y + player->text.height;
            float plat_top = ei->rect.y;
            float plat_left = ei->rect.x;
            float plat_right = plat_left + ei->rect.width;
            float plat_bottom = plat_top + ei->rect.height;

            if ( player->collide.y > ei->rect.y && player->collide.y + player->collide.height < ei->rect.y + ei->rect.height &&
                 player->collide.x > ei->rect.x && player->collide.x + player->collide.width < ei->rect.x + ei->rect.width)
            {
                collision_2 = true;
            }

            if ( collision_2 )
            {
                Vector2 targetPosition = { 200, 150 };
                float speed = 2.0f; // Adjust this value to control the speed of the movement
                player->position.x = 150;
                player->position.y = 130;
            }

            if (plat_left <= player_left && plat_right > player_left && plat_top - player->text.height >= player_top && plat_top - player->text.height <= player_top + player->speed*(*delta) && player_bottom <= plat_top
                )
            {
                hitObstacle = 1;
                player->speed = 0.0f;
                p->y = ei->rect.y - player->text.height;
            }
            else if (p->x + (*framew) >= ei->rect.x - 1&&
                     p->x < ei->rect.x &&
                     ei->rect.y <= p->y + player->text.height &&
                     ei->rect.y + ei->rect.height >= p->y)
            {
                //CHOCA IZQUIERDA DE LA PLATAFORMA
                hitwall = 1;
                //player->speed = 0.0f;
                p->x = ei->rect.x - (*framew);
            }
            else if (p->x <= ei->rect.x + ei->rect.width + 1 &&
                     p->x + (*framew) > ei->rect.x + ei->rect.width &&
                     p->y >= ei->rect.y &&
                     p->y + player->text.height <= ei->rect.y + ei->rect.height)
            {
                //CHOCA DESDE LA DERECHA DE LA PLATAFORMA
                hitwall = 1;
                p->x = ei->rect.x + ei->rect.width;
            }
            else if (p->y <= ei->rect.y + ei->rect.height &&
                     p->y + player->text.height > ei->rect.y + ei->rect.height &&
                     p->x + (*framew) > ei->rect.x &&
                     p->x < ei->rect.x + ei->rect.width)
            {
                //REBOTAR EN EL TECHO
                hittop = 1;
                p->y = ei->rect.y + ei->rect.height;
            }
        }

    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*(*delta);
        if (hittop)
        {
            player->speed += (G*3)*(*delta);
        }else
        {
            player->speed += G*(*delta);
        }
        player->canJump = false;
    }
    else player->canJump = true;

    if(hitwall && IsKeyDown(KEY_Z) && IsKeyUp(KEY_SPACE))
    {
        player->position.y += 0;
        player->speed = 0.0f;
        player->canJump = true;
    }

}