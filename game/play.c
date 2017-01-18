
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
	/*	 Reset	*/
	nullHands(game);
	resetScore(game);

	/*	 Cards	*/
	game->player.hand[0] = dealNextCard(game);
	game->dealer.hand[0] = dealNextCard(game);
	game->player.hand[1] = dealNextCard(game);
	game->dealer.hand[1] = dealNextCard(game);

	/*	Score
	 *	Dealer's second card is face down,
	 * 	don't reveal score for second card	*/
	addScore(game, *game->player.hand[0], PLAYER);
	addScore(game, *game->player.hand[1], PLAYER);
	addScore(game, *game->dealer.hand[0], DEALER);
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

/*	A natural is ACE + 10+ card on first deal
 * 	Player gets 1,5x their bet, unless dealer
 * 	also has a natural. In that case, the player
 * 	gets his bet back. */
bool checkNatural(game * game, bool player){
	int card1Value, card2Value;
	if(player == PLAYER){
		card1Value = game->player.hand[0]->value;
		card2Value = game->player.hand[1]->value;
	}
	else{
		card1Value = game->dealer.hand[0]->value;
		card2Value = game->dealer.hand[1]->value;
	}
	/*	 If one of the cards is an ACE and the other is
	 *	 TEN or over, it's a natural blackjack. */
	if(card1Value == ACE || card2Value == ACE){
		if(card1Value + card2Value >= ACE + TEN){
			return 1;
		}
	}
	return 0;
}

/*	 Dealer must draw at 16 and stay at 17	*/
bool dealerDraw(game * game){
	int scoreHigh = game->dealer.score.high;
	int scoreLow = game->dealer.score.low;
	return (scoreHigh <= 16 && scoreLow <= 16);
}
