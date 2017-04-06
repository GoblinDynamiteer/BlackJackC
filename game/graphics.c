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

	if(!loadArt(game)){
		return 0;
	}

	return 1;
}

bool loadArt(game * game){
	const char * imageFiles[] = {
			"art/bg_table.png",
	};

	SDL_Surface * surface = NULL;

	for(int i = 0; i < 1; i++){
		surface = IMG_Load(imageFiles[i]);
		game->art.background = SDL_CreateTextureFromSurface(
				game->renderer, surface);
	}

	/*	 Free surfaces	*/
	SDL_FreeSurface(surface);
	game->art.font = TTF_OpenFont("font/joystix_monospace.ttf", FONT_SIZE);

	return 1;
}
