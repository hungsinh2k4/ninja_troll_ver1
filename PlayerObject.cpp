#include "PlayerObject.h"

PlayerObject ::PlayerObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_value = 0;
    y_value = 0;
    Width_Frame = 0;
    Height_Frame = 0;
    status = IDLE_RIGHT;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.up = 0;
    input_type.Throw_Right = 0;
    input_type.Throw_Left = 0;
    input_type.Slide_Left = 0;
    On_Ground = false;
    map_x = 0;
    map_y = 0;
    ComeBackTimer = 0;
    old_status = status;
    cout_uet = 0;
}

PlayerObject ::~PlayerObject()
{
}

bool PlayerObject ::LoadImg(std ::string path, SDL_Renderer *screen)
{
    bool rec = BaseObject ::LoadImg(path, screen);
    if (rec == true)
    {
        Width_Frame = rect.w / 10;
        Height_Frame = rect.h;
    }
    return rec;
}

SDL_Rect PlayerObject ::Get_Rect_Frame()
{
    SDL_Rect tRect;
    tRect.x = rect.x;
    tRect.y = rect.y;
    tRect.w = Width_Frame;
    tRect.h = Height_Frame;
    return tRect;
}

void PlayerObject ::set_clips()
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
void PlayerObject ::Show(SDL_Renderer *des)
{

    //  dùng đẻ load cái frame tiếp theo

    UpdateImagePlayer(des);
    if (input_type.left == 1 || input_type.right == 1)
    {
        // do có 10 frame nên dùng cáI này đẻ nó lặp lại việc load từng tấm
        frame = (frame + 1) % 10;
    }

    if (input_type.left == 0 && input_type.right == 0)
    {
        frame = (frame + 1) % 10;
    }

    if (ComeBackTimer == 0)
    {
        // trong thoi gian hồi sinh thi ko load anh

        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y; // why
        // bởi vì khi chúng ta chạy nv thì màn hinhf đi theo x_pos tính từ mốc ban đầu đến hiện tại
        // màn hình hiển thị từ map_x trờ đi - mao_x để bị đi theo ;

        SDL_Rect *current_clip = &frame_clip[frame];

        SDL_Rect renderQuad = {rect.x, rect.y, Width_Frame, Height_Frame};

        SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
    }
}

