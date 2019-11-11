# Filler

#### Résumé du projet: 
> Créez votre programme joueur pour affronter d’autres étudiants sur le célèbre
> (ou pas) plateau du Filler. Le principe est simple : deux joueurs s’affrontent sur un
> plateau, et doivent placer, tour à tour, la pièce que le maître du jeu (fourni sous la
> forme d’un exécutable Ruby) leur donne, gagnant ainsi des points. La partie s’arrête dès
> qu’une pièce ne peut plus être placée.

Mon algorithme est basé sur 3 stratégies qui dépendent de la position absolue de l'adversaire,
de son occupation du plateau ainsi que de sa position relative par rapport à mon joueur.

#### Les différentes stratégies sont:
* Angle: Joue au plus près d'un des 3 angles désigné qui varie à chaque tour et en fonction de la proximité de mon joueur
et de celle de l'adversaire à celui-ci
* Attack: Joue au plus près de la position adverse la plus proche.
* Glue: Joue au plus près de la dernière position occupé par l'adversaire.

Mon joueur tente en permanence de maximiser l'espace occupé en évitant de jouer dans des zones suffisamment saturée par lui-même
(à hauteur de 70%).

## Usage:

make && ./ressources/filler_vm -p1 [player1] -p2 [player2] -f [map]

#### Un visualisateur en séquence d'échapement est également disponible. Pour l'utiliser:
make && make -C ./visu && ./ressources/filler_vm -p1 [player1] -p2 [player2] -f [map] | ./visu/visu [delay]
