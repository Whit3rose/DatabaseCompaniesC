//
// Created by martin on 23.01.20.
//
#include "header.h"

void up_structListe(t_feld *f) {
    strcpy(f -> mom -> name, f -> name);
    strcpy(f -> mom -> ort, f -> ort);
    strcpy(f -> mom -> land, f -> land);
    strcpy(f -> mom -> umsatz, f -> umsatz);
}

void up_dateneingabe(t_feld *f) {
    printf("Name eingeben:");
    scanf("%s", f -> name);
    fflush(stdin);
    printf("Hauptsitz eingeben:");
    scanf("%s", f -> ort);
    fflush(stdin);
    printf("Land eingeben:");
    scanf("%s", f -> land);
    fflush(stdin);
    printf("Umsatz eingeben (in 1 mio):");
    scanf("%s", f -> umsatz);
    fflush(stdin);

    up_listeAdd(f);
}

void up_datenausgabe(t_feld *f) {
    char name[10];
    char ort[10];
    char land[10];
    char umsatz[10];
    char index[10];
    int i = 1;
    strcpy(index, "Index");
    strcpy(name, "Name");
    strcpy(ort, "Hauptsitz");
    strcpy(land, "Land");
    strcpy(umsatz, "Umsatz");

    printf("\n");

    f -> mom = f -> start;
    if (!f -> mom) {
        printf("Zwischenspeicher leer\n");
    }
    else {
        f -> mom = f -> start;
        printf("%-10s %-20s %-20s %-20s %-20s\n", index, name, ort, land, umsatz);
        printf("\n");
        while (f -> mom) {
            printf("% -10d %-20s %-20s %-20s %-20s", i, f -> mom -> name, f -> mom -> ort, f -> mom -> land, f -> mom -> umsatz);
            f -> mom = f -> mom -> danach;
            i++;
        }
    }
    printf("\n");
}

void up_listeAdd(t_feld *f) {
    f -> mom = (t_TINF19B*) malloc(sizeof(t_TINF19B));
    up_structListe(f);
    f -> mom -> davor = f -> zwischen;
    f -> mom -> danach = 0;
    if (!f -> zwischen) {
        f -> start = f -> mom;
    }
    else {
        f -> zwischen -> danach = f -> mom;
    }
    f -> zwischen = f -> mom;
}

void up_hex(t_feld *f) {
    f -> mom = f -> start;
    printf("Name                   mom        davor      danach\n");
    while (f -> mom) {
        printf("%-20s %10X %10X %10X\n", f -> mom -> name, f -> mom, f-> mom -> davor, f -> mom -> danach);
        f -> mom = f -> mom -> danach;
    }
}

void up_zwischenspeicher_loeschen(t_feld *f) {
    f -> start = 0;
    f -> mom = 0;
    f -> zwischen = 0;
}

void up_firmenInZwischenspeicher(t_feld *f, char *datei) {
    FILE *einschreiben;
    char name[80 + 1];
    char ort[80 + 1];
    char land[80 + 1];
    char umsatz[80 + 1];
    char index[80 + 1];
    int kommentare[80 + 1];
    int x = 1;
    int i = 0;

    up_zwischenspeicher_loeschen(f);

    einschreiben = fopen(datei, "r");
    if (!einschreiben) {
        printf("Fehler beim oeffnen der Datei!\nBitte versichern Sie sich, dass der Dateiname richtig geschrieben ist\n");
        exit(0);
    }
    else {
        while (1) {
            fgets(index, 6, einschreiben);
            fgets(name, 21, einschreiben);
            strcpy(f -> name, name);
            fgets(ort, 21, einschreiben);
            strcpy(f -> ort, ort);
            fgets(land, 21, einschreiben);
            strcpy(f -> land, land);
            fgets(umsatz, 80, einschreiben);
            strcpy(f -> umsatz, umsatz);

            if(feof(einschreiben)) {
                break;
            }
            up_listeAdd(f);
            while(f -> mom) {
                if(strncmp(index, "***", 3) == 0) {
                    kommentare[i] = x;
                    i++;
                }
                f -> mom = f -> mom -> danach;
            }
            x++;

        }
        fclose(einschreiben);
    }
    for(int in = 0; in < i; in++) {
        up_kommentareEntfernen(f, kommentare[in] - in, datei);
    }
}