void PlayerObject ::HandelInputAction(SDL_Event events, SDL_Renderer *screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status = WALK_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            UpdateImagePlayer(screen);
        }
        break;
        case SDLK_LEFT:
        {
            status = WALK_LEFT;
            input_type.left = 1;
            input_type.right = 0;
            UpdateImagePlayer(screen);
        }
        break;
        case SDLK_s:
        {
            if (cout_uet > 0)
            {
                BulletObject *p_bullet = new BulletObject();
                if (status == WALK_RIGHT || status == IDLE_RIGHT)
                {
                    p_bullet->LoadImg("IMG_PNG\\PNG_Main\\Kunai_Right.png", screen);
                }
                else if (status == WALK_LEFT || status == IDLE_LEFT)
                {
                    p_bullet->LoadImg("IMG_PNG\\PNG_Main\\Kunai_Left.png", screen);
                }
                // Xét vị trí kunai

                if (status == WALK_LEFT || status == IDLE_LEFT)
                {
                    status = THROW_LEFT;
                    UpdateImagePlayer(screen);
                    p_bullet->Set_bullet_dir(BulletObject ::DIR_LEFT);
                    p_bullet->SetRect(this->rect.x, rect.y + Height_Frame * 0.55);
                }
                else if (status == WALK_RIGHT || status == IDLE_RIGHT)
                {
                    status = THROW_RIGHT;
                    UpdateImagePlayer(screen);
                    p_bullet->Set_bullet_dir(BulletObject ::DIR_RIGHT);
                    p_bullet->SetRect(this->rect.x + Width_Frame - 20, rect.y + Height_Frame * 0.55);
                }
                p_bullet->Set_x_value(20);
                p_bullet->Set_is_move(true);
                if (cout_uet == 1)
                {
                    // Nếu chỉ còn 1 viên đạn thì tạo viên đạn cuối cùng
                    p_bullet_list.push_back(p_bullet);
                    cout_uet = 0;
                }
                else
                {
                    p_bullet_list.push_back(p_bullet);
                    cout_uet--;
                }
            }
        }
        break;
        case SDLK_c:
        {
            if (status == WALK_RIGHT || status == IDLE_RIGHT)
            {
                status = SLIDE_RIGHT;
                input_type.Slide_Right = 1;
                input_type.jump = 0;
                UpdateImagePlayer(screen);
            }
            else if (status == WALK_LEFT || status == IDLE_LEFT)
            {
                status = SLIDE_LEFT;
                input_type.Slide_Left = 1;
                input_type.jump = 0;
                UpdateImagePlayer(screen);
            }
        }
        break;
        case SDLK_a:
        {
            if (status == WALK_RIGHT || status == IDLE_RIGHT)
            {
                status = ATTACK_RIGHT;
                // input_type.Attack_Right = 1;
                UpdateImagePlayer(screen);
            }
            else if (status == WALK_LEFT || status == IDLE_LEFT)
            {
                status = ATTACK_LEFT;
                UpdateImagePlayer(screen);
            }
        }
        break;
        }
        if (events.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            // Space bar was pressed
            input_type.jump = 1;
            if (input_type.Slide_Right == 1 || input_type.Slide_Left == 1)
            {
                input_type.jump = 0;
            }
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status = IDLE_RIGHT;
            input_type.right = 0;
            input_type.left = 0;
            input_type.Slide_Left = 0;
            input_type.Slide_Right = 0;
            UpdateImagePlayer(screen);
        }
        break;
        case SDLK_LEFT:
        {
            status = IDLE_LEFT;
            input_type.right = 0;
            input_type.left = 0;
            input_type.Slide_Left = 0;
            input_type.Slide_Right = 0;
            UpdateImagePlayer(screen);
        }
        break;
        case SDLK_SPACE:
        {
            input_type.jump = 0;
        }
        break;
        case SDLK_s:
        {
            if (status == THROW_RIGHT)
            {
                input_type.Throw_Right = 0;
                if (input_type.right == 0)
                {
                    status = IDLE_RIGHT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.right == 1)
                {
                    status = WALK_RIGHT;
                    UpdateImagePlayer(screen);
                }
            }
            else if (status == THROW_LEFT)
            {
                input_type.Throw_Left = 0;
                if (input_type.left == 0)
                {
                    status = IDLE_LEFT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.left == 1)
                {
                    status = WALK_LEFT;
                    UpdateImagePlayer(screen);
                }
            }
        }
        break;
        case SDLK_c:
        {
            if (status == SLIDE_RIGHT)
            {
                input_type.Slide_Right = 0;
                if (input_type.right == 0)
                {
                    status = IDLE_RIGHT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.right == 1)
                {
                    status = WALK_RIGHT;
                    UpdateImagePlayer(screen);
                }
            }
            else if (status == SLIDE_LEFT)
            {
                input_type.Slide_Left = 0;
                if (input_type.left == 0)
                {
                    status = IDLE_LEFT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.left == 1)
                {
                    status = WALK_LEFT;
                    UpdateImagePlayer(screen);
                }
            }
        }
        break;
        case SDLK_a:
            if (status == ATTACK_RIGHT)
            {
                if (input_type.right == 0)
                {
                    status = IDLE_RIGHT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.right == 1)
                {
                    status = WALK_RIGHT;
                    UpdateImagePlayer(screen);
                }
            }
            else if (status == ATTACK_LEFT)
            {
                if (input_type.left == 0)
                {
                    status = IDLE_LEFT;
                    UpdateImagePlayer(screen);
                }
                else if (input_type.left == 1)
                {
                    status = WALK_LEFT;
                    UpdateImagePlayer(screen);
                }
            }
            break;
        }
    }
}

