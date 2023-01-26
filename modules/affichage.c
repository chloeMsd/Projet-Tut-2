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

void afficherPoidsSolutionEtSac(struct Instance* instance, int* solution)
{
    int* poids = SolutionCalculDimension(instance, solution);
    
    printf("\n\nSac     Solution     Libre");

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n%d    %d    %d", instance->b[i], poids[i], instance->b[i]-poids[i]);
	}
}

void afficherHeuristiques(struct Instance* instance)
{
    int valeurs[6];
    for (int i = 0; i < 6; i++)
    {
        valeurs[i] = SolutionFonctionObjectif(instance, solutionHeuristique(instance, i+1));
    }
    
    printf("HEURISTIQUE          %d      |  %d        |  %d      |  %d          |  %d         |  %d", valeurs[0], valeurs[1], valeurs[2], valeurs[3], valeurs[4], valeurs[5]);
}

void afficherMetaheuristiques(struct Instance* instance)
{
    int RL[6];
    int RT[6];
    int RG[6];
    
    for (int i = 0; i < 6; i++)
    {
        RL[i] = SolutionFonctionObjectif(instance, Metaheuristique_RL(instance, i+1));
        RT[i] = SolutionFonctionObjectif(instance, Metaheuristique_Tabou(instance, i+1, 10, 50, 1));
        RG[i] = 0;
    }

    printf("\nRecherche LOCALE     %d      |  %d        |  %d      |  %d          |  %d         |  %d", RL[0], RL[1], RL[2], RL[3], RL[4], RL[5]);
    printf("\nRecherche TABOUE     %d      |  %d        |  %d      |  %d          |  %d         |  %d", RT[0], RT[1], RT[2], RT[3], RT[4], RT[5]);
    printf("\nRecherche GENETIQUE  %d      |  %d        |  %d      |  %d          |  %d         |  %d", RG[0], RG[1], RG[2], RG[3], RG[4], RG[5]);
}
