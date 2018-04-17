#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>

int main() {
	SDL_SetMainReady();
	bool quit = false;
	bool direc[4] = { false, false, false, false};
	//SDL_Event event;
	SDL_Window *window;                    // Declare a pointer
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		0                // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		std::cout << "window null" << std::endl;
		return 1;
	}

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface * image = SDL_LoadBMP("bmp-icon.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Rect rect = { 5,5,100,100 };

	while (!quit)
	{
		//SDL_WaitEvent(&event);
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					rect.y -= 10;
					break;
				case SDLK_LEFT:
					rect.x -= 10;
					break;
				case SDLK_DOWN:
					rect.y += 10;
					break;
				case SDLK_RIGHT:
					rect.x += 10;
					break;
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, &rect);
			SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}