void PlayerObject ::HandeleBullet(SDL_Renderer *des)
{
    for (int i = 0; i < p_bullet_list.size(); i++)
    {
        BulletObject *p_bullet = p_bullet_list.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->Get_is_move() == true)
            {
                p_bullet->HandelMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin() + i);
                if (p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void PlayerObject ::Do_Player(Map &map_data)
{

    if (ComeBackTimer == 0)
    {
        x_value = 0;
        y_value += DOWN_SPEED;
        // y_value là tốc độ khi nó rơi
        // khi tốc độ rơi bằng 1 lượng ổn định thì sẽ không tăng nữa

        if (y_value == MAX_DOWN_SPEED)
        {
            y_value = MAX_DOWN_SPEED;
        }

        // kiểm tra nếu player ấn nút bên trái thì sẽ găns x_value =  tốc độ của người chơi
        // tọa độ của của main chính sẽ trừ đi một lượng là :
        if (input_type.left == 1)
        {
            x_value -= PLAYER_SPEED;
            // kiểm tra nếu .....
            // tọa độ của của main chính sẽ công đi một lượng
        }
        else if (input_type.right == 1)
        {
            x_value += PLAYER_SPEED;
        }
        else if (input_type.Slide_Right == 1)
        {
            x_value += PLAYER_SILE;
        }
        else if (input_type.Slide_Left == 1)
        {
            x_value -= PLAYER_SILE;
        }
        if (input_type.jump == 1)
        {
            Mix_PlayChannel(-1, audio.gJump, 0);
            if (On_Ground == true)
            {
                y_value = -PLAYER_JUMP;
            }
            On_Ground = false;
            input_type.jump = 0;
        }
        Check_Map(map_data);
        SeachOnMap(map_data);
    }

    // kiểm tra dư liệu của map
    if (ComeBackTimer > 0)
    {
        ComeBackTimer--;
        if (ComeBackTimer == 0)
        {
            InitPlayer();
            Check_Map(map_data);
            SeachOnMap(map_data);
        }
    }
}

void PlayerObject::SeachOnMap(Map &map_data)
{
    int new_start_x = x_pos - (SCREEN_WIDTH / 2);
    int new_start_y = y_pos - (SCREEN_HEIGHT / 2);

    if (new_start_x < 0)
    {
        new_start_x = 0;
    }
    else if (new_start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        new_start_x = map_data.max_x - SCREEN_WIDTH;
    }

    if (new_start_y < 0)
    {
        new_start_y = 0;
    }
    else if (new_start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        new_start_y = map_data.max_y - SCREEN_HEIGHT;
    }

    map_data.start_x = new_start_x * 1;
    map_data.start_y = new_start_y * 1;
}

void PlayerObject ::Check_Map(Map &map_data)
{

    // đây là hàm chính kiểu tra nhân vật va chạm với map đã tạo ra

    // hoành độ nhân vật
    // đứng trên x1,y1;
    int x1 = 0;
    int x2 = 0;
    // kết thúc ở x2,y2;
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

    /*
        x1, y1******x2,y1
        *               *
        *               *
        *               *
        x1,y2*******x2,y2

    */

    // kiểm tra nó nằm trên bản độf
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_value > 0)
        { // PlayerObject is moving to height
            // trạng thái của ô đấy khác ô trống
            int value1 = map_data.Tile[y1][x2];
            int value2 = map_data.Tile[y2][x2];

            if (value1 == UET || value2 == UET)
            {
                map_data.Tile[y1][x2] = 0;
                map_data.Tile[y2][x2] = 0;
                IncreasseUet();
            }
            else
            {
                if ((value1 != BLANK_TILE || value2 != BLANK_TILE) && (value1 != 14 && value2 != 14))
                {

                    // vị trí bị va đập thì ko được +  thêm x_value nưã mà cho nó ở trang thái đấy
                    x_pos = x2 * TILE_SIZE;
                    x_pos -= Width_Frame + 1;
                    // ra vị trí biên của nhân vật
                    x_value = 0;
                }
            }
            if (y2 == 3 && x2 == 16)
            {
                map_data.Tile[y2][x2] = 2;
            }
        }
        else if (x_value < 0)
        {

            int value1 = map_data.Tile[y1][x1];
            int value2 = map_data.Tile[y2][x1];

            if (value1 == UET || value2 == UET)
            {
                map_data.Tile[y1][x1] = 0;
                map_data.Tile[y2][x1] = 0;
                IncreasseUet();
            }
            else
            {
                if ((value1 != BLANK_TILE || value2 != BLANK_TILE) && (value1 != 14 && value2 != 14))
                {
                    x_pos = (x1 + 1) * TILE_SIZE;
                    x_value = 0;
                }
            }
            // đi lùi cũng tươg tự thôi
        }
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
            if (value1 == UET || value2 == UET)
            {
                map_data.Tile[y2][x1] = 0;
                map_data.Tile[y2][x2] = 0;
                IncreasseUet();
            }
            else
            {
                if ((value1 != BLANK_TILE || value2 != BLANK_TILE) && (value1 != 14 && value2 != 14))
                {
                    y_pos = y2 * TILE_SIZE;
                    y_pos -= Height_Frame;
                    y_value = 0;
                    On_Ground = true;
                }
            }
            if (value1 == TROLL_1)
            {
                for (int i = 0; i <= 1; i++)
                {
                    map_data.Tile[y2 + i][x1] = 0;
                    map_data.Tile[y2 + i][x1 + 1] = 0;
                }
                // // Thiết lập chế độ blend mode cho renderer
                // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

                // // Vẽ hình chữ nhật trong suốt
                // SDL_Rect rect = {x1 * TILE_SIZE, y1 * TILE_SIZE, 64, 64};
                // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Màu đen, alpha = 0 (trong suốt)
                // SDL_RenderFillRect(renderer, &rect);
            }
            else if (value2 == TROLL_1)
            {
                for (int i = 0; i <= 1; i++)
                {
                    map_data.Tile[y2 + i][x2] = 0;
                    map_data.Tile[y2 + i][x2 + 1] = 0;
                }
            }
            if (value1 == 4)
            {
                map_data.Tile[y2][x1] = 0;
                map_data.Tile[y2][x1 - 1] = 0;
            }
            else if (value2 == 4)
            {
                map_data.Tile[y2][x2] = 0;
                map_data.Tile[y2][x2 - 1] = 0;
            }
        }
        else if (y_value < 0)
        {
            int col = x_pos / TILE_SIZE; // cột của ô mà nhân vật chạm vào
            int row = y_pos / TILE_SIZE; // hàng của ô mà nhân vật chạm vào

            int value1 = map_data.Tile[y1][x1];
            int value2 = map_data.Tile[y1][x2];
            if (value1 == UET || value2 == UET)
            {
                map_data.Tile[y1][x1] = 0;
                map_data.Tile[y1][x2] = 0;
                IncreasseUet();
            }
            else
            {
                if ((value1 != BLANK_TILE || value2 != BLANK_TILE) && (value1 != 14 && value2 != 14))
                {
                    y_pos = (y1 + 1) * TILE_SIZE;
                    y_value = 0;
                }
            }
            if (value1 == 16)
            {
                map_data.Tile[y1][x1] = 15;
                if (y1 == 5 && x1 == 19)
                {
                    PlayerObject ::a.push_back(2688);
                    map_data.Tile[y1 - 2][x1] = 7;
                }
                if (y1 == 1 && x1 == 36)
                {
                    map_data.Tile[y1 + 2][x1] = 0;
                }
            }
            else if (value2 == 16)
            {
                map_data.Tile[y1][x2] = 15;
                if (y1 == 5 && x2 == 19)
                {
                    PlayerObject ::a.push_back(2688);
                    map_data.Tile[y1 - 2][x2] = 7;
                }
                if (y1 == 1 && x2 == 36)
                {
                    map_data.Tile[y1 + 2][x2] = 0;
                }
            }
            if (y1 == 3 && x1 == 16)
            {
                map_data.Tile[y1][x1] = 2;
            }
            if (y1 == 3 && x2 == 16)
            {
                map_data.Tile[y1][x2] = 2;
            }
            if (y1 == 5 && (x1 == 43 || x1 == 44 || x1 == 45 || x1 == 46))
            {
                map_data.Tile[y1][x1] = 15;
            }
            else if (y1 == 5 && (x2 == 43 || x2 == 44 || x2 == 45 || x2 == 46))
            {
                map_data.Tile[y1][x2] = 15;
            }
            if (y1 == 5 && x1 == 46)
            {
                map_data.Tile[y1 + 3][x1] = 0;
                map_data.Tile[y1 + 4][x1] = 0;
            }
            if (y1 == 6 && x1 == 60)
            {
                map_data.Tile[y1 - 3][x1] = 3;
            }
            if (y1 == 5 && x1 == 75)
            {
                map_data.Tile[y1 + 3][x1] = 0;
                map_data.Tile[y1 + 4][x1] = 0;
                map_data.Tile[y1 + 3][x1 + 1] = 0;
                map_data.Tile[y1 + 4][x1 + 1] = 0;
                map_data.Tile[y1 + 3][x1 - 1] = 0;
                map_data.Tile[y1 + 4][x1 - 1] = 0;
            }
            if (y1 == 1 && x1 == 115)
            {
                map_data.Tile[y1][x1] = 3;
            }
            else if (y1 == 1 && x2 == 115)
            {
                map_data.Tile[y1][x2] = 3;
            }
            if (y1 == 3 && (x1 == 114 || x1 == 115 || x1 == 116 || x1 == 117))
            {
                map_data.Tile[y1][x1] = 15;
            }
            else if (y1 == 3 && (x2 == 114 || x2 == 115 || x2 == 116 || x2 == 117))
            {
                map_data.Tile[y1][x2] = 15;
            }
            if (y1 == 5 && x1 == 171)
            {
                map_data.Tile[y1][x1] = 15;
                map_data.Tile[y1 - 2][x1] = 7;
                map_data.Tile[y1 - 2][x1 - 1] = 7;
                map_data.Tile[y1 - 2][x1 + 1] = 7;
            }
            else if (y1 == 5 && x2 == 171)
            {
                map_data.Tile[y1][x2] = 15;
                map_data.Tile[y1 - 2][x2] = 7;
                map_data.Tile[y1 - 2][x2 - 1] = 7;
                map_data.Tile[y1 - 2][x2 + 1] = 7;
            }
        }
    }
    x_pos += x_value;
    y_pos += y_value;
    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + Width_Frame >= map_data.max_x)
    {
        x_pos = map_data.max_x - Width_Frame + 2;
        x_value = 0;
    }

    if (y_pos > map_data.max_y)
    {
        Mix_PlayChannel(-1, audio.Troll, 0);
        ComeBackTimer = 30;
        y_pos = map_data.max_y;
    }
}

