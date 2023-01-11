#include <stdio.h>

void afficherListeInteger(int* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%d:%d]", i,liste[i]);
        else printf("%d:%d, ", i,liste[i]);
    }
}

void afficherListeFloating(float* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%.3f]", liste[i]);
        else printf("%.3f, ", liste[i]);
    }
}

void afficherSolution(struct Instance* instance, int* solution)
{
	printf("\nSolutions : ");
    
    for (size_t i = 0; i < instance->N; i++)
	{
		if (solution[i]==1){
			printf("[%ld] ", i);
		}
	}
    
    printf("\n\nSomme totale des valeurs  : %d\n", SolutionFonctionObjectif(instance, solution));
}