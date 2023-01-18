#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"
#include "parser.h"
#include "listeTabou.h"
#include "listeTabou.c"

int* Metaheuristique_RL(struct Instance* instance, int methode, int dynamique)
{	
	printf("\n\n-- METAHEURISTIQUE RL --");

	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode, dynamique);
	
	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	
	//initialisation de fCourant, fBest et fPrec
	int fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
	int fBest = SolutionFonctionObjectif(instance, SolutionCourante);
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);

	int continuer = 0; 
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin = 0;
	int compteur=0;
	
	while (continuer==0){		
		compteur++;
		int fBestVoisin = 0;
			
		//pour tous les objets contenus dans le sac 
		for(int k = 0; k < instance->N; k++)
		{	
			memcpy(SolutionVoisine, SolutionCourante, instance->N*sizeof(int));
			
			//si on a un 0 on le transforme en 1
			if (SolutionVoisine[k] == 0)
			{ 
				SolutionVoisine[k] = 1;

				//pour chaque AUTRE élément s'il est égal à 1 on le transforme en 0
				for (size_t i = 0; i < instance->N; i++)
				{
					if (SolutionVoisine[i] == 1)
					{
						if(i!=k) SolutionVoisine[i] = 0;

						//si la solution est meilleure ET elle est faisable, on l'ajoute
						if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin && SolutionTestFaisabilite(instance,SolutionVoisine) == 0)
						{ // si la solution est meilleur on l'ajoute
							fBestVoisin = SolutionFonctionObjectif(instance, SolutionVoisine);
							memcpy( SolutionBestVoisine, SolutionVoisine, instance->N*sizeof(int) );
						}

						SolutionVoisine[i] = 1;
					}
				}
			}
		}
		
		fCourant=fBestVoisin;
		memcpy( SolutionCourante, SolutionBestVoisine, instance->N*sizeof(int) );
		
		if (fCourant > fBest){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fCourant;
			memcpy( SolutionBest, SolutionCourante, instance->N*sizeof(int) );
		}
		else{
			if (fCourant < fPrec){
				continuer = 1; //le programme se termine, on a pas de meilleur solution que precedemment
			}
		}
		fPrec = fCourant;
		
	}	
	
	afficherPoidsSolutionSac(instance, SolutionBest);

	return SolutionBest;
}

//methode = numero de l'heuristique; aspi = 1 si aspiration
int* Metaheuristique_Tabou(struct Instance* instance, int methode, int dynamique, int nbIterationsMax, int tailleListeTabou, int aspi)
{	
	printf("\n\n-- METAHEURISTIQUE TABOU --");
	//initialisation d'une liste tabou de taille N
	//cette liste stocke des couples d'entier
	struct ListeTabou* listeTabou;
	ListeTabouInit(listeTabou, tailleListeTabou);
	
	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode, dynamique);
	
	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	
	//initialisation de fCourant, fBest et fPrec
	int fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
	int fBest = SolutionFonctionObjectif(instance, SolutionCourante);
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);
	
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin = 0;
	int compteur=0;
	int mouvement[2];
	
	while (compteur <= nbIterationsMax){		
		
		int fBestVoisin = 0;
			
		//pour tous les objets contenus dans le sac 
		for(int k = 0; k < instance->N; k++)
		{	
			if (aspi==1)
			{
				memcpy(SolutionVoisine, SolutionCourante, instance->N*sizeof(int));
				
				//si on a un 0 on le transforme en 1
				if (SolutionVoisine[k] == 0)
				{ 
					SolutionVoisine[k] = 1;

					//pour chaque AUTRE élément s'il est égal à 1 on le transforme en 0
					for (size_t i = 0; i < instance->N; i++)
					{
						if (SolutionVoisine[i] == 1)
						{
							if (i!=k) SolutionVoisine[i] = 0;

							//mouvement pas tabou
							if (!mouvementDansListeTabou(listeTabou, k, i))
							{
								//si la solution est meilleure ET elle est faisable, on l'ajoute
								if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin && SolutionTestFaisabilite(instance,SolutionVoisine) == 0)
								{ // si la solution est meilleur on l'ajoute
									fBestVoisin = SolutionFonctionObjectif(instance, SolutionVoisine);
									memcpy( SolutionBestVoisine, SolutionVoisine, instance->N*sizeof(int) );
									mouvement[0] = k;
									mouvement[1] = i;
								}
							}
							else
								{
									if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBest && SolutionTestFaisabilite(instance,SolutionVoisine) == 0)
									{ // si la solution est meilleur on l'ajoute
										fBestVoisin = SolutionFonctionObjectif(instance, SolutionVoisine);
										memcpy( SolutionBestVoisine, SolutionVoisine, instance->N*sizeof(int) );
										mouvement[0] = k;
										mouvement[1] = i;
									}
								}

							SolutionVoisine[i] = 1;
						}
					}
				}
			}
		}
		
		fCourant = fBestVoisin;
		memcpy( SolutionCourante, SolutionBestVoisine, instance->N*sizeof(int) );
		
		if (listeTabouPleine(listeTabou)) supprimerElementListeTabou(listeTabou);
		
		ajouterMouvementListeTabou(listeTabou, mouvement[0], mouvement[1]);

		if (fCourant > fBest){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fCourant;
			memcpy( SolutionBest, SolutionCourante, instance->N*sizeof(int) );
			compteur = 0;
		}
		
		fPrec = fCourant;
		compteur++;
	}	

	afficherPoidsSolutionSac(instance, SolutionBest);

	return SolutionBest;
}

