/*
 * cycles.c
 *
 *  Created on: 23 jan. 2017
 *      Author: Johan Kämpe
 */


#include "..\def.h"

/*   Sets up new game */
bool newGameCycle(game * game){
  firstDeal(game);
  printf("|DEALER CARDS\n");
  printCardName(game, *game->dealer.hand[0]);
  printf("[CARD FACE DOWN]\n");
  /*    Print score for shown card */
  printf("|DEALER SCORE [%d / %d]\n",
      game->dealer.score.low,
      game->dealer.score.high
  );
  /*    Add score for hidden card */
  addScore(game, *game->dealer.hand[1], DEALER, MAIN_HAND);
  return 1;
}

/*    Dealer draw cycle after player is done */
bool dealerCycle(game * game){
  printf("|REVEAL DEALER CARD\n");
  printCardName(game, *game->dealer.hand[1]);
  printf("|DEALER SCORE [%d / %d]\n",
      game->dealer.score.low,
      game->dealer.score.high
  );
  int i = 2;
  while(dealerDraw(game)){
    printf("|DEALER DRAWS\n");
    dealCardToPlayer(game, DEALER, MAIN_HAND);
    assert(game->dealer.hand[i] != NULL);
    printCardName(game, *game->dealer.hand[i++]);
    printf("|DEALER SCORE [%d / %d]\n",
        game->dealer.score.low,
        game->dealer.score.high
    );
  }
  if(checkNatural(game, DEALER, MAIN_HAND)){
    printf("|DEALER HAS NATURAL BLACKJACK>\n");
  }
  else if(isPlayerBust(game, DEALER, MAIN_HAND)){
    printf("|DEALER BUST>\n");
  }
  else{
    printf("|DEALER STAYING>\n");
  }
  return 1;
}

/*    Player play cycle */
bool playerCycle(game * game){
  for(int hand = MAIN_HAND; hand < SPLITS_MAX; hand++){
    printf("\n\n- PLAYER %d TURN -\n\n", hand);
    printf("+PLAYER %d CARDS\n", hand);
    if(hand > MAIN_HAND){
      dealCardToPlayer(game, PLAYER, hand);
      dealCardToPlayer(game, PLAYER, hand);
    }
    printCardName(game, *game->player[hand].hand[0]);
    printCardName(game, *game->player[hand].hand[1]);

    if(game->player[hand].score.low != game->player[hand].score.high
      && game->player[hand].score.high <= 21){
      printf("+PLAYER %d SCORE [%d / %d]\n",
          hand,
          game->player[hand].score.low,
          game->player[hand].score.high
      );
    }
    else{
      printf("+PLAYER %d SCORE [%d]\n",
          hand,
          getScore(game, PLAYER, hand)
      );
    }

    if(canSplit(*game->player[hand].hand[0], *game->player[hand].hand[1])){
      printf("+PLAYER %d CAN SPLIT <----------\n", hand);
    }

    if(checkNatural(game, PLAYER, hand)){
      printf("+PLAYER %d HAS NATURAL BLACKJACK <----------\n", hand);
    }
    else{
      int i = 2;
      //while(playerHit()){
      while(1){
        printf("+PLAYER %d GETS CARD\n", hand);
        dealCardToPlayer(game, PLAYER, hand);
        assert(game->player[hand].hand[i] != NULL);
        printCardName(game, *game->player[hand].hand[i++]);
        if(game->player[hand].score.low != game->player[hand].score.high
          && game->player[hand].score.high <= 21){
          printf("+PLAYER %d SCORE [%d / %d]\n",
              hand,
              game->player[hand].score.low,
              game->player[hand].score.high
          );
        }
        else{
          printf("+PLAYER %d SCORE [%d]\n",
              hand,
              getScore(game, PLAYER, hand)
          );
        }
        if(isPlayerBust(game, PLAYER, hand)){
          printf("+PLAYER %d BUST\n", hand);
          break;
        }
      }
    }
  }
  return 1;
}
