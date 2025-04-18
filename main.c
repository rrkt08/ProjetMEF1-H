#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void main() {
    // Nettoyage + affichage stylisé du lancement
    system("clear || cls");

    // Message d'accueil en violet avec encadrement
    printf("\033[1;35m╔═════════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;35m║         🎴  BIENVENUE DANS CARDYARD         ║\033[0m\n");
    printf("\033[1;35m╚═════════════════════════════════════════════╝\033[0m\n\n");

    printf("\033[1;36mPréparez-vous à la bataille des cartes...\033[0m\n\n");

    // Menu interactif
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
}