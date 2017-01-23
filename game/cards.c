/*
 * cards.c
 *
 *  Created on: 16 jan. 2017
 *      Author: kampe_000
 */


#include "..\def.h"

/*	 Sets cards to decks	*/
bool setCards(game * game){
	int count = 0;
	int value = ACE;
	int suit;
	for(int deck = 0; deck < DECKS; deck++){
		suit = HEARTS;
		for(int card = 0; card < DECK_SIZE; card++){
			assert(suit < SUITS_MAX);
			assert(value < VALUES_MAX);
			game->deck[deck].card[card].value = value++;
			game->deck[deck].card[card].suit = suit;
			game->deck[deck].card[card].dealt = NO;
			if(value == VALUES_MAX){
				value = ACE;
				suit++;
			}
			count++;
		}
	}
	assert(count == DECK_SIZE * DECKS);
	return (count == DECK_SIZE * DECKS);
}

/* Fix swedish translation
 * Copies text names to char arrays	*/
bool setCardsNames(game * game){
	int count = 0;
	char * values[VALUES_MAX] = {
		"Ace",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten",
		"Jack",
		"Queen",
		"King"
	};

	for(int i = 0; i < VALUES_MAX; i++){
		game->cardValues[i] = malloc(sizeof(char)* 8);
		strcpy(game->cardValues[i], values[i]);
		count++;
	}

	char * suits[SUITS_MAX] = {
		"Hearts",
		"Diamonds",
		"Clubs",
		"Spades",
	};

	for(int i = 0; i < SUITS_MAX; i++){
		game->cardSuits[i] = malloc(sizeof(char)* 10);
		strcpy(game->cardSuits[i], suits[i]);
		count++;
	}

	assert(count == SUITS_MAX + VALUES_MAX);
	return (count == SUITS_MAX + VALUES_MAX);
}

void shuffleDeck(game * game, int cardSwaps){
	int deck1 = 1, deck2 = 1, card1, card2;
	for(int i = 0; i< cardSwaps; i++){
		do {
			deck1 = getRandomNumber(DECKS);
			deck2 = getRandomNumber(DECKS);
			card1 = getRandomNumber(DECK_SIZE);
			card2 = getRandomNumber(DECK_SIZE);
		} while(deck1 == deck2 && card1 == card2);

		swapCards(game, deck1, card1, deck2, card2);
	}
}

/*	 Swaps values of two card structs	*/
void swapCards(game * game, int deck1, int card1, int deck2, int card2){
	int tempValue, tempSuit;
	tempValue = game->deck[deck1].card[card1].value;
	tempSuit = game->deck[deck1].card[card1].suit;
	game->deck[deck1].card[card1].value = game->deck[deck2].card[card2].value;
	game->deck[deck1].card[card1].suit = game->deck[deck2].card[card2].suit;
	game->deck[deck2].card[card2].value = tempValue;
	game->deck[deck2].card[card2].suit = tempSuit;
}

/*	 Determines that decks are correctly shuffled	*/
bool checkShuffle(game *game){
	int calcCardValues =
		(ACE+TWO+THREE+FOUR+FIVE+SIX+SEVEN+EIGHT+NINE+TEN+JACK+QUEEN+KING) *
		SUITS_MAX * DECKS;
	int calcSuitValues =
		(HEARTS+DIAMONDS+CLUBS+SPADES) *
		VALUES_MAX * DECKS;
	int sumCardValues = 0, sumSuitValues = 0;
	for(int deck = 0; deck < DECKS; deck++){
		for(int card = 0; card < DECK_SIZE; card++){
			sumCardValues += game->deck[deck].card[card].value;
			sumSuitValues += game->deck[deck].card[card].suit;
		}
	}
	assert (sumCardValues == calcCardValues && calcSuitValues == sumSuitValues);
	return (sumCardValues == calcCardValues && calcSuitValues == sumSuitValues);
}

/*	 Print a card in text-form, e.g. "Ace of Spades"	*/
void printCardName(game * game, card card){
	printf("%s of %s\n",
			game->cardValues[card.value],
			game->cardSuits[card.suit]
	);
}

/*	Prints all decks, mostly for debugging	*/
void printDeck(game * game){
	for(int deck = 0; deck < DECKS; deck++){
		for(int card = 0; card < DECK_SIZE; card++){
			printf("Deck[%d] - Card [%d]: ", deck, card);
			printCardName(game, game->deck[deck].card[card]);
			printf("Dealt: %d\n", game->deck[deck].card[card].dealt);
		}
	}
}
