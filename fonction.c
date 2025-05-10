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
    if(j==NULL){
        printf("Erreur mémoire");
        exit(37);
    }
    system("clear || cls"); // nettoie le terminal

    printf("\033[1;36m╔══════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U0001F3AE  CRÉATION DES JOUEURS        ║\033[0m\n");
    printf("\033[1;36m╚══════════════════════════════════╝\033[0m\n\n");

    for (int i = 0; i < n; i++) {
        printf("\033[1;33m\U0001F9D1  Nom du joueur %d : \033[0m", i + 1);
        scanf("%s", j[i].nom);
        printf("\033[1;32m\U00002705  Bienvenue, %s !\n\n\033[0m", j[i].nom);

        j[i].id_defausse = -1; // Pour plus tard, on choisit une valeur et il y'aura une condition pour que sa affiche que la défausse est vide
    }

    printf("\033[1;36m╔═══════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║  \U00002705  TOUS LES JOUEURS SONT PRÊTS !        ║\033[0m\n");
    printf("\033[1;36m╚═══════════════════════════════════════════╝\033[0m\n");

    printf("\n\033[1;34mAppuyez sur [Entrée] pour continuer...\033[0m");
    while (getchar() != '\n');
    getchar();
}

int Menu() {
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
                if (choix == 0){
                    system("clear || cls"); //Quitte le menu pour lancer le jeu
                    return 1;
                } 
                if (choix == 1) return 2; //charge une partie sauvegardée
                if (choix == 2) {
                    printf("\033[1;31mBye Bye 👋\n\033[0m");
                    exit(40); //Quitte le jeu
                }
                break;
        }
        while (getchar() != '\n'); //lecture du 1er caractère seulement, tous les autres ne sont pas pris en compte ("jiazoiahfohza", lecture: j)
    }
}

void sauvegarder_partie(Joueur *j, int nbr_joueur, int nbr_carte, Pioche *p) {
    FILE *f = fopen("sauvegarde.txt", "w");
    if (!f) {
        printf("\033[1;31mErreur ouverture du fichier de sauvegarde !\033[0m\n");
        return;
    }

    fprintf(f, "%d %d\n", nbr_joueur, nbr_carte);

    for (int i = 0; i < nbr_joueur; i++) {
        fprintf(f, "%s %d\n", j[i].nom, j[i].id_defausse);
        for (int c = 0; c < nbr_carte; c++) {
            fprintf(f, "%d %d\n", j[i].cartes[c].valeur, j[i].cartes[c].visible);
        }
        for (int d = 0; d <= j[i].id_defausse; d++) {
            fprintf(f, "%d\n", j[i].defausse[d]);
        }
    }

    fprintf(f, "%d\n", p->nbr_cartes);
    for (int i = 0; i < p->nbr_cartes; i++) {
        fprintf(f, "%d\n", p->cartes[i].valeur);
    }

    fclose(f);
    printf("\033[1;32mSauvegarde effectuée avec succès !\033[0m\n");
    exit(39);
}

void charger_partie(Joueur **j, int *nbr_joueur, int *nbr_carte, Pioche **p) {
    FILE *f = fopen("sauvegarde.txt", "r");
    if (!f) {
        printf("\033[1;31mAucune sauvegarde trouvée !\033[0m\n");
        printf("\033[1;34mAppuyez sur Entrée pour revenir au menu...\033[0m");
        while (getchar() != '\n'); // Vide le buffer
        getchar(); // Attend l'appui sur Entrée
        system("clear || cls");
    }

    fscanf(f, "%d %d\n", nbr_joueur, nbr_carte);

    *j = malloc(sizeof(Joueur) * (*nbr_joueur));
    *p = malloc(sizeof(Pioche));

    for (int i = 0; i < *nbr_joueur; i++) {
        fscanf(f, "%s %d\n", (*j)[i].nom, &(*j)[i].id_defausse);
        for (int c = 0; c < *nbr_carte; c++) {
            fscanf(f, "%d %d\n", &(*j)[i].cartes[c].valeur, &(*j)[i].cartes[c].visible);
        }
        for (int d = 0; d <= (*j)[i].id_defausse; d++) {
            fscanf(f, "%d\n", &(*j)[i].defausse[d]);
        }
    }

    fscanf(f, "%d\n", &(*p)->nbr_cartes);
    for (int i = 0; i < (*p)->nbr_cartes; i++) {
        fscanf(f, "%d\n", &(*p)->cartes[i].valeur);
        (*p)->cartes[i].visible = 0;
    }

    fclose(f);
    printf("\033[1;34mPartie restaurée depuis la sauvegarde !\033[0m\n");
}

