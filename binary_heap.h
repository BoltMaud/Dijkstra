#ifdef BH 

#define initialisation initialisation_h
#define minimum minh
#define recherche rech
#define deacreasekey dea_key_h

//renvoie l'indice du fils gauche selon l'indice du père
int indicefg(int cour);

//renvoie l'indice du fils droit selon l'indice du père
int indicefd(int cour);

//renvoie l'indice du père selon un fils qqcc
int indicepere(int cour);

//créer un tas vide
heap *create ();

//reallocation de la taille du tableau
heap * reallocheap(heap *h);

//insertion pas orgranisée
heap *insert_not_organized (heap *h, elmtpq val);

//percolate up : tri du tas
heap *percolate_up (heap *h);

//min des deux fils
int minfils (heap *h,int fd,int fg);

//min pointeur
//elmtpq *minp (elmtpq *fd, elmtpq *fg);

//percolate up pour une certaine valeur du tas
heap *percolate_up_val(heap *h, int pos);

//init organisée pour tous les noeuds
heap *init_all (heap *h, int val);

//init organisée pour le départ
heap *init_first (heap *h,int val);

//initialisation
heap *initialisation_h (Graphe g, S depart);

//supprime la premiere val du tas
heap *remove_first (heap *h);

//tamiser = remettre tout le tas en ordre
heap *tamiser (heap *h);

//renvoie l'arête minimum donc le sommet du tas et la supprime
elmtpq minh ( heap *h );

//renvoi un bool qui dit si les deux arêtes sont pareilles ou non
bool same (elmtpq a1, elmtpq a2);

//recherche une elmtpq dans un tab
elmtpq rech (heap *h, S val);

//suppression d'une arête
heap *supp(heap *h, elmtpq a);

//deacreasekey : remplace antecedant et priority
heap *dea_key_h(heap *h, S val , int priority, S antecedant);

//affichage debug
void affi_h(heap *h);

//libère le tas
void freeheap(heap *h);

#endif
