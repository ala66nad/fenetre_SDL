#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <array>

#define UNHEX(c) ((c >> 8 * 3) & 0xFF), ((c >> 8 * 2) & 0xFF), ((c >> 8 * 1) & 0xFF), ((c >> 8 * 0) & 0xFF)

//----------------------------------------------------------------------
SDL_Window *window{nullptr};
SDL_Renderer *renderer{nullptr};
SDL_Rect backGround{0, 0, 800, 640};
bool running{true};
int _limitR{0}, _x{50}, _y{300};
std::array<int, 4> _fps_limit{1000 / 20, 1000 / 30, 1000 / 60, 1000 / 90};

//----------------------------------------------------------------------
bool OnInit();
void OnError(std::string);
void OnCleanUp();
void OnLoop();
void OnEvent(SDL_Event *Event);
void OnDraw(SDL_Rect rectangle);
void OnRender(SDL_Rect rectangle);
void LimitFPS(uint32_t limit);
void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod, SDL_Keycode scancode);
void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod, SDL_Keycode scancode);

//----------------------------------------------------------------------
int main(int argc, char *argv[])
{    
    if (OnInit() == false)
    {
        return -1;
    }    
    OnLoop();
    OnCleanUp();
    return 0;
}

//----------------------------------------------------------------------
void OnRender(SDL_Rect rectangle)
{
    if (SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255) != 0)
        OnError("Impossible de changer la couleur du rendu");    
    SDL_RenderClear(renderer);
    OnDraw(rectangle);
    SDL_RenderPresent(renderer);
}

//----------------------------------------------------------------------
void OnDraw(SDL_Rect rectangle)
{
    if (SDL_SetRenderDrawColor(renderer, 255,255,0,255) != 0)
    {
        OnError("Impossible de changer la couleur du rendu");
    }

    if (SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
    {
        OnError("Impossible de dessiner");
    }

    if (SDL_SetRenderDrawColor(renderer, UNHEX(0xFF88EEFF)) != 0)
    {
        OnError("Impossible de changer la couleur du rendu");
    }

    if (SDL_RenderFillRect(renderer, &rectangle) != 0)
    {
        OnError("Impossible de dessiner");
    }

}

//----------------------------------------------------------------------
void OnEvent(SDL_Event *Event)
{
    switch (Event->type)
    {
    case SDL_KEYDOWN:
    {
        OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
        break;
    }

    case SDL_KEYUP:
    {
        OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
        break;
    }
    case SDL_QUIT:
        running = false;
        break;

    default:
        break;
    }
}

//----------------------------------------------------------------------
void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod, SDL_Keycode scancode)
{
    switch (sym)
    {
    case SDLK_KP_PLUS:
        _limitR = _limitR < std::size(_fps_limit) - 1 ? _limitR + 1 : 0;
        break;
    case SDLK_RIGHT:
        _x +=3;
        break;
    case SDLK_LEFT:
        _x -= 3;
        break;
    case SDLK_UP:
        _y -= 3;
        break;
    case SDLK_DOWN:
        _y += 3;
        break;
    default:
        break;
    }
}

//----------------------------------------------------------------------
void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod, SDL_Keycode scancode)
{
    // do nothing
}

//----------------------------------------------------------------------
void OnLoop()
{    
    SDL_Rect rectangle{_x, _y, 200, 150};
    uint32_t frame_limit = 0;
    SDL_Event Event;
    while (running)
    {
        while (SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }
        frame_limit = SDL_GetTicks() + _fps_limit[_limitR];
        OnRender(rectangle);
        LimitFPS(frame_limit);
        rectangle.x = _x;
        rectangle.y = _y;
    }
}

//----------------------------------------------------------------------
bool OnInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        OnError("Initialisation SDL");
        return false;
    }

    window = SDL_CreateWindow("Ma fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, backGround.w, backGround.h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        OnError("Creation de la fenetre a echouee");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        OnError("Impossible de creer le rendu");
        return false;
    }
    return true;
}

//----------------------------------------------------------------------
void LimitFPS(uint32_t limit)
{
    uint32_t ticks = SDL_GetTicks();
    if (limit < ticks)
        return;
    if (limit > ticks + _fps_limit[_limitR])
        SDL_Delay(_fps_limit[_limitR]);
    else
        SDL_Delay(limit - ticks);
}

//----------------------------------------------------------------------
void OnCleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//----------------------------------------------------------------------
void OnError(std::string s)
{
    std::cout << "Erreur : " << s << " > " << SDL_GetError() << std::endl;
    OnCleanUp();
}
//----------------------------------------------------------------------