void up_firmenInZwischenspeicherBeginn(t_feld *f, char *datei) {
    FILE *einschreiben;
    char name[80 + 1];
    char ort[80 + 1];
    char land[80 + 1];
    char umsatz[80 + 1];
    char index[80 + 1];
    int kommentare[80 + 1];
    int x = 1;
    int i = 0;

    up_zwischenspeicher_loeschen(f);

    einschreiben = fopen(datei, "r");
    if (!einschreiben) {
        printf("Fehler beim oeffnen der Datei!\nBitte versichern Sie sich, dass der Dateiname richtig geschrieben ist\n");
        exit(0);
    }
    else {
        while (1) {
            fgets(index, 6, einschreiben);
            fgets(name, 21, einschreiben);
            strcpy(f -> name, name);
            fgets(ort, 21, einschreiben);
            strcpy(f -> ort, ort);
            fgets(land, 21, einschreiben);
            strcpy(f -> land, land);
            fgets(umsatz, 80, einschreiben);
            strcpy(f -> umsatz, umsatz);

            if(feof(einschreiben)) {
                break;
            }
            up_listeAdd(f);
            while(f -> mom) {
                if(strncmp(index, "***", 3) == 0) {
                    kommentare[i] = x;
                    i++;
                }
                f -> mom = f -> mom -> danach;
            }
            x++;

        }
        fclose(einschreiben);
        printf("%s erfolgreich eingelesen!\n", datei);
    }
    for(int in = 0; in < i; in++) {
        up_kommentareEntfernen(f, kommentare[in] - in, datei);
    }
}

void up_printFirmen(char *datei) {
    FILE *einlesen;
    char htext[80 + 1];
    einlesen = fopen(datei, "r");
    if (!einlesen) {
        printf("Fehler beim öffnen der Datei");
    }
    else {
        fgets(htext, 80, einlesen);
        while (!feof(einlesen)) {
            printf("%s", htext);
            fgets(htext, 80, einlesen);
        }
        fclose(einlesen);
    }
}

void up_zwischenspeicherspeichern(t_feld *f, char *datei) {
    char name[80 + 1];
    char ort[80 + 1];
    char land[80 + 1];
    char umsatz[80 + 1];
    char index[80 + 1];
    int i = 1;

    up_deleteFile(datei);
    f -> mom = f -> start;
    FILE *einschreiben;
    einschreiben = fopen(datei, "a");
    if (!einschreiben) {
        printf("Fehler beim öffnen der Datei");
    }
    else {
        while (f -> mom) {
            sprintf(index, "%-5s", itoa(i, index, 10));
            sprintf(name, "%-20s", f -> mom -> name);
            sprintf(ort, "%-20s", f -> mom -> ort);
            sprintf(land, "%-20s", f -> mom -> land);
            sprintf(umsatz, "%-19s", f -> mom -> umsatz);
            fputs(index, einschreiben);

            fputs(name, einschreiben);
            fputs(ort, einschreiben);
            fputs(land, einschreiben);
            fputs(umsatz, einschreiben);
            f -> mom = f -> mom -> danach;
            i++;
        }
        fputs("\n", einschreiben);
    }
    fclose(einschreiben);
}

void up_deleteFile(char *datei) {
    FILE *pFile;

    pFile = fopen(datei, "w");

    if (pFile != NULL) {
        fwrite(NULL, 0, 0, pFile);
        fclose(pFile);
    }
}

void up_bubbleUmsatz(t_feld *f, char *datei) {
    int i = 0;
    int j = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    while (i < counter - 1) {
        j = 0;
        f -> mom = f -> start;
        while (j < counter - 1) {
            if (f -> mom -> danach == NULL){
            }
            else if (atoi(f -> mom -> umsatz) > atoi(f -> mom -> danach -> umsatz)) {
                up_tauscheZeiger(f);
            }
            else {
                f -> mom = f -> mom -> danach;
            }
            j++;
        }
        i++;
    }
    printf("done\n");
    up_datenausgabe(f);
    up_zwischenspeicherspeichern(f, datei);
}

void up_bubbleLand(t_feld *f, char *datei) {
    int i = 0;
    int j = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    while (i < counter - 1) {
        j = 0;
        f -> mom = f -> start;
        while (j < counter - 1) {
            if (f -> mom -> danach == NULL){
            }
            else if (strcmp((f -> mom -> land), (f -> mom -> danach -> land)) > 0) {
                up_tauscheZeiger(f);
            }
            else {
                f -> mom = f -> mom -> danach;
            }
            j++;
        }
        i++;
    }
    printf("done\n");
    up_datenausgabe(f);
    up_zwischenspeicherspeichern(f, datei);
}

