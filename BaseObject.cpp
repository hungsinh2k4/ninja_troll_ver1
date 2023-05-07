#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_object = 0;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer *screen)
{
    Free();
    SDL_Texture *new_Texture = NULL;

    SDL_Surface *load_surface = IMG_Load(path.c_str());

    if (load_surface != NULL)
    {
        // SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)) ;
        new_Texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_Texture != NULL)
        {
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        else
        {
            // std ::cout << "Error createTexture form Surface\n";
            SDL_Log("Unable to create texture from surface. Error: %s", SDL_GetError());
        }
        SDL_FreeSurface(load_surface);
    }
    else
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    p_object = new_Texture;
    return p_object != NULL;
}

// bool BaseObject ::LoadImg(std::string path, SDL_Renderer *screen)
// {
//     SDL_Surface *surface = IMG_Load(path.c_str());
//     if (surface == NULL)
//     {
//         printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//         return false;
//     }

//     Free();

//     if (screen == NULL)
//     {
//         printf("Unable to create texture from %s! SDL Error: Invalid renderer\n", path.c_str());
//         SDL_FreeSurface(surface);
//         return false;
//     }

//     texture = SDL_CreateTextureFromSurface(screen, surface);
//     if (texture == NULL)
//     {
//         printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//         SDL_FreeSurface(surface);
//         return false;
//     }

//     rect.w = surface->w;
//     rect.h = surface->h;

//     SDL_FreeSurface(surface);

//     return true;
// }

void BaseObject::Render(SDL_Renderer *des, const SDL_Rect *clip)
{
    SDL_Rect Renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(des, p_object, clip, &Renderquad);
}
void BaseObject ::Free()
{
    if (p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
