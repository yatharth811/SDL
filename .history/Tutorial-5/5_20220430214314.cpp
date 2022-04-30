#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
using namespace std;

enum KeyMaps{
    KEY_DEFAULT,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_TOTAL
};

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gKeySurfaces[KEY_TOTAL];

bool init() {
  
    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not be initialised. " << SDL_GetError() << endl;
        success = false;
    }
    
    else {
        gWindow = SDL_CreateWindow("Tutorial - 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            cout << "Window couldn't be initialised. " << SDL_GetError() << endl;
            success = false;
        } 

        else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

SDL_Surface* loadSurface(string path){
    SDL_Surface* optimisedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface = NULL){
        cout << "Media could not be loaded. " << SDL_GetError() <<  endl;
    }
    else{
        optimisedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface -> format, 0);
        if (optimisedSurface = NULL){
            cout << "Could not optimise surface. " << SDL_GetError() << endl;
        }
    
        SDL_FreeSurface(loadedSurface);
    }

    return optimisedSurface;
}

bool loadMedia() {
    bool success = true;

    gKeySurfaces[KEY_DEFAULT] = loadSurface("1.jpg");

    if (gKeySurfaces[KEY_DEFAULT] == NULL) {
        cout << "Media could not be loaded." << endl;
        success = false;
    }

    gKeySurfaces[KEY_UP] = loadSurface("2.jpg");
    if (gKeySurfaces[KEY_UP] == NULL) {
        cout << "Media could not be loaded." << endl;
        success = false;
    }

    gKeySurfaces[KEY_DOWN] = loadSurface("3.jpg");
    if (gKeySurfaces[KEY_DOWN] == NULL) {
        cout << "Media could not be loaded." << endl;
        success = false;
    }

    gKeySurfaces[KEY_LEFT] = loadSurface("4.jpg");
    if (gKeySurfaces[KEY_LEFT] == NULL) {
        cout << "Media could not be loaded." << endl;
        success = false;
    }

    gKeySurfaces[KEY_RIGHT] = loadSurface("5.jpg");
    if (gKeySurfaces[KEY_RIGHT] == NULL) {
        cout << "Media could not be loaded." << endl;
        success = false;
    }

    return success;
}

void close() {
    for (int i=0; i<KEY_TOTAL; i++){
        SDL_FreeSurface(gKeySurfaces[i]);
        gKeySurfaces[i] = NULL;
    }

    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main(int argc, char *args[]) {

    if (!init()) {
        cout << "SADLY NOT INITIALISED" << endl;
    }

    else {
        if (!loadMedia()) {
        cout << "SADLY MEDIA COULD NOT BE INITIALISED" << endl;
        } 
        else {
            SDL_Event e;
            bool quit = false;
            SDL_Rect stretchRect;
            stretchRect.x = 0;
            stretchRect.y = 0;
            stretchRect.w = 1366;
            stretchRect.h = 768;
            // SDL_BlitScaled(gKeySurfaces[KEY_DEFAULT], NULL, gScreenSurface, &stretchRect);
            gCurrentSurface = gKeySurfaces[KEY_DEFAULT];
            while(!quit){
                SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
                SDL_UpdateWindowSurface(gWindow);
                while(SDL_PollEvent(&e)){

                    if (e.type == SDL_QUIT){quit = true; break;}
                    
                    else if (e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                                gCurrentSurface = gKeySurfaces[KEY_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeySurfaces[KEY_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeySurfaces[KEY_LEFT];
                                break;
                            case SDLK_RIGHT:
                                gCurrentSurface = gKeySurfaces[KEY_RIGHT];
                                break;
                            default:
                                gCurrentSurface = gKeySurfaces[KEY_DEFAULT];
                                break;
                        }
                    }
                }
            }
        }
    }

    close();
    return 0;

}
