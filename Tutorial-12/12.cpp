#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#define null NULL
using namespace std;


const int width = 640;
const int height = 480;

// Class wrapper for texture
class LTexture{
    public:
        //Initialise Variables
        LTexture();
        
        //Deallocate Memory
        ~LTexture();

        bool loadFromFile(string path);

        void free();

        // Render at x, y position
        void render(int x, int y, SDL_Rect* clip = NULL);

        void setColor(int r, int g, int b);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(int alpha);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gBgTexture;
LTexture gFgTexture;

LTexture :: LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture :: ~LTexture(){
    free();
}

bool LTexture :: loadFromFile(string path){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL){
        cout << "Image Load Error. " << IMG_GetError() << endl;
    }
    else{
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL){
            cout << "Texture Eroor. " << SDL_GetError() << endl;
        }
        else{
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture :: free(){
    if (mTexture!=null){
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture :: render(int x, int y, SDL_Rect* clip){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL){
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture :: getWidth(){
    return mWidth;
}

int LTexture :: getHeight(){
    return mHeight;
}

void LTexture :: setColor(int r, int g, int b){
    SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture :: setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture :: setAlpha(int alpha){
    SDL_SetTextureAlphaMod(mTexture, alpha);
}


bool loadMedia(){
    bool success = true;

    if (!gFgTexture.loadFromFile("fg.png")){
        success = false;
        cout << "F in chat for fg." << endl;
    }
    else{
        gFgTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    }

    if (!gBgTexture.loadFromFile("bg.png")){
        success = false;
        cout << "F in chat for bg." << endl;
    }

    return success;
}

void close(){
    gFgTexture.free();
    gBgTexture.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool init(){
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << SDL_GetError() << endl;
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("Tutorial - 11", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

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
            int a = 255;
            while(!quit){
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                gBgTexture.render(0, 0);

                gFgTexture.setAlpha(a);
                gFgTexture.render(0,0);

                SDL_RenderPresent(gRenderer);
                while(SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit = true;
                        break;
                    }
                    else if (e.type == SDL_KEYDOWN){
                        if (e.key.keysym.sym == SDLK_w){
                            a = min(255, a+32);
                        }
                        else if (e.key.keysym.sym == SDLK_s){
                            a = max(0, a-32);
                        }
                    }
                }
            }
        }

    }
    close();
    return 0;
}