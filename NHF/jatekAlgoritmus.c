//
// Created by admin on 11/5/2026.
//

#include "jatekAlgoritmus.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomSzinValasztas(char* szinek, int meret) {
    int min = 1, max = 8;
    for (int i = 0; i < meret; ++i) {
        int szin = rand() % (max - min + 1) + min;
        switch (szin) {
            case 1:
                //piros
                szinek[i] = 'P';
                break;
            case 2:
                //feher
                szinek[i] = 'F';
                break;
            case 3:
                //kek
                szinek[i] = 'K';
                break;
            case 4:
                //rozsaszin
                szinek[i] = 'R';
                break;
            case 5:
                szinek[i] = 'N';
                break;
            case 6:
                szinek[i] = 'L';
                break;
            case 7:
                szinek[i] = 'S';
                break;
            case 8:
                szinek[i] = 'Z';
                break;
        }
    }
}


void mainJatekAlgoritmus() {
    srand(time(NULL));
    char szinek [4] = {0};
    randomSzinValasztas(szinek, 4);
    for (int i = 0; i < 4; ++i) {
        printf("%c\t", szinek[i]);
    }
}