//
// Created by marep on 27/04/2023.
//

#ifndef EXAMPLE_HAZARD_H
#define EXAMPLE_HAZARD_H

#include "raylib.h"

typedef struct hazard
{
    Rectangle coll;
    Vector2 position;
    bool isActive;

}Hazard;

void inithazards(Image img, int *numhazard, Hazard *hazs);

#endif //EXAMPLE_HAZARD_H
