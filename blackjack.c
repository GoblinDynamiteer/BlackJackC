/* 

BlackJack by Johan Kämpe! 
For C programming practice.

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


TODO:
Betting
Dealer

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "libtxt.h"

#define SUITS 4
#define CARDS 52
#define DECKS 6
#define SHUFFLES 10000
#define CHIPS 500

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
void setScore(struct deck deck, int *score1, int *score2);
void displayScore(int *score1, int *score2);

int main(){
	int score1 = 0, score2 = 0, dealerScore1 = 0, dealerScore2 = 0, cardIndex = 0, choice = 0, chips = CHIPS;
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
	//printLine prints a char x times, last argument toggles newline before and after
	system("cls");
	printLine('*', 25, 1);
	printf("Welcome to "FORM_RED"BLACKJACK C"FORM_END"!");
	printLine('*', 25, 1);

	//First deal, get two cards and display score:
	printf("You got dealt:\n");
	for(int i=0;i<2;i++){
		printCard(deck[cardIndex]);
		if(!i){
			printf("\n");
		}
		setScore(deck[cardIndex], &score1, &score2);
		cardIndex++;
	}
	displayScore(&score1, &score2);
	
	while(1){
		printf("1: Hit - 2: Stand. INPUT: ");
		scanf("%d", &choice);
		if(choice == 1){
			printCard(deck[cardIndex]);
			setScore(deck[cardIndex], &score1, &score2);
			displayScore(&score1, &score2);
			cardIndex++;
		}
		if((score1 > 21) && (score2 > 21)){
			printf("Bust!");
			break;
		}
	}
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

void setScore(struct deck deck, int *score1, int *score2){
	if((deck.value > 1) && (deck.value < 11)){
		*score1 += deck.value;
		*score2 += deck.value;
	}
	else if(deck.value == 1){
		*score1 += deck.value;
		*score2 += 11;
	}
	else{
		*score1 += 10;
		*score2 += 10;
	}
	return;
}

//Displays score
void displayScore(int *score1, int *score2){
	printLine('-', 25, 1);
	if(*score1 == *score2){
		printf("Your Score: %d", *score1);
	}
	else{
		printf("Your Score: %d / %d", *score1, *score2);
	}
	printLine('-', 25, 1);
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
	printf("%s", cardSuit[deck.suit]);
}

//Prints out all card values in deck
void printDeck(struct deck *deck){
	for(int i=0; i<deckSize; i++){
		printf("CARD #%d: ", i);
		printCard(deck[i]);
	}
	return;
}
