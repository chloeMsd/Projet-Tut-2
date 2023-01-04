
/*
#include <stdio.h>
#include <stdlib.h>
#include "instance.h"
#include "parser.h"
#include "solution.h"
#include "solution.c" //???? comment je recupere mes fonctions de solution.c ?? 

int* Metheuristique_RL(struct Instance* instance){
	//j'ai pris comme si on avait deja une solution courante venant d'une heuristique mais dans le code final il faudra utiliser l'appel à
	//une fonction heuristique et pas mettre solution courante en parametre du coup
	int *SolutionBest = malloc(instance->N*sizeof(int));
	int *SolutionCourante;
	int fPrec = SolutionFonctionObjectif(SolutionCourante);
	int Continue = 0; 
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin=0;
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestSousVoisine;
	int fCourant;
	//1er sous operateur, on echange un 0 en 1 a cahque fois, le voisinage est constité de tout ca et on prend la best solution
	while (Continue=0){
		//il faut rappeler une solutionCourante a chaque tour de boucle et recalculé le fCourants
		SolutionCourante = ;//une heuristque
		fCourant = SolutionFonctionObjectif(SolutionCourante);
		for(int i=0;i<instance->N;i++){ //pour tous les objets contenus dans le sac 
			free(SolutionBestVoisine);
			fBestVoisin=0;
			SolutionVoisine = SolutionCourante;
			SolutionBestVoisine = SolutionCourante;
			if (SolutionVoisine[i]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
				SolutionVoisine[i]=1;
			}
			else{
				SolutionVoisine[i]=0;
			}
			if (SolutionFonctionObjectif(SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
				fBestVoisin= SolutionFonctionObjectif(SolutionVoisine);
				free(SolutionBestVoisine);
				SolutionBestVoisine=SolutionVoisine
			}
			free(SolutionVoisine);
		}
		if (fBestVoisin > fPrec){ //si on a trouve une meilleur solution qu'avec la solution courante precedente, on remplace 
			fBest->fBestVoisin;
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
	
	//2eme sous operateur, échanger un objet dans le sac avec un autre hors du sac (= mettre un 0 en 1 et mettre un 1 en 0)
	Continue=0;
	while (Continue==0){
		SolutionCourante = ;//une heuristque
		fCourant = SolutionFonctionObjectif(SolutionCourante);
		for(int i=0; i<instance->N; i++){ //pour tous les objets contenus dans le sac 
			free(SolutionBestVoisine);
			fBestVoisin=0;
			SolutionVoisine = SolutionCourante;
			SolutionBestSousVoisine = SolutionCourante;
			if (SolutionVoisine[i]==0){ //si on a un 0 on le transforme en 1 a l'objet i et inversement si c'est un 1
				for (int j=0; j<instance->N; j++){
					//il faut tester pour cahque solution si ca fonctionne du coup tout le truc pour recuperer la valeur et tout faurdait 
					// peut etre faire une fonction juste pour ca histoire que le code fasse pas 500 lignes !!
					
				}
				
			}
			
			else{
				SolutionVoisine[i]=0;
			}
			if (SolutionFonctionObjectif(SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
				fBestVoisin= SolutionFonctionObjectif(SolutionVoisine);
				free(SolutionBestVoisine);
				SolutionBestVoisine=SolutionVoisine
			}
			free(SolutionVoisine);
		}
	}
	return SolutionBest;
	//revoir les free il en manque un paquet !!
}

*/