# Wolf3d ToDoList
-------------------------------------------------------------------------------------
-->Wolf3d minimal todolist-----------------------------------------------------------
-------------------------------------------------------------------------------------
  -->makefile sans relinkage qui compile le code source et les diferentes librairies
  -->gestion d'erreur
      -->le programme quite proprement si un malloc indispensable ne se fait pas (exemple fenetre principale)
  -->zero leak
      -->free de toutes les alocations lorsque le programme quite
  -->programme qui quite proprement sur croix rouge fenetre et touche echape
  -->map3d
      -->affichage des texture en fonction de l'orientation sans aucun defaut d'affichage
      -->mapper les touches comme demander dans le sujet
  -->map2d
      -->c'est pas obligatoire mais une bonne map 2d donne une bonne map 3d non?
  -->plus aucun crash possible et boucle infinie
      -->division par zero
      -->put pixel en dehors de la window
      -->proteger l'entrer du programme (map invalide..)
      -->...
  -->fichiers sources a la norme42
  
------------------------------------------------------------------------------------
------------>BONUS<-----------------------------------------------------------------
------------------------------------------------------------------------------------
-->introduire le plus de parametre variable, dans une fenetre de parametre?
        -->taille des cellules
        -->tailles de la map
        -->vitesse personnage
        -->angle de vue
        
-->editeur de map
      -->placer des mur ou l'on veux
      
-->game play
      -->introduire la souris pour l'angle du joueur
  
-->graphisme
      -->texture au sol et plafond

-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------


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

