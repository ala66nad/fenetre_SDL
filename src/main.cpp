#include <SDL.h>
#include <iostream>
#include <string>

#define UNHEX(c) ((c >> 8 * 3) & 0xFF), ((c >> 8 * 2) & 0xFF), ((c >> 8 * 1) & 0xFF), ((c >> 8 * 0) & 0xFF)

//----------------------------------------------------------------------
SDL_Window *window{nullptr};
SDL_Renderer *renderer{nullptr};

bool OnInit();
void OnError(std::string);
void OnClean();

//----------------------------------------------------------------------
int main(int argc, char *argv[])
{

    if (OnInit() == false)
    {
        return -1;
    }

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255) != 0)
    {
        OnError("Impossible de changer la couleur du rendu");
    }

    if (SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
    {
        OnError("Impossible de dessiner");
    }

    if (SDL_SetRenderDrawColor(renderer, UNHEX(0xFF00EEFF)) != 0)
    {
        OnError("Impossible de changer la couleur du rendu");
    }

    SDL_Rect rectangle{300,300,200,150};
    if (SDL_RenderFillRect(renderer, &rectangle) != 0)
    {
        OnError("Impossible de dessiner");
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    OnClean();
    return 0;
}

//----------------------------------------------------------------------
bool OnInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        OnError("Initialisation SDL");
        return false;
    }

    window = SDL_CreateWindow("Ma fenetre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);
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
void OnClean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//----------------------------------------------------------------------
void OnError(std::string s)
{
    std::cout << "Erreur : " << s << " > " << SDL_GetError() << std::endl;
    OnClean();
}
//----------------------------------------------------------------------