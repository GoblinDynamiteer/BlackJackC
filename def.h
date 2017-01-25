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
enum {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, TEN, JACK, QUEEN, KING, VALUES_MAX};

/*	 Card suits	*/
enum {HEARTS, DIAMONDS, CLUBS, SPADES, SUITS_MAX};

/*	 Misc 1/0	*/
enum {NO, YES};
enum {FALSE, TRUE};
enum {PLAYER, DEALER, DRAW};
enum {MAIN_HAND, SPLIT1, SPLIT2, SPLIT3, SPLIT4, SPLIT5, SPLITS_MAX};


#define DECK_SIZE 52
#define DECKS 6

#define START_CREDITS 1000
#define SHUFFLES 50000

#define MAX_HAND 20

/*	 A card	*/
typedef struct card{
	int value; //ACE to KING
	int suit; //HEARTS to SPADES
	bool dealt;
}card;

/*	 A deck of cards	*/
typedef struct deck{
	card card[DECK_SIZE];
}deck;

/*	 Score low/high: Aces are worth 1/11	*/
typedef struct score{
	int low, high;
}score;

/*	 The player	*/
typedef struct player{
	int credits;
	card * hand[MAX_HAND]; //Current cards
	score score;
	bool bust;
	bool natural;
}player;

/*	 The dealer	*/
typedef struct dealer{
	card * hand[MAX_HAND]; //Current cards
	score score;
	bool bust;
	bool natural;
}dealer;

/*	 Game struct	*/
typedef struct game{
	deck deck[DECKS];
	char * cardValues[VALUES_MAX];
	char * cardSuits[SUITS_MAX];
	player player[SPLITS_MAX];
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
void dealCardToPlayer(game * game, bool player, int hand);
void nullHands(game * game);
void firstDeal(game * game);
bool canSplit(card card1, card card2);
bool playerHit(void);

/*	score.c	*/
void addScore(game * game, card card, bool player, int hand);
void resetScore(game * game);
bool checkNatural(game * game, bool player, int hand);
bool isBust(int score);
bool isPlayerBust(game * game, bool player, int hand);
bool dealerDraw(game * game);
int getScore(game * game, bool player, int hand);
int getWinner(game * game, int hand);

/*	cycles.c 	*/
bool newGameCycle(game * game);
bool dealerCycle(game * game);
bool playerCycle(game * game);
void winnerCycle(game * game);

#endif /* DEF_H_ */
