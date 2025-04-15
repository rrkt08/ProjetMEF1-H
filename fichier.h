#include <stdio.h> 
#define MAX_CARTES 150

typedef struct{
    int valeur; // dans le fichier les valeurs
    int visible; // vrai 1 affiché, faux 0 caché
}Carte;

typedef struct{
    Carte cartes[MAX_CARTES];//tableau de cartes
    int defausse;// vaut 0 au début (vide)
    char nom[30];
}Joueur;

typedef struct{
    Carte cartes[MAX_CARTES];
    int nbr_cartes; // Pour savoir si c'est fini ou pas car on prend des cartes a chaque tour
}Pioche;

int card_user(){
    int a;
    printf("Nombre de cartes par joueur ? (entre 3 et 10)\n");
    scanf("%d",&a);
    while((a>10)||(a<3)){
        printf("Erreur !\n");
        printf("Nombre de cartes par joueur ? (ENTRE 3 ET 10)\n");
        scanf("%d",&a);
    }
    return a;
}

int nbr_user(){
    int a;
    printf("Nombre de joueurs ? (entre 2 et 4)\n");
    scanf("%d",&a);
    while((a>4)||(a<2)){
        printf("Erreur !\n");
        printf("Nombre de joueurs ? (ENTRE 2 ET 4)\n");
        scanf("%d",&a);
    }
    return a;
}

void crea_joueurs(Joueur *j, int n){
    for(int i = 1; i <= n; i++){
        // faire la distribution de carte pour avoir la main de chaque joueur...
        printf("Nom du joueur %d ?\n",i);
        scanf("%s",j->nom);
    }
}

/*
void distribution_carte(){
}
void creation_pioche_centrale(){
}
*/

