//
// Created by marep on 27/04/2023.
//

#include "Include/hazard.h"
#include "Include/platform.h"

void inithazards(Image img, int *numhazard, Hazard *hazs)
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

                for (int i = 0; i < (*numhazard); i++)
                {
                    overlaps = RectanglesOverlap(rect, hazs[i].coll);
                    if (overlaps) break;
                }

                if (!overlaps)
                {
                    hazs[*numhazard].coll = rect;
                    hazs[*numhazard].position = (Vector2){col + width / 2.0f, row + height / 2.0f};
                    hazs[*numhazard].isActive =  true;
                    (*numhazard)++;
                }

                col += width;
            }
        }
    }
}
