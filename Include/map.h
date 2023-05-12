//
// Created by marep on 27/04/2023.
//

#ifndef EXAMPLE_MAP_H
#define EXAMPLE_MAP_H

#include "raylib.h"
#include "object.h"
#include "platform.h"
#include "hazard.h"

#define MAX_RECTS 50
#define MAX_HAZARDS 50
#define MAX_OBS 30

typedef struct map
{
    int numPlatforms;
    Platform platforms[MAX_RECTS];
    int numHazards;
    Hazard hazards[MAX_HAZARDS];
    int numObjects;
    Object Objects[MAX_OBS];
} Map;


#endif //EXAMPLE_MAP_H
