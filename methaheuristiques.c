#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"
#include "parser.h"

int* Metaheuristique_RL(struct Instance* instance, int methode)
{	
	printf("\n\n--Métaheuristique RL - Initialisation--");

	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
	printf("\n\nSolution courante : "); afficherListeInt(SolutionCourante, instance->N);
	int* poids = SolutionCalculDimension(instance, SolutionCourante);

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n poids solution - dim %d : %d", i, poids[i]);
		printf("\n poids sac      - dim %d : %d", i, instance->b[i]);

	}
	

	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	printf("\n\nSolution best : "); afficherListeInt(SolutionBest, instance->N);
	
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

				//printf("\nk = %d : Valeurs du sac de la solution voisine : %d",k, SolutionFonctionObjectif(instance, SolutionVoisine));
				//printf("\nk = %d : faisabilite : %d",k, SolutionTestFaisabilite(instance,SolutionVoisine));
				
				//si la solution est meilleure ET elle est faisable, on l'ajoute
				if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin && SolutionTestFaisabilite(instance,SolutionVoisine) == 0)
				{ 
					printf("\nNouvelle solution best voisine !");
					fBestVoisin = SolutionFonctionObjectif(instance, SolutionVoisine);
					memcpy(SolutionBestVoisine, SolutionVoisine, instance->N*sizeof(int));
				}

				//pour chaque AUTRE élément s'il est égal à 1 on le transforme en 0
				for (size_t i = 0; i < instance->N; i++)
				{
					if (i!=k && SolutionVoisine[i] == 1)
					{
						SolutionVoisine[i] = 0;

						//printf("\nk = %d, i = %d : Valeurs du sac de la solution voisine : %d",k,i, SolutionFonctionObjectif(instance, SolutionVoisine));
						//printf("\nk = %d, i = %d : faisabilite : %d",k,i, SolutionTestFaisabilite(instance,SolutionVoisine));
						
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
		//printf("\n\nSolution courante : "); afficherListeInt(SolutionCourante, instance->N);
		
		if (fCourant > fBest){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fCourant;
			memcpy( SolutionBest, SolutionCourante, instance->N*sizeof(int) );
			//printf("\n\nSolution best : "); afficherListeInt(SolutionBest, instance->N);
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

//A MODIFIER
int* Metaheuristique_Tabou(struct Instance* instance, int methode, int nbIterationsMax, int tailleListeTabou, int aspi)
{	
	printf("\n\n--Métaheuristique Tabou - Initialisation--");

	//initialisation d'une liste tabou de taille N
	//cette liste stocke des couples d'entier
	int **ListeTabou = malloc(tailleListeTabou*sizeof(int)*2);

	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
	printf("\n\nSolution courante : "); afficherListeInt(SolutionCourante, instance->N);
	int* poids = SolutionCalculDimension(instance, SolutionCourante);

	for (size_t i = 0; i < instance->M; i++)
	{
		printf("\n poids solution - dim %d : %d", i, poids[i]);
		printf("\n poids sac      - dim %d : %d", i, instance->b[i]);

	}
	

	//initialisation de la meilleure solution
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, SolutionCourante, instance->N*sizeof(int));
	printf("\n\nSolution best : "); afficherListeInt(SolutionBest, instance->N);
	
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

				//printf("\nk = %d : Valeurs du sac de la solution voisine : %d",k, SolutionFonctionObjectif(instance, SolutionVoisine));
				//printf("\nk = %d : faisabilite : %d",k, SolutionTestFaisabilite(instance,SolutionVoisine));
				
				//si la solution est meilleure ET elle est faisable, on l'ajoute
				if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin && SolutionTestFaisabilite(instance,SolutionVoisine) == 0)
				{ 
					printf("\nNouvelle solution best voisine !");
					fBestVoisin = SolutionFonctionObjectif(instance, SolutionVoisine);
					memcpy(SolutionBestVoisine, SolutionVoisine, instance->N*sizeof(int));
				}

				//pour chaque AUTRE élément s'il est égal à 1 on le transforme en 0
				for (size_t i = 0; i < instance->N; i++)
				{
					if (i!=k && SolutionVoisine[i] == 1)
					{
						SolutionVoisine[i] = 0;

						//printf("\nk = %d, i = %d : Valeurs du sac de la solution voisine : %d",k,i, SolutionFonctionObjectif(instance, SolutionVoisine));
						//printf("\nk = %d, i = %d : faisabilite : %d",k,i, SolutionTestFaisabilite(instance,SolutionVoisine));
						
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
		//printf("\n\nSolution courante : "); afficherListeInt(SolutionCourante, instance->N);
		
		if (fCourant > fBest){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fCourant;
			memcpy( SolutionBest, SolutionCourante, instance->N*sizeof(int) );
			//printf("\n\nSolution best : "); afficherListeInt(SolutionBest, instance->N);
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

//supprime le plus vieil élément de la liste
void supprimerElementListeTabou(int** listeTabou)
{

}

//ajoute un nouveau mouvement à la liste
void ajouterMouvementListeTabou(int** listeTabou, int element0, int element1)
{

}

//renvoie 0 si la liste est pleine
int listeTabouPleine(int** listeTabou)
{
	return 0;
}

//retourne 0 si le mouvement est dans la liste
int mouvementDansListeTabou(int** listeTabou, int element0, int element1)
{
	return 0;
}
