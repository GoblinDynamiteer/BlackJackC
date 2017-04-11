#include "..\def.h"

/*	 Process game events	*/
bool processEvent(game * game){
	/*	 Event union	*/
	SDL_Event event;
	bool quit = 0;

	while(SDL_PollEvent(&event)){
		Uint32 type = event.type;
		switch(type){
			/*	 Close button is pressed	*/
			case SDL_QUIT:
				quit = 1;
				break;
			/*	 A key has been pressed	*/
			case SDL_KEYDOWN:
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					quit = 1;
				}
				break;
			/*	 A mouse button has been pressed	*/
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT){
					if(!game->running){
						newGameCycle(game);
						printf("NEW GAME!!\n");
					}
					else if(!game->player[MAIN_HAND].done){
						printf("+PLAYER GETS CARD\n");
						dealCardToPlayer(game, PLAYER, MAIN_HAND);
						int cards = game->player[MAIN_HAND].cardsOnHand;
						printCardName(game, *game->player[MAIN_HAND].hand[cards-1]);
						printf("DRAWING!\n");
					}
				}
				if(event.button.button == SDL_BUTTON_RIGHT){
					game->player[MAIN_HAND].done = 1;
					printf("RMB - STAYING!\n");
				}
				break;
		}
	}
	if(game->running && game->player[MAIN_HAND].done && dealerDraw(game)){
		printf("|DEALER DRAWS\n");
    dealCardToPlayer(game, DEALER, MAIN_HAND);
		int cards = game->dealer.cardsOnHand;
		assert(game->dealer.hand[cards-1] != NULL);
    printCardName(game, *game->dealer.hand[cards-1]);
	}
	else if(!dealerDraw(game) && game->running && game->player[MAIN_HAND].done){
		if(checkNatural(game, DEALER, MAIN_HAND)){
	    game->dealer.natural = 1;
	    printf("|DEALER HAS NATURAL BLACKJACK>\n");
	  }
	  else if(isPlayerBust(game, DEALER, MAIN_HAND)){
	    game->dealer.bust = 1;
			printf("|DEALER IS BUST>\n");
	  }
		else{
			printf("|DEALER STAYING>\n");
		}
		winnerCycle(game);
	}
	return (quit == 0);
}
