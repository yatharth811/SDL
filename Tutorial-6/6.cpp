#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
SDL_Renderer* gRenderer = NULL;

const int width = 1366;
const int height = 768; 


bool init(){

    bool success = true;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialised. " << SDL_GetError() << endl;
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("Tutorial - 6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            cout << "Window could not be initialised. " << SDL_GetError() << endl;
            success = false;
        }
        else{
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL){
                cout << "Renderer could not be initialised. " << SDL_GetError() << endl;
                success = false;           
            }
            else{
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imageFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imageFlags) & imageFlags)){
                    cout << "SDL_Image could not be initialised. " << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;

}

SDL_Texture* loadTexture(string path){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL){
        cout << "Media could not be loaded. " << IMG_GetError() << endl;
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL){
            cout << "Unable to create texture from surface. " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

SDL_Texture* loadTextureBetter(string path){
    SDL_Texture* newTexture = NULL;
    newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if (newTexture == NULL){
        cout << IMG_GetError() << endl;
    }
    return newTexture;
}

bool loadMedia(){
    bool success = true;
    gTexture = loadTextureBetter("1.jpg");
    if (gTexture == NULL){
        cout << "Failed to load texture image" << endl;
        success = false;
    }
    return success;
}

void close(){
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();

}

int main(int argc, char* args[]){
    if (!init()){
        cout << "Initialisation Failure." << endl;
    }
    else{
        if (!loadMedia()){
            cout << "Media Failure." << endl;
        }
        else{
            bool quit = false;
            SDL_Event e;
            while(!quit){
                SDL_RenderClear(gRenderer);
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
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