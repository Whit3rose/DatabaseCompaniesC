#include "header.h"

int main() {
    char datei[80 + 1];
    t_feld feld, *f;
    f = &feld;
    f -> start = 0;
    f -> mom = 0;
    f -> zwischen = 0;

    printf("Welche Datei soll verwendet werden?");
    gets(datei);
    up_firmenInZwischenspeicher(f, datei);
    up_zwischenspeicherspeichern(f, datei);
    up_firmenInZwischenspeicherBeginn(f, datei);
    while(1) {
        menu(f, datei);
    }
}

void menu(t_feld *f, char *datei) {
    int eingabe = 0;
    printf("Waehlen Sie eine der Optionen: \n");
    printf("(1) neues Unternehmen hinzufuegen\n");
    printf("(2) Zwischenspeicher ausgeben\n");
    printf("(3) Liste ausgeben\n");
    printf("(4) Daten speichern\n");
    printf("(5) Daten loeschen\n");
    printf("(6) Firmen einlesen\n");
    printf("(7) Sortieren\n");
    printf("(8) Adressen der Pointer ausgeben\n");
    printf("(9) Nach Elemtenten suchen\n");
    printf("(0) exit\n");
    scanf("%d", &eingabe);
    fflush(stdin);
    switch(eingabe) {
        case 1: up_dateneingabe(f); neuedatei_menu(f, datei); break;
        case 2: up_datenausgabe(f); break;
        case 3: up_printFirmen(datei); break;
        case 4: up_zwischenspeicherspeichern(f, datei); break;
        case 5: loeschen_menu(f, datei); break;
        case 6: up_firmenInZwischenspeicher(f, datei); break;
        case 7: sortier_menu(f, datei); break;
        case 8: up_hex(f); break;
        case 9: suchen_menu(f, datei); break;
        case 0: exit(0);
        default: printf("Error 404. Intelligence not found!\n"); break;
    }
}

void sortier_menu(t_feld *f, char *datei) {
    int eingabe = 0;
    printf("Please choose an option: \n");
    printf("(1) Unternehmen alphabetisch sortieren\n");
    printf("(2) Orte alphabetisch sortieren\n");
    printf("(3) Unternehmen nach Laendern sortieren\n");
    printf("(4) Unternehmen nach Umsatz sortieren\n");
    printf("(9) exit\n");
    scanf("%d", &eingabe);
    fflush(stdin);
    switch(eingabe) {
        case 1: up_bubbleName(f, datei); break;
        case 2: up_bubbleOrt(f, datei); break;
        case 3: up_bubbleLand(f, datei); break;
        case 4: up_bubbleUmsatz(f, datei); break;
        case 9: break;
        default: printf("Error 404. Intelligence not found!\n"); break;
    }
}

void neuedatei_menu(t_feld *f, char *datei) {
    int eingabe = 0;
    printf("Wollen Sie ein neues Unternehmen hinzufuegen?\n");
    printf("(1) Ja\n");
    printf("(2) Nein\n");
    scanf("%d", &eingabe);
    fflush(stdin);
    switch (eingabe) {
        case 1: up_zwischenspeicherspeichern(f, datei); up_zwischenspeicher_loeschen(f); up_firmenInZwischenspeicher(f, datei); up_dateneingabe(f); neuedatei_menu(f, datei); break;
        case 2: up_zwischenspeicherspeichern(f, datei); up_zwischenspeicher_loeschen(f); up_firmenInZwischenspeicher(f, datei); break;
        default: printf("Error 404. Intelligence not found!\n"); break;
    }
}

void loeschen_menu(t_feld *f, char *datei) {
    int eingabe = 0;
    int input = 0;
    printf("Waehlen Sie eine der folgenden Optionen:\n");
    printf("(1) Einzelne Elemente loeschen\n");
    printf("(2) Alle Elemente loeschen\n");
    printf("(3) Zwischenspeicher loeschen\n");
    printf("(4) doppelte Eintraege loeschen (ACHTUNG: Mit sortieren!)\n");
    printf("(5) zurueck\n");
    scanf("%d", &eingabe);
    fflush(stdin);
    switch (eingabe) {
        case 1: printf("Welches Element soll geloescht werden?");
            scanf("%d", &input);
            up_loeschen(f, input, datei);
            up_zwischenspeicherspeichern(f, datei);
            up_firmenInZwischenspeicher(f, datei);
            break;
        case 2: up_deleteFile(datei); break;
        case 3: up_zwischenspeicher_loeschen(f); break;
        case 4: up_doppelteLoeschen(f, datei); break;
        case 5: break;
        default: printf("Error 404. Intelligence not found!\n"); break;
    }
}

void suchen_menu(t_feld *f, char *datei) {
    int eingabe = 0;
    printf("Wonach wollen Sie suchen?\n");
    printf("(1) Name\n");
    printf("(2) Ort\n");
    printf("(3) Land\n");
    printf("(4) Umsatz\n");
    printf("(5) zurueck\n");
    scanf("%d", &eingabe);
    fflush(stdin);
    switch (eingabe) {
        case 1: up_sucheName(f); break;
        case 2: up_sucheOrt(f); break;
        case 3: up_sucheLand(f); break;
        case 4: up_sucheUmsatz(f); break;
        case 5: break;
        default: printf("Error 404. Intelligence not found!\n"); break;
    }
}