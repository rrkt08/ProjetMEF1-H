
![Logo](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4a/CY_Tech.png/640px-CY_Tech.png)



# Project CardYard MEF1-H

Inspiré en partie par le jeu de cartes Skyjo, ce projet est un jeu de cartes codé en langage C. Le jeu permet à plusieurs joueurs de s'affronter en échangeant des cartes et en essayant de révéler toute leur main en premier. Chaque participant possède un ensemble de cartes étalées face cachée devant lui, et tous les joueurs partagent une pioche centrale et des défausses individuelles.  

*Le but : être le joueur avec la plus petite somme de points lorsque toutes les cartes personnelles d’un joueur ont été révélées.*

Le programme inclut des fonctionnalités comme la sauvegarde et le chargement de parties, ainsi qu'une interface en ligne de commande colorée.

## Comment jouer ?


#### Menu principal :

    - Jouer : Commence une nouvelle partie
    - Charger : Reprend une partie sauvegardée
    - Quitter : Quitte le jeu

( appuyer sur 'z' ou 'Z' et 's' ou 'S' puis sur ENTRÉE pour naviguer sur le menu principale et ENTRÉE pour valider votre choix )


#### Pour une nouvelle partie :

    1. Entrez le nombre de joueurs (2-4) 
    2. Entrez le nombre de cartes par joueur (3-10)
    3. Saisissez les noms des joueurs

#### Pendant le jeu :

Les joueurs jouent chacun leur tour et à chaque tour, vous pouvez :

    - Piocher une carte et :  
        -> l'échanger avec une de vos cartes 
        -> la mettre dans votre défausse

    - Prendre une carte de la défausse d'un autre joueur

Le jeu se termine quand un joueur a toutes ses cartes visibles (face retournée).

#### Sauvegarde :

    - À la fin de chaque tour, vous aurez le choix de sauvegarder la partie 
      ou non.

    - Si vous sauvegardez la partie cela vous retournera au menu principal.

    - En choisissant "Charger", vous pourrez reprendre la partie sauvegardée 
      à partir de là où vous en étiez.



