/* 

BlackJack by Johan Kämpe! 
For C programming & english language practice.


Rules from 
http://www.bicyclecards.com/how-to-play/blackjack/
http://www.cherryapp.se/casino-school/


Struct for decks:
Values 
01: ACE 
02-10 VALUES 2-10
11: JACK 
12: QUEEN
13: KING

Suits
0: HEARTS
1: DIAMONDS
2: CLUBS
3: SPADES



TODO:
Betting 		**DONE!**
Dealer	 	**In progress**
Split
Raise
Insurance (Dealer draws ACE as first card)
BlackJack Score (ACE+10 first deal)
GUI with curses lib?

BUGS:
Dealer doesnt win on 11 / 21 vs 19 score

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "libtxt.h"

#define SUITS 4
#define CARDS 52
#define DECKS 6	//Amount of decks in play
#define SHUFFLES 10000 //Amount of random card swaps - "Shuffle"
#define CHIPS 500	//Amount of player starting chips
#define LINELEN 30 //Lenght of "lines"
#define MAXBET 70 //Swedish Pub/club limits
#define MINBET 20 //Swedish Pub/club limits

struct deck{
	int suit;
	int value; 
};

//For printing out suit name
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
//Asks for bet amount, returns value. Subtracts from chip pool
int bet(int *chips);
void dealPlayer(struct deck *deck, int *cardIndex);
void dealDealer(struct deck *deck, int *cardIndex);
bool dealerDraw(int *dscore1, int *dscore2);
int checkWinner(int dscore1, int dscore2, int score1, int score2);

int main(){
	//Could set variables as globals, functions would not need arguments
	int score1 = 0, score2 = 0, dealerScore1 = 0;
	int dealerScore2 = 0, cardIndex = 0, choice = 0;
	int chips = CHIPS, currentBet = 0, winCheck;
	bool play = 1, play2 = 1;
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
	//Clears the screen (for Windows CMD), needed for 
	//ANSI color formatting of text
	system("cls");
	//printLine prints a char-variable # times, last argument toggles
	//if newline should be printed before and after the line 1-on 0-off
	printLine('*', LINELEN, 1);
	printf("Welcome to "FORM_RED"BLACKJACK C"FORM_END"!");
	printLine('*', LINELEN, 1);
	//Initial bet
	while(play){
		play2 = 1;
		score1 = 0;
		score2 = 0;
		dealerScore1 = 0;
		dealerScore2 = 0;
		currentBet = bet(&chips);
		//Get dealed two cards
		for(int i=0;i<2;i++){
			dealPlayer(deck, &cardIndex);
			if(!i){ //Prints a newline after first displayed card
				printf("\n");
			}
			setScore(deck[cardIndex], &score1, &score2);
			cardIndex++;
		}
		dealDealer(deck, &cardIndex);
		setScore(deck[cardIndex], &dealerScore1, &dealerScore2);
		while(play2){
			printLine('-', LINELEN, 1);
			printf("Your score: "FORM_CYAN_DARK);
			displayScore(&score1, &score2);
			printf("\nDealer score: "FORM_CYAN_DARK);
			displayScore(&dealerScore1, &dealerScore2);
			printLine('-', LINELEN, 1);
			printf("1: Hit - 2: Stand.\nEnter: "); //temporary -- fix split/raise/etc
			scanf("%d", &choice); //Fix instant keypress
			if(choice == 1){
				dealPlayer(deck, &cardIndex);
				setScore(deck[cardIndex], &score1, &score2);
				cardIndex++;
			}
			if(choice == 2){
				while(dealerDraw(&dealerScore1, &dealerScore2)){
					dealDealer(deck, &cardIndex);
					setScore(deck[cardIndex], &dealerScore1, &dealerScore2);
					cardIndex++;
					printLine('-', LINELEN, 1);
					printf("Your score: "FORM_CYAN_DARK);
					displayScore(&score1, &score2);
					printf("\nDealer score: "FORM_CYAN_DARK);
					displayScore(&dealerScore1, &dealerScore2);
					printLine('-', LINELEN, 1);
					if((dealerScore1 > 21) && (dealerScore2 > 21)){
						printf(FORM_GREEN"\n<<Dealer bust!>>\n"FORM_END);
						winCheck = 2;
						play2 = 0;
						break;
					}
					Sleep(1000);
				}
				if(play2){
					winCheck = checkWinner(
						dealerScore1, dealerScore2, score1, score2);
				}
				if(winCheck == 1){
					printf(FORM_RED"\n<<Dealer wins!>>\n"FORM_END);
					play2 = 0;
					break;
				}
				else if(winCheck == 2){
					printf(FORM_GREEN"\n<<You Win!>>"FORM_END);
					printf("\n+%d credits!\n", currentBet);
					chips += (currentBet*2);
					play2 = 0;
					break;
				}
				else if(winCheck == 3){
					printf(FORM_YELLOW"\n<<Draw!>>\n"FORM_END);
					chips += currentBet;
					play2 = 0;
					break;
				}
			}
			if((score1 > 21) && (score2 > 21)){
				
				printf(FORM_RED"\n<<Bust!>>\n"FORM_END);
				printf("Score: ");
				displayScore(&score1, &score2);
				break;
			}
		}
	}
	return 0;
}

void dealPlayer(struct deck *deck, int *cardIndex){
	printf("You got dealt: ");
	printCard(deck[*cardIndex]);
}

void dealDealer(struct deck *deck, int *cardIndex){
	printf("\nDealer got: ");
	printCard(deck[*cardIndex]);
}


//Determins if dealer shall draw another card
//Dealer must stay if score is >= 17
bool dealerDraw(int *dscore1, int *dscore2){
	bool dealerDraw;
	//Dealer is under 17
	if (*dscore1 < 17 && *dscore2 < 17){
		dealerDraw = 1;
	}
	//Dealer has gotten ace
	else if (*dscore1 > 21 && *dscore2 < 17){
		dealerDraw = 1;
	}
	else if (*dscore2 > 21 && *dscore1 < 17){
		dealerDraw = 1;
	}
	//dealer has 17 or over
	else if (*dscore1 >= 17 || *dscore2 >= 17){
		dealerDraw = 0;
	}
	return dealerDraw;
}

//Checks who is the winner, returns 1 if dealer, 2 if player, 3 if draw
//If player and dealer has same score, dealer wins at 17, 18, 19. 
//Draw at 20, 21 or Black Jack
int checkWinner(int dscore1, int dscore2, int score1, int score2){
	int playerScore, dealerScore;
	if(score1 == score2){
		playerScore = score1;
	}
	else if(score1 > 21 && score2 < 21){
		playerScore = score2;
	}
	else if(score2 > 21 && score1 < 21){
		playerScore = score1;
	}
	if(dscore1 == dscore2){
		dealerScore = dscore1;
	}
	else if(dscore1 > 21 && dscore2 < 21){
		dealerScore = dscore2;
	}
	else if(dscore2 > 21 && dscore1 < 21){
		dealerScore = dscore1;
	}
	if(dealerScore > playerScore || 
	(	(dealerScore == playerScore) && (dealerScore < 20)	)	){
		return 1;
	}
	else if(dealerScore < playerScore){
		return 2;
	}
	else if((dealerScore == playerScore) && 
		(dealerScore >= 20)	){
		return 3;
	}
}

//Asks for bet amount and checks if correct, according to 
//"house-rules" defined in MINBET/MAXBET macros
int bet(int *chips){
	int betAmount;
	while(1){
		printf("You have %d credits.\n", *chips);
		printf("Enter amount to bet: ");
		scanf("%d", &betAmount);
		if(betAmount > MAXBET || betAmount < MINBET){
			printf("Max bet: %d, min bet: %d\n", MAXBET, MINBET);
			continue;
		}
		else if(betAmount > *chips){
			printf("Not enouch credits!\n");
			continue;
		}
		else if(betAmount <= 0){
			printf("Wrong bet!\n");
			continue;
		}
		break;
	}
	*chips -= betAmount;
	return betAmount;
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

//Sets score for player and dealer -- send adresses to score variables as argument
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
void displayScore(int *score1, int *score2){ //Change from pointers, not needed
	printf("\t");
	if(*score1 == *score2){
		printf("%2d", *score1);
	}
	else if(*score1 > 21 && *score2 < 21){
		printf("%2d", *score2);
	}
	else if(*score2 > 21 && *score1 < 21){
		printf("%2d", *score1);
	}
	else{
		printf("%2d / %2d", *score1, *score2);
	}
	printf(FORM_END);
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
			//If function found more, or less cards of a certain type, 
			//than amount of decks in play
			if(cardCount != DECKS){ 
				return false;
			}
		}
	}
	return true;
}

//Swaps two cards in the deck
void shuffleDeck(struct deck *deck){
	int tempValue, tempSuit;
	int card1 = 0; 
	int card2 = 0;
	//Randomizes two cards to swap values
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
	printf(FORM_GREEN);
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
	printf(FORM_END" of ", deck.value);
	printf(FORM_RED"%s"FORM_END, cardSuit[deck.suit]);
}

//Prints out all card values in deck - for testing purpouses
void printDeck(struct deck *deck){
	for(int i=0; i<deckSize; i++){
		printf("CARD #%d: ", i);
		printCard(deck[i]);
	}
	return;
}
