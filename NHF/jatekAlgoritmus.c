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
    printf("\n");

    int formatEll = scanf(" %c-%c-%c-%c", &kapottSzinek[0], &kapottSzinek[1], &kapottSzinek[2], &kapottSzinek[3]);
    int szinEll = bevitelEll(kapottSzinek, 4);
    while (formatEll != 4 || szinEll != 1) {
        formatEll = scanf(" %c-%c-%c-%c", &kapottSzinek[0], &kapottSzinek[1], &kapottSzinek[2], &kapottSzinek[3]);
        szinEll = bevitelEll(kapottSzinek, 4);
    }
    return kapottSzinek;
}

int* visszaJelzes(char* randomSzinek, char* kapottSzinek, int meret) {

    int* tomb = calloc(meret * sizeof (int));
    int feketeTomb [meret] = {0};

    //Feketek avagy 2esek ellenorzese
    for (int i = 0; i < meret; ++i) {
        if (kapottSzinek[i] == randomSzinek[i]) {
            feketeTomb[i] = 1;
            tomb[i] = 2;
        }
    }

    //Feherek avagy 1esek ellenorzese, de ugy hogy nem vesszuk figyelembe azokat, ahol mar 2eset kapott
    for (int i = 0; i < meret; ++i) {
        if (tomb[i] != 2) {
            for (int j = 0; j < meret; ++j) {
                if (kapottSzinek[i] == randomSzinek[j] && feketeTomb[j] != 1) {
                    tomb[i] = 1;
                    feketeTomb[j] = 1;
                    break;
                }
            }
        }
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
    printf("------------------------------------------------------------\n------------------------------------------------------------");
    printf("\n");
    for (int i = 0; i < 4; ++i) {
        printf("||  ?  ");
    }
    printf("||");

    int jatekFolyamat = 1;
    while (jatekFolyamat) {
        //Ide jon minden olyan kod ami a jatek folyaman meghivodik
        char* kapottSzinek = szinBevitel();
        //printf("\n");
        for (int i = 0; i < 4; ++i) {
            printf("||  %c  ", kapottSzinek[i]);
        }
        printf("||");

        int* visszaJelzesTomb = visszaJelzes(szinek, kapottSzinek, 4);
        for (int i = 0; i < 4; ++i) {
            printf("||  %d  ", visszaJelzesTomb[i]);
        }
        printf("||");

        int jatekFolyamatEll = 0;
        for (int i = 0; i < 4; ++i) {
            if (visszaJelzesTomb[i] == 2) {
                jatekFolyamatEll++;
            }
        }

        if (jatekFolyamatEll == 4) {
            jatekFolyamat = 0;
            free(visszaJelzesTomb);
            free(kapottSzinek);
        }
        else {
            printf("\n");
            printf("------------------------------------------------------------\n------------------------------------------------------------");
            free(visszaJelzesTomb);
            free(kapottSzinek);
        }
    }
    printf("\nGratula gyoztel!");
    printf("\n");
}