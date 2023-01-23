#include <stdio.h>
#pragma once

struct Parser {
    
    //fichier à lire
    FILE* fichier;

    //le nombre d'instances
    int nb_instances;

    //le nombre d'objet contenus dans l'instance (N)
    int N;
    int N;

    //le nombre de dimensions (M)
    int M;

    //la valeur de chaque objet
    int* p;
    int* p;

    //le poid de chaque objet dans chaque dimension (ex : [[1,2,3][4,5,6][7,8,9]]
    int** r;
    int** r;

    //le poid maximum possible de l'instance dans chaque dimension
    int* b;
    int* b;
};