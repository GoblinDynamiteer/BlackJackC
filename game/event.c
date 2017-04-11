#include "..\def.h"

/*	 Process game events	*/
bool processEvent(game * game){
	/*	 Event union	*/
	SDL_Event event;
	bool quit = 0;
	renderBackground(game);

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
					game->player->done = 1;
					printf("LMB!\n");
				}
				if(event.button.button == SDL_BUTTON_RIGHT){
					game->player->done = 0;
					printf("RMB!\n");
				}
				break;
		}
	}
	return (quit == 0);
}
