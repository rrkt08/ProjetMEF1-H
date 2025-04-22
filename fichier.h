#include <stdio.h> 
#include <stdlib.h>
#define MAX_CARTES 150

typedef struct{
    int valeur; // dans le fichier les valeurs
    int visible; // vrai 1 affiché, faux 0 caché
}Carte;

typedef struct{
    Carte cartes[MAX_CARTES];//tableau de cartes
    int defausse;// vaut 0 au début (vide)
    char nom[30];
}Joueur;

typedef struct{
    Carte cartes[MAX_CARTES];
    int nbr_cartes; // Pour savoir si c'est fini ou pas car on prend des cartes a chaque tour
}Pioche;

int card_user();
int nbr_user();
void crea_joueurs(Joueur *j, int n);
void charger();
void Menu();
void initialiserPioche(Pioche *pioche);
void melangerPioche(Pioche *pioche);
int piocherCarte(Pioche *pioche);


