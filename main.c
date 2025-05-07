#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int main() {
    Menu();

    // Saisie du nombre de joueurs et cartes
    int nbr_j = nbr_user();      // nombre de joueurs
    int nbr_c = card_user();      // nombre de cartes par joueur

    // Allocation mémoire pour les joueurs
    Joueur *joueur = malloc(sizeof(Joueur) * nbr_j);

    // Création des joueurs avec affichage stylisé
    crea_joueurs(joueur, nbr_j);

    Pioche *pioche = malloc(sizeof(Pioche));
    initialiserPioche(pioche);
    melangerPioche(pioche);
    distrib_joueurs(joueur,pioche,nbr_c,nbr_j);
    
    
    int i = 0;
    
    printf("\n=== Tour de %s ===\n\n", joueur[i].nom);
            int defausse_valide = 0;
            afficher_jeu(joueur,nbr_c,nbr_j);
            
            //Le joueur choisit une action
            int choix1;
            printf("1. Piocher | 2. Prendre une défausse : "); // Le joueur a le choix
            while(scanf("%d", &choix1) != 1 || (choix1 != 1 && choix1 != 2)) { //
                printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                while(getchar() != '\n'); 
                printf("1. Piocher | 2. Prendre d'une défausse : ");
            }
          
            if (choix1 == 2){
               // Gestion des défausses
            int choix3;
            do {
                printf("Choisissez un joueur (1-%d) : ", nbr_j);
                while(scanf("%d", &choix3) != 1 || choix3 < 1 || choix3 > nbr_j) {
                    printf("\033[1;31mErreur!\033[0m Joueur invalide.\n");
                    while(getchar() != '\n');
                    printf("Choisissez un joueur (1-%d) : ", nbr_j);
                }
    
                if (joueur[choix3-1].defausse == -5) {
                    printf("\033[1;33mLa défausse de ce joueur est vide!\033[0m\n");
                    printf("1. Choisir un autre joueur | 2. Piocher à la place : ");
                    int choix4;
                    while(scanf("%d", &choix4) != 1 || (choix4 != 1 && choix4 != 2)) {
                        printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                        while(getchar() != '\n');
                        printf("1. Choisir un autre joueur | 2. Piocher à la place : ");
                    }
                    if (choix4 == 2) {
                        choix1 = 1; // On bascule sur pioche
                        break;
                    }
                } else {
                    defausse_valide = 1;
                }
            } while (!defausse_valide);
        }
        
        
            if (choix1 == 1){
                int carte_piochee = piocherCarte(pioche);
                printf("\n");
                printf("Carte piochée : %d\n", carte_piochee);
                
                int choix2;
                printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                while(scanf("%d", &choix2) != 1 || (choix2 != 1 && choix2 != 2)) {
                    printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                    while(getchar() != '\n'); 
                    printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                }
                if(choix2 == 1){
                    echange(joueur,i,nbr_c,carte_piochee);
                }
                else if(choix2 == 2){
                    printf("La carte piochée va dans la défausse...\n");
                    joueur[i].defausse = carte_piochee;
                }
            }
            
            afficher_jeu(joueur,nbr_c,nbr_j);
          
 

    // Libération mémoire
    free(joueur);
    free(pioche);
    return 1;
}