/*
int* Metaheuristique_Genetique(struct Instance* instance, int methode, int nbIterationsMax, int taillePopu, int Pmut)
{
	int **PopulationCourante = malloc(instance->N*sizeof(int));
	for (int i = 0; i < taillePopu; i++)
	{
        PopulationCourante[i] = malloc(instance->N * sizeof(int));
    }
	
	int **PopulationEnfant = malloc(instance->N*sizeof(int));
	for (int i = 0; i < taillePopu; i++)
	{
        PopulationEnfant[i] = malloc(instance->N * sizeof(int));
    }
	
	int *SolutionBest = malloc(instance->N*sizeof(int));
	int *Solution = malloc(instance->N*sizeof(int));
	int fBest=0;
	
	for (int i=0; i<taillePopu; i++)
	{
		PopulationCourante[i]=solutionHeuristique(instance, methode);
	}
	for (int i=0; i<taillePopu; i++)
	{
		if (SolutionFonctionObjectif(instance,PopulationCourante[i]) > fBest)
		{
			memcpy(SolutionBest, PopulationCourante[i], instance->N*sizeof(int));
		}
	}
	
	int *indices=malloc(instance->N*sizeof(int));
	int compteur=0;
	printf("\n\nSolution best : "); afficherListeInteger(SolutionBest, instance->N);
	
	while (compteur < nbIterationsMax)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j=0 ; j< instance->N; j++){
				PopulationEnfant[i][j]=-1

			}
		}	
		
		for (int i=0; i < instance->N; i++)
		{
			srand(time(0)); 

			int j = rand() % (instance->N-i) + i;
			int temp = indices[i];
			indices[i] = indices[j];
			indices[j] = temp;
		}
		
		int a=0;
		int compteurPopEnfant=0;
		
		for (int i=0; i < (taillePopu/2); i++)
		{
			if (SolutionFonctionObjectif(instance, PopulationCourante[indices[a]]) < SolutionFonctionObjectif(instance, PopulationCourante[indices[a+1]]))
			{
				PopulationEnfant[compteurPopEnfant]= PopulationCourante[indices[a+1]];
			} 
			else{
				PopulationEnfant[compteurPopEnfant]= PopulationCourante[indices[a]];
			}
			
			a++;
			compteurPopEnfant++;
			
			if (SolutionFonctionObjectif(instance, PopulationCourante[indices[a]]) < SolutionFonctionObjectif(instance, PopulationCourante[indices[a+1]]))
			{
				PopulationEnfant[compteurPopEnfant]= PopulationCourante[indices[a+1]];
			} 
			else{
				PopulationEnfant[compteurPopEnfant]= PopulationCourante[indices[a]];
			}
			
			a++;
			compteurPopEnfant++;
			
		}
		
		for (int i=0; i < taillePopu; i++)
		{
			if (SolutionFonctionObjectif(instance, PopulationEnfant[i]) > fBest)
			{
				fBest = SolutionFonctionObjectif(instance, PopulationEnfant[i]);
				memcpy(SolutionBest, PopulationEnfant[i], instance->N*sizeof(int));
			}			

			if (Pmut != 0)
			{
				Solution = Mutation(Population[i]);
				
				if (SolutionFonctionObjectif(instance, Solution) > SolutionFonctionObjectif(instance, Population[i]))
				{
					memcpy(PopulationEnfant[i], Solution ,instance->N*sizeof(int));
				}
				
				if (SolutionFonctionObjectif(instance, PopulationEnfant[i]) > fBest)
				{
					fBest = SolutionFonctionObjectif(instance, PopulationEnfant[i]);
					memcpy(SolutionBest, PopulationEnfant[i], instance->N*sizeof(int));
				}
			}
		}
		
		// faut faire un renouvellement de PopulationCourante
		//un algo qui prend les n meilleurs solutions de population courante
		compteur++;
	}
	return SolutionBest;
}


//garde les n meilleurs solutions de l'ensemble de solutions
int *MeilleursSolutions(struct Instance* instance, int taillePopu, int **Solutions, int n){
	
	int *OrdresMeilleursIndice=malloc(taillePopu*sizeof(int));
	
	int fBest=0;
	for(int i=0; i< taillePopu; i++)
	{
		if (SolutionFonctionObjectif(instance, Solutions[i]) >= fBest )
		{
			
		}
	} 
}
*/