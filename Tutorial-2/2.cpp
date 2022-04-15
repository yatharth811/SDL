#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bits/stdc++.h>

using namespace std;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;
const int width = 640;
const int height = 480;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << SDL_GetError() << endl;
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL-Tutorial-2", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "SDL Window could not be initialised. SDL_Error: "
           << SDL_GetError() << endl;
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  // Load image on screen
  gHelloWorld = SDL_LoadBMP("sample.bmp");

  if (gHelloWorld == NULL) {
    cout << "Image could not be loaded. SDL_Error: " << SDL_GetError() << endl;
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
    cout << "Failed to Initialize" << endl;
  } else {
    if (!loadMedia()) {
      cout << "Failed to load media" << endl;
    } else {
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
      SDL_Delay(2000);
    }
  }
  close();
  return 0;
}
