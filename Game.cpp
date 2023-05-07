#include "Game.h"

Game ::Game()
{
}
Game ::~Game()
{
}

bool Game ::InitData()
{

    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        printf("Could not init SDL %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enable ");
        }
        g_window = SDL_CreateWindow("Game.cpp SDL2.0",
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (g_window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
            if (g_screen == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) && imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                audio.MusicInit();
                audio.ChannelInit();
            }
        }
    }

    play_button[0].SetRect(0, 610);
    start_button.SetRect(490, 255);
    exit_button[0].SetRect(495, 395);
    return success;
}

void Game ::loadSource(SDL_Renderer *des)
{
    play_button[0].LoadImg(inPlay, des);
    play_button[1].LoadImg(inPlay_Red, des);
    start_button.LoadImg(inStart, des);
    exit_button[0].LoadImg(Exit_Game, des);
    exit_button[1].LoadImg(Exit_Game_Blue, des);
}

bool Game ::CheckXYButton(const int &x, const int &y, const SDL_Rect &rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}
void Game ::renderButtons(SDL_Renderer *screen)
{
    play_button[0].Render(screen);
    start_button.Render(screen);
    exit_button[0].Render(screen);

    if (CheckXYButton(mousex, mousey, play_button[0].GetRect()))
    {
        play_button[1].SetRect(0, 610);
        play_button[1].Render(screen);
    }
    if (CheckXYButton(mousex, mousey, exit_button[0].GetRect()))
    {
        exit_button[1].SetRect(495, 395);
        exit_button[1].Render(screen);
    }
}

bool Game ::LoadBackground()
{
    bool ret = g_background.LoadImg("IMG_PNG\\BackGround\\backgroundmenu.png", g_screen);
    if (ret == false)
    {
        return false;
        std ::cout << "Error BackGround\n";
    }
    return true;
}

void Game ::close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}
PlayerObject vectorr;
std ::vector<ThreatsObject *> MakeBotList(const PlayerObject &player)
{
    std ::vector<ThreatsObject *> list_bot;
    ThreatsObject *dynamic_bot = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject *p_threat = (dynamic_bot + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("IMG_PNG\\PNG_Mod1\\golem1_run_left.png", g_screen);
            p_threat->set_clips();
            p_threat->Set_Type_Move(ThreatsObject ::MOVE_IN_SPACE_BOT);
            p_threat->Set_x_pos(vectorr.a[i]);
            p_threat->Set_y_pos(200);

            int pos1 = p_threat->Get_x_pos() - 60;
            int pos2 = p_threat->Get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->Set_Input_Left(1);
            list_bot.push_back(p_threat);
        }
    }

    ThreatsObject *dynamic_bot2 = new ThreatsObject[15];
    for (int i = 0; i < vectorr.a.size() - 20; i++)
    {
        ThreatsObject *p_threat2 = (dynamic_bot2 + i);
        if (p_threat2 != NULL)
        {
            p_threat2->LoadImg("IMG_PNG\\PNG_Mod1\\golem2_throw_left.png", g_screen);
            p_threat2->set_clips();
            p_threat2->Set_Input_Left(0);
            p_threat2->Set_x_pos(vectorr.a[i + 20]);
            if (i >= 5 && i % 2 == 1)
            {
                p_threat2->Set_y_pos(250);
            }
            else
            {
                p_threat2->Set_y_pos(384);
            }

            p_threat2->Set_Type_Move(ThreatsObject::STATIC_THREAT);

            BulletObject *p_bullet = new BulletObject();
            p_threat2->CreateBullet(p_bullet, g_screen);
            // p_threat2->set_is_alive(true);
            list_bot.push_back(p_threat2);
        }
    }
    return list_bot;
}
void Game ::LoadSource()
{
}
void Game ::update()
{
}