void initialiserPioche(Pioche *pioche){
    if(pioche==NULL){
        printf("Erreur mémoire");
        exit(38);
    }
    FILE *fichier = fopen("Value_file.txt", "r"); // ouverture du fichier en mode lecture
    if(fichier == NULL){
        printf("Ouverture du fichier impossible\n"); // erreur fichier introuvable
        exit(1);
    }

    pioche->nbr_cartes = 0; 
    int val, qte;

    while(fscanf(fichier, "%d %d", &val, &qte) == 2){ //on récupére la valeur ainsi que son nombre d'exemplaires
        for(int i = 0; i < qte; i++){
            if(pioche->nbr_cartes >= MAX_CARTES){ // On donne auparavant le nombre de cartes qu'il y'a au total, pour éviter d'en avoir + que prévu
                printf("Attention : Dépassement de capacité de la pioche !\n");
                break;
            }
            pioche->cartes[pioche->nbr_cartes].valeur = val; // tableau de cartes, à l'indice nbr_cartes on a la valeur
            pioche->nbr_cartes++; 
        }
    }
    fclose(fichier); 
}

void melangerPioche(Pioche *pioche){
    if(pioche==NULL){
        printf("Erreur mémoire");
        exit(50);
    }
    srand(time(NULL)); //pour pouvoir utiliser rand()
    //on commence à l'indice n-1, car parcours dans un tableau
    for(int i = pioche->nbr_cartes - 1; i > 0; i--){
        int j = rand() % (i + 1); //on prend une valeur j comprise entre 0 et i (aléatoire)
        Carte temp = pioche->cartes[i]; //variable temporaire qui stocke la valeur de la carte à l'indice i
        pioche->cartes[i] = pioche->cartes[j]; //échange des valeurs
        pioche->cartes[j] = temp; //cartes[j] prend la valeur de cartes[i] à l'aide de la variable temporaire
    }
}

// Pioche une carte 
int piocherCarte(Pioche *pioche){
    if(pioche==NULL){
        printf("Erreur mémoire");
        exit(51);
    }
    if(pioche->nbr_cartes <= 0){
        printf("Pioche épuisée !\n");
        exit(2);  //Pour l'instant, il faudra rediriger vers une défausse
    }
    pioche->nbr_cartes--;
    return pioche->cartes[pioche->nbr_cartes].valeur; // carte piocher
}

void distrib_joueurs(Joueur *j, Pioche *p, int nbr_carte, int nbr_joueur){
    if((j==NULL)||(p==NULL)){
        printf("Erreur mémoire");
        exit(52);
    }
    for (int c = 0; c < nbr_carte; c++) {
        for (int i = 0; i < nbr_joueur; i++){
            j[i].cartes[c].valeur = piocherCarte(p);
            j[i].cartes[c].visible = 0;
        }    
    }

    // Message de confirmation
    printf("\033[1;32m\u2705 Cartes distribuées avec succès à tous les joueurs.\033[0m\n");
    printf("\033[1;34mAppuyez sur Entrée pour continuer...\033[0m");
    getchar();

    system("clear || cls");
    printf("\033[1;35m╔════════════════════════════════╗\033[0m\n");
    printf("\033[1;35m║  \U0001F6A8  LE JEU PEUT COMMENCER !        ║\033[0m\n");
    printf("\033[1;35m╚════════════════════════════════╝\033[0m\n");
    printf("\n\033[1;34mAppuyez sur Entrée pour afficher le plateau...\033[0m");
    getchar();
}

void ajouter_defausse(Joueur *j, int valeur) {
    if (j->id_defausse < MAX_CARTES - 1) {
        j->id_defausse++;
        j->defausse[j->id_defausse] = valeur; // Ajoute à la fin
    } else {
        printf("Défausse pleine !\n");
    }
}

