/* 

BlackJack by Johan Kämpe! 
For C programming practice.

*/

/* 
Struct for decks
Values 
01: ACE 
11: JACK 
12: QUEEN
13: KING

Suits
0: HEARTS
1: DIAMONDS
2: CLUBS
3: SPADES

*/
#include <stdio.h>
#define SUITS 4
#define CARDS 52
#define DECKS 6

struct deck{
	int suit;
	int value; 
};

char *cardSuit[4] ={
		"Hearts",
		"Diamonds",
		"Clubs",
		"Spades"
};

//Sets card values to deck in play
void setCards(struct deck *deck);
//Prints out card values in deck
void printDeck(struct deck *deck);

int main(){
	struct deck deck[CARDS*DECKS];
	setCards(deck);
	printDeck(deck);
}

//Sets card values to deck in play
void setCards(struct deck *deck){
	int cardNo = 0;
	while(cardNo < CARDS*DECKS){
		for(int suit = 0;suit<SUITS;suit++){
			for(int value=1;value<14;value++){
				deck[cardNo].suit = suit;
				deck[cardNo].value = value;
				cardNo++;
			}
		}
	}
	return;
}

//Prints out card values in deck
void printDeck(struct deck *deck){
	for(int i=0; i<CARDS*DECKS; i++){
		printf("CARD #%d: ", i);
		printf("%d of ", deck[i].value);
		printf("%s\n", cardSuit[deck[i].suit]);
	}
	return;
}
