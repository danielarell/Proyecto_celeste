//
// Created by marep on 25/04/2023.
//

#ifndef EXAMPLE_PLATFORM_H
#define EXAMPLE_PLATFORM_H

#include "raylib.h"

typedef struct platform
{
    Rectangle rect;
    Vector2 position;
} Platform;

void initlevel(Image img, int *numplats, Platform *plats);
bool RectanglesOverlap(Rectangle r1, Rectangle r2);

#endif //EXAMPLE_PLATFORM_H
