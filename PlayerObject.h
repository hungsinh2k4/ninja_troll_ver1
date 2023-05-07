#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <vector>

#include "Commonfunc.h"
#include "BaseObject.h"
#include "Bullet.h"
#include "Audio.h"
// tốc độ khi rơi ban đâu
#define DOWN_SPEED 2.5
// tốc độ khi rơi max
#define MAX_DOWN_SPEED 30
// Tốc độ nguơif chơi di chuyển
#define PLAYER_SPEED 14
// tốc độ nhảy lên
#define PLAYER_JUMP 30

// tốc độ khi trượt
#define PLAYER_SILE 13

// Block lừa đaỏ heheeeeeeeeee

#define TROLL_1 1

#define TROLL_3 3

class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        IDLE_RIGHT = 2,
        IDLE_LEFT = 3,
        THROW_RIGHT = 4,
        THROW_LEFT = 5,
        SLIDE_RIGHT = 6,
        SLIDE_LEFT = 7,
        ATTACK_RIGHT = 8,
        ATTACK_LEFT = 9,
        WALK_NONE = 0,
    };

    // ham ao
    bool LoadImg(std ::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer *des);
    void HandelInputAction(SDL_Event events, SDL_Renderer *screen);
    void set_clips();
    void Do_Player(Map &map_data);
    void Check_Map(Map &map_data);
    void Set_MapXY(const int map_x0, const int map_y0)
    {
        map_x = map_x0;
        map_y = map_y0;
    }
    void SeachOnMap(Map &map_data);
    void Check_Jump(Map &map_data);

    // cập nhập Player đang hoạt động cái gì
    // tạm thời chưa làm
    void UpdatePlayer(SDL_Renderer *screen);

    // cập nhật Hình ảnh hiện tại của player
    void UpdateImagePlayer(SDL_Renderer *des);

    // dan
    void Set_bullet_list(std ::vector<BulletObject *> bullet_list)
    {
        p_bullet_list = bullet_list;
    }
    std ::vector<BulletObject *> Get_bullet_list() const { return p_bullet_list; }

    // xử lí khi ấn phím tạo ra đạn
    void HandeleBullet(SDL_Renderer *des);

    void IncreasseUet();

    void UpdateCameraPosition(Map &map_data, int &camera_x, int &camera_y, float smooth_factor);

    bool Get_You_Die();

    bool Set_x_pos_playermain(const float &x_pos_background);

    void InitPlayer();

    void EraseBullet(const int &idex);

    void Return_ComeBackTime()
    {
        ComeBackTimer = 30;
    }

    SDL_Rect Get_Rect_Frame();

    std ::vector<int> a = {600, 1200, 1800, 2400, 3136, 3600, 4200, 4800, 5400, 6000,
                           6600, 7200, 7800, 8600, 9400, 10000, 10600, 11200, 11800, 12400,
                           12928, 14080, 14464, 15040, 16000};

private:
    Audio audio;

    std ::vector<BulletObject *> p_bullet_list;

    float x_value;
    float y_value;

    float x_pos;
    float y_pos;

    int Width_Frame;
    int Height_Frame;

    SDL_Rect frame_clip[10];

    Input input_type;

    int frame;
    int status;

    int old_status;

    int On_Ground;

    int map_x;
    int map_y;
    int FPS = 1;
    int cout_uet;

    // thời gian rơi xuống vực sẽ quay trở lại ở trên mặt đất trc đố
    int ComeBackTimer;
};

#endif