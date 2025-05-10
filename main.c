#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int main() {
    Joueur *joueur = NULL;
    Pioche *pioche = NULL;
    int nbr_j = 0;
    int nbr_c = 0;

while(1){

    int menu_result = Menu();  // 1 = jouer, 2 = charger, 3 = quitter (déjà géré)

    if (menu_result == 2) { // option "Charger" dans le menu
        charger_partie(&joueur, &nbr_j, &nbr_c, &pioche);
        if(joueur==NULL){
            continue;
        }
    } else {
        // Création nouvelle partie
        nbr_j = nbr_user();      // nombre de joueurs
        nbr_c = card_user();     // nombre de cartes par joueur
        joueur = malloc(sizeof(Joueur) * nbr_j); // Allocation mémoire pour les joueurs
        crea_joueurs(joueur, nbr_j);

        pioche = malloc(sizeof(Pioche));
        initialiserPioche(pioche);
        melangerPioche(pioche);
        distrib_joueurs(joueur, pioche, nbr_c, nbr_j);
    }
    
    int partie_terminee = 0;
    while(!partie_terminee){
        for(int i = 0; i< nbr_j; i++){
            printf("\n=== Tour de %s ===\n\n", joueur[i].nom);
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
        // Sauvegarde à la fin
        char save;
        printf("\n\033[1;33mSouhaitez-vous sauvegarder la partie ? (o/n) : \033[0m");
        scanf(" %c", &save);
        if (save == 'o' || save == 'O') {
            sauvegarder_partie(joueur, nbr_j, nbr_c, pioche);
        }
    }
}
// calcul_score(...);


    // Libération mémoire
    free(joueur);
    free(pioche);
}
    return 1;
}