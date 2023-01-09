#include <stdio.h>

void afficherListeInt(int* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%d:%d]", i,liste[i]);
        else printf("%d:%d, ", i,liste[i]);
    }
}

void afficherListeFloat(float* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%.3f]", liste[i]);
        else printf("%.3f, ", liste[i]);
    }
}
