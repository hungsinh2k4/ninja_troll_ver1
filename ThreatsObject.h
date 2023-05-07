#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H

#include <vector>
#include "Commonfunc.h"
#include "BaseObject.h"
#include "Bullet.h"

#define GRAVITY_SPEED 0.8

#define RUN_SPEED 5

#define MAX_GRAVITY_SPEED 10

#define BOT_SPEED 5

#define BOT_JUMP = 10

class ThreatsObject : public BaseObject
{

public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_BOT = 1,
    };
    void Set_x_value(const float &x_value0) { x_value = x_value0; }
    void Set_y_value(const float &y_value0) { y_value = y_value0; }

    void Set_x_pos(const float &x_pos0) { x_pos = x_pos0; }
    void Set_y_pos(const float &y_pos0) { y_pos = y_pos0; }

    float Get_x_pos() const { return x_pos; }
    float Get_y_pos() const { return y_pos; }

    int Get_width_frame() const { return Width_Frame; }
    int Get_HeightFrame() const { return Height_Frame; }

    bool LoadImg(std ::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer *des);

    void set_clips();

    void Do_Bot(Map &map_data);

    void Check_Map(Map &map_data);

    void Set_MapXY(const int map_x0, const int map_y0)
    {
        map_x = map_x0;
        map_y = map_y0;
    }

    void InitBot();

    // cập nhật Hình ảnh hiện tại của player
    void UpdateImageBot(SDL_Renderer *des);

    // dan
    // void Set_bullet_list (std :: vector<BulletObject*>  bullet_list) {
    //     p_bullet_list = bullet_list;
    //

    // xử lí khi ấn phím tạo ra đạn

    void Set_Type_Move(const int &Type_Move0) { Type_Move = Type_Move0; }
    void SetAnimationPos(const int &pos_left, const int &pos_right)
    {
        Animation_Left = pos_left;
        Animation_Right = pos_right;
    }
    void Set_Input_Left(const int &input_left) { input_type.left = input_left; }
    void ImpMoveType(SDL_Renderer *screen);

    void Check_Die_Bot(SDL_Renderer *des);

    std ::vector<BulletObject *> Get_bullet_list() const { return p_bullet_list; }

    void set_bullet_list(const std::vector<BulletObject *> &am_list) { p_bullet_list = am_list; }

    void ResetBullet(BulletObject *p_bullet);

    void CreateBullet(BulletObject *p_bullet, SDL_Renderer *screen);

    void MakeBullet(SDL_Renderer *des, const int &x_limit, const int &y_limit);

    void FreeBullet(const int &idx);

    int bot_die = false;

    SDL_Rect Get_Rect_Frame();

private:
    std ::vector<BulletObject *> p_bullet_list;

    float x_value;
    float y_value;

    float x_pos;
    float y_pos;

    float wall_x;

    int Width_Frame;
    int Height_Frame;

    SDL_Rect frame_clip[10];

    Input input_type;

    int frame;
    int status;

    int On_Ground;

    int map_x;
    int map_y;

    bool is_alive;

    bool is_stop_bullet;

    int Animation_Left = 0;
    int Animation_Right = 0;
    int Type_Move = 0;

    // thời gian rơi xuống vực sẽ quay trở lại ở trên mặt đất trc đố
    int ComeBackTimer;
};

#endif