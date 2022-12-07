struct Instance {
    
    //le nombre d'objet contenus dans l'instance (N)
    int nombre_objets;
    
    //le nombre de dimensions (M)
    int dimension;

    //deux solutions optimales de l'instance
    int* valeurs_solution[2];

    //indique si l'objet fait partie de la solution optimale (0 = non, 1 = oui)
    int* solution;

    //la valeur de chaque objet
    int* valeurs_objets;

    //le poid de chaque objet dans chaque dimension (ex : [[1,2,3][4,5,6][7,8,9]]
    int** poids_objets;

    //le poid maximum possible de l'instance dans chaque dimension
    int * poids_maximum;
};