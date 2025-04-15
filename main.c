#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void main(){
    // début de partie
    Menu();
    int nbr_joueur = nbr_user(); // nombre de joueurs souhaités
    int nbr_carte = card_user(); // nombre de cartes souhaités
    Joueur *joueur = malloc(sizeof(Joueur)*nbr_joueur); // allocation de mémoire nécessaire
    crea_joueurs(joueur,nbr_joueur);
    



    free(joueur);
}