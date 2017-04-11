/*
 * cycles.c
 *
 *  Created on: 23 jan. 2017
 *      Author: Johan Kämpe
 */


#include "..\def.h"

/*   Sets up new game */
bool newGameCycle(game * game){
  game->running = 1;
  firstDeal(game);
  printf("|DEALER CARDS\n");
  printCardName(game, *game->dealer.hand[0]);
  printCardName(game, *game->dealer.hand[1]);

  /*    Add score for hidden card */
  addScore(game, *game->dealer.hand[1], DEALER, MAIN_HAND);
  /*    Print score for shown card */
  printf("|DEALER SCORE [%d / %d]\n",
      game->dealer.score.low,
      game->dealer.score.high
  );
  printf("\n\n- PLAYER TURN HAND %d-\n\n", MAIN_HAND);
  printf("+PLAYER %d CARDS\n", MAIN_HAND);
  printCardName(game, *game->player[MAIN_HAND].hand[0]);
  printCardName(game, *game->player[MAIN_HAND].hand[1]);
  game->player[MAIN_HAND].done = 0;
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
    game->dealer.natural = 1;
    printf("|DEALER HAS NATURAL BLACKJACK>\n");
  }
  else if(isPlayerBust(game, DEALER, MAIN_HAND)){
    game->dealer.bust = 1;
  }
  else{
    printf("|DEALER STAYING>\n");
  }
  return 1;
}

/*    Player play cycle */
bool playerCycle(game * game){
  int hand = MAIN_HAND;
  printf("\n\n- PLAYER TURN HAND %d-\n\n", hand);
  printf("+PLAYER %d CARDS\n", hand);
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
    game->player[hand].natural = 1;
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
        game->player[hand].bust = 1;
        break;
      }
      /*   Stay  */
      if(getScore(game, PLAYER, hand) > getRandomNumber(21-8) + 8){
        printf("+PLAYER %d STAYS AT SCORE [%d]\n",
            hand,
            getScore(game, PLAYER, hand)
        );
        break;
      }
    }
  }
  return 1;
}

void winnerCycle(game * game){
  for(int hand = MAIN_HAND; hand < SPLITS_MAX; hand++){
    bool playerBust = game->player[hand].bust;
    bool dealerBust = game->dealer.bust;
    bool dealerNatural = game->dealer.natural;
    bool playerNatural = game->player[hand].natural;
    int winner = getWinner(game, hand);

    /*  Player has natural blackjack, 1.5x credits,
        unless dealer has natural   */
    if(playerNatural && !dealerNatural){
      printf("+PLAYER %d WINS (NATURAL): ", hand);
    }

    /*  Player bust, automatically loses   */
    else if(playerBust){
      printf("+PLAYER %d LOSES (BUST): ", hand);
    }

    /*  Player is not bust, but dealer is  */
    else if(!playerBust && dealerBust){
      printf("+PLAYER %d WINS (DEALER BUST): ", hand);
    }

    /*   Neither player or dealer is bust  */
    else if(!playerBust && !dealerBust){
      if(winner == PLAYER){
        printf("+PLAYER %d WINS: ", hand);
      }
      if(winner == DEALER){
        printf("+PLAYER %d LOSES: ", hand);
      }
      if(winner == DRAW){
        if(playerNatural && dealerNatural){
          printf("+PLAYER %d DRAWS: (BOTH NATURAL): ", hand);
        }
        else{
          printf("+PLAYER %d DRAWS: ", hand);
        }
      }
    }

    /*   Should not get here!  */
    else{
      printf("------> !! UNKNOWN WINNER !! ");
    }

    printf("[%d VS %d]\n",
      getScore(game, PLAYER, hand),
      getScore(game, DEALER, MAIN_HAND)
    );
  }
}