bool Game ::CheckCollision(const SDL_Rect &bot1, const SDL_Rect &bot2)
{
    int left_a = bot1.x;
    int right_a = bot1.x + bot1.w;
    int top_a = bot1.y;
    int bottom_a = bot1.y + bot1.h;

    int left_b = bot2.x;
    int right_b = bot2.x + bot2.w;
    int top_b = bot2.y;
    int bottom_b = bot2.y + bot2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

void PlayerObject ::EraseBullet(const int &idex)
{
    int size = p_bullet_list.size();
    if (size > 0 && idex < size)
    {
        BulletObject *p_bullet = p_bullet_list.at(idex);
        p_bullet_list.erase(p_bullet_list.begin() + idex);
        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void Game ::Play_Game()
{
    Mix_PlayMusic(audio.gingame, -1);
    game_map.LoadMap("map\\map01.txt");
    game_map.LoadTiles(g_screen);
    Player_main.LoadImg("IMG_PNG\\PNG_Main\\Player_Idle_Right.png", g_screen);
    Player_main.set_clips();
    quit_game = false;
    Timer.start();
    std ::vector<ThreatsObject *> bot_list = MakeBotList(vectorr);
    while (!quit_game)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            Timer.start();
            if (g_event.type == SDL_QUIT)
            {
                quit_game = true;
                isRunning = false;
            }
            Player_main.HandelInputAction(g_event, g_screen);
        }
        // SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
        map_data = game_map.Get_Map();

        Player_main.HandeleBullet(g_screen);

        Player_main.Set_MapXY(map_data.start_x, map_data.start_y);
        Player_main.Do_Player(map_data);
        Player_main.Show(g_screen);

        game_map.Set_Map(map_data);
        game_map.DrawMap(g_screen);
        if (Player_main.Get_You_Die() == true)
        {
            game_map.DrawMap(g_screen);
        }

        for (int i = 0; i < bot_list.size(); i++)
        {
            ThreatsObject *p_threat = bot_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->Set_MapXY(map_data.start_x, map_data.start_y);
                p_threat->Do_Bot(map_data);
                p_threat->ImpMoveType(g_screen);
                p_threat->Show(g_screen);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

                SDL_Rect Player_Rect = Player_main.Get_Rect_Frame();
                bool Bullet_Col = false;

                std::vector<BulletObject *> bullet_list = p_threat->Get_bullet_list();
                for (int am = 0; am < bullet_list.size(); am++)
                {
                    BulletObject *p_bullet = bullet_list.at(am);
                    if (p_bullet)
                    {
                        Bullet_Col = Game::CheckCollision(p_bullet->GetRect(), Player_Rect);
                        if (Bullet_Col == true)
                        {
                            p_threat->ResetBullet(p_bullet);
                            break;
                        }
                    }
                }

                SDL_Rect Threat_Rect = p_threat->Get_Rect_Frame();
                bool Bullet_Col2 = Game ::CheckCollision(Player_Rect, Threat_Rect);
                if (Bullet_Col || Bullet_Col2)
                {
                    int Comebacktimer = 30;
                    while (Comebacktimer--)
                    {
                        if (Comebacktimer == 0)
                        {
                            SDL_Delay(100);
                            Player_main.InitPlayer();
                        }
                    }
                    Mix_PlayChannel(-1, audio.Troll, 0);
                }
            }
        }

        std ::vector<BulletObject *> Bullet_Arr = Player_main.Get_bullet_list();
        for (int r = 0; r < Bullet_Arr.size(); ++r)
        {
            BulletObject *p_bullet = Bullet_Arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < bot_list.size(); ++t)
                {
                    ThreatsObject *p_threats = bot_list.at(t);
                    if (p_threats != NULL)
                    {
                        SDL_Rect Bot_Rect;
                        Bot_Rect.x = p_threats->GetRect().x;
                        Bot_Rect.y = p_threats->GetRect().y;
                        Bot_Rect.w = p_threats->Get_width_frame();
                        Bot_Rect.h = p_threats->Get_HeightFrame();

                        SDL_Rect Bullet_Rect = p_bullet->GetRect();
                        bool Bullet_Col = Game ::CheckCollision(Bullet_Rect, Bot_Rect);

                        if (Bullet_Col)
                        {
                            Player_main.EraseBullet(r);
                            long long die = 1000000;
                            Mix_PlayChannel(-1, audio.gDie_Mod, 0);
                            p_threats->Check_Die_Bot(g_screen);
                            p_threats->set_clips();
                            p_threats->Show(g_screen);
                            // p_threats->set_clips();
                            while (die--)
                            {
                                if (die == 0)
                                {
                                    SDL_Delay(200);
                                    p_threats->Free();
                                    bot_list.erase(bot_list.begin() + t);
                                }
                            }
                        }
                    }
                }
            }
        }

        int value1 = MAX_MAP_X * TILE_SIZE - (map_data.start_x + Player_main.GetRect().x);
        if (value1 < 0)
        {
            Status_Play = 2;
            quit_game = true;
        }

        SDL_RenderPresent(g_screen);

        // int real_time = Timer.get_stick();

        int Time_One_Frame = 1000 / FPS_SECOND; // ms
        Uint32 Frame_Start = SDL_GetTicks();
        int Frame_Timer = SDL_GetTicks() - Frame_Start;
        if (Time_One_Frame > Frame_Timer)
        {
            // tạo độ tre
            SDL_Delay(Time_One_Frame - Frame_Timer);
        }
    }
}

