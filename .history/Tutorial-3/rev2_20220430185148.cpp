#include<SDL2/SDL.h>
#include<bits/stdc++.h>
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not be initialised. "  << SDL_GetError() << endl;
    }

}

bool loadMedia(){

}

bool close(){

}

int main(int argc, char* args[]){

}