# Wolf3d ToDoList<br/>
-------------------------------------------------------------------------------------<br/>
-->Wolf3d minimal todolist-----------------------------------------------------------<br/>
-------------------------------------------------------------------------------------<br/>

--->le programme quite proprement si un malloc indispensable ne se fait pas <br/>
--->zero leak<br/>
--->free de toutes les alocations lorsque le programme quite<br/>
--->plus aucun crash possible et boucle infinie<br/>
-      -division par zero<br/>
-      -put pixel en dehors de la window<br/>
-      -proteger l'entrer du programme (map invalide..)<br/>
--->fichiers sources a la norme42<br/>
  <br/>
  
  
  
  
  
  
------------------------------------------------------------------------------------<br/>
------------>BONUS<-----------------------------------------------------------------<br/>
------------------------------------------------------------------------------------<br/>
-->introduire le plus de parametre variable, dans une fenetre de parametre?<br/>
.        -->taille des cellules<br/>
.        -->tailles de la map<br/>
.        -->vitesse personnage<br/>
.        -->angle de vue<br/>
        <br/>
-->editeur de map<br/>
.      -->placer des mur ou l'on veux<br/>
      <br/>
-->game play<br/>
.      -->introduire la souris pour l'angle du joueur<br/>
  <br/>
-->graphisme<br/>
.      -->texture au sol et plafond<br/>
<br/>
-----------------------------------------------------------------------------------<br/>
-----------------------------------------------------------------------------------<br/>
<br/>
<br/>
- Recuperation de la map et parsing - DONE
  - Decoupage de la map en case - DONE
  - Sauvegarde du render de la map - DONE

- Positionnement du Personnage - IN PROGRESS
  - Recuperation de la position - DONE
  - Dessin du personnage - DONE
  - Orientation du personnage - DONE
  - Deplacement du personnage - NEXT STEP

- Raycasting 2D
  - Mini-Algo:
    - distance = 0
    - tant que distance < dist_max
      - x = cos(angle_rayon) * distance
      - y = sin(angle_rayon) * distance
      - afficher pixel de coordonnees { x ; y }
      - distance++
  - En 2 etapes:
    - Dessin de la carte autours du perso
    - Puis uniquement ce que le personnage vois

- Affichage basique de la vu a la 1er personne

- Creation d'une structure personnage
  - Position x et y sur la map
  - Image ou renderer de la vu 1er personne

- Editeur de map

- Retirer le relinkage du MAKEFILE sur les libs

