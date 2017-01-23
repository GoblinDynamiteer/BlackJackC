/*	 Include guard	*/
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

/*	 Card values	*/
enum {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, VALUES_MAX};

/*	 Card suits	*/
enum {HEARTS, DIAMONDS, CLUBS, SPADES, SUITS_MAX};

/*	 Misc 1/0	*/
enum {NO, YES};
enum {FALSE, TRUE};
enum {PLAYER, DEALER};


#define DECK_SIZE 52
#define DECKS 6

#define START_CREDITS 1000
#define SHUFFLES 50000

#define MAX_HAND 20

typedef struct card{
	int value;
	int suit;
	bool dealt;
}card;

typedef struct score{
	int low, high;
}score;

typedef struct deck{
	card card[DECK_SIZE];
}deck;

typedef struct player{
	int credits;
	card * hand[MAX_HAND];
	score score;
}player;

typedef struct dealer{
	card * hand[MAX_HAND];
	score score;
}dealer;

typedef struct game{
	deck deck[DECKS];
	char * cardValues[VALUES_MAX];
	char * cardSuits[SUITS_MAX];
	player player;
	dealer dealer;
}game;


/*	 cards.c	*/
bool setCards(game * game);
bool setCardsNames(game * game);
void printCardName(game * game, card card);
void printDeck(game * game);
void shuffleDeck(game * game, int cardSwaps);
void swapCards(game * game, int deck1, int card1, int deck2, int card2);
bool checkShuffle(game *game);

/*	 num.c	*/
int getRandomNumber(int max);
void initRandom();

/*	 play.c	*/
void setupGame(game * game);
card * dealNextCard(game * game);
void dealCardToPlayer(game * game, bool player);
void addScore(game * game, card card, bool player);
void resetScore(game * game);
void nullHands(game * game);
void firstDeal(game * game);
bool checkNatural(game * game, bool player);
bool dealerDraw(game * game);
bool isBust(int score);
bool isPlayerBust(game * game, bool player);

#endif /* DEF_H_ */
