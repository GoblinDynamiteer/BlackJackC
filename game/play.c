
#include "..\def.h"

void setupGame(game * game){
	resetScore(game);
	nullHands(game);

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
	/*	No more cards in deck, reset & shuffle
	 *	deal first card in deck.	*/
	setCards(game);
	shuffleDeck(game, SHUFFLES);
	printf("\n\n<No more cards -- Shuffling deck>\n");
	if(!checkShuffle(game)){
		printf("<Shuffle failed!>\n\n");
		return NULL;
	}
	game->deck[0].card[0].dealt = YES;
	return &game->deck[0].card[0];
}

void nullHands(game * game){
	for(int i = 0; i< MAX_HAND; i++){
		game->player.hand[i] = NULL;
		game->dealer.hand[i] = NULL;
		assert(game->player.hand[i] == NULL &&
				game->dealer.hand[i] == NULL);
	}
}

void firstDeal(game * game){
	nullHands(game);
	resetScore(game);
	game->player.hand[0] = dealNextCard(game);
	game->dealer.hand[0] = dealNextCard(game);
	game->player.hand[1] = dealNextCard(game);
	game->dealer.hand[1] = dealNextCard(game);
}

void resetScore(game * game){
	game->dealer.score.high = 0;
	game->dealer.score.low = 0;
	game->player.score.high = 0;
	game->player.score.low = 0;
}

void addScore(game * game, card card, bool player){
	int scoreHigh = 0, scoreLow = 0;
		switch(card.value){
			case ACE:
				scoreHigh = 11;
				scoreLow = 1;
				break;
			case KING:
			case JACK:
			case QUEEN:
			case TEN:
				scoreHigh = scoreLow = 10;
				//scoreLow = 10;
				break;
			default:
				scoreHigh = scoreLow = card.value + 1;
				//scoreLow = card.value + 1;
				break;
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
