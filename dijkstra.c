#include "system.h"

/**
*\author Laurine Huber
*\author Mathilde Boltenhagen
*/

void dijkstra_gen (Graphe g, S depart, S arrivee){
	#if defined (TAB) //si on est dans le cas tableau a la compilation
	table *pq=init_table(g,depart);
	#elif defined (BH) //si on est dans le cas binary heap a la compilation
	heap *pq=initialisation_h(g,depart);
	#endif
	S n,i;
//	affih_
	int tab_ante[MAXI];
	int tab_poids[MAXI];

	while(g!=NULL){
		elmtpq a1=minimum(pq);
		tab_ante[a1.courant]=a1.antecedant;
		tab_poids[a1.courant]=a1.priority;
	//	fprintf(stderr,"Alors on a : %d\n ",a1.arrivee);
		n=a1.courant;
		ListeArc succ_n=recherche_graphe(g,n)->ls->succ;

		while (succ_n != NULL ){
			elmtpq a2=recherche(pq,succ_n->vals);

			if(a2.priority != -1 && (a1.priority + succ_n->poids) < a2.priority){
				pq=deacreasekey(pq,succ_n->vals,a1.priority+succ_n->poids,n);
				}

			succ_n=succ_n->succ;
		}
		g=suppression_sommet(g,n);// on supprime toutes les arretes partant de n
	}
	i=arrivee;
	printf("ITINERAIRE : [ ");

	while(tab_ante[i]!=-1){
		//printf("[ %d | distance à %d : %d ]\n",i,depart,tab_poids[i]);
		printf(" %d --",i);
		i=tab_ante[i];
	}
	printf(" %d ]",depart);
	printf("\n \n DISTANCE DE %d à %d : %d \n",depart,arrivee,tab_poids[arrivee]);
}


void dijkstra_Liste (Graphe g, S depart, S arrivee){
	Liste l=initialisationListe(g,depart);//INF partout sauf au depart
	S n;
	//int continuer=1;// pas obligatoire
	int tab_ante[MAXI];
	int tab_poids[MAXI];//on charge à la ieme place le sommet i

	// DEBUT DE LA BOUCLE-------------------------------------------------------
	while(g!=NULL ){ //FAIRE toutes les arêtes ou être ARRIVE
		elmtpq* a1=extract_min_liste(l);//on donne le minimum de l'arbre et on le supprime de l'arbre

		//-----on remplit les tableaux
		tab_ante[a1->courant]=a1->antecedant;
		tab_poids[a1->courant]=a1->priority;

		n=a1->courant;
		ListeArc succ_n=recherche_graphe(g,n)->ls->succ;//ON CHERCHE LES SUCCESSEURS (l ->suiv est normal)
		while(succ_n!=NULL){//tant qu'il y a des successeurs à n
			elmtpq* a2=recherche_Liste(l,succ_n->vals);//etiquette du succ dans notre SD
			if ( a2!=NULL && (a1->priority+succ_n->poids) < a2->priority ){//soit a2 est déjà sorti de la liste soit le priority est inf sinon on rentre dans le IF
				dea_key_liste(l,succ_n->vals,a1->priority+succ_n->poids,n);// dea_key(arbre,val_clé,nouveau_poids,nouvel antecedant/antecedant);
				}
			succ_n=succ_n->succ;//SUCCESSEUR SUIVANT
		}
//	if(a1->courant == courant)continuer =0;//on peut arreter quand on a trouvé l'courant.
	g=suppression_sommet(g,n);// on supprime toutes les arretes partant de n
	free(a1);
	//affichage(g);
	}

	//---ALGO FINI, AFFICHAGE DES RESULTATS-------------------------------------
	S i=arrivee;
	printf("ITINERAIRE : [ ");
	while(tab_ante[i]!=-1){
		//printf("[ %d | distance à %d : %d ]\n",i,depart,tab_poids[i]);
		printf(" %d --",i);
		i=tab_ante[i];
	}
	printf(" %d ]",depart);
	printf("\n \n DISTANCE DE %d à %d : %d \n",depart,arrivee,tab_poids[arrivee]);

}


/*
void dijkstra_Avl (Graphe g, S depart, S arrivee){
	Avl l=initialisationAvl(g,depart);// une fonction pour chaque SD qui rempli l'arbre avec des priority =inf pour tous sauf depart=0
	S n;
	//int continuer=1;// pas obligatoire
	int tab_ante[MAXI];
	int tab_poids[MAXI];//on charge à la ieme place le sommet i

	// DEBUT DE LA BOUCLE-------------------------------------------------------
	while(g!=NULL && l!=NULL){ //FAIRE toutes les arêtes ou être ARRIVE
		//affichage_avl(l);
		elmtpq* a1=extract_min_avl(l);//on donne le minimum de l'arbre et on le supprime de l'arbre
		l=suppression(l,a1->courant);
		//affichage(g);
		//printf("%d %d\n",a1->priority,a1->courant);

		//-----on remplit les tableaux
		tab_ante[a1->courant]=a1->antecedant;
		tab_poids[a1->courant]=a1->priority;

		n=a1->courant;
		//fprintf(stderr,"oui");
		ListeArc succ_n=recherche_graphe(g,n)->ls->succ;//ON CHERCHE LES SUCCESSEURS (l ->suiv est normal)
		while(succ_n!=NULL){//tant qu'il y a des successeurs à n
			affichage_avl(l);
			fprintf(stderr,"on veut chercher %d",succ_n->vals);
			elmtpq* a2=recherche_avl(l,succ_n->vals);//etiquette du succ dans notre SD
			if ( a2!=NULL && (a1->priority+succ_n->poids) < a2->priority ){
				fprintf(stderr,"oui");//soit a2 est déjà sorti de la liste soit le priority est inf sinon on rentre dans le IF
				l=dea_key_avl(l,succ_n->vals,a1->priority+succ_n->poids,n);// dea_key(arbre,val_clé,nouveau_poids,nouvel antecedant/depart);
				}
			succ_n=succ_n->succ;//SUCCESSEUR SUIVANT
		}
	//if(a1->courant == courant)continuer =0;//on peut arreter quand on a trouvé l'courant.
	free(a1);
	g=suppression_sommet(g,n);// on supprime toutes les arretes partant de n
	}

	//---ALGO FINI, AFFICHAGE DES RESULTATS-------------------------------------
	S i=arrivee;
	printf("ITINERAIRE : [ ");
	while(tab_ante[i]!=-1){
		//printf("[ %d | distance à %d : %d ]\n",i,depart,tab_poids[i]);
		printf(" %d --",i);
		i=tab_ante[i];
	}
	printf(" %d ]",depart);
	printf("\n \n DISTANCE DE %d à %d : %d \n",depart,arrivee,tab_poids[arrivee]);
}
*/
