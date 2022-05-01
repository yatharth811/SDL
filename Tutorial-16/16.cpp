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
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

// Class wrapper for texture
class LTexture{
    public:
        //Initialise Variables
        LTexture();
        
        //Deallocate Memory
        ~LTexture();

        bool loadFromFile(string path);

        #if defined(SDL_TTF_MAJOR_VERSION)
        bool loadFromRenderedText(string text, SDL_Color color);
        #endif

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

class LButton{
    public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render();

    private:
    SDL_Point mPosition;
    LButtonSprite currentSprite;
};

SDL_Rect gSpriteClips[4];
TTF_Font* gFont = NULL;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gTexture;
LButton gButtons[BUTTON_SPRITE_TOTAL];

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

#if defined(SDL_TTF_MAJOR_VERSION)
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
#endif

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

LButton::LButton(){
    mPosition.x = 0;
    mPosition.y = 0;

    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y ){
    mPosition.x = x;
    mPosition.y = y;
}

void LButton :: handleEvent(SDL_Event* e){
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if( x < mPosition.x ){
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }

        if (!inside){
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else{
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}


void LButton::render(){
    //Show current button sprite
    gTexture.render( mPosition.x, mPosition.y, &gSpriteClips[currentSprite ] );
}


bool loadMedia(){
    bool success = true;

    if (!gTexture.loadFromFile("button.png")){
        cout << "F in chat for buttons." << endl;
        success = false;
    }
    else{
        for (int i=0; i<BUTTON_SPRITE_TOTAL; i++){
            gSpriteClips[ i ].x = 0;
            gSpriteClips[ i ].y = i * 200;
            gSpriteClips[ i ].w = BUTTON_WIDTH;
            gSpriteClips[ i ].h = BUTTON_HEIGHT;
        }
        gButtons[ 0 ].setPosition( 0, 0 );
        gButtons[ 1 ].setPosition( width - BUTTON_WIDTH, 0 );
        gButtons[ 2 ].setPosition( 0, height - BUTTON_HEIGHT );
        gButtons[ 3 ].setPosition( width - BUTTON_WIDTH, height - BUTTON_HEIGHT );
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
                for (int i=0; i<BUTTON_SPRITE_TOTAL; i++){
                    gButtons[i].render();
                }

                SDL_RenderPresent(gRenderer);

                while(SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit = true;
                        break;
                    }
                    for (int i=0; i<BUTTON_SPRITE_TOTAL; i++){
                        gButtons[i].handleEvent(&e);
                    }
                }
            }
        }

    }
    close();
    return 0;
}