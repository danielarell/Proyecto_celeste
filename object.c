//
// Created by marep on 27/04/2023.
//

#include "Include/object.h"
#include "Include/platform.h"

bool color_equal(Color a, Color b)
{
    return ColorToInt(a) == ColorToInt(b);
}

void InitObjects(Image img, int *numobjects, Object *objects)
{
    int imgWidth = img.width;
    int imgHeight = img.height;

    int height = 0;

    for (int row = 0; row < imgHeight; row++)
    {
        for (int col = 0; col < imgWidth; col++)
        {
            Color color_act = GetImageColor(img, col, row);

            if (color_act.a > 0)
            {
                int width = 1;

                while (col + width < imgWidth && GetImageColor(img, col + width, row).a > 0)
                {
                    width++;
                }

                height = 1;

                while (row + height < imgHeight && GetImageColor(img, col, row + height).a > 0)
                {
                    height++;
                }

                Rectangle rect = (Rectangle){col, row, width, height};

                bool overlaps = false;

                for (int i = 0; i < (*numobjects); i++)
                {
                    if (RectanglesOverlap(rect, objects[i].colli))
                    {
                        overlaps = true;
                        break;
                    }
                }

                if (!overlaps)
                {
                    objects[*numobjects].colli = rect;
                    objects[*numobjects].recta = (Rectangle){0,0,rect.width, rect.height};
                    objects[*numobjects].position = (Vector2){col + width / 2.0f, row + height / 2.0f};
                    objects[*numobjects].isActive =  true;

                    if (color_equal(color_act, RED))
                    {
                        objects[*numobjects].type = berry;
                        //objects[numobjects].imagen = LoadTexture("coin.png");
                    }
                    if (color_equal(color_act, YELLOW))
                    {
                        objects[*numobjects].type = star;
                    }
                    (*numobjects)++;
                }

                col += width;
            }
        }
    }
}