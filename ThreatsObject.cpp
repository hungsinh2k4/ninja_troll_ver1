#include "ThreatsObject.h"

ThreatsObject ::ThreatsObject()
{
    x_value = 0.0;
    y_value = 0.0;
    x_pos = 0.0;
    y_pos = 0.0;
    On_Ground = false;
    Width_Frame = 0;
    Height_Frame = 0;
    frame = 0;
    Type_Move = STATIC_THREAT;
    ComeBackTimer = 0;
    input_type.left = 0;
    input_type.right = 0;
    is_stop_bullet = false;
}

ThreatsObject ::~ThreatsObject()
{
    // đây dùng để giải phóng tài nguyên bộ nhớ đã cấp phất cho lớp bullet
    if (p_bullet_list.size() > 0)
    {
        for (int i = 0; i < p_bullet_list.size(); i++)
        {
            // truy cập vào chỉ số mong muốn
            BulletObject *p_bullet = p_bullet_list.at(i);
            if (p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list.clear();
    }
}

void ThreatsObject::ResetBullet(BulletObject *p_bullet)
{
    p_bullet->SetRect(x_pos + 20, y_pos + 10);
    p_bullet->Set_x_value(15);
}

bool ThreatsObject ::LoadImg(std ::string path, SDL_Renderer *screen)
{
    bool rec = BaseObject ::LoadImg(path, screen);
    if (rec == true)
    {
        Width_Frame = rect.w / 10;
        Height_Frame = rect.h;
    }
    return rec;
}

void ThreatsObject::CreateBullet(BulletObject *p_bullet, SDL_Renderer *screen)
{
    if (p_bullet)
    {
        // bool ret = p_bullet->LoadImg("IMG_PNG\\PNG_Main\\Kunai_Left.png", screen);
        // if (ret)
        // {
        p_bullet->LoadImg("IMG_PNG\\PNG_Main\\Kunai_Left.png", screen);
        p_bullet->Set_is_move(true);
        p_bullet->Set_bullet_dir(BulletObject::DIR_LEFT);
        // p_bullet->set_type(BulletObject::SPHERE);
        p_bullet->SetRect(rect.x + 5, rect.y + 10);
        p_bullet->Set_x_value(15);
        p_bullet_list.push_back(p_bullet);
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer *des, const int &x_limit, const int &y_limit)
{
    for (int i = 0; i < p_bullet_list.size(); i++)
    {
        BulletObject *p_bullet = p_bullet_list.at(i);
        if (p_bullet != NULL)
        {
            if (is_stop_bullet == false)
            {
                if (p_bullet->Get_is_move())
                {
                    int distance_bullet = rect.x + Width_Frame - p_bullet->GetRect().x;
                    if (distance_bullet > 0 && distance_bullet < 400)
                    {
                        p_bullet->HandelMove(x_limit, y_limit);
                        p_bullet->Render(des);
                    }
                    else
                    {
                        p_bullet->Set_is_move(false);
                    }
                }
                else
                {
                    p_bullet->Set_is_move(true);
                    p_bullet->SetRect(this->rect.x + 5, this->rect.y + 35);
                }
            }
        }
    }
}

void ThreatsObject::FreeBullet(const int &idx)
{
    if (p_bullet_list.size() > 0 && idx < p_bullet_list.size())
    {
        BulletObject *p_bullet = p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

SDL_Rect ThreatsObject ::Get_Rect_Frame()
{
    SDL_Rect tRect;
    tRect.x = rect.x;
    tRect.y = rect.y;
    tRect.w = Width_Frame;
    tRect.h = Height_Frame;
    return tRect;
}

void ThreatsObject ::set_clips()
{
    if (Width_Frame > 0 && Height_Frame > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            frame_clip[i].x = i * Width_Frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = Width_Frame;
            frame_clip[i].h = Height_Frame;
        }
    }
}

void ThreatsObject ::Do_Bot(Map &map_data)
{
    if (ComeBackTimer == 0)
    {
        x_value = 0;
        y_value += GRAVITY_SPEED;
        if (y_value >= MAX_GRAVITY_SPEED)
        {
            y_value = MAX_GRAVITY_SPEED;
        }
        if (input_type.left == 1)
        {
            x_value -= BOT_SPEED;
        }
        else if (input_type.right == 1)
        {
            x_value += BOT_SPEED;
        }
        Check_Map(map_data);
    }
    // else if (ComeBackTimer != 0)
    // {
    //     ComeBackTimer--;
    //     if (ComeBackTimer == 0)
    //     {
    //         InitBot();
    //     }
    // }
}

// void ThreatsObject ::InitBot()
// {
//     x_value = 0;
//     y_value = 0;
//     if (x_pos > 256)
//     {
//         x_pos -= 256;
//         Animation_Left -= 256;
//         Animation_Right -= 256;
//     }
//     else
//     {
//         x_pos = 0;
//     }
//     y_pos = 0;
//     ComeBackTimer = 0;
//     input_type.left = 1;
// }

void ThreatsObject ::Show(SDL_Renderer *des)
{

    //  dùng đẻ load cái frame tiếp theo

    // UpdateImageBot(des);
    //  if (input_type.left == 1 || input_type.right == 1) {
    //      // do có 10 frame nên dùng cáI này đẻ nó lặp lại việc load từng tấm
    //      frame = (frame + 1) % 10;
    //  }

    // if (input_type.left == 0 && input_type.right == 0) {
    //     frame = (frame + 1)  % 10;
    // }

    if (ComeBackTimer == 0)
    {
        // trong thoi gian hồi sinh thi ko load anh
        frame++;
        if (frame >= 10)
        {
            frame = 0;
        }
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y; // why
        // bởi vì khi chúng ta chạy nv thì màn hinhf đi theo x_pos tính từ mốc ban đầu đến hiện tại
        // màn hình hiển thị từ map_x trờ đi - mao_x để bị đi theo ;

        SDL_Rect *current_clip = &frame_clip[frame];

        SDL_Rect renderQuad = {rect.x, rect.y, Width_Frame, Height_Frame};

        SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
    }
}

void ThreatsObject::Check_Map(Map &map_data)
{

    // đây là hàm chính kiểu tra nhân vật va chạm với map đã tạo ra

    // hoành độ nhân vật
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // On_Ground == false;

    // check horizantai checkj chiều ngang
    // so sánh TILE_SIZE vối height_frame

    int Height_Min = Height_Frame < TILE_SIZE ? Height_Frame : TILE_SIZE;

    // tính tọa độ nhân vật xem đang ở ô thứ bao nhiêu ;
    x1 = (x_pos + x_value) / TILE_SIZE;
    // -1 là sai số để xử lí va chạm , đường biên nhân vât sẽ lùi lại 1 thì check sẽ chính xác hơn
    x2 = (x_pos + x_value + Width_Frame - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + Height_Frame - 1) / TILE_SIZE;

    // kiểm tra nó nằm trên bản độf
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_value > 0)
        { // Main_Chinh is moving to height
            // trạng thái của ô đấy khác ô trống
            int value1 = map_data.Tile[y1][x2];
            int value2 = map_data.Tile[y2][x2];
            if ((value1 != BLANK_TILE && value1 != UET) || (value2 != BLANK_TILE && value2 != UET))
            {

                // vị trí bị va đập thì ko được +  thêm x_value nưã mà cho nó ở trang thái đấy
                x_pos = x2 * TILE_SIZE;
                // ra vị trí biên của nhân vật
                x_pos -= Width_Frame + 1;
                x_value = 0;
                input_type.right = 0;
                input_type.left = 1;
            }
        }
        else if (x_value < 0)
        {

            int value1 = map_data.Tile[y1][x1];
            int value2 = map_data.Tile[y2][x1];
            if ((value1 != BLANK_TILE && value1 != UET) || (value2 != BLANK_TILE && value2 != UET))
            {
                x_pos = (x1 + 1) * TILE_SIZE;
                x_value = 0;
                // wall_x = x_pos;
                input_type.left = 0;
                input_type.right = 1;
            }
        }
        // đi lùi cũng tươg tự thôi
    }
    // check vertical
    int Width_Min = Width_Frame < TILE_SIZE ? Width_Frame : TILE_SIZE;
    // tính ô theo chiều ngang
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + Width_Min) / TILE_SIZE;
    // tính ô theo chiều dọc
    y1 = (y_pos + y_value) / TILE_SIZE;
    y2 = (y_pos + y_value + Height_Frame - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_value > 0)
        {
            int value1 = map_data.Tile[y2][x1];
            int value2 = map_data.Tile[y2][x2];
            if ((value1 != BLANK_TILE && value1 != UET) || (value2 != BLANK_TILE && value2 != UET))
            {
                y_pos = y2 * TILE_SIZE;
                y_pos -= Height_Frame + 1;
                y_value = 0;
                On_Ground = true;
            }
        }
        else if (y_value < 0)
        {
            int value1 = map_data.Tile[y1][x1];
            int value2 = map_data.Tile[y1][x2];
            if ((value1 != BLANK_TILE && value1 != UET) || (value2 != BLANK_TILE && value2 != UET))
            {
                y_pos = (y1 + 1) * TILE_SIZE;
                y_value = 0;
            }
        }
    }
    x_pos += x_value;
    y_pos += y_value;
    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + Width_Frame > map_data.max_x)
    {
        x_pos = map_data.max_x + Width_Frame - 1;
    }

    if (y_pos > map_data.max_y)
    {
        // roi xuong
        ComeBackTimer = 30;
    }
}

