#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#define null NULL
using namespace std;


const int width = 1366;
const int height = 768;

SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Window* gWindow = NULL;

bool init(){
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << SDL_GetError() << endl;
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("Tutorial-6 Revision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        if (gWindow == null){
            cout << SDL_GetError() << endl;
            success = false;
        }
        else{
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == null){
                cout << SDL_GetError() << endl;
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imageFlags = IMG_INIT_PNG;
                if (!(IMG_Init(IMG_INIT_PNG) & imageFlags)){
                    cout << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }
    return success;
}

SDL_Texture* loadTexture(string path){
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if (newTexture == null){
        cout << IMG_GetError() << endl;
    }
    return newTexture;
}

bool loadMedia(){
    bool success = true;
    gTexture = loadTexture("1.jpg");

    if (gTexture == null){
        cout << "Texture image not loaded." << endl;
        success = false;
    }

    return success;
}

void close(){
    SDL_DestroyTexture(gTexture);
    gTexture = null;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = null;
    gWindow = null;

    IMG_Quit();
    SDL_Quit();

}

int main(int argc, char* args[]){
    if (!init()){
        cout << "Initialisation Failure" << endl;
    }
    else{
        if (!loadMedia()){
            cout << "Media Failure" << endl;
        }
        else{
            SDL_Event e;
            bool quit = false;
            while(!quit){
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
                SDL_RenderClear(gRenderer);

                SDL_Rect topLeft = {0, 0, width/2, height/2};
                SDL_RenderSetViewport(gRenderer, &topLeft);
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                SDL_Rect topRight = {width/2, 0, width/2, height/2};
                SDL_RenderSetViewport(gRenderer, &topRight);
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // SDL_Rect bottomVp = {0, height/2, width, height/2};
                // SDL_RenderSetViewport(gRenderer, &bottomVp);
                // SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                SDL_RenderPresent(gRenderer);
                while(SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit = true;
                        break;
                    }
                }
            }
        }

    }
    close();
    return 0;
}