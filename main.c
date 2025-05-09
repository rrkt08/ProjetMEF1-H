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



    int partie_terminee = 0;
    while(!partie_terminee){
        for(int i = 0; i< nbr_j; i++){
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
          
            if (choix1 == 2) {
                int choix_joueur;
                printf("Choisissez un joueur (1-%d) : ", nbr_j);
                while(scanf("%d", &choix_joueur) != 1 || choix_joueur < 1 || choix_joueur > nbr_j){
                    printf("\033[1;31mErreur!\033[0m Joueur invalide.\n");
                    while(getchar() != '\n');
                    printf("Choisissez un joueur (1-%d) : ", nbr_j);
                }
            
                if (joueur[choix_joueur-1].id_defausse < 0) {
                    printf("\033[1;33mLa défausse de ce joueur est vide!\033[0m\n");
                    // Retour au début du tour
                    continue;
                }
            
                // Appel à la fonction modifiée
                echange_defausse(&joueur[i], &joueur[choix_joueur-1], nbr_c);
            }
        
        //Choix 1
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
                    echange_pioche(joueur,i,nbr_c,carte_piochee);
                }
                else if(choix2 == 2){
                    printf("La carte piochée va dans la défausse...\n");
                    ajouter_defausse(&joueur[i],carte_piochee);
                }
            }

            if(verifJoueurAtermine(joueur,nbr_c,i)) {  // À implémenter
                printf("Le Joueur %s a terminé !\n", joueur[i].nom);
                exit(92);
            }
        }
    }


    // Libération mémoire
    free(joueur);
    free(pioche);
    return 1;
}