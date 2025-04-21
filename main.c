#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int main() {
    Menu();

    // Saisie du nombre de joueurs et cartes
    int nbr_joueur = nbr_user();      // nombre de joueurs
    int nbr_carte = card_user();      // nombre de cartes par joueur

    // Allocation mémoire pour les joueurs
    Joueur *joueur = malloc(sizeof(Joueur) * nbr_joueur);

    // Création des joueurs avec affichage stylisé
    crea_joueurs(joueur, nbr_joueur);

    // Libération mémoire
    free(joueur);
    return 1;
}