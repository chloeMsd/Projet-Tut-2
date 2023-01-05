#include <stdio.h>
#include <stdlib.h>
#include "instance.h"
#include "parser.h"

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
			
		for(int k=0;k<instance->N;k++){ //pour tous les objets contenus dans le sac 
			
			SolutionVoisine = SolutionCourante;
			
			if (SolutionVoisine[k]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
				SolutionVoisine[k]=1;
			}

			if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
				fBestVoisin= SolutionFonctionObjectif(instance, SolutionVoisine);
				SolutionBestVoisine=SolutionVoisine;
			}
			
		}
		
		if (fBestVoisin > fPrec){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest = fBestVoisin;
			SolutionBest = SolutionBestVoisine;
		}
		else{
			if (fCourant < fPrec){
				Continue=1; //le programme se termine, on a pas de meilleur solution que precedemment
			}
		}
		fPrec=fCourant;
	}	
	return SolutionBest;
	//revoir les free il en manque un paquet !!
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