void up_bubbleOrt(t_feld *f, char *datei) {
    int i = 0;
    int j = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    while (i < counter - 1) {
        j = 0;
        f -> mom = f -> start;
        while (j < counter - 1) {
            if (f -> mom -> danach == NULL){
            }
            else if (strcmp((f -> mom -> ort), (f -> mom -> danach -> ort)) > 0) {
                up_tauscheZeiger(f);
            }
            else {
                f -> mom = f -> mom -> danach;
            }
            j++;
        }
        i++;
    }
    printf("done\n");
    up_datenausgabe(f);
    up_zwischenspeicherspeichern(f, datei);
}

void up_bubbleName(t_feld *f, char *datei) {
    int i = 0;
    int j = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    while (i < counter - 1) {
        j = 0;
        f -> mom = f -> start;
        while (j < counter - 1) {
            if (f -> mom -> danach == NULL){
            }
            else if (strcmp((f -> mom -> name), (f -> mom -> danach -> name)) > 0) {
                up_tauscheZeiger(f);
            }
            else {
                f -> mom = f -> mom -> danach;
            }
            j++;
        }
        i++;
    }
    printf("done\n");
    up_datenausgabe(f);
    up_zwischenspeicherspeichern(f, datei);
}

void up_sucheName(t_feld *f) {
    int counter = 0;
    char name[20 + 1];
    int i = 0;
    int zaehler = 1;

    printf("Welches Unternehmen soll gesucht werden?\n");
    gets(name);

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    f -> mom = f -> start;
    while (i < counter) {
        if (strncmp(name, f -> mom -> name, strlen(name)) == 0) {
            printf("%-20s %-20s %-20s %-20s", f -> mom -> name, f -> mom -> ort, f -> mom -> land, f -> mom -> umsatz);
        }

        if (f -> mom -> danach == NULL){
            break;
        }

        f -> mom = f -> mom -> danach;
        i++;
        zaehler++;

        if (zaehler == counter) {
            printf("Kein passendes Element gefunden\n");
        }
    }
}

void up_sucheOrt(t_feld *f) {
    int counter = 0;
    char ort[20 + 1];
    int i = 0;
    int zaehler = 1;

    printf("Welcher Ort soll gesucht werden?\n");
    gets(ort);

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    f -> mom = f -> start;
    while (i < counter) {
        if (strncmp(ort, f -> mom -> ort, strlen(ort)) == 0) {
            printf("%-20s %-20s %-20s %-20s", f -> mom -> name, f -> mom -> ort, f -> mom -> land, f -> mom -> umsatz);
        }
        if (f -> mom -> danach == NULL){
            break;
        }

        f -> mom = f -> mom -> danach;
        i++;
        zaehler++;

        if (zaehler == counter) {
            printf("Kein passendes Element gefunden\n");
        }
    }
}

void up_sucheLand(t_feld *f) {
    int counter = 0;
    char land[20 + 1];
    int i = 0;
    int zaehler = 1;

    printf("Welches Land soll gesucht werden?\n");
    gets(land);

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    f -> mom = f -> start;
    while (i < counter) {
        if (strncmp(land, f -> mom -> land, strlen(land)) == 0) {
            printf("%-20s %-20s %-20s %-20s", f -> mom -> name, f -> mom -> ort, f -> mom -> land, f -> mom -> umsatz);
            zaehler = 0;
        }

        if (f -> mom -> danach == NULL){
            break;
        }

        f -> mom = f -> mom -> danach;
        i++;
        zaehler++;

        if (zaehler == counter) {
            printf("Kein passendes Element gefunden\n");
        }
    }
}

void up_sucheUmsatz(t_feld *f) {
    int counter = 0;
    int umsatz = 0;
    int i = 0;
    int zaehler = 1;

    printf("Welcher Umsatz soll gesucht werden?\n");
    scanf("%d", &umsatz);

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    f -> mom = f -> start;
    while (i < counter) {
        if (umsatz == atoi(f -> mom -> umsatz)) {
            printf("%-20s %-20s %-20s %-20s", f -> mom -> name, f -> mom -> ort, f -> mom -> land, f -> mom -> umsatz);
        }

        if (f -> mom -> danach == NULL){
            break;
        }
        f -> mom = f -> mom -> danach;
        i++;
        zaehler++;

        if (zaehler == counter) {
            printf("Kein passendes Element gefunden\n");
        }
    }
}

