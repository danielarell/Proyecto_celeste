//
// Created by marep on 27/04/2023.
//

#include "Include/level.h"

void RenderLevel(int level, Level *nivel, Map *mapi, Platform *plats, Hazard *hazs, Object *objects, int *numplats, int *numhazard, int *numobjects)
{
    initlevel(nivel->plat_img, numplats, plats);
    inithazards(nivel->haz_img, numhazard, hazs);
    InitObjects(nivel->obj_img, numobjects, objects);

    mapi->numPlatforms = (*numplats);
    mapi->numHazards = (*numhazard);
    mapi->numObjects = (*numobjects);

    for (int i = 0; i < (*numplats); i++)
    {
        mapi->platforms[i] = plats[i];
    }
    for ( int i = 0; i < (*numhazard); i++)
    {
        mapi->hazards[i] = hazs[i];
    }
    for ( int i  = 0; i < (*numobjects); i++)
    {
        mapi->Objects[i] = objects[i];
    }
}

Level createlevel(char *background_path, char *platform_img_path, char *hazard_img_path, char *objects_img_path, Map mapi, int global_objects, int special_objects)
{
    Level new_level;

    new_level.Background = LoadTexture(background_path);
    new_level.levmap = mapi;
    new_level.global_objects = global_objects;
    new_level.special_objects = special_objects;
    new_level.count_n_obj = 0;
    new_level.count_sp_obj = 0;
    new_level.plat_img = LoadImage(platform_img_path);
    new_level.haz_img = LoadImage(hazard_img_path);
    new_level.obj_img = LoadImage(objects_img_path);

    return  new_level;
}