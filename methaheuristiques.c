
/*
 * Codage direct : un opérateur pertinent serait l’utilisation de deux sous-opérateurs. Le premier
consisterait à ajouter un objet dans le sac (=transformer un 0 en 1), il faudrait alors tester
tous les cas (N) et ne garder que les solutions réalisables. Ces solutions réalisables constitueront
la première partie des solutions du voisinage. Le deuxième sous-opérateur consisterait à
échanger un objet dans le sac avec un autre hors du sac (= mettre un 0 en 1 et mettre un 1 en
0). La deuxième partie des solutions voisines serait alors constituée des solutions réalisables
résultantes de tous les échanges possibles.
 * */
/*
int* Metaheuristique_RL(struct Instance* instance){
	//j'ai pris comme si on avait deja une solution courante venant d'une heuristique mais dans le code final il faudra utiliser l'appel à
	//une fonction heuristique et pas mettre solution courante en parametre du coup
	int *SolutionBest = malloc(instance->N*sizeof(int));
	int *SolutionCourante= malloc(instance->N*sizeof(int));
	
	int fPrec = SolutionFonctionObjectif(instance, SolutionCourante);
	int Continue = 0; 
	int *SolutionVoisine = malloc(instance->N*sizeof(int));
	int fBestVoisin=0;
	int *SolutionBestVoisine = malloc(instance->N*sizeof(int));
	int *SolutionBestSousVoisine = malloc(instance->N*sizeof(int));
	int fCourant;
	
	//1er sous operateur, on echange un 0 en 1 a cahque fois, le voisinage est constité de tout ca et on prend la best solution
	while (Continue=0){		
	
		for (int i=0 ; i < instance->N ; i++){
			SolutionCourante[i]=instance->x[i];
		}
		//SolutionCourante = ;//une heuristique
		fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
		
		for (int i=0 ; i < instance->N ; i++){
			
			for(int k=0;k<instance->N;k++){ //pour tous les objets contenus dans le sac 
				
				free(SolutionBestVoisine);
				SolutionVoisine = SolutionCourante;
				SolutionBestVoisine = SolutionCourante;
				fBestVoisin= SolutionFonctionObjectif(instance, SolutionBestVoisin);
				
				if (SolutionVoisine[k]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
					SolutionVoisine[k]=1;
				}

				if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
					fBestVoisin= SolutionFonctionObjectif(instance, SolutionVoisine);
					free(SolutionBestVoisine);
					SolutionBestVoisine=SolutionVoisine
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
				SolutionCourante[i]==1
				
				for (int j=0 ; j < instance->N ; j++){
					if (SolutionCourante[j]==1 && i!=j){
						SolutionCourante[j]==0
					}
					SolutionCourante = ;//une heuristque
					fCourant = SolutionFonctionObjectif(instance, SolutionCourante);
					
					for(int k=0;k<instance->N;k++){ //pour tous les objets contenus dans le sac 
				
						free(SolutionBestVoisine);
						SolutionVoisine = SolutionCourante;
						SolutionBestVoisine = SolutionCourante;
						fBestVoisin= SolutionFonctionObjectif(instance, SolutionBestVoisin);
						
						if (SolutionVoisine[k]==0){ //si on a un 0 on le transforme en 1 a l'objet ir
							SolutionVoisine[k]=1;
						}

						if (SolutionFonctionObjectif(instance, SolutionVoisine) > fBestVoisin){ // si la solution est meilleur on l'ajoute
							fBestVoisin= SolutionFonctionObjectif(instance, SolutionVoisine);
							free(SolutionBestVoisine);
							SolutionBestVoisine=SolutionVoisine
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