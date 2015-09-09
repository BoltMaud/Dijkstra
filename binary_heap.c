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
 ****************************************************/



/********FONCTIONS***********/
//fg(i)=position :2i+1
int indicefg (int cour){
	return 2*cour+1;
}


//fd(i)=position 2i+2
int indicefd (int cour){
	return 2*cour+2;
}


//position du père
int indicepere (int cour){
	if ((cour % 2 == 0) && (cour != 0)) return ((cour-2)/2);
	else if ((cour % 2 != 0) && (cour != 0)) return ((cour-1)/2);
	return -1;
}

//creation d'un tas vide
heap *create (){
	heap *heapnouv=(heap*)malloc(sizeof(heap));

	heapnouv->tab=malloc(nbelem*sizeof(elmtpq)); //taille max du tableau au départ
	heapnouv->capacity=nbelem;
	heapnouv->size=0; //taille remplie au départ : nulle

	return heapnouv;
}


//reallocation du tas
heap * reallocheap(heap *h){
	//int size=h->capacity+10;

	h->capacity+=10;
	h->tab=realloc(h->tab,h->capacity*sizeof(elmtpq));
	return h;
}


//insertion pas organisée : on insert à la première place libre sans tester si on a encore un tas
heap *insert_not_organized (heap *h, elmtpq val){
	if (h->size == h->capacity) h=reallocheap(h); // si plus de place, on en alloue

	h->tab[h->size++]=val;

	return h;
}


//percolate up pour la derniere valeure ajoutée
heap *percolate_up (heap *h){
	elmtpq tmp;

	int last = h->size-1;

	while(indicepere(last) >= 0){
		//si le pere est plus grand que le fils
		if (h->tab[indicepere(last)].priority > h->tab[last].priority ) {
			tmp=h->tab[indicepere(last)]; //on met la val du père ds un tmp
			h->tab[indicepere(last)]=h->tab[last]; //le pere devient le fils
			h->tab[last]=tmp; //le fils devient le tmp dc le père
		}

		last=last-indicepere(last)-1;
	}
	return h;
}

//min des deux fils
int minfils (heap *h, int fd, int fg){
	if (h->tab[fd].priority > h->tab[fg].priority) return fg; //priority de fg plus petit
	else return fd; //priority de fd plus pett
}

elmtpq *minp (elmtpq *fd, elmtpq *fg){
	if (fd->priority > fg->priority) return fg;
	else return fd;
}


heap *percolate_up_val(heap *h, int pos){
	int cour=pos;
	elmtpq tmp; //temporaire pour l'échange

	//tant que la valeur n'est pas a sa place
	while (h->tab[indicepere(cour)].priority > h->tab[cour].priority){
		//j'échange la valeur avec le pere
		tmp=h->tab[indicepere(cour)];
		h->tab[indicepere(cour)]=h->tab[cour];
		h->tab[cour]=tmp;
		//le courant devient celui qu'on a echangé et on recommence
		cour=indicepere(cour);
	}
return h;
}


//insertion organisée pour tous les noeuds
heap *init_all(heap *h, int val){
	elmtpq a;
	//definition de larete
	a.courant=val;
	a.antecedant=-1;
	a.priority=INF;

	//insertion dans le tas et remise en ordre
	insert_not_organized(h,a);
	percolate_up(h);

	return h;
}


heap *init_first(heap *h, int val){
	elmtpq a;

	a.courant=val;
	a.antecedant=-1;
	a.priority=0;

	insert_not_organized(h,a);
	percolate_up(h);

	return h;
}


//initialisation de départ
heap *initialisation_h (Graphe g, S depart){
	Graphe tmp=g;    //sauvegarde du graphe
	heap *h=create();//creation tas vide

	while(tmp != NULL){

		if(tmp->vals != depart) h=init_all(h,tmp->vals); //si on est pas au départ

		else h=init_first(h,tmp->vals); //sinon

		tmp=tmp->suiv; //on avance dans la liste d'adjacence
	}

return h;
}


heap *remove_first (heap *h){
	int j;
	//la taille du tab est plus petite de 1 vu qu'on supprime une val
	h->size--;

	//décalage des valeurs suivantes du tableau
	for (j=0;j<h->size;j++){
		h->tab[j]=h->tab[j+1];
	}
return h;
}

//tamiser : remetttre le tas en place
heap *tamiser (heap *h){
	int i,minf;

	for (i=0; indicefg(i)<h->size && indicefd(i)<h->size ;i++){

		//minf prend la valeur du plus petit des fils
		minf=minfils(h,indicefd(i),indicefg(i));

		//si le minimum des deux fils est plus petit, j'echange
		if( h->tab[minf].priority < h->tab[i].priority ){
			percolate_up_val(h,minf); //remonter la valeur
		}
	}
	return h;
}

//renvoie le minimum
elmtpq minh ( heap *h ){
	elmtpq min;
	//j'enregistre le min qi se trouve en première place
	min.priority=h->tab[0].priority;
	min.courant=h->tab[0].courant;
	min.antecedant=h->tab[0].antecedant;
	//j'enleve le premier
	remove_first(h);
	//je range les valeurs
	tamiser(h);
	//je renvoi le min
	return min;
}

//comparaison de deux arêtes
bool same (elmtpq a1, elmtpq a2){

	if ((a1.priority==a2.priority) && (a1.courant == a2.courant) && (a1.antecedant == a2.antecedant)) return true;

	else return false;
}

//recherche une valeur dans un tableau
elmtpq rech (heap *h, S val){
	int i;
	elmtpq a;

	if ( h->size <=0 ){
		a.priority =-1;
		a.courant = -1;
		a.antecedant = -1;
		}
	else{

		for(i=0;i != h->size-1 && h->tab[i].courant != val;i++);

		if (same(h->tab[i],h->tab[h->size-1])) { //on est jamais dans ce cas logiquement,
			a.priority=-1;			 //donc je renvoie n'importe quoi
			a.courant=-1;
			a.antecedant=-1;
		}

		else a=h->tab[i];
	}
		return a;
}


//deacrease key, va remplacer l'antécédent et le priority par des nouveaux si on trouve un chemin plus court
heap *dea_key_h(heap *h, S val, int priority, S antecedant){
	int i;
		
	for(i=0;i!=h->size && h->tab[i].courant != val;i++);

	if (!same(h->tab[i],h->tab[h->size-1])){
		h->tab[i].priority=priority;
		h->tab[i].antecedant=antecedant;
	}
	tamiser(h);
	return h;
}

//affichage debug
void affi_h(heap *h){
	int i;

	for(i=0;i<h->size;i++) printf("Antecedent: %d priority : %d Valeur : %d\n",h->tab[i].antecedant,h->tab[i].priority,h->tab[i].courant);
}

//free
void freeheap(heap *h){
	free(h->tab);
	free(h);
	}
