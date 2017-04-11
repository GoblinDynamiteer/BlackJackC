#include "..\def.h"

int initGfx(game * game){
	/*	 Init SDL and SDL subsystems	*/
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  /*	 Show cursor	*/
  SDL_ShowCursor(SDL_ENABLE);

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
			"art/cards.png"
	};

	SDL_Surface * surface = NULL;

	for(int i = 0; i < TEXTURES_MAX; i++){
		surface = IMG_Load(imageFiles[i]);
		game->art.textures[i] = SDL_CreateTextureFromSurface(
				game->renderer, surface);
	}

	/*	 Free surfaces	*/
	SDL_FreeSurface(surface);
	game->art.font = TTF_OpenFont("font/joystix_monospace.ttf", FONT_SIZE);

	return 1;
}

/*	 Render background image	*/
void renderBackground(game * game){
	SDL_Rect bgRect = {0, 0, WIN_WIDTH, WIN_HEIGHT};
	SDL_RenderCopy(
		game->renderer,
		game->art.textures[BACKGROUND],
		NULL,
		&bgRect
	);
}

/*	 Draw text	*/
void drawText(game * game, char * text, int posx, int posy){
	SDL_Surface *textSurface;
	SDL_Color color = {255,255,255}; //white
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

void renderCard(game * game, card card, int x, int y){
	/*	 Source and destination rectangles	*/
	SDL_Rect src = {
		0 + CARD_ART_WIDTH * card.value,
		0 + CARD_ART_HEIGHT * card.suit,
		CARD_ART_WIDTH,
		CARD_ART_HEIGHT
	};
	SDL_Rect dest = {x, y, CARD_ART_WIDTH, CARD_ART_HEIGHT};

	/*	 Draw part of texture in src rectangle to dest rectangle	*/
	SDL_RenderCopyEx(
			game->renderer,
			game->art.textures[CARDS],
			&src,
			&dest,
			0.0,
			NULL,
			SDL_FLIP_NONE
	);
}

void renderGame(game * game){
	renderBackground(game);
	/*	Draw game title in middle top 	*/
	drawText(game, GAME_WINDOW_TITLE, (WIN_WIDTH/2-170), 10);
	if(!game->running){
		drawText(game, "PRESS LMB TO PLAY!", 10, 10);
	}
	else if(!game->player[MAIN_HAND].done){
		drawText(game, "LMB: HIT", 10, 10);
		drawText(game, "RMB: STAY/RESET", 10, 10+30);
	}

	/* Render score	*/
	char text[80];
	sprintf(text, "Dealer score: %d / %d",
		game->dealer.score.low,
		game->dealer.score.high
	);
	drawText(game, text, WIN_WIDTH-500, 10);
	sprintf(text, "Player score: %d / %d",
		game->player[MAIN_HAND].score.low,
		game->player[MAIN_HAND].score.high
	);
	drawText(game, text, WIN_WIDTH-500, 10+30);
	sprintf(text, "Dealer cards: %d",
		game->dealer.cardsOnHand
	);
	drawText(game, text, WIN_WIDTH-500, 10+30+30);
	sprintf(text, "Player cards: %d",
		game->player[MAIN_HAND].cardsOnHand
	);
	drawText(game, text, WIN_WIDTH-500, 10+30+30+30);

	/* Render dealer cards	*/
	for(int i = 0; game->dealer.hand[i] != NULL; i++){
		renderCard(game, *game->dealer.hand[i],
			CARD_PLACEMENT_DEALER_X + CARD_RENDER_SPACING * i,
			CARD_PLACEMENT_DEALER_Y);
	}
	/* Render player cards	*/
	for(int i = 0; game->player[MAIN_HAND].hand[i] != NULL; i++){
		renderCard(game, *game->player[MAIN_HAND].hand[i],
			CARD_PLACEMENT_PLAYER_X + CARD_RENDER_SPACING * i,
			CARD_PLACEMENT_PLAYER_Y);
	}
}
