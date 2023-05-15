//
// Created by marep on 27/04/2023.
//

#ifndef EXAMPLE_LEVEL_H
#define EXAMPLE_LEVEL_H

#include "raylib.h"
#include "map.h"

typedef struct level
{
    Map levmap;
    Texture2D Background;
    int global_objects;
    int special_objects;
    Image plat_img, haz_img, obj_img;
    int count_sp_obj, count_n_obj;
}Level;

void RenderLevel(Level *nivel, Map *mapi, Platform *plats, Hazard *hazs, Object *objects, int *numplats, int *numhazard, int *numobjects);

Level createlevel(char *background_path, char *platform_img_path, char *hazard_img_path, char *objects_img_path, Map mapi, int global_objects, int special_objects);

#endif //EXAMPLE_LEVEL_H
