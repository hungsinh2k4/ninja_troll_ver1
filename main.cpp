#include "Game.h"
Game *game = nullptr;
int main(int argc, char *argv[])
{
    game = new Game();
    if (game->InitData() == false)
    {
        return -1;
    }
    if (game->LoadBackground() == false)
    {
        return -1;
    }
    if (game->LoadBackground_Menu() == false)
    {
        return -1;
    }
    while (game->running())
    {
        switch (game->Status_Play)
        {
        case 0:
            std ::cout << game->Status_Play << std ::endl;
            game->Menu_Game();
            break;
        case 1:
            std ::cout << game->Status_Play << std ::endl;
            game->Play_Game();
            break;
        case 2:
            std ::cout << game->Status_Play << std ::endl;
            game->WinGame();
        default:
            SDL_Quit();
        }
        std ::cout << game->Status_Play << std ::endl;
        // game->Play_Game();
    }
    game->close();
    return 0;
}