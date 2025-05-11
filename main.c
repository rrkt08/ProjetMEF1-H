#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int main() {
    Joueur *joueur = NULL;
    Pioche *pioche = NULL;
    int nbr_j = 0;
    int nbr_c = 0;
    int i = 0;

    while (1) {
        int menu_result = afficher_menu();  // 1 = jouer, 2 = charger, 3 = quitter

        if (menu_result == 2) {
            if (!sauvegarde_existe()) {
                printf("\033[1;31mAucune sauvegarde trouvée...\033[0m\n");
                printf("Appuyez sur [Entrée] pour retourner au menu...");
                while(getchar() != '\n');
                getchar(); // Attendre l'entrée de l'utilisateur
                continue;
            }
                    
            charger_partie(&joueur, &nbr_j, &nbr_c, &pioche, &i); // on charge une partie
            if (joueur == NULL) {
                continue;
            }
        } else {
            // On créer une nouvelle partie
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
                system("clear || cls");
                afficher_jeu(joueur, nbr_c, nbr_j);

                int choix_valide = 0;
                int choix1;

                printf("\033[1;35mAu tour de %s : \033[0m",joueur[i].nom);
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
                            printf("\033[1;31mErreur! Vous ne pouvez pas prendre dans votre propre défausse!\033[0m\n");
                            continue;
                        }

                        if (joueur[choix_joueur - 1].id_defausse < 0) {
                            printf("\033[1;33mLa défausse de ce joueur est vide!\033[0m\n");
                            continue;
                        }

                        echange_defausse(&joueur[i], &joueur[choix_joueur - 1], nbr_c);
                        choix_valide = 1;

                    } else if (choix1 == 1) {
                        int carte_piochee;
                        if(pioche->nbr_cartes > 0){
                            carte_piochee = piocherCarte(pioche);
                            printf("\nCarte piochée : \033[1;33m%d\033[00m\n", carte_piochee);
                        } 
                        else{
                            printf("\033[1;33mLa pioche est vide ! Vous devez prendre une carte dans une défausse.\033[0m\n");
                            continue;  // Retourne au début du tour pour forcer le choix 2
                        }

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
                    system("clear || cls");
                    afficher_jeu(joueur, nbr_c, nbr_j);
                    printf("\033[1;32mLe Joueur %s a terminé ! Dernier tour pour les autres joueurs...\n\033[0m", joueur[i].nom);
                    
                    int dt_en_cours = 1;
                    int dt_joueur_termine = i;
                    
                    while (dt_en_cours) {
                        i = (i + 1) % nbr_j;
                        
                        if (i == dt_joueur_termine) {
                            dt_en_cours = 0;
                            break;
                        }
                        
                        system("clear || cls");
                        afficher_jeu(joueur, nbr_c, nbr_j);
                        
                        printf("\033[1;35mDernier tour pour %s : \033[0m", joueur[i].nom);
                        
                        int dt_choix_valide = 0;
                        int dt_action;
                        
                        while (!dt_choix_valide) {
                            printf("1. Piocher | 2. Prendre une défausse : ");
                            if (scanf("%d", &dt_action) != 1 || (dt_action != 1 && dt_action != 2)) {
                                printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                                while (getchar() != '\n');
                                continue;
                            }

                            if (dt_action == 2) {
                                int dt_joueur_cible;
                                printf("Choisissez un joueur (1-%d) : ", nbr_j);
                                if (scanf("%d", &dt_joueur_cible) != 1 || dt_joueur_cible < 1 || dt_joueur_cible > nbr_j) {
                                    printf("\033[1;31mErreur!\033[0m Joueur invalide.\n");
                                    while (getchar() != '\n');
                                    continue;
                                }

                                if (dt_joueur_cible - 1 == i) {
                                    printf("\033[1;31mErreur! Vous ne pouvez pas prendre dans votre propre défausse!\033[0m\n");
                                    continue;
                                }

                                if (joueur[dt_joueur_cible - 1].id_defausse < 0) {
                                    printf("\033[1;33mLa défausse de ce joueur est vide!\033[0m\n");
                                    continue;
                                }

                                echange_defausse(&joueur[i], &joueur[dt_joueur_cible - 1], nbr_c);
                                dt_choix_valide = 1;

                            } else if (dt_action == 1) {
                                int dt_carte_piochee;
                                if(pioche->nbr_cartes > 0){
                                    dt_carte_piochee = piocherCarte(pioche);
                                    printf("\nCarte piochée : \033[1;33m%d\033[00m\n", dt_carte_piochee);
                                } 
                                else{
                                    printf("\033[1;33mLa pioche est vide ! Vous devez prendre une carte dans une défausse.\033[0m\n");
                                    continue;
                                }

                                int dt_decision;
                                printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                                while (scanf("%d", &dt_decision) != 1 || (dt_decision != 1 && dt_decision != 2)) {
                                    printf("\033[1;31mErreur!\033[0m Choisissez 1 ou 2.\n");
                                    while (getchar() != '\n');
                                    printf("1. Echanger avec une carte | 2. Mettre dans la défausse : ");
                                }

                                if (dt_decision == 1) {
                                    echange_pioche(joueur, i, nbr_c, dt_carte_piochee);
                                } else {
                                    printf("La carte piochée va dans la défausse...\n");
                                    ajouter_defausse(&joueur[i], dt_carte_piochee);
                                }

                                dt_choix_valide = 1;
                            }
                        }
                    }
                    
                    
                    system("clear || cls");
                    afficher_jeu(joueur, nbr_c, nbr_j);
                    afficher_scores_finaux(joueur, nbr_j, nbr_c);
                    printf("\nAppuyez sur [Entrée] pour retourner au menu...");
                    while(getchar() != '\n');
                    getchar();
                    partie_terminee = 1;
                    break;
                }

                i = (i + 1) % nbr_j;

                char save;
                printf("\n\033[1;33mSouhaitez-vous sauvegarder la partie ? (o/n) : \033[0m");
                scanf(" %c", &save);
                if (save == 'o' || save == 'O') {
                    sauvegarder_partie(joueur, nbr_j, nbr_c, pioche, i);
                }
        }
        free(joueur);
        free(pioche);
    }

    return 1;
}
