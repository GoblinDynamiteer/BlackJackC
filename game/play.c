/*
 * play.c
 *
 *  Created on: 16 jan. 2017
 *      Author: Johan Kämpe
 */

#include "..\def.h"

void setupGame(game * game){
	resetScore(game);
	nullHands(game);
}

/*	 Gets the next card in the deck 	*/
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

/*	 Deals a new card to player/dealer and adds card score	*/
void dealCardToPlayer(game * game, bool player){
	if(player == PLAYER){
		for(int i = 0; i < MAX_HAND; i++){
			if(game->player.hand[i] == NULL){
				game->player.hand[i] = dealNextCard(game);
				addScore(game, *game->dealer.hand[i], PLAYER);
				break;
			}
		}

	}
	else{
		for(int i = 0; i < MAX_HAND; i++){
			if(game->dealer.hand[i] == NULL){
				game->dealer.hand[i] = dealNextCard(game);
				addScore(game, *game->dealer.hand[i], DEALER);
				break;
			}
		}
	}
}

/*	 Nulls pointers in player and dealer card hands	*/
void nullHands(game * game){
	for(int i = 0; i< MAX_HAND; i++){
		game->player.hand[i] = NULL;
		game->dealer.hand[i] = NULL;
		assert(game->player.hand[i] == NULL &&
				game->dealer.hand[i] == NULL);
	}
}

/*	 Sets up first deal, 2 each to player and dealer	*/
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

/*	 Resets score, before a new deal 	*/
void resetScore(game * game){
	game->dealer.score.high = 0;
	game->dealer.score.low = 0;
	game->player.score.high = 0;
	game->player.score.low = 0;
}

/*	 Adds score from card value(s)	*/
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
	return (
		(scoreHigh <= 16 && scoreLow <= 16) ||
		(isBust(scoreHigh) && scoreLow <= 16) ||
		(isBust(scoreHigh) && scoreHigh <= 16)
	);
}

/*	 Checks if score is bust	*/
bool isBust(int score){
	return (score > 21);
}

/*	 Checks if player/dealer is bust	*/
bool isPlayerBust(game * game, bool player){
	int scoreHigh, scoreLow;
	if(player == PLAYER){
		scoreHigh = game->player.score.high;
		scoreLow = game->player.score.low;
	}
	else{
		scoreHigh = game->dealer.score.high;
		scoreLow = game->dealer.score.low;
	}
	return (isBust(scoreHigh) && isBust(scoreLow));
}

bool playerHit(void){
	printf("(H)IT / (S)TAY\n");
	char c = getchar();
	return (tolower(c) == 'h');
}