void up_tauscheZeiger(t_feld *f) {
    if (!f -> mom -> danach) {
        f -> mom -> davor -> davor -> danach = f -> mom;
        f -> mom -> danach = f -> mom -> davor;
        f -> mom -> davor = f -> mom -> davor -> davor;
        f -> mom -> davor -> danach = NULL;
        f -> mom -> davor -> davor = f -> mom;
    }

    else if (!f -> mom -> danach -> danach) {
        f -> mom -> danach -> danach = f -> mom;
        f -> mom -> davor -> danach = f -> mom -> danach;
        f -> mom -> danach -> davor = f -> mom -> davor;
        f -> mom -> davor = f -> mom -> danach;
        f -> mom -> danach = NULL;
    }

    else if (!f -> mom -> davor){
        f -> mom -> danach -> danach -> davor = f -> mom;
        f -> mom -> danach -> davor = NULL;
        f -> mom -> davor = f -> mom -> danach;
        f -> mom -> danach = f -> mom -> danach -> danach;
        f -> mom -> davor -> danach = f -> mom;
        f -> start = f -> mom -> davor;
    }

    else {
        f -> mom -> danach -> danach -> davor = f -> mom;
        f -> mom -> davor -> danach = f -> mom -> danach;
        f -> mom -> danach -> davor = f -> mom -> davor;
        f -> mom -> danach = f -> mom -> danach -> danach;
        f -> mom -> davor -> danach -> danach = f -> mom;
        f -> mom -> davor = f -> mom -> davor -> danach;
    }
}

void up_doppelteLoeschen(t_feld *f, char *datei) {
    int i = 0;
    int j = 0;
    int counter = 0;

    up_bubbleOrt(f, datei);
    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    while (i < counter) {
        j = 0;
        f -> mom = f -> start;
        while (j < counter) {
            if (f -> mom -> danach == NULL){
                break;
            }
            if (strcmp((f -> mom -> name), (f -> mom -> danach -> name)) == 0 && strcmp((f -> mom -> ort), (f -> mom -> danach -> ort)) == 0 && strcmp((f -> mom -> land), (f -> mom -> danach -> land)) == 0 && strcmp((f -> mom -> umsatz), (f -> mom -> danach -> umsatz)) == 0) {
                up_loeschen(f, j + 1, datei);
            }
            f -> mom = f -> mom -> danach;
            j++;
        }
        i++;
    }
    printf("done\n");
    up_datenausgabe(f);
    up_zwischenspeicherspeichern(f, datei);
}

void up_loeschen(t_feld *f, int element, char *datei) {
    int i = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    if (element > counter) {
        printf("So viele Eintraege sind nicht vorhanden\n");
        menu(f, datei);
    }

    f -> mom = f -> start;
    while (i < element - 1) {
        f -> mom = f -> mom -> danach;
        i++;
    }

    if (f -> mom -> davor && f -> mom -> danach) {
        f -> mom -> davor -> danach = f -> mom -> danach;
        f -> mom -> danach -> davor = f -> mom -> davor;
        free(f -> mom);
        f -> mom = f -> start;
    }

    else if (!f -> mom -> danach && !f -> mom -> davor) {
        up_deleteFile(datei);
    }

    else if (!f -> mom -> danach) {
        f -> mom -> davor -> danach = NULL;
        f -> mom = NULL;
        f -> mom = f -> start;
    }

    else {
        f -> mom = f -> mom -> danach;
        f -> start = f -> mom;
    }
    printf("Element %d wurde erfolgreich geloescht\n", element);
    up_zwischenspeicherspeichern(f, datei);
}

void up_kommentareEntfernen(t_feld *f, int element, char *datei) {
    int i = 0;
    int counter = 0;

    f -> mom = f -> start;
    while (f -> mom) {
        counter++;
        f -> mom = f -> mom -> danach;
    }

    if (element > counter) {
        printf("So viele Eintraege sind nicht vorhanden\n");
        menu(f, datei);
    }

    f -> mom = f -> start;
    while (i < element - 1) {
        f -> mom = f -> mom -> danach;
        i++;
    }

    if (f -> mom -> davor && f -> mom -> danach) {
        f -> mom -> davor -> danach = f -> mom -> danach;
        f -> mom -> danach -> davor = f -> mom -> davor;
        free(f -> mom);
        f -> mom = f -> start;
    }

    else if (!f -> mom -> danach && !f -> mom -> davor) {
        up_deleteFile(datei);
    }

    else if (!f -> mom -> danach) {
        f -> mom -> davor -> danach = NULL;
        f -> mom = NULL;
        f -> mom = f -> start;
    }

    else {
        f -> mom = f -> mom -> danach;
        f -> start = f -> mom;
    }
}