#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <bits/stdc++.h>
using namespace std;
// Screen dimension constants
const int width = 640;
const int height = 480;

int main(int argc, char *args[]) {
  // Initialize SDL Window
  SDL_Window *window = NULL;

  // Initialize SDL Surface
  SDL_Surface *screenSurface = NULL;

  // In case of error SDL_Init returns -1
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not Initialize. SDL_Error: " << SDL_GetError() << endl;
  } else {
    window = SDL_CreateWindow("SDL-WINDOW", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
      cout << "SDL Window could not be initialized. SDL_Error: "
           << SDL_GetError() << endl;
    } else {
      // get window surface
      screenSurface = SDL_GetWindowSurface(window);

      // this is to fill the surface with white
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      // Update the surface
      SDL_UpdateWindowSurface(window);

      // Wait for two seconds
      SDL_Delay(2000);
    }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
