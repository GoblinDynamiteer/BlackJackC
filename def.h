/*	 Include guard	*/
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/*	 Card values	*/
enum {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, VALUES_MAX};

/*	 Card suits	*/
enum {HEARTS, DIAMONDS, CLUBS, SPADES, SUITS_MAX};

#define DECK_SIZE 52
#define DECKS 6

typedef struct card{
	int value;
	int suit;
}card;

typedef struct deck{
	card card[DECK_SIZE];
}deck;

typedef struct game{
	deck deck[DECKS];
	char * cardValues[VALUES_MAX];
	char * cardSuits[SUITS_MAX];
}game;


/*	 cards.c	*/
bool setCards(game * game);
bool setCardsNames(game * game);
void printCardName(game * game, card card);

#endif /* DEF_H_ */

