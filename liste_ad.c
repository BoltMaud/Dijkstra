#include "system.h"

/**
*\file listechainee.c
*\author Mathilde BOLTENHAGEN
* les descriptions des fonctions sont dans list_ad.h
*/

/** ------------ FONCTION DE BASE --------- **/
Graphe graphenouv(){
	return NULL;
	}

ListeArc listenouv(){
	ListeArc nouv=(ListeArc)malloc(sizeof(strArc));
	nouv->poids=-1;
	nouv->vals=-1;
	nouv->succ=NULL;
	return nouv;
	}
void affichage (Graphe g){
	Graphe temp=g;
	while(temp!=NULL){
		ListeArc templ=temp->ls->succ;
		while(templ!=NULL){
			printf("S : %d ",temp->vals);
			printf("%d %d \n",templ->vals,templ->poids);
			templ=templ->succ;
			}
		printf("\n");
		temp=temp->suiv;
	}
}

Graphe desalloue(Graphe g){
	Graphe temp=g;
	Graphe temp2;
	while(temp!=NULL){
		ListeArc templ=temp->ls;
		ListeArc templ2;
		while(templ!=NULL){
			templ2=templ->succ;
			free(templ);
			templ=templ2;
			}
		temp2=temp->suiv;
		free(temp);
		temp=temp2;
	}
	return NULL;
	}

/** ------- CONSTRUCTION D'UN GRAPHE ------**/

ListeArc inserl(ListeArc l, S val, int poids){
	ListeArc nouv=(ListeArc)malloc(sizeof(strArc));
	nouv->poids=poids;
	nouv->vals=val;
	ListeArc temp=l;
	while(temp->succ!=NULL && temp->succ->vals<val){
		temp=temp->succ;
		}
	if(temp->succ!=NULL && temp->succ->vals==val){
		free(nouv);
		}
	else {
		if (temp->succ!=NULL){
			ListeArc temp2=temp->succ;
			temp->succ=nouv;
			nouv->succ=temp2;
		}
		else {
			temp->succ=nouv;
			nouv->succ=NULL;
		}
	}
	return l;
}

Graphe insersom(Graphe g, S val, ListeArc Lista){
	Graphe nouv=(Graphe)malloc(sizeof(strSom));
	nouv->vals=val;
	nouv->ls=Lista;
	Graphe temp=g;
	if(g==NULL){
		nouv->suiv=NULL;
		return nouv;}
	else {
		if(val<temp->vals){
			nouv->suiv=temp;
			 return nouv;
			}
		else {
			while(temp->suiv!=NULL &&temp->suiv->vals<val){
				temp=temp->suiv;
				}
				if(temp->suiv!=NULL){
					Graphe temp2=temp->suiv;
					temp->suiv=nouv;
					nouv->suiv=temp2;
					}
				else {
					temp->suiv=nouv;
					nouv->suiv=NULL;
				}
		return g;
	}
}
}

/** ------------NOS GRAPHES ALEATOIRES ---------------------**/

//max multiple de 10
Graphe remplissage(int max){
	Graphe g=graphenouv();
	int *tab=NULL;//une elmtpq
	Graphe temp;
	g=petit_graphe(g,max);//Attention condition sur petit graphe
	int i=1;
        while(i<(max*2)){
        	tab=aleat_arete(max);
        	temp=g;
			//ARRETE DANS LE BON SENS
		while(temp->vals!=tab[0] &&temp->suiv!=NULL){// si on trouve pas le sommet ET si on est pas au bout des sommets
				temp=temp->suiv;// alors on cherche le sommet dans le graphe
				}
			if(temp->vals==tab[0]){// si on a trouve le sommet alors on insere
				temp->ls=inserl(temp->ls,tab[1],tab[2]);
				}
			else {
				ListeArc l=listenouv();
				l=inserl(l,tab[1],tab[2]);
				g=insersom(g,tab[0],l);
			}
		//ARRETE INVERSE
		/*if(tab[1]<tab[0])*/temp=g;
		while(temp->vals!=tab[1] &&temp->suiv!=NULL){// si on trouve pas le sommet ET si on est pas au bout des sommets
				temp=temp->suiv;// alors on cherche le sommet dans le graphe
				}
			if( temp->vals==tab[1]){// si on a trouve le sommet alors on insere
				temp->ls=inserl(temp->ls,tab[0],tab[2]);
				}
			else {//Le cas où le sommet est pas dans le graphe
				ListeArc l=listenouv();
				l=inserl(l,tab[0],tab[2]);
				g=insersom(g,tab[1],l);
			}
		free(tab);
		i++;
        }
return g;
}

int* aleat_arete(int max){
	int *tab=(int*)malloc(3*sizeof(int));
	tab [2]=((int)rand()%100)+1;
	tab[0] =((int)rand()%max)+1;
	tab[1]=((int)rand()%max)+1;
	if(tab[1]==tab[0]) tab[1]=((int)rand()%max)+1;
	return tab;
	}


//max >20 et max multiple de 10
Graphe petit_graphe(Graphe g, int max){
	//on va creer quelques points de bases liées
	int i=1;
	while(i<(max-(max/10))){// pour 600 on s'arretera à i < 540
		int d;
   		d=((int)rand()%100)+1;//les distances entre les points seront de 1 à 10
   		int s=i+(max/10);//succ 1/10 plus loin
   		//DANS UN SENS
		ListeArc l=listenouv();
		l=inserl(l,s,d);
		g=insersom(g,i,l);
		//DANS L'AUTRE
		l=listenouv();
		l=inserl(l,i,d);
		g=insersom(g,s,l);
		i=i+max/5;
		}
	return g;
	}

/** ------------------FONCTIONS POURS DIJKSTRA ----------------------**/

Graphe suppression_sommet(Graphe g,S val){
	Graphe temp=g;
	ListeArc tempa;
	ListeArc tempab;
	if(g->vals==val){//si c'est le premier sommet
		tempa=g->ls;//on met un pointeur sur la liste
		while(tempa!=NULL){
			tempab=tempa->succ;//on garde les suivants
			free(tempa);//on free en ce moment
			tempa=tempab;//on va au suivant
			}
		g=g->suiv;//on dit que g est le suivant
		free(temp);
	}
	else {
		while(temp->suiv!=NULL && temp->suiv->vals!=val){//tant qu'on est pas au bon sommet
			temp=temp->suiv;
			}
		if(temp->suiv!=NULL){//si le suivant = val ça veut dire quee c'est pas le dernier
			tempa=temp->suiv->ls;//on supprime la liste
			while(tempa!=NULL){
				tempab=tempa->succ;
				free(tempa);
				tempa=tempab;
			}
			free(tempa);
			Graphe temp2=temp->suiv->suiv;//on enregistre le suiv du suiv
			free(temp->suiv);
			temp->suiv=temp2;
			}
	}
	return g;
}

Graphe recherche_graphe(Graphe g, S val){
	Graphe temp=g;
	while(temp!=NULL && temp->vals!=val ){
		temp=temp->suiv;
		}
	return temp;
}

Graphe copiage(Graphe g){
	Graphe copie=graphenouv();
	Graphe temp=g;
	while(temp!=NULL){
		ListeArc copiel=listenouv();
		ListeArc templ=temp->ls->succ;
		while(templ!=NULL){
			copiel=inserl(copiel,templ->vals,templ->poids);
			templ=templ->succ;
			}
		copie=insersom(copie,temp->vals,copiel);
		temp=temp->suiv;
	}
	return copie;
}


