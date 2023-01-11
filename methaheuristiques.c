#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"
#include "parser.h"

int* Metaheuristique_RL(struct Instance* instance, int methode)
{	
	printf("\n\n--Métaheuristique - Initialisation--");

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
/*
int* Metaheuristique_RL(struct Instance* instance, int methode){
	//j'ai pris comme si on avait deja une solution courante venant d'une heuristique mais dans le code final il faudra utiliser l'appel à
	//une fonction heuristique et pas mettre solution courante en parametre du coup
	int *SolutionCourante = solutionHeuristique(instance, methode);
	int *SolutionBest = SolutionCourante;
	int fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
	int fBest = SolutionFonctionObjectif(instance, SolutionCourante);
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);
	int Continue = 0; 
	
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin=0;
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestSousVoisine = malloc(instance->N*sizeof(int));
	
	//1er sous operateur, on echange un 0 en 1 a cahque fois, le voisinage est constité de tout ca et on prend la best solution
	while (Continue=0){		
	
		int fBestVoisin=0;

		for (int i=0 ; i < instance->N ; i++){
			
			for(int k=0;k<instance->N;k++){ //pour tous les objets contenus dans le sac 
				
				SolutionVoisine = SolutionCourante;
				
				if (SolutionVoisine[k]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
					SolutionVoisine[k]=1;
				}

				if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
					fBestVoisin= SolutionFonctionObjectif(instance, SolutionVoisine);
					free(SolutionBestVoisine);
					SolutionBestVoisine=SolutionVoisine;
				}
				free(SolutionVoisine);
				
			}
			
			if (fBestVoisin > fPrec){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
				fBest = fBestVoisin;
				free(SolutionBest);
				SolutionBest = SolutionBestVoisine;
			}
			else{
				if (fCourant < fPrec){
					Continue=1; //le programme se termine, on a pas de meilleur solution que precedemment
				}
			}
			fPrec=fCourant;
			
			if (SolutionCourante[i]==0){
				SolutionCourante[i]==1;
				
				for (int j=0 ; j < instance->N ; j++){
					if (SolutionCourante[j]==1 && i!=j){
						SolutionCourante[j]==0;
					}
					
					for(int k=0;k<instance->N;k++){ //pour tous les objets contenus dans le sac 
				
						free(SolutionBestVoisine);
						SolutionVoisine = SolutionCourante;
						SolutionBestVoisine = SolutionCourante;
						fBestVoisin= SolutionFonctionObjectif(instance, SolutionBestVoisine);
						
						if (SolutionVoisine[k]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
							SolutionVoisine[k]=1;
						}

						if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
							fBestVoisin= SolutionFonctionObjectif(instance, SolutionVoisine);
							free(SolutionBestVoisine);
							SolutionBestVoisine=SolutionVoisine;
						}
						free(SolutionVoisine);
					}
					
					if (fBestVoisin > fPrec){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
						fBest = fBestVoisin;
						free(SolutionBest);
						SolutionBest = SolutionBestVoisine;
					}
					else{
						if (fCourant < fPrec){
							Continue=1; //le programme se termine, on a pas de meilleur solution que precedemment
						}
					}
					fPrec=fCourant;
					
				}
			}
		}
	}	
	return SolutionBest;
	//revoir les free il en manque un paquet !!
}
*/