void PlayerObject ::IncreasseUet()
{
    cout_uet++;
}

void PlayerObject ::UpdateImagePlayer(SDL_Renderer *des)
{
    if (On_Ground == true)
    {
        if (status == WALK_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Player_Left.png", des);
        }
        else if (status == WALK_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Player_Right.png", des);
        }
        else if (status == IDLE_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Player_Idle_Right.png", des);
        }
        else if (status == IDLE_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Player_Idle_Left.png", des);
        }
        else if (status == THROW_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Throw_Right.png", des);
        }
        else if (status == THROW_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Throw_Left.png", des);
        }
        else if (status == SLIDE_RIGHT)
        {
            LoadImg("IMG_PNG\\Menu\\start.png", des);
        }
        else if (status == SLIDE_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Slide_Left.png", des);
        }
        else if (status == ATTACK_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Attack1_Right.png", des);
        }
        else if (status == ATTACK_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Attack1_Left.png", des);
        }
    }
    else
    {
        if (status == WALK_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Jump_Left.png", des);
        }
        else if (status == WALK_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Jump_Right1.png", des);
        }
        else if (status == IDLE_RIGHT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Jump_Right1.png", des);
        }
        else if (status == IDLE_LEFT)
        {
            LoadImg("IMG_PNG\\PNG_Main\\Jump_Left.png", des);
        }
    }
    set_clips();
}

bool PlayerObject ::Get_You_Die()
{
    if (ComeBackTimer == 30)
    {
        return true;
    }
    return false;
}
bool PlayerObject ::Set_x_pos_playermain(const float &x_pos_background)
{
    if (x_pos > x_pos_background)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PlayerObject ::InitPlayer()
{
    x_value = 0;
    y_value = 0;
    map_x = 0;
    x_pos = 0;
    y_pos = 0;
    ComeBackTimer = 0;
}