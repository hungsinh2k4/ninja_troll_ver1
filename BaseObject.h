#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Commonfunc.h"
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y)
    {
        rect.x = x;
        rect.y = y;
    }
    int GetW() const { return rect.w; }
    int GetH() const { return rect.h; }
    SDL_Rect GetRect() const { return rect; }
    SDL_Texture *GetObject() const { return p_object; }

    // ham loadimg ao
    virtual bool LoadImg(std::string path, SDL_Renderer *screen);
    void Render(SDL_Renderer *des, const SDL_Rect *clip = NULL);
    void Free();

    void render_button(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip &flip);

    bool LoadImge(std ::string path);

protected:
    SDL_Texture *p_object;
    SDL_Rect rect;
};
#endif
