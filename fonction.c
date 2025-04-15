#include "fichier.h"

int card_user(){
    int a;
    printf("Nombre de cartes par joueur ? (entre 3 et 10)\n");
    scanf("%d",&a);
    while((a>10)||(a<3)){
        printf("Erreur !\n");
        printf("Nombre de cartes par joueur ? (ENTRE 3 ET 10)\n");
        scanf("%d",&a);
    }
    system("clear || cls"); // nettoie le terminal
    return a;
}

int nbr_user(){
    int a;
    printf("===Début du jeu===\n\n");
    printf("Nombre de joueurs ? (entre 2 et 4)\n");
    scanf("%d",&a);
    while((a>4)||(a<2)){
        printf("Erreur !\n");
        printf("Nombre de joueurs ? (ENTRE 2 ET 4)\n");
        scanf("%d",&a);
    }
    system("clear || cls"); // nettoie le terminal
    return a;
}

void crea_joueurs(Joueur *j, int n){
    for(int i = 1; i <= n; i++){
        // faire la distribution de carte pour avoir la main de chaque joueur...
        printf("Nom du joueur %d ?\n",i);
        scanf("%s",j->nom);
    }
}

//a completer
void charger() {
    printf("\n=== CHARGEMENT ===\n");
    printf("(Le jeu a chargé...)\n"); 
    while (getchar() != '\n'); // Attendre Entrée
}

void Menu() {
    const char *options[] = {"Jouer", "Charger", "Quitter"}; // 3 choix
    int choix = 0;
    char input; // saisit par l'utilisateur

    while (1) {
        system("clear || cls"); // nettoie le terminal

        printf("=== MENU PRINCIPAL ===\n\n");
        for (int i = 0; i < 3; i++) {
            printf("%s%s%s\n", (i == choix) ? "> " : "  ", options[i], (i == choix) ? " <" : ""); //affichage des choix et des chevrons qui montent ou descendent 
        }
        printf("\nNavigation: [z]Haut [s]Bas [ENTREE]Valider\n"); //guide

        input = getchar(); // saisit "z" ou "s" ou "entree"
        
        switch (input) {
            case 'z': case 'Z': if (choix > 0) choix--; break; //on monte (Jouer 0, Charger 1, Quitter 2), donc on diminue choix
            case 's': case 'S': if (choix < 2) choix++; break; // on descend (Jouer 0, Charger 1, Quitter 2), donc on augmente choix
            case '\n':
                if (choix == 0) return system("clear || cls");  // Quitte le menu pour lancer le jeu, et efface le menu
                if (choix == 1) charger(); // charge une sauvegarde
                if (choix == 2) printf("Bye Bye \\o/\n"); exit(0); //Quitte le jeu
                break;
        }
        while (getchar() != '\n'); //lecture du 1er caractère saisit
    }
}