void ThreatsObject ::ImpMoveType(SDL_Renderer *screen)
{
    if (Type_Move == STATIC_THREAT)
    {
        //
    }
    else if (Type_Move == MOVE_IN_SPACE_BOT)
    {
        if (On_Ground == true)
        {
            if (input_type.right == 1)
            {
                LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_right.png", screen);
                if (x_pos > Animation_Right)
                {
                    // Animation_Right = wall_x;
                    input_type.left = 1;
                    input_type.right = 0;
                    // status = WALK_LEFT;
                    LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_left.png", screen);
                }
            }
            else if (input_type.left == 1)
            {
                LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_left.png", screen);
                if (x_pos < Animation_Left)
                {
                    // Animation_Left = wall_x;
                    input_type.right = 1;
                    input_type.left = 0;
                    // status = WALK_RIGHT;
                    LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_right.png", screen);
                }
            }
        }
        else if (On_Ground == false)
        {
            if (input_type.left == 1)
            {
                // status = WALK_LEFT;
                LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_left.png", screen);
            }
        }
    }
}

void ThreatsObject ::Check_Die_Bot(SDL_Renderer *des)
{
    bot_die = true;
    if (input_type.left == 1)
    {
        LoadImg("IMG_PNG\\PNG_Mod1\\golem1_die_left.png", des);
    }
    else if (input_type.left == 0)
    {
        LoadImg("IMG_PNG\\PNG_Mod1\\golem1_die_right.png", des);
    }
}
