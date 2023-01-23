#include <stdio.h>

void afficherListeInteger(int* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%d]", liste[i]);
        else printf("%d,", liste[i]);
    }
    printf("\n\n");
}

void afficherListeFloating(float* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille; i++)
    {
        if (i == taille-1) printf("%.3f]", liste[i]);
        else printf("%.3f,", liste[i]);
    }
    printf("\n\n");
}

void afficherSolution(struct Instance* instance, int* solution)
{
	printf("\n\nSolution : ");
    
    for (size_t i = 0; i < instance->N; i++)
	{
		if (solution[i]==1){
			printf("[%ld] ", i);
		}
	}
    
    printf("\nSomme totale des valeurs : %d\n", SolutionFonctionObjectif(instance, solution));
}

void afficherPoidsSolutionSac(struct Instance* instance, int* solution)
{
    int* poids = SolutionCalculDimension(instance, solution);

    printf("\n\nSac     Solution    Libre");

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n%d    %d    %d", instance->b[i], poids[i], instance->b[i]-poids[i]);
	}
}