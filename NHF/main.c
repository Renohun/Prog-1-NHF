#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "jatekAlgoritmus.h"
#include "tabellaOlvasas.h"
#include "debugmalloc.h"

int main(void) {

    int menu;
    do {
        printf("(1.) Jatek kezdese.\n");
        printf("(2.) Tabella megtekintese.\n");
        printf("(3.) Kilepes.\n");
        printf("\nMenu valasztasa: ");

        //Ha valami teljesen mas erteket adott meg
        if (scanf("%d", &menu) != 1) {
            //a getchar() a pufferben levo karakterek kiolvassa aztan eldobja oket, ez azert kell, hogy a ilyen eseten a jol fusson a kovetkezo kerdezes.
            //Hiszen ha nem csinaljuk meg akkor a kovetkezo scanf is ezt kapja meg, mert a puffer nem lesz ures
            while (getchar() != '\n');
            menu = 0;
        }

        if (menu == 1) {
            char valasz;
            do {
                mainJatekAlgoritmus();
                printf("\nSzeretnel megegyet jatszni? (I - N) ");
                scanf(" %c", &valasz);
            } while (toupper(valasz) != 'N');
            printf("\n");
        }
        else if (menu == 2) {
            tabellaOlvasasMain();
            printf("\n");
        }
        else if (menu != 3) {
            printf("Kerlek 1 - 3 kozott valassz egy szamot!\n\n");
        }
    } while (menu != 3);

    return 0;
}