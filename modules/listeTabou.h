#pragma once

struct ListeTabou {
    
    //le nombre de couples contenus dans la liste
    int N;

    //l'indice du dernier objet
    int dernier;

    //le tableau des couples
    int **liste;
};