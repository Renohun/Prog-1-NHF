#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "jatekAlgoritmus.h"
#include "tabellaOlvasas.h"
#include "debugmalloc.h"

int main(void) {

    printf("(1.) Jatek kezdese.\n");
    printf("(2.) Tabelle megtekintes.\n");
    printf("(3.) Kilepes.\n");


    printf("\n\nMenu valasztasa:");
    int menu;
    scanf("%d", &menu);

    if (menu == 1) {
        mainJatekAlgoritmus();

        char valasz;
        printf("\nSzeretnel megegyet jatszni? (I - N) ");
        scanf(" %c", &valasz);

        while (toupper(valasz) != 'N') {
            mainJatekAlgoritmus();
            printf("\nSzeretnel megegyet jatszni? (I - N) ");
            scanf(" %c", &valasz);
        }
        printf("\n");
        main();
    }
    else if (menu == 2) {
        tabellaOlvasasMain();
        printf("\n");
        main();
    }
    else if (menu == 3) {
        exit(0);
    }

    return 0;
}