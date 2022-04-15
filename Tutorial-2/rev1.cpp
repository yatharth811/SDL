#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bits/stdc++.h>
using namespace std;

const int width = 640;
const int height = 480;

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << SDL_GetError() << endl;
  } else {
    window = SDL_CreateWindow("SDL-Window", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {

    } else {
      screenSurface = SDL_GetWindowSurface(window);
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
      SDL_UpdateWindowSurface(window);
      SDL_Delay(2000);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  return 0;
}
