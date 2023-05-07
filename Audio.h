#ifndef AUDIO_H
#define AUDIO_H

#include "Commonfunc.h"
class Audio
{
public:
    Audio();

    ~Audio();

    static Mix_Music *gingame;
    static Mix_Music *gMenu;
    static Mix_Chunk *gWinGame;
    static Mix_Chunk *gMenuButton;
    static Mix_Chunk *gLoseGame;
    static Mix_Chunk *gJump;
    static Mix_Chunk *Troll;
    static Mix_Chunk *gImpact;
    static Mix_Chunk *gDie_Mod;

    void MusicInit();

    void ChannelInit();

    void MusicClose();

    void ChannelClose();
};

#endif