bool Game ::LoadBackground_Menu()
{
    bool ret = gBackGround_Menu.LoadImg("IMG_PNG\\Menu\\background_menu.png", g_screen);
    if (ret == false)
    {
        return false;
        std ::cout << "Error BackGround\n";
    }
    return true;
}
void Game ::Menu_Game()
{
    bool quit = false;
    Mix_PlayMusic(audio.gMenu, -1);
    while (!quit)
    {
        SDL_GetMouseState(&mousex, &mousey);

        while (SDL_PollEvent(&g_event) != 0)
        {

            if (g_event.type == SDL_QUIT)
            {
                quit = true;
                isRunning = true;
                SDL_Quit();
                return;
            }

            if (g_event.type == SDL_MOUSEBUTTONDOWN)
            {
                std ::cout << "Click Succeed\n";
                if (CheckXYButton(mousex, mousey, play_button[0].GetRect()))
                {
                    Mix_PlayChannel(-1, audio.gMenuButton, 0);
                    isRunning = true;
                    Status_Play = 1;
                    std ::cout << Status_Play << std ::endl;
                    quit = true;
                    std::cout << "ChecK Play succees\n";
                    return;
                }
                if (CheckXYButton(mousex, mousey, exit_button[0].GetRect()))
                {
                    Mix_PlayChannel(-1, audio.gMenuButton, 0);
                    quit = true;
                    isRunning = false;
                    std ::cout << "Check Exit Succees\n";
                    return;
                }
                if (CheckXYButton(mousex, mousey, start_button.GetRect()))
                {
                    Mix_PlayChannel(-1, audio.gMenuButton, 0);
                    std ::cout << "Click start succeed\n";
                    start_button.SetRect(rand() % (1280 - start_button.GetW()), rand() % (640 - start_button.GetH()));
                    start_button.Render(g_screen);
                }
            }
        }

        // SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_screen);
        gBackGround_Menu.Render(g_screen, NULL);
        loadSource(g_screen);

        renderButtons(g_screen);
        SDL_RenderPresent(g_screen);
    }
}

void Game ::WinGame()
{
    bool quit = false;
    Mix_PlayMusic(audio.gMenu, -1);
    while (!quit)
    {

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                quit = true;
                isRunning = true;
                SDL_Quit();
                return;
            }
        }
        SDL_RenderClear(g_screen);
        gWinGame.LoadImg(win_game, g_screen);
        gWinGame.Render(g_screen);
        SDL_RenderPresent(g_screen);
    }
}