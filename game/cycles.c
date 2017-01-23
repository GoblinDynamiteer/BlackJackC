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
  addScore(game, *game->dealer.hand[1], DEALER);
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
    dealCardToPlayer(game, DEALER);
    assert(game->dealer.hand[i] != NULL);
    printCardName(game, *game->dealer.hand[i++]);
    printf("|DEALER SCORE [%d / %d]\n",
        game->dealer.score.low,
        game->dealer.score.high
    );
  }
  if(checkNatural(game, DEALER)){
    printf("|DEALER HAS NATURAL BLACKJACK>\n");
  }
  else if(isPlayerBust(game, DEALER)){
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
  printCardName(game, *game->player.hand[0]);
  printCardName(game, *game->player.hand[1]);
  printf("+PLAYER SCORE [%d / %d]\n",
      game->player.score.low,
      game->player.score.high
  );
  if(checkNatural(game, PLAYER)){
    printf("+PLAYER HAS NATURAL BLACKJACK>\n");
  }
  else{
    int i = 2;
    while(playerHit()){
      printf("+PLAYER GETS CARD\n");
      dealCardToPlayer(game, PLAYER);
      assert(game->player.hand[i] != NULL);
      printCardName(game, *game->player.hand[i++]);
      printf("[%d / %d]\n",
          game->player.score.low,
          game->player.score.high
      );
      /*    temp: clear input buffer */
      char c;
      while ((c = getchar()) != '\n' && c != EOF){
        ; // empty
      }
      if(isPlayerBust(game, PLAYER)){
        printf("+PLAYER BUST\n");
        break;
      }
    }
  }
  return 1;
}
