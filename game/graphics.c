#include "..\def.h"

int initGfx(game * game){
	/*	 Init SDL and SDL subsystems	*/
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  /*	 Hide cursor	*/
  SDL_ShowCursor(SDL_DISABLE);

  /*	 Declare window and renderer	*/
  SDL_Window * window;
  SDL_Renderer * renderer;

  /*	 Create window	*/
	window = SDL_CreateWindow(
		GAME_WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIN_WIDTH,
		WIN_HEIGHT,
		WIN_FLAGS
	);

    /*	 Create renderer	*/
	renderer = SDL_CreateRenderer(
			window,
			-1,
			REN_FLAGS
	);

	if(renderer == NULL || window == NULL){
		return 0;
	}
	
	game->renderer = renderer;
	game->window = window;

	return 1;
}
