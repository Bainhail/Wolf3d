# Wolf3d ToDoList

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

