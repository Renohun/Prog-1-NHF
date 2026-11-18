//
// Created by admin on 11/5/2026.
//

#include "tabellaOlvasas.h"
#include  <stdio.h>
#include "debugmalloc.h"

void tabellaOlvasasMain() {
    printf("A jelenlegi tabella allasa:\n");

    FILE* fileOlv = fopen("tabella.txt", "r");
    if (fileOlv == NULL) {printf("Sikeretlen fajl olvasas - Valoszinuleg meg nem letezik a fajl");}
    char sor [100];
    while (fgets(sor, 100, fileOlv) != NULL) {
        printf("%s", sor);
    }
    fclose(fileOlv);
}
