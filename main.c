#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int main() {
    Joueur *joueur = NULL;
    Pioche *pioche = NULL;
    int nbr_j = 0;
    int nbr_c = 0;

    while (1) {
        int menu_result = Menu();  // 1 = jouer, 2 = charger, 3 = quitter

        if (menu_result == 2) {
            if (!sauvegarde_existe()) {
                printf("\033[1;31mAucune sauvegarde valide trouvée. Retour au menu.\033[0m\n");
                printf("Appuyez sur Entrée pour continuer...");
                while(getchar() != '\n'); // Vider le buffer si nécessaire
                getchar(); // Attendre l'entrée de l'utilisateur
                continue;
            }
                    
            charger_partie(&joueur, &nbr_j, &nbr_c, &pioche);
            if (joueur == NULL) {
                continue;
            }
        } else {
            // Nouvelle partie
            nbr_j = nbr_user();
            nbr_c = card_user();
            joueur = malloc(sizeof(Joueur) * nbr_j);
            crea_joueurs(joueur, nbr_j);

            pioche = malloc(sizeof(Pioche));
            initialiserPioche(pioche);
            melangerPioche(pioche);
            distrib_joueurs(joueur, pioche, nbr_c, nbr_j);
        }

        int partie_terminee = 0;
        while (!partie_terminee) {
            for (int i = 0; i < nbr_j; i++) {
                printf("\n=== Tour de %s ===\n\n", joueur[i].nom);
                afficher_jeu(joueur, nbr_c, nbr_j);

                int choix_valide = 0;
                int choix1;

                while (!choix_valide) {
                    printf("1. Piocher | 2. Prendre une défausse : ");
                    if (scanf("%d", &choix1) != 1 || (choix1 != 1 && choix1 != 2)) {
                        printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    if (choix1 == 2) {
                        int choix_joueur;
                        printf("Choisissez un joueur (1-%d) : ", nbr_j);
                        if (scanf("%d", &choix_joueur) != 1 || choix_joueur < 1 || choix_joueur > nbr_j) {
                            printf("\033[1;31mErreur!\033[0m Joueur invalide.\n");
                            while (getchar() != '\n');
                            continue;
                        }

                        if (choix_joueur - 1 == i) {
                            printf("\033[1;31mErreur: Vous ne pouvez pas prendre dans votre propre défausse!\033[0m\n");
                            continue;
                        }

                        if (joueur[choix_joueur - 1].id_defausse < 0) {
                            printf("\033[1;33mLa défausse de ce joueur est vide!\033[0m\n");
                            continue;
                        }

                        echange_defausse(&joueur[i], &joueur[choix_joueur - 1], nbr_c);
                        choix_valide = 1;

                    } else if (choix1 == 1) {
                        int carte_piochee = piocherCarte(pioche);
                        printf("\nCarte piochée : %d\n", carte_piochee);

                        int choix2;
                        printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                        while (scanf("%d", &choix2) != 1 || (choix2 != 1 && choix2 != 2)) {
                            printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                            while (getchar() != '\n');
                            printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                        }

                        if (choix2 == 1) {
                            echange_pioche(joueur, i, nbr_c, carte_piochee);
                        } else {
                            printf("La carte piochée va dans la défausse...\n");
                            ajouter_defausse(&joueur[i], carte_piochee);
                        }

                        choix_valide = 1;
                    }
                }

                if (verifJoueurAtermine(joueur, nbr_c, i)) {
                    printf("Le Joueur %s a terminé !\n", joueur[i].nom);
                    exit(92);
                }

                // Sauvegarde
                char save;
                printf("\n\033[1;33mSouhaitez-vous sauvegarder la partie ? (o/n) : \033[0m");
                scanf(" %c", &save);
                if (save == 'o' || save == 'O') {
                    sauvegarder_partie(joueur, nbr_j, nbr_c, pioche);
                }
            }
        }

        free(joueur);
        free(pioche);
    }

    return 1;
}
