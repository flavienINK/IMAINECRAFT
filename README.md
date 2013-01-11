IMAINECRAFT
===========

Open GL project by Timtothée Riom, Nicolas Giannuzzi, Corentin Marc, Arnaud Gicquello

Fonctionnalités :

    -Terrain de 1000x1000x30 blocs.

    -Fonctionne en temps réel.

    -Clipping pour le dessin du terrain. Dessin de 3600 cubes par frame (carré de 60x60 autour de la position du personnage).

    -Construction aléatoire du terrain avec une graine et morphologie répétée à plusieurs endroits aléatoirement.

    -Plusieurs types de cubes : avec des textures différentes, destructibles ou pas.

    -Skybox.

    -Camera FreeFly.

    -Gestion des collisions dans les 3 directions.

    -Saut.

    -Création/Destruction de cubes (s'ils sont destructibles).

    -Sauvegarde d'une partie.

    -Chargement d'une partie.

    -Son d'ambiance et bruitages d'interactions ( bruits de pas, de création de cube ... )


Pour les contraintes techniques :

    -Héritage pour les différents cubes.

    -Template pour la classe GLShapeInstance qui permet le dessin d'un objet quelconque.

    -Enumeration pour clarifier le code.

    -RAII.

    -Redéfinition d'opérateur pour la classe TerrainData.

    -Format XML pour les parties sauvegardées.

    -Utilisation de la STL pour le stockage des données terrain dans un vector.
