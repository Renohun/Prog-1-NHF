//
// Created by admin on 11/5/2026.
//

#include "jatekAlgoritmus.h"
#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
int bevitelEll(char* szinek, int meret) {
    for (int i = 0; i < meret; ++i) {
        if (!strchr("PFKRNLSZ", szinek[i])) {
            return 0;
        }
    }
    return 1;
}

char* szinBevitel(void) {
    char* kapottSzinek = malloc (4 * sizeof (char));
    if (!kapottSzinek) { return  NULL; }
    printf("\t");

    int formatEll = scanf(" %c-%c-%c-%c", &kapottSzinek[0], &kapottSzinek[1], &kapottSzinek[2], &kapottSzinek[3]);
    int szinEll = bevitelEll(kapottSzinek, 4);
    while (formatEll != 4 || szinEll != 1) {
        formatEll = scanf(" %c-%c-%c-%c", &kapottSzinek[0], &kapottSzinek[1], &kapottSzinek[2], &kapottSzinek[3]);
        szinEll = bevitelEll(kapottSzinek, 4);
    }
    return kapottSzinek;
}

int* visszaJelzes(char* randomSzinek, char* kapottSzinek, int meret) {

    int* tomb = malloc(4 * sizeof (int));
    int oszlopVissajelzes;
    for (int i = 0; i < meret; ++i) {
        oszlopVissajelzes = 0;
        for (int j = 0; j < meret; ++j) {
            if (kapottSzinek[i] == randomSzinek[j]) {
                oszlopVissajelzes = 1;
                if (i == j) {
                    oszlopVissajelzes = 2;
                }
            }
        }
        tomb[i] = oszlopVissajelzes;
    }
    return tomb;
}

void mainJatekAlgoritmus(void) {
    //Ez azert kell hogy mindig rendesen generalja le a random szamok, avagy valtozzon a seed
    srand(time(NULL));
    char szinek [4] = {0};
    randomSzinValasztas(szinek, 4);

    for (int i = 0; i < 4; ++i) {
        printf("%c", szinek[i]);
    }

    printf("\n");

    //Tablazat elkezdese
    printf("------------------------------\n------------------------------");
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        printf("||  ?  ");
    }
    printf("||");

    char* kapottSzinek = szinBevitel();
    int* jelzes = visszaJelzes(szinek, kapottSzinek, 4);

    for (int i = 0; i < 4; ++i) {
        printf("%d", jelzes[i]);
    }
    free(kapottSzinek);
    free(jelzes);

    //int jatekFolyamat = 1;

    /*
    while (jatekFolyamat) {
        //Ide jon minden olyan kod ami a jatek folyaman meghivodik
    }*/
    printf("\n");
}