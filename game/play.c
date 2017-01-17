
#include "..\def.h"

void setupGame(game * game){
	game->dealer.score.high = 0;
	game->dealer.score.low = 0;
	game->player.score.high = 0;
	game->player.score.low = 0;

	game->dealer.mustDraw = YES;
}

card * dealNextCard(game * game){
	for(int deck = 0; deck < DECKS; deck++){
		for(int card = 0; card < DECK_SIZE; card++){
			/*	 Finds undealt card, returns pointer	*/
			if(!game->deck[deck].card[card].dealt){
				game->deck[deck].card[card].dealt = YES;
				return &game->deck[deck].card[card];
			}
		}
	}
	/*	 No more undealt cards	*/
	return NULL;
}

void addScore(game * game, card card, bool player){
	int scoreHigh = 0, scoreLow = 0;

	if (card.value > NINE || card.value == ACE){
		switch(card.value){
			case ACE:
				scoreHigh = 11;
				scoreLow = 1;
				break;
			case KING:
			case JACK:
			case QUEEN:
			case TEN:
				scoreHigh = 10;
				scoreLow = 10;
				break;
		}
	}

	else{
		scoreHigh = card.value + 1;
		scoreLow = card.value + 1;
	}

	if(player == DEALER){
		game->dealer.score.high += scoreHigh;
		game->dealer.score.low += scoreLow;
	}
	else{
		game->player.score.high += scoreHigh;
		game->player.score.low += scoreLow;
	}
}
