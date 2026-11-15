#include <ctype.h>
#include <stdio.h>
#include "jatekAlgoritmus.h"
#include "tabellaOlvasas.h"

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
            printf("\n Szeretnel megegyet jatszni? (I - N) ");
            scanf("%c", &valasz);
        }
    }
    else if (menu == 2) {
        irasTestA();
    }
    else if (menu == 3) {

    }

    return 0;
}