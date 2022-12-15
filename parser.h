#include <stdio.h>
#pragma once

struct Parser {
    
    //fichier à lire
    FILE* fichier;

    //le nombre d'instances
    int nb_instances;

    //le nombre d'objet contenus dans l'instance (N)
    int N;

    //le nombre de dimensions (M)
    int M;

    //deux solutions optimales de l'instance
    int solutions[2];

    //indique si l'objet fait partie de la solution optimale (0 = non, 1 = oui)
    int* x;

    //la valeur de chaque objet
    int* p;

    //le poid de chaque objet dans chaque dimension (ex : [[1,2,3][4,5,6][7,8,9]]
    int** r;

    //le poid maximum possible de l'instance dans chaque dimension
    int* b;
};