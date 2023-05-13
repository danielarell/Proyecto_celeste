#include <stdio.h>
#include "raylib.h"
#include "Include/platform.h"
#include "Include/hazard.h"
#include "Include/object.h"
#include "Include/map.h"
#include "Include/level.h"
#include "Include/player.h"

const int WIDTH = 900, HEIGHT = 600;
int numplats = 0;
int numhazard = 0;
int numobjects = 0;
Hazard hazs[MAX_HAZARDS];
Platform plats[MAX_RECTS];
Object objects[MAX_OBS];
Map mapi_1;
Map mapi_2;

Texture2D Game;
Rectangle cameraRec;

void render_main_levels(int *TOTAL_DEATHS,Player *player,float *deltaTime,int *framewidth, Level *level, Texture2D star_2, Texture2D berry, Map *mapi);
void jugabilidad(Player *player, bool isPaused, int *TOTAL_DEATHS, Camera2D *camera);
void pause(Level level, int TOTAL_DEATHS);

int main()
{

    InitWindow(WIDTH, HEIGHT, "Game");

    int TOTAL_DEATHS = 0;
    bool isPaused = false;

    // Initialization
    typedef enum {LOGO, TITLE, GAME, ENDING} Gamescreen;
    Gamescreen gameScreen = LOGO;
    int screen = 0;
    float counter = 0.0;
    int counterf = 0;

    Texture2D Logo = LoadTexture("../Assets/LOGO.png");
    Texture2D Title = LoadTexture("../Assets/TITLE.png");
    Texture2D End = LoadTexture("../Assets/ENDING.png");
    Texture2D star_2 = LoadTexture("../Assets/Star.png");
    Texture2D berry = LoadTexture("../Assets/berry.png");
    Texture2D livel1 = LoadTexture("../Assets/map_text.png");
    Texture2D livel2 = LoadTexture("../Assets/Map_lvl_text.png");

    Player player = { 0 };
    player.text = LoadTexture("../Assets/character.png");
    player.text_j = LoadTexture("../Assets/char_j.png");
    int framewidth = player.text.width / 4;
    player.position = (Vector2){150, 130};
    player.recta = (Rectangle){0, 0, (float)framewidth, (float)player.text.height};
    player.collide = (Rectangle){player.position.x, player.position.y, (float)framewidth, (float)player.text.height};
    player.speed = 0;
    player.canJump = false;
    player.IsAlive = true;
    player.isFalling = true;
    player.velocity = (Vector2) {0,0};

    Level level1 = createlevel("../Assets/Lvl1_BCK.png", "../Assets/map_lvl1.png", "../Assets/Map_lvl_h.png", "../Assets/nivel1objetos.png", mapi_1, 9, 4);
    Level level2 = createlevel("../Assets/Lvl2_BCK.png", "../Assets/lvl2plat.png", "../Assets/lvl2hazards.png", "../Assets/nivel2objetos.png", mapi_2, 10, 4);


    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.position.x + 20.0f, player.position.y + 20.0f};
    camera.offset = (Vector2){ WIDTH/2, HEIGHT/2};
    camera.rotation = 0.0f;
    camera.zoom = 2.5f;

    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        // Update Screen
        float deltaTime = GetFrameTime();

        counterf++;

        switch(gameScreen)
        {
            case LOGO:
            {
                if (screen == 0)
                {
                    if (counter < 1.0) counter += 0.05;
                    else screen = 1;
                }
                else if (screen == 1)
                {
                    counter = 1.0;
                    if (counterf % 180 == 0)
                    {
                        screen = 2;
                    }
                }
                else if (screen == 2)
                {
                    if (counter > 0.0) counter -= 0.05;
                    else
                    {
                        gameScreen = TITLE;
                        screen = 0;
                    }
                }

            }break;

            case TITLE:
            {
                if (screen == 0)
                {
                    if (counter < 1.0) counter += 0.05;
                    else screen = 1;
                }
                else if (screen == 1)
                {
                    counter = 1.0;

                    //Mouse
                    if(IsKeyDown(KEY_A))
                    {
                        screen = 2;
                    }
                }
                else if (screen == 2)
                {
                    if (counter > 0.0) counter -= 0.05;
                    else
                    {
                        gameScreen = GAME;
                        screen = 0;
                    }
                }

            }break;

            case GAME:
            {

                if (screen == 0)
                {
                    if (counter < 1.0) counter += 0.05;
                    else screen = 1;
                }
                else if (screen == 1)
                {

                    RenderLevel(screen, &level1, &mapi_1, plats, hazs, objects, &numplats, &numhazard, &numobjects);

                    if (IsKeyPressed(KEY_P)) {
                        isPaused = !isPaused;
                    }

                    jugabilidad(&player, isPaused, &TOTAL_DEATHS, &camera);

                    if (level1.count_n_obj == level1.global_objects)
                    {
                        player.position.x = 150;
                        player.position.y = 100;
                        numobjects = 0;
                        numhazard = 0;
                        numplats = 0;
                        screen = 2;
                    }
                }
                else if (screen == 2)
                {
                    if (IsKeyDown(KEY_N))
                    {
                        screen = 3;
                    }
                }
                else if (screen == 3)
                {
                    RenderLevel(screen, &level2, &mapi_2, plats, hazs, objects, &numplats, &numhazard, &numobjects);

                    if (IsKeyPressed(KEY_P)) {
                        isPaused = !isPaused;
                    }

                    jugabilidad(&player, isPaused, &TOTAL_DEATHS, &camera);

                    if (level2.count_n_obj == level2.global_objects)
                    {
                        screen = 0;
                        gameScreen = ENDING;
                    }
                }
            }break;

            case ENDING:
            {

            }break;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        switch(gameScreen)
        {
            case LOGO:
            {
                switch(screen)
                {
                    case 0:
                    {
                        DrawTexture(Logo, 0, 0, Fade(BLACK, counter));
                    }break;

                    case 1:
                    {
                        DrawTexture(Logo, 0, 0, WHITE);
                    }break;

                    case 2:
                    {
                        DrawTexture(Logo, 0, 0, Fade(BLACK, counter));
                    }
                }

            }break;

            case TITLE:
            {
                switch(screen)
                {
                    case 0:
                    {
                        DrawTexture(Title, 0, 0, Fade(BLACK,counter));
                    }break;

                    case 1:
                    {
                        DrawTexture(Title, 0, 0, WHITE);
                    }break;

                    case 2:
                    {
                        DrawTexture(Title, 0, 0, Fade(BLACK,counter));
                    }break;
                }
            }break;

            case GAME:
            {
                BeginMode2D(camera);
                switch(screen)
                {
                    case 1:
                    {
                        if ( !isPaused)
                        {
                            DrawTexture(level1.Background, 0, -41, WHITE);
                            render_main_levels(&TOTAL_DEATHS, &player, &deltaTime, &framewidth, &level1, star_2, berry, &mapi_1);
                            DrawTexture(livel1, 0, 0, WHITE);
                        } else
                        {
                            pause(level1, TOTAL_DEATHS);
                        }
                    }break;

                    case 2:
                    {
                        DrawText("Level Completed!!!", cameraRec.x + 20, cameraRec.y + 10, 40, WHITE);
                        DrawText("Press N to play level 2", cameraRec.x + 25, cameraRec.y + 50, 20, WHITE);
                    }break;

                    case 3:
                    {
                        if ( !isPaused)
                        {
                            DrawTexture(level2.Background, 0, 0, WHITE);
                            render_main_levels(&TOTAL_DEATHS, &player, &deltaTime, &framewidth, &level2, star_2, berry, &mapi_2);
                            DrawTexture(livel2, 0, 0, WHITE);
                        } else
                        {
                            pause(level2, TOTAL_DEATHS);
                        }
                        //DrawText("Nivel 2", cameraRec.x + 20, cameraRec.y + 10, 40, BLACK);
                    }break;
                }
                EndMode2D();

            }break;

            case ENDING:
            {
                DrawTexture(End, 0, 0, WHITE);
            }break;
        }
        DrawFPS(5,5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void pause(Level level, int TOTAL_DEATHS)
{
    DrawRectangleRec(cameraRec, GRAY);
    DrawText("PAUSED", cameraRec.x + 20, cameraRec.y + 10, 40, WHITE);
    DrawText("Press P to resume", cameraRec.x + 25, cameraRec.y + 50, 20, WHITE);
    DrawText(TextFormat("Muertes: %d", TOTAL_DEATHS), cameraRec.x + 35, cameraRec.y + cameraRec.height/4 + 20, 20, WHITE);
    DrawText(TextFormat("Fresas: %d    Total: %d",level.count_n_obj , level.global_objects), cameraRec.x + 35, cameraRec.y + cameraRec.height/4 + 40, 20, WHITE);
    DrawText(TextFormat("Stars: %d     Total: %d",level.count_sp_obj , level.special_objects ), cameraRec.x + 35, cameraRec.y + cameraRec.height/4 + 60, 20, WHITE);
}

void render_main_levels(int *TOTAL_DEATHS, Player *player, float *deltaTime, int *framewidth, Level *level, Texture2D star_2, Texture2D berry, Map *mapi)
{
    DrawTexture(Game, 0, 0, WHITE);
    if ( player->canJump )
    {
        DrawTextureRec(player->text, player->recta, player->position, WHITE);
    } else DrawTextureRec(player->text_j, player->recta, player->position, WHITE);
    for ( int u = 0; u < mapi->numObjects; u++)
    {
        if (mapi->Objects[u].isActive && CheckCollisionRecs(cameraRec, mapi->Objects[u].colli))
        {
            Rectangle recti = mapi->Objects[u].recta;
            if ( mapi->Objects[u].type == star)
            {
                DrawTextureRec(star_2,recti,mapi->Objects[u].position, WHITE);
            } else
            {
                DrawTextureRec(berry, recti, mapi->Objects[u].position, WHITE);
            }
        }
    }
    UpdatePlayer(player, plats, hazs, objects, deltaTime, framewidth, TOTAL_DEATHS, mapi, cameraRec, level);
    player->collide.x = player->position.x;
    player->collide.y = player->position.y;
}

void jugabilidad(Player *player, bool isPaused, int *TOTAL_DEATHS, Camera2D *camera)
{
    if ( !isPaused )
    {
        if ( player->collide.y < HEIGHT)
        {
            camera->target = (Vector2){ player->collide.x + 20, player->collide.y + 20};
        } else
        {
            player->position = (Vector2) {150,100};
            (*TOTAL_DEATHS)++;
        }
        cameraRec.x = camera->target.x - (WIDTH / 2.0f / camera->zoom);
        cameraRec.y = camera->target.y - (HEIGHT / 2.0f / camera->zoom);
        cameraRec.width = WIDTH / camera->zoom;
        cameraRec.height = HEIGHT / camera->zoom;
    }
}