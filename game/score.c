/*
 * score.c
 *
 *  Created on: 25 jan. 2017
 *      Author: Johan Kämpe
 */

#include "..\def.h"

/*	 Adds score from card value(s)	*/
void addScore(game * game, card card, bool player, int hand){
	int scoreHigh = 0, scoreLow = 0;
		switch(card.value){
			case ACE:
				scoreHigh = 11;
				scoreLow = 1;
				break;
			case KING:
			case JACK:
			case QUEEN:
			case TEN:
				scoreHigh = scoreLow = 10;
				//scoreLow = 10;
				break;
			default:
				scoreHigh = scoreLow = card.value + 1;
				//scoreLow = card.value + 1;
				break;
		}


	if(player == DEALER){
		game->dealer.score.high += scoreHigh;
		game->dealer.score.low += scoreLow;
	}
	else{
		game->player[hand].score.high += scoreHigh;
		game->player[hand].score.low += scoreLow;
	}
}

/*	A natural is ACE + 10+ card on first deal
* 	Player gets 1,5x their bet, unless dealer
* 	also has a natural. In that case, the player
* 	gets his bet back. */
bool checkNatural(game * game, bool player, int hand){
	int card1Value, card2Value;
	if(player == PLAYER){
		card1Value = game->player[hand].hand[0]->value;
		card2Value = game->player[hand].hand[1]->value;
	}
	else{
		card1Value = game->dealer.hand[0]->value;
		card2Value = game->dealer.hand[1]->value;
	}
	/*	 If one of the cards is an ACE and the other is
	 *	 TEN or over, it's a natural blackjack. */
	if(card1Value == ACE || card2Value == ACE){
		if(card1Value + card2Value >= ACE + TEN){
			return 1;
		}
	}
	return 0;
}

/*	 Checks if score is bust	*/
bool isBust(int score){
	return (score > 21);
}

/*	 Checks if player/dealer is bust	*/
bool isPlayerBust(game * game, bool player, int hand){
	int scoreHigh, scoreLow;
	if(player == PLAYER){
		scoreHigh = game->player[hand].score.high;
		scoreLow = game->player[hand].score.low;
	}
	else{
		scoreHigh = game->dealer.score.high;
		scoreLow = game->dealer.score.low;
	}
	return (isBust(scoreHigh) && isBust(scoreLow));
}

/*	 Dealer must draw at 16 and stay at 17	*/
bool dealerDraw(game * game){
	int scoreHigh = game->dealer.score.high;
	int scoreLow = game->dealer.score.low;
	return (
		(scoreHigh <= 16 && scoreLow <= 16) ||
		(isBust(scoreHigh) && scoreLow <= 16) ||
		(isBust(scoreHigh) && scoreHigh <= 16)
	);
}

/*	 Resets score, before a new deal 	*/
void resetScore(game * game){
	game->dealer.score.high = 0;
	game->dealer.score.low = 0;
	for(int i = 0; i < SPLITS_MAX; i++){
		game->player[i].score.high = 0;
		game->player[i].score.low = 0;
	}
}
