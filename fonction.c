#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

int card_user() {
    int a;
    printf("\033[1;36m╔═══════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m  🃏  Choix du nombre de cartes/joueur   \033[0m\n");
    printf("\033[1;36m╚═══════════════════════════════════════╝\033[0m\n\n");

    printf("➡️  Combien de cartes ? (entre \033[1;33m3\033[0m et \033[1;33m10\033[0m)\n> ");
    scanf("%d", &a);
    while((scanf("%d", &a) != 1 || a < 3 || a > 10)) {
        printf("\033[1;31mErreur!\033[0m Entre 3 et 10.\n");
        while(getchar() != '\n');
    }

    system("clear || cls");
    return a;   
}

int nbr_user() {
    int a;
    printf("\033[1;36m╔═══════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m  👥  Nombre de joueurs à définir   \033[0m\n");
    printf("\033[1;36m╚═══════════════════════════════════╝\033[0m\n\n");

    printf("➡️  Combien de joueurs ? (entre \033[1;33m2\033[0m et \033[1;33m4\033[0m)\n> ");
    while((scanf("%d", &a) != 1 || a < 2 || a > 4)) {
        printf("\033[1;31mErreur !\033[0m Nombre de joueurs entre 2 et 4\n> ");
        while(getchar() != '\n');
    }

    system("clear || cls");
    return a;
}

void crea_joueurs(Joueur *j, int n) {
    system("clear || cls");

    printf("\033[1;36m╔══════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m      🎮  CRÉATION DES JOUEURS          \033[0m\n");
    printf("\033[1;36m╚══════════════════════════════════════╝\033[0m\n\n");

    for (int i = 0; i < n; i++) {
        printf("\033[1;33m🧑  Nom du joueur %d : \033[0m", i + 1);
        scanf("%s", j[i].nom);
        printf("\033[1;32m✔️  Bienvenue, %s !\n\n\033[0m", j[i].nom);
    }

    printf("\033[1;36m╔══════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m     ✅ Tous les joueurs sont prêts !  \033[0m\n");
    printf("\033[1;36m╚══════════════════════════════════════╝\033[0m\n");

    printf("\n\033[1;34mAppuyez sur [Entrée] pour continuer...\033[0m");
    while (getchar() != '\n'); // nettoie le buffer
    getchar(); // attend Entrée
}

void charger() {
    system("clear || cls");
    printf("\033[1;34m╔══════════════════════════════╗\033[0m\n");
    printf("\033[1;34m  📂  Chargement d'une partie  \033[0m\n");
    printf("\033[1;34m╚══════════════════════════════╝\033[0m\n\n");

    printf("\033[1;33mLe jeu est chargé ! (placeholder)\033[0m\n");
    printf("\033[1;34mAppuyez sur Entrée pour revenir...\033[0m");
    while (getchar() != '\n'); // vider le buffer
    getchar();
}

void Menu() {
    const char *options[] = {"Jouer", "Charger", "Quitter"};
    int choix = 0;
    char input;

    while (1) {
        system("clear || cls");
        

        printf("\033[1;35m╔════════════════════════════╗\033[0m\n");
        printf("\033[1;35m       🎮 MENU PRINCIPAL     \033[0m\n");
        printf("\033[1;35m╚════════════════════════════╝\033[0m\n\n");

        for (int i = 0; i < 3; i++) {
            if (i == choix)
                printf("\033[1;32m> %s <\033[0m\n", options[i]);
            else
                printf("  %s\n", options[i]);
        }

        printf("\n\033[1;36mNavigation:\033[0m [z]Haut [s]Bas [ENTREE]Valider\n");

        input = getchar();

        switch (input) {
            case 'z': case 'Z': if (choix > 0) choix--; break;
            case 's': case 'S': if (choix < 2) choix++; break;
            case '\n':
                if (choix == 0) return system("clear || cls");
                if (choix == 1) charger();
                if (choix == 2) {
                    printf("\033[1;31mBye Bye 👋\n\033[0m");
                    exit(0);
                }
                break;
        }
        while (getchar() != '\n'); // nettoyage du buffer
    }
}