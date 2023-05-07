#include "Audio.h"

Mix_Music *Audio::gingame = nullptr;
Mix_Music *Audio::gMenu = nullptr;
Mix_Chunk *Audio::gWinGame = nullptr;
Mix_Chunk *Audio::gMenuButton = nullptr;
Mix_Chunk *Audio::gLoseGame = nullptr;
Mix_Chunk *Audio ::gJump = nullptr;
Mix_Chunk *Audio ::Troll = nullptr;
Mix_Chunk *Audio ::gDie_Mod = nullptr;

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::MusicInit()
{
    gingame = Mix_LoadMUS("Sounds\\ingame.mp3");
    if (gingame == nullptr)
    {
        printf("Could not load GINGAME! %s\n");
        Mix_GetError();
    }

    gMenu = Mix_LoadMUS("Sounds\\onmenu.mp3");
    if (gMenu == nullptr)
    {
        printf("Could not load GMENU! %s\n");
        Mix_GetError();
    }
}

void Audio::ChannelInit()
{
    gMenuButton = Mix_LoadWAV("Sounds\\click.wav");
    if (gMenuButton == nullptr)
    {
        printf("Could not load gMenuButton %s\n");
        Mix_GetError();
    }

    // gWinGame = Mix_LoadWAV("audios/winMenu.wav");

    gLoseGame = Mix_LoadWAV("Sounds\\diemain.wav");

    gJump = Mix_LoadWAV("Sounds\\jump2.wav");
    if (gJump == nullptr)
    {
        printf("Could not load gJump %s\n");
        Mix_GetError();
    }
    Troll = Mix_LoadWAV("Sounds\\troll.wav");
    gDie_Mod = Mix_LoadWAV("Sounds\\diemod.wav");
}
