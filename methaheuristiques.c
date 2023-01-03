int* Heuristique_3(){
	int *
}

/*
Input : Données
Output : La solution (tableau binaire : SolutionDirect)
1 L ←Ordonner tous les objets selon une stratégie
2 SolutionDirect ← [0, 0, ..., 0]
3 while L ̸= ∅ do
4 j ← Premier élément de L
5 Retirer j de L
6 if j peut loger dans le sac then
7 SolutionDirect[j] ← 1
8 end
9 Mise à jour de L
10 end
11 return SolutionDirect

1 Aléatoire.
2 Selon la valeur des objets (décroissant).
3 Selon un ratio entre la valeur des objets et la somme des poids de toutes les dimensions
(décroissant).
4 Selon un ratio entre la valeur des objets et le poids de la dimension la plus critique (décroissant).
5 etc.
6 La mise à jour dynamique de la liste peut être intéressante dans certains cas. Par exemple, au fur
et à mesure que le sac se remplit, on réordonne la liste en fonction de la stratégie de trie 4 et de
la nouvelle dimension la plus critique
*/