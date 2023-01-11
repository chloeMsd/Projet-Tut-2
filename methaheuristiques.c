#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"
#include "parser.h"
#include "listeTabou.h"
#include "listeTabou.c"

int* Metaheuristique_RL(struct Instance* instance, int methode)
{	
	printf("\n\n--Métaheuristique RL - Initialisation--");

	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
	printf("\n\nSolution courante : "); afficherListeInteger(SolutionCourante, instance->N);
	int* poids = SolutionCalculDimension(instance, SolutionCourante);

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n poids solution - dim %d : %d", i, poids[i]);
		printf("\n poids sac      - dim %d : %d", i, instance->b[i]);

	}
	

	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	printf("\n\nSolution best : "); afficherListeInteger(SolutionBest, instance->N);
	
	//initialisation de fCourant, fBest et fPrec
	int fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
	int fBest = SolutionFonctionObjectif(instance, SolutionCourante);
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);
	printf("\n\nfCourant : %d \nfBest : %d \nfPrec : %d", fCourant, fBest, fPrec);
	
	int continuer = 0; 
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin = 0;
	int compteur=0;
	
	while (continuer==0){		
		compteur++;
		printf("\ntour %d\n", compteur);
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
							printf("\nNouvelle solution best voisine !");
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
		//printf("\n\nSolution courante : "); afficherListeInteger(SolutionCourante, instance->N);
		
		if (fCourant > fBest){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fCourant;
			memcpy( SolutionBest, SolutionCourante, instance->N*sizeof(int) );
			//printf("\n\nSolution best : "); afficherListeInteger(SolutionBest, instance->N);
		}
		else{
			if (fCourant < fPrec){
				continuer = 1; //le programme se termine, on a pas de meilleur solution que precedemment
			}
		}
		fPrec = fCourant;
		
		printf("\n\nfCourant : %d \nfBest : %d \nfPrec : %d", fCourant, fBest, fPrec);
		printf("\n\ncontinuer : %d", continuer);
		
	}	
	return SolutionBest;
}

//methode = numero de l'heuristique; aspi = 1 si aspiration
int* Metaheuristique_Tabou(struct Instance* instance, int methode, int nbIterationsMax, int tailleListeTabou, int aspi)
{	
	printf("\n\n--Métaheuristique Tabou - Initialisation--");

	//initialisation d'une liste tabou de taille N
	//cette liste stocke des couples d'entier
	struct ListeTabou* listeTabou;
	ListeTabouInit(listeTabou, tailleListeTabou);
	
	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
	printf("\n\nSolution courante : "); afficherListeInteger(SolutionCourante, instance->N);
	int* poids = SolutionCalculDimension(instance, SolutionCourante);

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n poids solution - dim %d : %d", i, poids[i]);
		printf("\n poids sac      - dim %d : %d", i, instance->b[i]);

	}
	
	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	printf("\n\nSolution best : "); afficherListeInteger(SolutionBest, instance->N);
	
	//initialisation de fCourant, fBest et fPrec
	int fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
	int fBest = SolutionFonctionObjectif(instance, SolutionCourante);
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);
	printf("\n\nfCourant : %d \nfBest : %d \nfPrec : %d", fCourant, fBest, fPrec);
	
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
									//printf("\nNouvelle solution best voisine !");
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
										//printf("\nNouvelle solution best voisine !");
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
		printf("\n\nfCourant : %d \nfBest : %d \nfPrec : %d", fCourant, fBest, fPrec);

		compteur++;
		printf("\ntour %d\n", compteur);
	}	
	return SolutionBest;
}
