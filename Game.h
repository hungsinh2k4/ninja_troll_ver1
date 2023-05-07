#ifndef GAME_H
#define GAME_H

// #include "Commonfunc.h"
// #include "BaseObject.h"
#include "Map.h"
#include "PlayerObject.h"
#include "FPSTimer.h"
#include "ThreatsObject.h"
// #include "Audio.h"

const std::string back_ground_menu = "Menu\\background_menu.png";
const std::string inPlay = "Menu\\play.png";
const std::string inPlay_Red = "IMG_PNG\\Menu\\play_red.png";
const std::string inStart = "IMG_PNG\\Menu\\start.png";
const std::string Exit_Game = "IMG_PNG\\Menu\\exit.png";
const std::string Exit_Game_Blue = "IMG_PNG\\Menu\\exit_blue.png";
const std ::string win_game = "IMG_PNG\\BackGround\\youwin.png";

// int GetRandom(int min, int max)
// {
//     return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
// }

class Game
{
public:
    Game();
    ~Game();
    bool InitData();
    bool LoadBackground();
    void close();
    void LoadSource();
    void update();
    void handleEvents();
    void Play_Game();
    bool running()
    {
        return isRunning;
    };

    void loadSource(SDL_Renderer *des);

    void renderButtons(SDL_Renderer *screen);

    void Menu_Game();

    bool LoadBackground_Menu();

    bool CheckXYButton(const int &x, const int &y, const SDL_Rect &rect);

    bool CheckCollision(const SDL_Rect &bot1, const SDL_Rect &bot2);

    int Status_Play = 0;
    void WinGame();

private:
    bool isRunning = true;
    Game_Map game_map;
    PlayerObject Player_main;
    FPSTimer Timer;
    BaseObject g_background;
    BaseObject gWinGame;
    BaseObject gBackGround_Menu;
    BaseObject play_button[2];
    BaseObject start_button;
    BaseObject exit_button[4];
    Map map_data;
    bool quit_game;
    Audio audio;
    SDL_Rect Rect;
    int mousex, mousey;
    // int Get_X = GetRandom(0, 1280);
    // int Get_Y = GetRandom(0, 640);
};

#endif