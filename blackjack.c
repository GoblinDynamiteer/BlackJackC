/* 

BlackJack by Johan K�mpe! 
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
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SUITS 4
#define CARDS 52
#define DECKS 6
#define SHUFFLES 5000

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

//Number of cards in play
int deckSize = CARDS * DECKS;

//Sets card values to deck in play
void setCards(struct deck *deck);
//Prints out card values in deck
void printDeck(struct deck *deck);
//Prints out single card value
void printCard(struct deck deck);
//Shuffles the cards
void shuffleDeck(struct deck *deck);
//Checks if deck contains valid cards
bool checkDeck(struct deck *deck);

int main(){
	srand(time(NULL));
	struct deck deck[deckSize];
	setCards(deck);
	for(int i=0;i<SHUFFLES;i++){
		shuffleDeck(deck);
	}
	if(!checkDeck(deck)){
		printf("The deck wasn't shuffled correctly!");
		return 1;
	}
	printDeck(deck);
	return 0;
}

//Sets card values to deck in play
void setCards(struct deck *deck){
	int cardNo = 0;
	while(cardNo < deckSize){
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

//Checks if deck contains valid cards
bool checkDeck(struct deck *deck){
		for(int suit=0;suit<SUITS;suit++){
			for(int value=1;value<14;value++){
				int cardNo = 0;
				int cardCount = 0;
				while(cardNo < deckSize){
					if((deck[cardNo].value == value) && (deck[cardNo].suit == suit)){
						cardCount++;
					}
				cardNo++;
			}
			if(cardCount != DECKS){
				return false;
			}
		}
	}
	return true;
}

void shuffleDeck(struct deck *deck){
	int tempValue, tempSuit;
	int card1 = 0; 
	int card2 = 0;
	do{
		card1 = rand() % deckSize;
		card2 = rand() % deckSize;
	}while(card1 == card2);
	tempSuit = deck[card1].suit;
	tempValue = deck[card1].value;
	deck[card1].suit = deck[card2].suit;
	deck[card1].value = deck[card2].value;
	deck[card2].suit = tempSuit;
	deck[card2].value = tempValue;
	return;
}

//Prints out single card value
void printCard(struct deck deck){
	switch(deck.value){
		case 1: 
			printf("Ace");
			break;
		case 11: 
			printf("Jack");
			break;
		case 12: 
			printf("Queen");
			break;
		case 13: 
			printf("King");
			break;
		default:
			printf("%d", deck.value);
	}
	printf(" of ", deck.value);
	printf("%s\n", cardSuit[deck.suit]);
}

//Prints out all card values in deck
void printDeck(struct deck *deck){
	for(int i=0; i<deckSize; i++){
		printf("CARD #%d: ", i);
		printCard(deck[i]);
	}
	return;
}
