#include "Map.h"

void Game_Map ::LoadMap(const char *name)
{
    FILE *pf = NULL;
    fopen_s(&pf, name, "rb");
    if (pf == NULL)
    {
        return;
    }
    game_map.max_x = 0;
    game_map.max_y = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf_s(pf, "%d", &game_map.Tile[i][j]);
            int value = game_map.Tile[i][j];
            if (value > 0)
            {
                if (j > game_map.max_x)
                {
                    game_map.max_x = j;
                }
                if (i > game_map.max_y)
                {
                    game_map.max_y = i;
                }
            }
        }
    }
    game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = name;
    fclose(pf);
}

void Game_Map ::LoadTiles(SDL_Renderer *screen)
{
    char file_png[30];
    FILE *pf = NULL;

    for (int i = 0; i < MAX_TILES; i++)
    {
        sprintf_s(file_png, "map\\%d.png", i);
        fopen_s(&pf, file_png, "rb");
        if (pf == NULL)
        {
            continue;
        }
        fclose(pf);
        tile_map[i].LoadImg(file_png, screen);
    }
}

void Game_Map ::DrawMap(SDL_Renderer *screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    x1 = (game_map.start_x % TILE_SIZE) * (-1);
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    y1 = (game_map.start_y % TILE_SIZE) * (-1);
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map.start_x / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int value = game_map.Tile[map_y][map_x];
            if (value > 0)
            {
                tile_map[value].SetRect(j, i);
                tile_map[value].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}