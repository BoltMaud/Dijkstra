#include "system.h"

/****************************************************
 * Pour le tableau et le tas, j'ai bufferisé les 
 * allocations ( méthode trouvée sur internet) pour
 * éviter d'allouer de la place à chaque ajout de 
 * valeur. Pour cela, dans les deux cas (tab et heap)
 * j'aurais une structure composée d'une taille (le
 * nombre de valeurs dans la SD ), d'un pointeur sur
 * le tableau de valeurs, ainsi que d'une capacité
 * (qu'on initialise à une valeur et qu'on augmente 
 * ensuite) . Ainsi, c'est seulement lorsque la taille
 * est la même que la capacité que j'alloue de la
 * place à nouveau. Cela économise l'appel de la fonction
 * realloc
 *****************************************************/

//déclaration tableau vide
table *tabnouv(){
	table *tabnouv=(table*)malloc(sizeof(table));

	tabnouv->tab=(elmtpq*)malloc(nbelem*sizeof(elmtpq));

	tabnouv->capacity=nbelem;
	tabnouv->size=0;

	return tabnouv;
}


//reallocation de place quand on en a plus
table * realloctab(table *t){

	t->capacity+=10;
	t->tab=realloc(t->tab,t->capacity*sizeof(elmtpq));

	return t;
}


//insertion dans un tableau
table *insert_tab(table *t, elmtpq val){
	if (t->size >= t->capacity) t=realloctab(t); //si plus de place on reallou

	t->tab[t->size++]=val; //sinon jaugmente la taille et j'insère a la fin

	return t;
}

//init pour tous les noeuds
table *t_init_all(table *t, S val){
	elmtpq a;
	a.courant=val;
	a.antecedant=-1;
	a.priority=INF;
	a.fait=0;

	insert_tab(t,a);
	return t;
}

//init pour le noeud de depart
table *t_init_first(table *t, S val){
	elmtpq a;
	a.courant=val;
	a.antecedant=-1;
	a.priority=0;
	a.fait=0;

	insert_tab(t,a);
	return t;
}

//init tableau
table *init_table (Graphe g, S depart){
	Graphe tmp =g; //sauvegarde  du graphe
	table *t=tabnouv();

	while (tmp != NULL) { //tant qu'on est pas a la fin de la liste d adj
		if (tmp->vals != depart) t=t_init_all(t,tmp->vals);

		else t=t_init_first(t,tmp->vals);

		tmp=tmp->suiv;
	}
return t;
}

table *supr (table *t, int val){
	int i,j;

	//la taille du tab est plus petite de 1 vu qu'on supprime une val
	t->size--;

	//la valeur est forcément dedans donc pas de condition spécifique
	for (i=0;t->tab[i].priority != val; i++);

	//décalage des valeurs suivantes du tableau
	for (j=i;j<t->size;j++){
		t->tab[j]=t->tab[j+1];
	}

return t;
}

//select_min et le supprime
elmtpq mintab ( table *t){
	elmtpq min=t->tab[0]; //initialement on donne le premier elem comme le min

	int i;

	for (i=0;i<t->size;i++){

	//des qu'on trouve un element plus petit que le min, on redéfini le min
		if (min.priority>t->tab[i].priority) min=t->tab[i];
	}

	//la valeur du minimum est enregistrée dans min, on appelle suppr de t, min pour supprimer la valeur :) izi
	t=supr(t,min.priority);

	return min;
}

//teste si deux aretes sont identiques
bool samet (elmtpq a1, elmtpq a2){

	if ((a1.priority==a2.priority) && (a1.courant == a2.courant) && (a1.antecedant == a2.antecedant)) return true;

	else return false;
}

//recherche une valeur dans un tableau
elmtpq recht (table *t, S val){
	int i;
	elmtpq a;
	if(t->size==0){
		a.priority=-1;			 //donc je renvoie n'importe quoi
		a.courant=-1;
		a.antecedant=-1;
		}
	else {
	for(i=0;i != t->size-1 && t->tab[i].courant != val;i++);

	if (samet(t->tab[i],t->tab[t->size-1])) { //on est jamais dans ce cas logiquement,
		a.priority=-1;			 //donc je renvoie n'importe quoi
		a.courant=-1;
		a.antecedant=-1;
	}

	else a=t->tab[i];
	}
	return a;
}


//deacrease key
table *deacrease_keyt(table *t,S val, int nouv_poids, S nouv_antecedent){
	int i;

	for(i=0;i!=t->size-1 && t->tab[i].courant != val;i++);

	if (!samet(t->tab[i],t->tab[t->size-1])){ //si on a bien la val
		t->tab[i].priority=nouv_poids;	 //modifie le priority
		t->tab[i].antecedant=nouv_antecedent;//modifie l'antécédent
	}

return t;
}

//free tableau
void freetab(table *t){
	free(t->tab);
	free(t);
}

//
void affichage_table(table *t){
	int i=0;
	while(i<t->size){
		printf("Antecedant : %d priority : %d Valeur : %d\n",t->tab[i].antecedant,t->tab[i].priority,t->tab[i].courant);
		i++;
		}
}
