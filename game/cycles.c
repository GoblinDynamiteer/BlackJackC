/*
 * cycles.c
 *
 *  Created on: 23 jan. 2017
 *      Author: Johan Kämpe
 */


#include "..\def.h"

bool newGameCycle(game * game){
  firstDeal(game);
  printf("\n- NEW HAND -\n");
  printf("\n<<DEALER HAS\n\t");
  printCardName(game, *game->dealer.hand[0]);
  printf("\t[CARD FACE DOWN]\n");
  /*    Print score for shown card */
  printf("[%d / %d]\n",
      game->dealer.score.low,
      game->dealer.score.high
  );
  /*    Add score for hidden card */
  addScore(game, *game->dealer.hand[1], DEALER);
  return 1;
}

bool dealerCycle(game * game){
  printf("\t<<REVEAL DEALER CARD\n\t");
  printCardName(game, *game->dealer.hand[1]);
  printf("[%d / %d]\n",
      game->dealer.score.low,
      game->dealer.score.high
  );
  int i = 2;
  while(dealerDraw(game)){
    printf("<< DEALER DRAWING\n\t");
    dealCardToPlayer(game, DEALER);
    assert(game->dealer.hand[i] != NULL);
    printCardName(game, *game->dealer.hand[i++]);
    printf("[%d / %d]\n",
        game->dealer.score.low,
        game->dealer.score.high
    );
  }
  if(checkNatural(game, DEALER)){
    printf(">> DEALER HAS NATURAL BLACKJACK>\n");
  }
  else if(isPlayerBust(game, DEALER)){
    printf(">> DEALER BUST>\n");
  }
  else{
    printf("<< DEALER STAYING>\n");
  }
  return 1;
}

bool playerCycle(game * game){
  return 1;
}
