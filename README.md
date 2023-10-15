### Base SDL2

Créer un répertoire sdl (mkdir sdl)  
Copie le contenu du fichier SDL2-devel-x.x.x-mingw.zip dans répertoire sdl  
Créer un répertoire bin (mkdir bin)  

Sources :  
SDL2                    => https://www.libsdl.org/  
zip SDL2                => https://github.com/libsdl-org/SDL/releases  
MinGW-w64 for windos    => https://winlibs.com/  


## Initialisation de la SDL

|NOM DRAPEAU (FLAG)|UTILISATION|
|:--|:--|
|SDL_WINDOW_FULLSCREEN|Plein écran|
|SDL_WINDOW_FULLSCREEN_DESKTOP|Plein écran (selon la résolution du bureau)|
|SDL_WINDOW_BORDERLESS|Sans contours|
|SDL_WINDOW_MINIMIZED|Réduite (minimisée)|
|SDL_WINDOW_MAXIMIZED|Affichée en grand (maximisée)|
|SDL_WINDOW_SHOWN|Affichée (visible)|
|SDL_WINDOW_HIDDEN|Masquée (invisible)|
|SDL_WINDOW_RESIZABLE|Redimensionnable|
|SDL_WINDOW_OPENGL|Utilisable dans un contexte OpenGL|
|SDL_WINDOW_INPUT_GRABBED|Garde la souris à l'intérieur de la fenêtre|
|SDL_WINDOW_INPUT_FOCUS|Indique l'activité de la fenêtre (depuis entrée)|
|SDL_WINDOW_MOUSE_FOCUS|Indique si la souris survole la fenêtre (active ou non)|
|SDL_WINDOW_ALLOW_HIGHDPI|Mode "High-DPI" (depuis SDL 2.0.1)|
|SDL_WINDOW_FOREIGN|Fenêtre non créée avec la SDL|
