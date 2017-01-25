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
    printf("\n\n- PLAYER TURN - HAND %d\n\n", hand);
    printf("+PLAYER CARDS - HAND %d\n", hand);
    if(hand > MAIN_HAND){
      dealCardToPlayer(game, PLAYER, hand);
      dealCardToPlayer(game, PLAYER, hand);
    }
    printCardName(game, *game->player[hand].hand[0]);
    printCardName(game, *game->player[hand].hand[1]);
    printf("+PLAYER SCORE [%d / %d] - HAND %d\n",
        game->player[hand].score.low,
        game->player[hand].score.high,
        hand
    );

    if(checkNatural(game, PLAYER, hand)){
      printf("+PLAYER HAS NATURAL BLACKJACK> - HAND %d\n", hand);
    }
    else{
      int i = 2;
      //while(playerHit()){
      while(1){
        printf("+PLAYER/SPLIT %d GETS CARD\n", hand);
        dealCardToPlayer(game, PLAYER, hand);
        assert(game->player[hand].hand[i] != NULL);
        printCardName(game, *game->player[hand].hand[i++]);
        printf("+PLAYER SCORE [%d / %d] - HAND %d\n",
            game->player[hand].score.low,
            game->player[hand].score.high,
            hand
        );
        if(isPlayerBust(game, PLAYER, hand)){
          printf("+PLAYER BUST - HAND %d\n", hand);
          break;
        }
      }
    }
  }
  return 1;
}
