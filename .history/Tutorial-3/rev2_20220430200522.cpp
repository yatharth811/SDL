#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bits/stdc++.h>
using namespace std;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not be initialised. " << SDL_GetError() << endl;
    success = false;
  } else {
    gWindow =
        SDL_CreateWindow("Tutorial - 2", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window couldn't be initialised. " << SDL_GetError() << endl;
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  gHelloWorld = SDL_LoadBMP("sample.bmp");
  if (gHelloWorld == NULL) {
    cout << "Media could not be loaded." << endl;
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(int argc, char *args[]) {
  if (!init()) {
    cout << "SADLY NOT INITIALISED" << endl;
  } else {
    if (!loadMedia()) {
      cout << "SADLY MEDIA COULD NOT BE INITIALISED" << endl;
    } else {
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
      SDL_Delay(200);
    }
  }
  close();
  return 0;
}
