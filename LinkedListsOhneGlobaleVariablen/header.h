//
// Created by martin on 23.01.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef LINKEDLISTSOHNEGLOBALEVARIABLEN_HEADER_H
#define LINKEDLISTSOHNEGLOBALEVARIABLEN_HEADER_H

#endif //LINKEDLISTSOHNEGLOBALEVARIABLEN_HEADER_H

typedef struct m_TINF19B {
    char name[80 + 1];
    char ort[80 + 1];
    char land[80 + 1];
    char umsatz[80 + 1];
    struct m_TINF19B *davor, *danach;
}t_TINF19B;

typedef struct {
    char name[80 + 1];
    char ort[80 + 1];
    char land[80 + 1];
    char umsatz[80 + 1];
    t_TINF19B *start, *mom, *zwischen;
}t_feld;


void menu(t_feld *f, char *datei);
void sortier_menu(t_feld *f, char *datei);
void loeschen_menu(t_feld *f, char *datei);
void suchen_menu(t_feld *f, char *datei);
void neuedatei_menu(t_feld *f, char *datei);
void up_structListe(t_feld *f);
void up_listeAdd(t_feld *f);
void up_hex(t_feld *f);
void up_dateneingabe(t_feld *f);
void up_datenausgabe(t_feld *f);
void up_printFirmen(char *datei);
void up_zwischenspeicher_loeschen(t_feld *f);
void up_deleteFile(char *datei);
void up_firmenInZwischenspeicher(t_feld *f, char *datei);
void up_firmenInZwischenspeicherBeginn(t_feld *f, char *datei);
void up_bubbleName(t_feld *f, char *datei);
void up_bubbleOrt(t_feld *f, char *datei);
void up_bubbleUmsatz(t_feld *f, char *datei);
void up_bubbleLand(t_feld *f, char *datei);
void up_loeschen(t_feld *f, int element, char *datei);
void up_doppelteLoeschen(t_feld *f, char *datei);
void up_kommentareEntfernen(t_feld *f, int element, char *datei);
void up_tauscheZeiger(t_feld *f);
void up_zwischenspeicherspeichern(t_feld *f, char *datei);
void up_sucheName(t_feld *f);
void up_sucheOrt(t_feld *f);
void up_sucheLand(t_feld *f);
void up_sucheUmsatz(t_feld *f);