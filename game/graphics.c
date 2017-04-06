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

bool renderGame(game * game){
	/*	 Sets background color	*/
	SDL_SetRenderDrawColor(game->renderer, 102, 204, 204, 255);
	SDL_RenderClear(game->renderer);

	drawText(game, GAME_WINDOW_TITLE, 10, 10);

	/*	 Presents render	*/
	SDL_RenderPresent(game->renderer);
	return 1;
}

/*	 Draw text	*/
void drawText(game * game, char * text, int posx, int posy){
	SDL_Surface *textSurface;
	SDL_Color color = {0,0,0};
	textSurface = TTF_RenderText_Solid(
		game->art.font, text, color
	);
	SDL_Texture * textTexture = SDL_CreateTextureFromSurface(
		game->renderer, textSurface
	);
	SDL_Rect textRect = {posx, posy, 0, 0};
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
}
