#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instance.h"
#include "parser.h"
#include "listeTabou.h"
#include "listeTabou.c"

//implémentation de la recherche locale.
//retourne une solution de l'instance.
int* Metaheuristique_RL(struct Instance* instance, int methode)
{	
	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
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
	
	return SolutionBest;
}

//implémentation de la recherche tabou.
//retourne une solution de l'instance.
int* Metaheuristique_Tabou(struct Instance* instance, int methode, int nbIterationsMax, int tailleListeTabou, int aspi)
{	
	//initialisation d'une liste tabou de taille N
	//cette liste stocke des couples d'entier
	struct ListeTabou* listeTabou = (struct ListeTabou*) malloc(sizeof(struct ListeTabou*));;
	ListeTabouInit(listeTabou, tailleListeTabou);
	
	//récupération d'une solution de base
	int *SolutionCourante = solutionHeuristique(instance, methode);
	
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

	return SolutionBest;
}


/*--------------------------------------------------------*/


//génère une liste de couples de solutions par tournoi
int** indicesParentsTournoi(int n)
{
    int** indicesAlea = malloc(sizeof(int*) * n); //allouer la mémoire pour la liste
    int i, temp, randomIndex;

    for (i = 0; i < n; i++) {
        indicesAlea[i] = (int*) malloc(sizeof(int) * 2); //allouer la mémoire pour chaque couple
    }
    for (i = 0; i < n; i++) {
        indicesAlea[i][0] = i;
        indicesAlea[i][1] = (i+1) % n; 
    }

    return indicesAlea;
}

//génère une solution enfant issue de deux solutions parent
int* croisement(struct Instance* instance, int* solutionParent1, int* solutionParent2)
{
	srand(time(NULL));

    int* solutionEnfant = malloc(instance->N * sizeof(int));
    int x = rand() % (instance->N - 1) + 1; // génère un entier aléatoire compris entre 1 et n-1
    int i;

    // copie les éléments de solutionParent1 avant x
    for (i = 0; i < x; i++) {
        solutionEnfant[i] = solutionParent1[i];
    }

    // copie les éléments de solutionParent2 après x
    for (i = x; i < instance->N; i++) {
        solutionEnfant[i] = solutionParent2[i];
    }

    return solutionEnfant;
}

//indique si une mutation doit avoir lieu
int muter(int proba)
{
	return 1;
}

//indique si une mutation doit avoir lieu
int* mutation(int* solution, int tailleSolution)
{
	int* solutionMutante = malloc(tailleSolution*sizeof(int));
	memcpy(solutionMutante, solution, tailleSolution*sizeof(int));

	return solutionMutante;
}

//renvoie une nouvelle population à partir de la population courante et enfant
int* renouvellement(int* populationCourante, int* populationEnfant, int taillePop)
{
	int* nouvellePopulation = malloc(taillePop*sizeof(int));

	return nouvellePopulation;
}

//implémentation de l'algorithme génétique.
//retourne une solution de l'instance.
//NE FONCTIONNE PAS
int* Metaheuristique_Genetique(struct Instance* instance, int taillePopu, int nbIterationsMax, float Pmut)
{
	//calcul d'une population initiale
	int** populationCourante = malloc(taillePopu*instance->N*sizeof(int));

	for (size_t i = 0; i < taillePopu; i++)
	{
		populationCourante[i] = solutionHeuristique(instance, 1);
	}
	
	//meilleur individu de la population courante
	int *SolutionBest = malloc(instance->N*sizeof(int));
	memcpy(SolutionBest, populationCourante[0], instance->N*sizeof(int) );

	for (size_t i = 1; i < taillePopu; i++)
	{
		if (SolutionFonctionObjectif(instance, populationCourante[i]) > SolutionFonctionObjectif(instance, SolutionBest))
		{
			SolutionBest = memcpy(SolutionBest, populationCourante[i], instance->N*sizeof(int) );
		}
	}

	int fBest = SolutionFonctionObjectif(instance, SolutionBest);

	int compteur = 0;
	while (compteur < nbIterationsMax)
	{
		int** populationEnfant = malloc(taillePopu*instance->N*sizeof(int));
		int** indicesParents = indicesParentsTournoi(taillePopu);

		//creation des enfants
		for (size_t i = 0; i < taillePopu/2; i++)
		{
			populationEnfant[indicesParents[i][0]] = croisement(instance, populationCourante[indicesParents[i][0]], populationCourante[indicesParents[i][1]]);
			populationEnfant[indicesParents[i][1]] = croisement(instance, populationCourante[indicesParents[i][0]], populationCourante[indicesParents[i][1]]);	
		}

		//bestSolution et mutations
		for (size_t i = 0; i < taillePopu; i++)
		{
			if (SolutionFonctionObjectif(instance, populationEnfant[i]) > SolutionFonctionObjectif(instance, SolutionBest))
			{
				SolutionBest = memcpy(SolutionBest, populationEnfant[i], instance->N*sizeof(int) );
				fBest = SolutionFonctionObjectif(instance, SolutionBest);
			}

			if (muter(Pmut))
			{
				memcpy(populationEnfant[i], mutation(populationEnfant[i], instance->N*sizeof(int)), instance->N*sizeof(int));
				if (SolutionFonctionObjectif(instance, populationEnfant[i]) > SolutionFonctionObjectif(instance, SolutionBest))
				{
					SolutionBest = memcpy(SolutionBest, populationEnfant[i], instance->N*sizeof(int) );
					fBest = SolutionFonctionObjectif(instance, SolutionBest);
				}
			}

			memcpy(populationCourante, renouvellement(populationCourante, populationEnfant, taillePopu), taillePopu*sizeof(int));
		}	
	}	
}