/*
 * num.c
 *
 *  Created on: 16 jan. 2017
 *      Author: Johan Kämpe
 */

#include "..\def.h"

void initRandom(){
	srand(time(NULL));
}

int getRandomNumber(int max){
	return rand() % max;
}
