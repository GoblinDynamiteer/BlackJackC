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
  printf("+PLAYER CARDS\n");
  printCardName(game, *game->player[MAIN_HAND].hand[0]);
  printCardName(game, *game->player[MAIN_HAND].hand[1]);
  printf("+PLAYER SCORE [%d / %d]\n",
      game->player[MAIN_HAND].score.low,
      game->player[MAIN_HAND].score.high
  );
  if(checkNatural(game, PLAYER, MAIN_HAND)){
    printf("+PLAYER HAS NATURAL BLACKJACK>\n");
  }
  else{
    /*   Testing splits */
    for(int hand = MAIN_HAND; hand < SPLITS_MAX; hand++){

      int i = 2;

      /*   Deal two cards to split  */
      if(hand > MAIN_HAND){
        printf("\n\n+ + + PLAYER/SPLIT %d + + +\n", hand);
        dealCardToPlayer(game, PLAYER, hand);
        dealCardToPlayer(game, PLAYER, hand);
        printCardName(game, *game->player[hand].hand[0]);
        printCardName(game, *game->player[hand].hand[1]);
        printf("+PLAYER/SPLIT %d SCORE [%d / %d]\n",
            hand,
            game->player[hand].score.low,
            game->player[hand].score.high
        );
      }

      while(playerHit()){
        printf("+PLAYER/SPLIT %d GETS CARD\n", hand);
        dealCardToPlayer(game, PLAYER, hand);
        assert(game->player[hand].hand[i] != NULL);
        printCardName(game, *game->player[hand].hand[i++]);
        printf("[%d / %d]\n",
            game->player[hand].score.low,
            game->player[hand].score.high
        );
        if(isPlayerBust(game, PLAYER, hand)){
          printf("+PLAYER BUST\n");
          break;
        }
      }
    }
  }
  return 1;
}
