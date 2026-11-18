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

    int* tomb = calloc(meret, sizeof (int));
    int feketeTomb [4] = {0};

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

int fajlOlvasas(char* felhasznaloNev) {
    FILE* file = fopen("tabella.txt", "r");
    if (file == NULL) {
        return 1;
    }
    //100 hossz kb eleg
    char sor[100];
    while (fgets(sor, sizeof sor, file) != NULL) {
        char fajlFelhasznaloNev[51];

        int i;
        for (i = 0; i < 50 && sor[i] != '-' && sor[i] != '\0'; ++i) {
            fajlFelhasznaloNev[i] = sor[i];
        }
        fajlFelhasznaloNev[i] = '\0';

        int cmpErtek = strcmp(felhasznaloNev, fajlFelhasznaloNev);
        if (cmpErtek == 0) {
            fclose(file);
            //Volt egyezes - tehat ez a nev mar szerepel a tabellan
            return 2;
        }
    }
    fclose(file);
    //Nem volt egyezes
    return 1;
}

int fajlIras(char* falhasznaloNev, int korokSzama, float ido) {

    int olvasasiErtek = fajlOlvasas(falhasznaloNev);

    if (olvasasiErtek == 1) {
        FILE* file = fopen("tabella.txt", "a");
        if (file == NULL) {
            printf("Hiba tortent fajlkezles alatt!");
            return 0;
        }
        fprintf(file, "%s-%d-%f\n", falhasznaloNev, korokSzama, ido);
        fclose(file);

        return 1;
    }
    else if (olvasasiErtek == 2) {

        FILE* fileOlv = fopen("tabella.txt", "r");
        FILE* fileIrj = fopen("tabella_uj.txt", "w");

        if (fileOlv == NULL){ fclose(fileIrj); return 0; }
        if (fileIrj == NULL){ fclose(fileOlv); return 0; }

        char sor [100];
        while (fgets(sor, sizeof sor, fileOlv) != NULL) {
            char fajlFelhasznaloNev[51];

            int i;
            for (i = 0; i < 50 && sor[i] != '-' && sor[i] != '\0'; ++i) {
                fajlFelhasznaloNev[i] = sor[i];
            }
            fajlFelhasznaloNev[i] = '\0';
            //jo sorban vagyunk kell osszahasonlitanunk erteket
            if (strcmp(fajlFelhasznaloNev, falhasznaloNev) == 0) {
                int fajlKorok;
                float fajlIdo;

                if (sscanf(sor, "%*[^-]-%d-%f", &fajlKorok, &fajlIdo) == 2) {
                    if (fajlKorok > korokSzama && fajlIdo > ido) {
                        fprintf(fileIrj, "%s-%d-%f\n", falhasznaloNev, korokSzama, ido);
                    }
                    else {
                        fprintf(fileIrj, "%s", sor);
                    }
                }
            }
            else  {
                fprintf(fileIrj, "%s", sor);
            }
        }

        fclose(fileOlv);
        fclose(fileIrj);
        remove("tabella.txt");
        rename("tabella_uj.txt", "tabella.txt");

        return 2;
    }
    return 0;
}

void mainJatekAlgoritmus(void) {
    //Ez azert kell hogy mindig rendesen generalja le a random szamok, avagy valtozzon a seed
    srand(time(NULL));
    char szinek [4] = {0};
    randomSzinValasztas(szinek, 4);


    for (int i = 0; i < 4; ++i) {
        printf("%c", szinek[i]);
    }

    char felhasznaloNev[51];
    printf("\nIrjon be egy felhasznalonevet (50 karakteres): ");
    //csak 50 karakter lehet + 1 a \0
    scanf(" %50s", felhasznaloNev);

    int korokSzama = 0;

    printf("\n");
    //Tablazat elkezdese
    printf("------------------------------------------------------------\n------------------------------------------------------------");
    printf("\n");
    for (int i = 0; i < 8; ++i) {
        printf("||  ?  ");
    }
    printf("||");

    //stopper inditasa
    clock_t indit = clock();

    int jatekFolyamat = 1;
    while (jatekFolyamat) {

        korokSzama++;

        //Ide jon minden olyan kod ami a jatek folyaman meghivodik
        char* kapottSzinek = szinBevitel();
        //printf("\n");
        for (int i = 0; i < 4; ++i) {
            printf("||  %c  ", kapottSzinek[i]);
        }
        //printf("||");

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

    clock_t leallit = clock();
    float ms = (float)(leallit - indit) / CLOCKS_PER_SEC;

    //Minden adat meg van ahhoz hogy fajlba irhassak
    printf("\nGratulalunk neked %s gyoztel!", felhasznaloNev);
    printf("\nEnnyi masodperc kellet neked: %f", ms);
    printf("\nEnnyi tipp kellett: %d", korokSzama);

    int eredmeny = fajlIras(felhasznaloNev, korokSzama, ms);
    if (eredmeny == 1 || eredmeny == 2) {
        printf("\nSikeres fajlkezelese!");
    }

    printf("\n");
}