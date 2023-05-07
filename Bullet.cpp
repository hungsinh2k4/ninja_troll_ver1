#include "Bullet.h"

BulletObject ::BulletObject()
{
    x_value = 0;
    y_value = 0;
    is_move = 0;
}

BulletObject ::~BulletObject()
{
}

void BulletObject ::HandelMove(const int &x_border, const int &y_border)
{

    if (bullet_dir == DIR_RIGHT)
    {
        rect.x += x_value;
        if (rect.x > x_border)
        {
            // vượt quá màn hình
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_LEFT)
    {
        rect.x -= x_value;
        if (rect.x < 0)
        {
            // vượt quá màn hình
            is_move = false;
        }
    }
}