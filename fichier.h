#include <stdio.h> 
#include <stdlib.h>
#define MAX_CARTES 150

typedef struct{
    int valeur; // dans le fichier les valeurs
    int visible; // vrai 1 affiché, faux 0 caché
}Carte;

typedef struct{
    Carte cartes[MAX_CARTES];//tableau de cartes
    int defausse[MAX_CARTES];
    int id_defausse;// vaut 0 au début (vide)
    char nom[30];
}Joueur;

typedef struct{
    Carte cartes[MAX_CARTES];
    int nbr_cartes; // Pour savoir si c'est fini ou pas car on prend des cartes a chaque tour
}Pioche;

int card_user();
int nbr_user();
void crea_joueurs(Joueur *j, int n);
int afficher_menu();
void initialiserPioche(Pioche *pioche);
void melangerPioche(Pioche *pioche);
int piocherCarte(Pioche *pioche);
void distrib_joueurs(Joueur *j, Pioche *p, int nbr_cartes, int nbr_joueur);
void afficher_jeu(Joueur *j, int nbr_carte, int nbr_joueur);
void echange_pioche(Joueur *j, int i_joueur, int nbr_carte, int carte_choisit);
void echange_defausse(Joueur *j1, Joueur *j2, int nbr_carte);
int prendre_defausse(Joueur *j);
void ajouter_defausse(Joueur *j, int valeur); 
int verifJoueurAtermine(Joueur *j, int nbr_carte, int i_joueur);
void sauvegarder_partie(Joueur *j, int nbr_joueur, int nbr_carte, Pioche *p, int i_joueur);
void charger_partie(Joueur **j, int *nbr_joueur, int *nbr_carte, Pioche **p, int *i_joueur);
int sauvegarde_existe(); 
void afficher_carte_horizontal(Joueur *j, int nbr_c);
void afficher_scores_finaux(Joueur *joueurs, int nbr_joueurs, int nbr_cartes);