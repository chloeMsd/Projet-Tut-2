#pragma once

struct Instance {
    
    //le nombre d'objet contenus dans l'instance (N)
    int N;

    //le nombre de dimensions (M)
    int M;

    //la valeur de chaque objet
    int* p;

    //le poid de chaque objet dans chaque dimension (ex : [[1,2,3][4,5,6][7,8,9]]
    int** r;

    //le poid maximum possible de l'instance dans chaque dimension
    int* b;
};