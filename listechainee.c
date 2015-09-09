#include "system.h"
/**
*\file listechainee.c
*\author Mathilde BOLTENHAGEN
*/

/** -----------------FONCTIONS DE BASES -----------------**/

Liste nouv(){
	return NULL;
	}

Liste desalloueliste(Liste l){
	Liste temp=l;
	Liste temp2;
	while(temp!=NULL){
		temp2=temp;
		temp=temp->suiv;
		free(temp2->a);
		free(temp2);
		}
		return NULL;
}

void affichage_liste(Liste l){
	Liste temp=l;
	while(temp!=NULL){
		printf("elmtpq : \n antecedant : %d, priority : %d, courant : %d\n",temp->a->antecedant,temp->a->priority,temp->a->courant);
		temp=temp->suiv;
		}
	}

/** -----------------INITIALISATION DIJKSTRA -------------------**/

Liste adjt_init(Liste l, S val){
	Liste lnouv= (Liste)malloc(sizeof(liste));
	elmtpq *pnouv=(elmtpq*)malloc(sizeof(elmtpq));
	pnouv->courant=val;
	pnouv->antecedant=-1;
	pnouv->priority =INF;
	pnouv->fait=0;
	lnouv->a=pnouv;
	lnouv->suiv=l;
	return lnouv;
	}

Liste adjt_init_depart(Liste l, S val){
	Liste lnouv=NULL;
	lnouv= (Liste)malloc(sizeof(liste));
	elmtpq *pnouv=(elmtpq*)malloc(sizeof(elmtpq));
	pnouv->courant=val;
	pnouv->antecedant=-1;
	pnouv->priority =0;
	pnouv->fait=0;
	lnouv->a=pnouv;
	lnouv->suiv=l;
	return lnouv;
	}

Liste initialisationListe(Graphe g, S depart){
	Graphe temp=g;//ne pas modifier l'adresse de g
	Liste l=nouv();//creation de la liste
	while(temp!=NULL){//tant qu'il y a des sommets
		if(temp->vals!=depart)l=adjt_init(l,temp->vals);// si c'est pas le depart
		else l=adjt_init_depart(l,temp->vals);//si c'est le depart
		temp=temp->suiv;//sommet suivant
	}
	return l;//liste remplie
}

/**-----------------EXTRAIRE LE MINIMUM----------------**/

//la fonction parait complexe car je n'ai pas fait de double chainage qui aurait été utile ici
elmtpq* extract_min_liste(Liste l){
	int a,b;
	Liste temp=l;
	a=temp->a->priority;
	elmtpq* ar;
	if(temp->suiv==NULL){//si c'est le dernier element restant de la liste
		ar=l->a;
		free(temp);
		l=NULL;
		}
	else {
		Liste temp2=temp->suiv;//permet d'avoir temp sur le precedant
		Liste tempreserve=NULL;//le temp prece du min
		while(temp2!=NULL){//tant qu'on a pas tout fait
			b=temp2->a->priority;//je note b la valeur du priority
			if(a>b){a=b; tempreserve=temp;}//et si b<a alors je garde b tempreserve c'est le temp d'avant b
			temp=temp->suiv;
			temp2=temp2->suiv;
		}
		if(tempreserve==NULL){//si le premier element est le min
			temp=l->suiv;
			ar=l->a;
			l->a=l->suiv->a;
			l->suiv=l->suiv->suiv;
			free(temp);
			}
		else {
			ar=tempreserve->suiv->a;
			temp=tempreserve->suiv;
			tempreserve->suiv=tempreserve->suiv->suiv;//on raccroche autour
			free(temp);
			}
		}
	return ar;
}

/** --------------RECHERCHE DANS LA LISTE ----------**/

elmtpq* recherche_Liste(Liste l,S valeur){
	Liste temp=l;
	while(temp!=NULL && temp->a->courant!=valeur){
		temp=temp->suiv;
	}
	if(temp==NULL)return NULL;
	else return temp->a;
	}

/** ----------------MODIFICATION DE VALEURS------------**/

void dea_key_liste(Liste l, S valeur, int nouv_priority, S nouv_antecedant){
	Liste temp=l;
	while(temp!=NULL && temp->a->courant!=valeur){//on cherche le bon sommet
		temp=temp->suiv;
	}
	if(temp!=NULL){//on verifie juste qu'on a le sommet
		temp->a->priority=nouv_priority;//modifie le priority
		temp->a->antecedant=nouv_antecedant;//modifie l'antecedant
		}
	}

/** -----------fonction inutile, utilisé dans desg pour infixe -------------**/

//juste utile comme pile pour desg
Liste empiler(Liste l,elmtpq*a){
	Liste lnouv= (Liste)malloc(sizeof(liste));
	lnouv->a=a;
	lnouv->suiv=l;
	return lnouv;
	}

//juste utile comme pile pour desg
Liste depiler(Liste l){
	Liste temp=l->suiv;
	free(l);
	return temp;
	}


