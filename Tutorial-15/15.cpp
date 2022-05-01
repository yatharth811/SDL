#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#define null NULL
using namespace std;


const int width = 640;
const int height = 480;
// const int walkingAnimationFrames = 4;
// Class wrapper for texture
class LTexture{
    public:
        //Initialise Variables
        LTexture();
        
        //Deallocate Memory
        ~LTexture();

        bool loadFromFile(string path);

        bool loadFromRenderedText(string text, SDL_Color color);

        void free();

        // Render at x, y position
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

TTF_Font* gFont = NULL;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gTexture;

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

bool LTexture :: loadFromRenderedText(string text, SDL_Color color){
    free();

    SDL_Surface* loadedSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);

    if (loadedSurface == NULL){
        cout << "F in chat for text. " << SDL_GetError() << endl;
    }
    else{
        mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (mTexture == NULL){
            cout << "F in chat for texture from text. " << SDL_GetError() << endl;
        }
        else{
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    return mTexture!=NULL;
}

void LTexture :: free(){
    if (mTexture!=null){
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture :: render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL){
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture :: getWidth(){
    return mWidth;
}

int LTexture :: getHeight(){
    return mHeight;
}

bool loadMedia(){
    bool success = true;

    gFont = TTF_OpenFont("lazy.ttf",  28);

    if (gFont == NULL){
        cout << TTF_GetError() << endl;
        success = false;
    }
    else{
        SDL_Color color = {255,0,0};
        if (!gTexture.loadFromRenderedText("The road not taken.",  color)){
            success = false;
            cout << "F in chat for arrow." << endl;
        }
    }
   
    return success;
}

void close(){
    gTexture.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    TTF_Quit();
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
        gWindow = SDL_CreateWindow("Tutorial - 14", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

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

                if(TTF_Init() == -1){
                    cout << TTF_GetError() << endl;
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
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            double degrees = 0;
            while(!quit){
                
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                gTexture.render((width-gTexture.getWidth()) / 2, (height-gTexture.getHeight()) / 2, NULL, degrees, NULL, flipType);

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