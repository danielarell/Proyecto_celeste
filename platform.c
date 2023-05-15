//
// Created by marep on 25/04/2023.
//

#include "Include/platform.h"

bool RectanglesOverlap(Rectangle r1, Rectangle r2)
{
    return CheckCollisionRecs(r1, r2);
}

void initlevel(Image img, int *numplats, Platform *plats)
{
    int imgWidth = img.width;
    int imgHeight = img.height;

    for (int row = 0; row < imgHeight; row++)
    {
        for (int col = 0; col < imgWidth; col++)
        {
            Color color_act = GetImageColor(img, col, row);

            if (color_act.a > 0)
            {
                int width = 1;
                int height = 1;

                while (col + width < imgWidth && GetImageColor(img, col + width, row).a > 0)
                {
                    width++;
                }

                while (row + height < imgHeight && GetImageColor(img, col, row + height).a > 0)
                {
                    height++;
                }

                Rectangle rect = (Rectangle){col, row, width, height};

                bool overlaps = false;

                for (int i = 0; i < (*numplats); i++)
                {
                    overlaps = RectanglesOverlap(rect, plats[i].rect);
                    if (overlaps) break;
                }

                if (!overlaps)
                {
                    plats[*numplats].rect = rect;
                    plats[*numplats].position = (Vector2){col + width / 2.0f, row + height / 2.0f};
                    (*numplats)++;
                }

                col += width;
            }
        }
    }
}

