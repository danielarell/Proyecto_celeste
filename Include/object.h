//
// Created by marep on 27/04/2023.
//

#ifndef EXAMPLE_OBJECT_H
#define EXAMPLE_OBJECT_H

#include "raylib.h"

typedef enum object_type
{
    berry,
    star

}OBJ_TYPE;

typedef struct object
{
    Rectangle recta;
    Rectangle colli;
    Vector2 position;
    bool isActive;
    OBJ_TYPE type;
}Object;

bool color_equal(Color a, Color b);

void InitObjects(Image img, int *numobjects, Object *objects);

#endif //EXAMPLE_OBJECT_H
