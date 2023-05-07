#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "Commonfunc.h"
#include "BaseObject.h"

class BulletObject : public BaseObject
{

public:
    enum BULLET_DIR
    {
        DIR_RIGHT = 10,
        DIR_LEFT = 11,
    };

    BulletObject();
    ~BulletObject();
    void Set_x_value(const int &x_value0)
    {
        x_value = x_value0;
    }
    void Set_y_value(const int &y_value0)
    {
        y_value = y_value0;
    }
    int Get_x_value() const { return x_value; }
    int Get_y_value() const { return y_value; }

    void Set_is_move(const bool &is_move0)
    {
        is_move = is_move0;
    }
    bool Get_is_move() const { return is_move; }

    void HandelMove(const int &x_border, const int &y_border);
    void Set_bullet_dir(const int &bullet_dir0)
    {
        bullet_dir = bullet_dir0;
    }
    int Get_bullet_dir() const
    {
        return bullet_dir;
    }

private:
    int x_value;
    int y_value;
    bool is_move;
    int bullet_dir;
};

#endif // BULLET_OBJECT_H
