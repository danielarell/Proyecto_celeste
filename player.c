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
                player->position.x = 150;
                player->position.y = 100;
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

            float player_top = p->y;
            float player_left = p->x;
            float player_bottom = player_top + player->text.height;
            float plat_top = ei->rect.y;
            float plat_left = ei->rect.x;
            float plat_right = plat_left + ei->rect.width;

            if ( player->collide.y > plat_top && player->collide.y + player->collide.height < ei->rect.y + ei->rect.height &&
                 player->collide.x > plat_left && player->collide.x + player->collide.width < plat_right)
            {
                collision_2 = true;
            }

            if ( collision_2 )
            {
                player->position.x = 150;
                player->position.y = 100;
            }

            if (plat_left <= player_left && plat_right > player_left && plat_top - player->text.height >= player_top && plat_top - player->text.height <= player_top + player->speed*(*delta) && player_bottom <= plat_top
                )
            {
                //Pisa plataforma
                hitObstacle = 1;
                player->speed = 0.0f;
                p->y = plat_top - player->text.height;
            }else  if (player_left + (*framew) >= plat_left && p->x < plat_left &&
                  plat_top <= player_bottom && plat_top + ei->rect.height >= p->y &&
                  player_top <= plat_top && player_bottom >= plat_top)
            {
                //esquina superior izquierda de la plataforma
                hitwall = 1;
                p->x = ei->rect.x - (*framew);
            }
            else if (player_left + (*framew) >= plat_left - 1&&
                     player_left < plat_left &&
                     plat_top <= player_bottom &&
                     plat_top + ei->rect.height >= player_top)
            {
                //CHOCA IZQUIERDA DE LA PLATAFORMA
                hitwall = 1;
                p->x = plat_left - (*framew);
            } else if (player_left < plat_right && player_left + (*framew) >= plat_right &&
                       plat_top <= player_bottom && plat_top + ei->rect.height >= player_top &&
                       player_top <= plat_top && player_bottom >= plat_top)
            {
                // esquina superior derecha de la plataforma
                hitwall = 1;
                p->x = plat_right;
            }
            else if (player_left <= plat_right + 1 &&
                     player_left + (*framew) > plat_right &&
                     player_top >= plat_top &&
                     player_bottom <= plat_top + ei->rect.height)
            {
                //CHOCA DESDE LA DERECHA DE LA PLATAFORMA
                hitwall = 1;
                p->x = plat_right;
            }
            else if (player_top <= plat_top + ei->rect.height &&
                     player_bottom > plat_top + ei->rect.height &&
                     player_left + (*framew) > plat_left &&
                     player_left < plat_right)
            {
                //REBOTAR EN EL TECHO
                hittop = 1;
                p->y = plat_top + ei->rect.height;
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