
#include "..\def.h"

void setupGame(game * game){

}

card * dealNextCard(game * game){
	card * nextCard = malloc(sizeof(card *));
	for(int deck = 0; deck < DECKS; deck++){
		for(int card = 0; card < DECK_SIZE; card++){
			if(!game->deck[deck].card[card].dealt){
				game->deck[deck].card[card].dealt = YES;
				nextCard = &game->deck[deck].card[card];
				break;
			}
		}
	}
	return nextCard;
}

