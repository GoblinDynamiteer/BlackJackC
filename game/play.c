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
void dealCardToPlayer(game * game, bool player, int hand){
	if(player == PLAYER){
		for(int i = 0; i < MAX_HAND; i++){
			if(game->player[hand].hand[i] == NULL){
				game->player[hand].hand[i] = dealNextCard(game);
				addScore(game, *game->player[hand].hand[i], PLAYER, hand);
				break;
			}
		}

	}
	else{
		for(int i = 0; i < MAX_HAND; i++){
			if(game->dealer.hand[i] == NULL){
				game->dealer.hand[i] = dealNextCard(game);
				addScore(game, *game->dealer.hand[i], DEALER, MAIN_HAND);
				break;
			}

/*	Gets index for next free pointer in dealer/player hand 	*/
int getFreeHandIndex(game * game, bool player, int hand){
	for(int i = 0; i < MAX_HAND; i++){
		if(game->dealer.hand[i] == NULL
			&& player == DEALER){
				return i;
		}
		if(game->player[hand].hand[i] == NULL
			&& player == PLAYER){
				return i;
		}
	}
	/*	Should not get here 	*/
	assert(1==2);
	return 0;
}

/*	 Nulls pointers in player and dealer card hands	*/
void nullHands(game * game){
	for(int i = 0; i< MAX_HAND; i++){
		game->dealer.hand[i] = NULL;
		assert(game->dealer.hand[i] == NULL);
	}
	for(int j = 0; j < SPLITS_MAX; j++){
		for(int i = 0; i< MAX_HAND; i++){
			game->player[j].hand[i] = NULL;
			assert(game->player[j].hand[i] == NULL);
		}
	}
}

/*	 Sets up first deal, 2 each to player and dealer	*/
void firstDeal(game * game){
	/*	 Reset	*/
	nullHands(game);
	resetScore(game);

	/*	 Cards	*/
	game->player[MAIN_HAND].hand[0] = dealNextCard(game);
	game->dealer.hand[0] = dealNextCard(game);
	game->player[MAIN_HAND].hand[1] = dealNextCard(game);
	game->dealer.hand[1] = dealNextCard(game);

	/*	Score
	 *	Dealer's second card is face down,
	 * 	don't reveal score for second card	*/
	addScore(game, *game->player[MAIN_HAND].hand[0], PLAYER, MAIN_HAND);
	addScore(game, *game->player[MAIN_HAND].hand[1], PLAYER, MAIN_HAND);
	addScore(game, *game->dealer.hand[0], DEALER, MAIN_HAND);
}

/*	 Checks if player is eligable for split		*/
bool canSplit(card card1, card card2){
	return (card1.value == card2.value);
}

/*	 Temporary hit/stay for player	*/
bool playerHit(void){
	printf("(H)IT / (S)TAY\n");
	char c = getchar();
	fflush(stdin);
	return (tolower(c) == 'h');
}
