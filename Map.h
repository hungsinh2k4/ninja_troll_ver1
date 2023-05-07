#ifndef MAP_H
#define MAP_H

#include "Commonfunc.h"
#include "BaseObject.h"

#define MAX_TILES 20
class TileMap : public BaseObject
{
public:
    TileMap() { ; }
    ~TileMap() { ; }
};

class Game_Map
{
public:
    Game_Map() { ; }
    ~Game_Map() { ; }

    void LoadMap(const char *name);
    void LoadTiles(SDL_Renderer *screen);
    void DrawMap(SDL_Renderer *screen);
    Map Get_Map() const { return game_map; }
    void Set_Map(Map &map_data)
    {
        game_map = map_data;
    };

private:
    Map game_map;
    TileMap tile_map[MAX_TILES];
};

#endif