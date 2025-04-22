#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fichier.h"

int card_user(){
    int a;
    printf("\033[1;36m╔════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U0001F0CF  CHOIX DU NOMBRE DE CARTES                 ║\033[0m\n");
    printf("\033[1;36m╚════════════════════════════════════════════════╝\033[0m\n\n");

    printf("\u27A1 Combien de cartes ? (entre \033[1;33m3\033[0m et \033[1;33m10\033[0m)\n> ");
    while((scanf("%d", &a) != 1 || a < 3 || a > 10)) {
        printf("\033[1;31mErreur!\033[0m Entre 3 et 10.\n");
        while(getchar() != '\n');
    }

    system("clear || cls"); // nettoie le terminal
    return a;   
}

int nbr_user(){
    int a;
    printf("\033[1;36m╔═════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U0001F46B  NOMBRE DE JOUEURS À DÉFINIR        ║\033[0m\n");
    printf("\033[1;36m╚═════════════════════════════════════════╝\033[0m\n\n");

    printf("\u27A1  Combien de joueurs ? (entre \033[1;33m2\033[0m et \033[1;33m4\033[0m)\n> ");
    while((scanf("%d", &a) != 1 || a < 2 || a > 4)) {
        printf("\033[1;31mErreur !\033[0m Nombre de joueurs entre 2 et 4\n> ");
        while(getchar() != '\n');
    }

    system("clear || cls"); // nettoie le terminal
    return a;
}

void crea_joueurs(Joueur *j, int n){
    system("clear || cls"); // nettoie le terminal

    printf("\033[1;36m╔══════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U0001F3AE  CRÉATION DES JOUEURS        ║\033[0m\n");
    printf("\033[1;36m╚══════════════════════════════════╝\033[0m\n\n");

    for (int i = 0; i < n; i++) {
        printf("\033[1;33m\U0001F9D1  Nom du joueur %d : \033[0m", i + 1);
        scanf("%s", j[i].nom);
        printf("\033[1;32m\U00002705  Bienvenue, %s !\n\n\033[0m", j[i].nom);
    }

    printf("\033[1;36m╔═══════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U00002705  TOUS LES JOUEURS SONT PRÊTS !        ║\033[0m\n");
    printf("\033[1;36m╚═══════════════════════════════════════════╝\033[0m\n");

    printf("\n\033[1;34mAppuyez sur [Entrée] pour continuer...\033[0m");
    while (getchar() != '\n');
    getchar();
}

void charger() {
    system("clear || cls"); // nettoie le terminal
    printf("\033[1;34m╔═════════════════════════════════════╗\033[0m\n");
    printf("\033[1;34m║  \U0001F4C2  CHARGEMENT D'UNE PARTIE        ║\033[0m\n");
    printf("\033[1;34m╚═════════════════════════════════════╝\033[0m\n\n");

    printf("\033[1;33mLe jeu est chargé ! (placeholder)\033[0m\n");
    printf("\033[1;34mAppuyez sur Entrée pour revenir...\033[0m");
    while (getchar() != '\n'); // Attendre Entrée
    getchar();
}

void Menu() {
    const char *options[] = {"Jouer", "Charger", "Quitter"};
    int choix = 0;
    char input; // saisit de l'utilisateur

    while (1) {
        system("clear || cls"); // nettoie le terminal
        

        printf("\033[1;35m╔════════════════════════════╗\033[0m\n");
        printf("\033[1;35m║  \U0001F3AE  MENU PRINCIPAL        ║\033[0m\n");
        printf("\033[1;35m╚════════════════════════════╝\033[0m\n\n");

        for (int i = 0; i < 3; i++) {
            if (i == choix)
                printf("\033[1;32m> %s <\033[0m\n", options[i]); //affichage des choix et des chevrons qui montent ou descendent 
            else
                printf("  %s\n", options[i]);
        }

        printf("\n\033[1;36mNavigation:\033[0m [z]Haut [s]Bas\n[ENTREE]Valider\n"); //guide

        input = getchar(); // saisit "z" ou "s" ou "entree"

        switch (input) {
            case 'z': case 'Z': if (choix > 0) choix--; break; //on monte (Jouer 0, Charger 1, Quitter 2), donc on diminue choix
            case 's': case 'S': if (choix < 2) choix++; break; //on descend (Jouer 0, Charger 1, Quitter 2), donc on augmente choix
            case '\n':
                if (choix == 0) return system("clear || cls"); //Quitte le menu pour lancer le jeu
                if (choix == 1) charger(); //charge une partie sauvegardée
                if (choix == 2) {
                    printf("\033[1;31mBye Bye 👋\n\033[0m");
                    exit(0); //Quitte le jeu
                }
                break;
        }
        while (getchar() != '\n'); //lecture du 1er caractère seulement, tous les autres ne sont pas pris en compte ("jiazoiahfohza", lecture: j)
    }
}

void initialiserPioche(Pioche *pioche){
    FILE *fichier = fopen("Value_file.txt", "r"); // ouverture du fichier en mode lecture
    if(fichier == NULL){
        printf("Ouverture du fichier impossible\n"); // erreur fichier introuvable
        exit(1);
    }

    pioche->nbr_cartes = 0; 
    int val, qte;

    while(fscanf(fichier, "%d %d", &val, &qte) == 2){ //on récupére la valeur ainsi que son nombre d'exemplaires
        for(int i = 0; i < qte; i++){
            if(pioche->nbr_cartes >= MAX_CARTES){ 
                printf("Attention : Dépassement de capacité de la pioche !\n");
                break;
            }
            pioche->cartes[pioche->nbr_cartes].valeur = val; // tableau de cartes, à l'indice nbr_cartes on a la valeur
            pioche->nbr_cartes++; 
        }
    }
    fclose(fichier); //fermeture du fichier
}

void melangerPioche(Pioche *pioche){
    srand(time(NULL)); //pour pouvoir utiliser rand()
    int i = pioche->nbr_cartes - 1; //on commence à l'indice n-1, car parcours dans un tableau
    for(i; i > 0; i--){
        int j = rand() % (i + 1); //on prend une valeur j comprise entre 0 et i (aléatoire)
        Carte temp = pioche->cartes[i]; //variable temporaire qui stocke la valeur de la carte à l'indice i
        pioche->cartes[i] = pioche->cartes[j]; //échange des valeurs
        pioche->cartes[j] = temp; //cartes[j] prend la valeur de cartes[i] à l'aide de la variable temporaire
    }
}

// Pioche une carte (retourne -1 si la pioche est vide)
int piocherCarte(Pioche *pioche){
    if(pioche->nbr_cartes <= 0){
        printf("Pioche épuisée !\n");
        exit(1);  //Pour l'instant, il faudra rediriger vers une défausse
    }
    pioche->nbr_cartes--;
    return pioche->cartes[pioche->nbr_cartes].valeur; // carte piocher
}