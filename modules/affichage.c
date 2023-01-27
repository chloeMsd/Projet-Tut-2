#include <stdio.h>

//affiche une liste d'entiers 
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

//affiche une liste de réels
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

//affiche une solution :
//  -les indices des éléments solution 
//  -la valeur totale de la solution
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

//affiche le détail des poids d'une solution :
//  -la capacité maximale de chaque dimension du sac 
//  -la place prise dans chaque dimension par la solution
//  -la place restante (négatif si la solution dépasse la capacité maximale)
void afficherPoidsSolutionEtSac(struct Instance* instance, int* solution)
{
    int* poids = SolutionCalculDimension(instance, solution);
    
    printf("\n\nSac     Solution     Libre");

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n%d    %d    %d", instance->b[i], poids[i], instance->b[i]-poids[i]);
	}
}

//affiche toutes les heuristiques pour une instance donnée
void afficherHeuristiques(struct Instance* instance)
{
    int valeurs[6];
    for (int i = 0; i < 6; i++)
    {
        valeurs[i] = SolutionFonctionObjectif(instance, solutionHeuristique(instance, i+1));
    }
    
    printf("HEURISTIQUE          %d      |  %d        |  %d      |  %d          |  %d         |  %d", valeurs[0], valeurs[1], valeurs[2], valeurs[3], valeurs[4], valeurs[5]);
}

//affiche toutes les métaheuristiques pour une instance donnée
void afficherMetaheuristiques(struct Instance* instance, int TABOUnbIterationsMax, int tailleListeTabou, int TABOUaspi)
{
    int RL[6];
    int RT[6];
    int RG[6];
    
    for (int i = 0; i < 6; i++)
    {
        RL[i] = SolutionFonctionObjectif(instance, Metaheuristique_RL(instance, i+1));
        RT[i] = SolutionFonctionObjectif(instance, Metaheuristique_Tabou(instance, i+1, TABOUnbIterationsMax, tailleListeTabou, TABOUaspi));
    }

    printf("\nRecherche LOCALE     %d      |  %d        |  %d      |  %d          |  %d         |  %d", RL[0], RL[1], RL[2], RL[3], RL[4], RL[5]);
    printf("\nRecherche TABOUE     %d      |  %d        |  %d      |  %d          |  %d         |  %d", RT[0], RT[1], RT[2], RT[3], RT[4], RT[5]);
}

//fonction qui affiche les valeurs de l'instance
void PrintInstance(struct Instance* instance)
{
    printf("-- INSTANCE --\n");
    printf("Nombre objets : %d\n", instance->N);
    printf("Dimension : %d\n", instance->M);

    printf("Valeurs objets : [");
	for (int i = 0; i < instance->N; i++)
	{
		printf("%d",instance->p[i]); 
        if (i+1 < instance->N) printf(",");
	}
	printf("]\n");
    
    printf("Poids objets : [\n\n");
	for (int i = 0; i < instance->M; i++)
	{
        printf("[");
        for (int j = 0; j < instance->N; j++)
        {
            printf("%d", instance->r[i][j]); 
            if (i+1 < instance->N) printf(",");
        }
	    printf("]\n\n");
	}
	printf("]\n\n");

    printf("Poids maximaux : [");
	for (int i = 0; i < instance->M; i++)
	{
		printf("%d",instance->b[i]); 
        if (i+1 < instance->M) printf(",");
	}
	printf("]\n");
}

//fonction qui affiche les valeurs du parser
void printParser(struct Parser* parser)
{
	printf("\n--- Parser ---\n\n");

	printf("N = %d\n\nM = %d\n\n", parser->N, parser->M);
	
	printf("Valeurs :\n"); 
	afficherListeInteger(parser->p, parser->N);

	for (int j=0;j<parser->M;j++){
		printf("Poids dim %d :\n", j); afficherListeInteger(parser->r[j], parser->N);
	}

	printf("Poids max : "); 
	afficherListeInteger(parser->b, parser->M);
}
