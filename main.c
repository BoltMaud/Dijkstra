#include "system.h"

int main(int argc, char *argv []){
	//DEBUG MATHILDE

	long clk_tck = CLOCKS_PER_SEC;
	clock_t t1, t2,t3;
	int s;
	printf("Donner un nombre supérieur à 10 : \n");
	scanf("%d",&s);
	s=s-(s%10);

	srand(time(NULL));//pour les aleatoires

	Graphe g=remplissage(s);
	Graphe a=copiage(g);
	#if defined (TAB)
	printf("TABLEAU : \n");
	#elif defined (BH)
	printf("TAS BINAIRE : \n");
	#endif
	t1 = clock();
	dijkstra_gen(a,1,s-1);
	t2 = clock();
	printf("\nLISTE :\n");
	dijkstra_Liste(g,1,s-1);
	t3 = clock();
	printf("\n");
	#if defined (TAB)
	printf("Temps consomme avec tableau (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
	#elif defined (BH)
	printf("Temps consomme avec tas binaire (s) : %lf \n",(double)(t2-t1)/(double)clk_tck);
	#endif
	printf("Temps consomme avec Liste (s) : %lf \n",(double)(t3-t2)/(double)clk_tck);
	//dijkstra_Liste(a,1,5);*/

	//free(g);
	//desalloue(g);
	//dijkstra_Liste(g,9,5);

	//desalloueliste(a);

	//DEBUG LAURINE
/*
	arete a1;
	a1.depart=2;
	a1.arrivee=3;
	a1.poids=3;

	arete a2;
	a2.depart=2;
	a2.arrivee=4;
	a2.poids=4;

	arete a3;
	a3.depart=2;
	a3.arrivee=98;
	a3.poids=5;

	arete a4;
	a4.depart=2;
	a4.arrivee=98;
	a4.poids=7;

	arete a5;
	a5.depart=2;
	a5.arrivee=98;
	a5.poids=9;

	arete a6;
	a6.depart=2;
	a6.arrivee=98;
	a6.poids=6;

	arete a7;
	a7.depart=2;
	a7.arrivee=98;
	a7.poids=10;
*/
/* //DEBUG TABLEAU
	table *new= tabnouv();

	new=insert_tab(new,a1);
	new=insert_tab(new,a2);
	new=insert_tab(new,a3);
	new=insert_tab(new,a4);
	new=insert_tab(new,a5);
	new=insert_tab(new,a6);
	new=insert_tab(new,a7);

	affichage_table(new);
	arete a=mintab(new);
	printf("arete :%d\n",a.poids);
	affichage_table(new);
	arete b=mintab(new);
	printf("rslt arete b : %d\n",b.arrivee);
	affichage_table(new);
	arete c=mintab(new);
	printf("arete c: %d\n", c.poids);
	affichage_table(new);
*/
/*
 //DEBUG heap
	heap *new=create();
	new=insert_not_organized(new,a1);
	new=insert_not_organized(new,a2);
	new=insert_not_organized(new,a3);
	new=insert_not_organized(new,a4);
	new=insert_not_organized(new,a5);
	new=insert_not_organized(new,a6);
	new=insert_not_organized(new,a7);

	printf("taille : %d\n",new->size);

//	new=percolate_down(new,1);
//	new=percolate_up(new);

	affi_h(new);
	arete a=minh(new);
	printf("poids arete a: %d\n\n",a.poids);
	affi_h(new);
	//arete b=minh(new);
	//printf("poids arete b: %d\n\n",b.poids);
	//affi_h(new);
	printf("\n");
	//new=tamiser(new);
	//affi_h(new);
	//new=tamiser(new);
	//affi_h(new);
*/
return 0;
}