int prendre_defausse(Joueur *j){
    if(j==NULL){
        printf("Erreur mémoire");
        exit(29);
    }
    if(j->id_defausse >= 0){
        int carte = j->defausse[j->id_defausse];
        j->defausse[j->id_defausse] = -5;  // Marquer la position comme vide
        j->id_defausse--;
        return carte; //retourne la carte prise de la défausse
    }
    return -5;  // Retourne -5 si défausse vide
}

void echange_defausse(Joueur *j1, Joueur *j2, int nbr_carte) {
    
    // 1. Afficher la carte disponible dans la défausse
    int carte_defausse = j2->defausse[j2->id_defausse];
    printf("Carte disponible dans la défausse : %d\n", carte_defausse);

    // 2. Demander quelle carte échanger
    printf("%s, choisissez la carte à échanger (1-%d) : ", j1->nom, nbr_carte);
    int choix;
    while(scanf("%d", &choix) != 1 || choix < 1 || choix > nbr_carte) {
        printf("\033[1;31mErreur!\033[0m Choisissez entre 1 et %d.\n", nbr_carte);
        while(getchar() != '\n');
        printf("Choisissez la carte à échanger (1-%d) : ", nbr_carte);
    }

    // 3. Effectuer l'échange
    int ancienne_carte = j1->cartes[choix-1].valeur;
    j1->cartes[choix-1].valeur = carte_defausse;
    j1->cartes[choix-1].visible = 1;

    // 4. Mettre l'ancienne carte dans la défausse du joueur actuel
    ajouter_defausse(j1, ancienne_carte);

    // 5. Retirer la carte de la défausse adverse
    prendre_defausse(j2);

    printf("Échange effectué !\n");
}

//Affichage du tour avec les différentes informations sur les cartes et la défausse de chaque joueur
void afficher_jeu(Joueur *j, int nbr_carte, int nbr_joueur){
    if(j==NULL){
        printf("Erreur mémoire");
        exit(53);
    }
    for(int i = 0; i < nbr_joueur; i++){
        printf("Joueur %s:\n", j[i].nom);
        for(int c = 0; c< nbr_carte; c++){
            if(!j[i].cartes[c].visible){ // Condition pour que les valeurs des cartes ne soient pas affichés (visible = 0)
                printf("%d:(face cachée)\n",c+1);
            }
            else{
                printf("%d:    %d\n",c+1,j[i].cartes[c].valeur); // Si visible = 1
            }

        }
        if(j[i].id_defausse == -1){ // Condition choisit volontairement pour qu'au 1er tour la défausse soit vide et pas égale à 0
            printf("défausse : (vide)\n");
        }
        else{
            printf("défausse : %d\n", j[i].defausse[j[i].id_defausse]);
        }
        printf("\n\n\n");
    }
}

void echange_pioche(Joueur *j, int i_joueur, int nbr_carte, int carte_choisit){
    if(j==NULL){
        printf("Erreur mémoire");
        exit(54);
    }
    printf("Indiquer le numéro de la carte à échanger: ");
    int x;
    
    while(scanf("%d", &x) != 1 || x < 1 || x > nbr_carte) {
        printf("\033[1;31mErreur!\033[0m Choisissez entre 1 et %d.\n", nbr_carte);
        while(getchar() != '\n'); 
        printf("Choisissez une carte (1-%d) : ", nbr_carte);
    }

    int temp = j[i_joueur].cartes[x-1].valeur;
    j[i_joueur].cartes[x-1].valeur = carte_choisit;
    j[i_joueur].cartes[x-1].visible = 1;
    ajouter_defausse(&j[i_joueur], temp); // Ajoute à la défausse du joueur
    
    printf("Carte échangée, l'ancienne carte va dans la défausse...\n\n");
}
    
int verifJoueurAtermine(Joueur *j, int nbr_carte, int i_joueur){
    if(j==NULL){
        printf("Erreur mémoire\n");
        exit(70);
    }
    for(int i = 0; i< nbr_carte; i++){
        if(!j[i_joueur].cartes[i].visible){
            return 0;
        } 
    }
    return 1;
}