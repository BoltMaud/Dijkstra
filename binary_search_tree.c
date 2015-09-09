#include "system.h"
/**
*\author Mathilde BOLTENHAGEN
* les descriptions/spécifications des fonctions sont dans binary_search_tree.h
*/

/**----------------- FONCTIONS DE BASES -----------------**/
/*
Avl anouv(){
	return NULL;
	}

int max(int a , int b){
  if (a<b) return b;
  else return a;
}

int h(Avl a){
  if (a==NULL) return -1;
  else return 1+ max(h(a->ag),h(a->ad));
}

Avl e(Avl ag, elmtpq* ar ,Avl ad){
	Avl nouv=(Avl)malloc(sizeof(strAvl));
	nouv->elemt=ar;
	nouv->ad=ad;
	nouv->ag=ag;
	if(ad!=NULL)ad->pere=nouv;
	if(ag!=NULL)ag->pere=nouv;
	nouv->pere =NULL;
	return nouv;
}

Avl insertion(elmtpq *ar,Avl a){
	if(a==NULL){//si c'est nul on creé
		return a= e(anouv(),ar,anouv());
		}
	else {//si arbre non null
		if(ar->priority<=a->elemt->priority){//si elmtpq est infe au priority de arbre
			return a=equilibre(e(insertion(ar,a->ag),a->elemt,a->ad));//on insert à gauche
		}
		else {//si elmtpq sup au priority de arbre
				return a=equilibre(e(a->ag,a->elemt,insertion(ar,a->ad)));//on insert à droite
			}

		}
	}

void affichage_avl(Avl arbre){

	if(arbre !=NULL){
	printf("elmtpq : \n");
	printf("antecedant : %d | priority %d | valeur : %d  " ,arbre->elemt->antecedant,arbre->elemt->priority,arbre->elemt->courant);
	if(arbre->ag!=NULL)printf("(ag %d ) ",arbre->ag->elemt->courant);
	if(arbre->ad!=NULL)printf("( ad %d )",arbre->ad->elemt->courant);
	printf("\n");
	affichage_avl(arbre->ag);
	affichage_avl(arbre->ad);
	}
}

** ------------ EQUILIBRE ----------*
//pour un deseq à gauche
Avl rot_droite(Avl arbre){
	Avl b=arbre->ag;
	arbre->ag=b->ad;
	if(arbre->ag!=NULL)
	arbre->ag->pere=arbre;
	b->ad=arbre;
	b->pere=NULL;
	b->ad->pere=b;
	arbre=b;
	return arbre;
	}

//deseq droite
Avl rot_gauche (Avl arbre){
	Avl b=arbre->ad;
	arbre->ad=b->ag;
	if(arbre->ad!=NULL)
	arbre->ad->pere=arbre;
	b->ag=arbre;
	b->pere=NULL;
	b->ag->pere=b;
	arbre=b;
	return arbre;
	}

Avl equilibre(Avl a){
	if(a!=NULL){//dans presque tous les cas
		int difference=h(a->ag)-h(a->ad);
		if(difference==2){
			if(h(a->ag->ag)<h(a->ag->ad)){
				a->ag=rot_gauche(a->ag);
				}
			a=rot_droite(a);
		}
	else {
			if(difference==-2){
				if(h(a->ad->ag)>h(a->ad->ad)){
				a->ad=rot_droite(a->ad);
				}
			a=rot_gauche(a);
			}
		}
	return a;
	}
	else return NULL;//normalement jamais utilisé
}

* ---------------- FONCTIONS POUR DIJKSTRA -----------**

Avl initialisationAvl(Graphe g,S depart){
	Graphe temp=g;//ne pas modifier l'adresse de g
	Avl a=anouv();//creation de l'AVL
	while(temp!=NULL){//tant qu'il y a des sommets
		if(temp->vals!=depart){// si c'est pas le antecedant
			elmtpq*ar=(elmtpq*)malloc(sizeof(elmtpq));
			ar->priority=INF;
			ar->antecedant=-1;
			ar->fait=0;
			ar->courant=temp->vals;
			a=insertion(ar,a);
		//	a=equilibre(a);
		}
		else {//sinon
			elmtpq*ar=(elmtpq*)malloc(sizeof(elmtpq));
			ar->priority=0;
			ar->antecedant=-1;
			ar->courant=temp->vals;
			ar->fait=0;
			a=insertion(ar,a);
		//	a=equilibre(a);
		}
		temp=temp->suiv;//sommet suivant
	}
	return a;//liste remplie
}

elmtpq* recherche_avl(Avl a,S valeur){
	if(a==NULL)return NULL;
	if(a->elemt->courant==valeur)
		return a->elemt;
	elmtpq* r;
	if((r=recherche_avl(a->ag,valeur))!=NULL)
		return r;
	else return recherche_avl(a->ad,valeur);
	}

Avl rech_sous_avl(Avl a,S valeur){
	if(a==NULL)return NULL;
	if(a->elemt->courant==valeur)
		return a;
	Avl b=NULL;
	if((b=rech_sous_avl(a->ag,valeur))!=NULL)
		return b;
	else return rech_sous_avl(a->ad,valeur);
	}


//arbre non null
Avl max_arbre(Avl arbre){
	Avl temp=arbre;
	while(temp->ad!=NULL){
		temp=temp->ad;
		}
	return temp;
}


Avl min_arbre (Avl arbre){
	Avl temp=arbre;
	while(temp->ag!=NULL){
		temp=temp->ag;
		}
	return temp;
	}


elmtpq * extract_min_avl(Avl arbre){
	Avl temp=arbre;
	elmtpq *ar=(elmtpq*)malloc(sizeof(elmtpq));
	while(temp->ag!=NULL){
		temp=temp->ag;
		}
	ar->priority=temp->elemt->priority;
	ar->courant=temp->elemt->courant;
	ar->antecedant=temp->elemt->antecedant;
	return ar;
	}

//condition valeur appartient à arbre
Avl suppression(Avl arbre, S valeur){
	//affichage_avl(arbre);
	if(arbre->ag==NULL && arbre->ad==NULL){//si c'est une feuille
		free(arbre);
		return NULL ;//on renvoie arbre vide
	}
	else {//au moins deux noeuds

		//1ere partie: remplacer arbre de 'valeur'
		Avl arbre_valeur = rech_sous_avl(arbre,valeur);// on cherche le sous arbre de 'valeur'
		//fprintf(stderr," arbre_valeur : %d",arbre_valeur->elemt->courant);
		//3 CAS:
			//1er cas : arbre_valeur == feuille
			if(arbre_valeur->ad ==NULL && arbre_valeur->ag==NULL){
				if(arbre_valeur->pere->ad==arbre_valeur) //si il est à droite de son père
					arbre_valeur->pere->ad=NULL;
				else arbre_valeur->pere->ag=NULL;
				free(arbre_valeur->elemt);//free de l'elmtpq
				free(arbre_valeur);

					}
			else {
			//2nd cas : il y a un fils à gauche (au moins)
			//fprintf(stderr,"oui j'ai un pere %d\n",arbre->pere->elemt->courant);
				Avl temparbre;
				if(arbre_valeur->ag!=NULL){
					Avl arbre_remplace = max_arbre(arbre_valeur->ag);// on cherche le maximum à gauche de 'valeur'
					//fprintf(stderr," arbre_remplace : %d",arbre_remplace->elemt->courant);
					elmtpq * temp=arbre_valeur->elemt;
					arbre_valeur->elemt=arbre_remplace->elemt;//on remplace l'elmtpq
					free(temp);//suppression de l'ancienne valeur de l'elmtpq
					temparbre=arbre_remplace->pere;
					if (arbre_valeur->ag!=arbre_remplace)arbre_remplace->pere->ad=anouv();//comme on va suppr cet arbre, on met null à gauche du père
					else arbre_remplace->pere->ag=anouv();
					free(arbre_remplace);
				}
			//3eme cas : il n'a qu'un fils droit
				else {
					Avl arbre_remplace = min_arbre(arbre_valeur->ad);// on cherche le min à droite
					//fprintf(stderr,"voici arbre_remplace : %d",arbre_remplace->elemt->courant);
					elmtpq * temp=arbre_valeur->elemt;
					arbre_valeur->elemt=arbre_remplace->elemt;//on remplace l'elmtpq
					free(temp);//suppression de l'ancienne valeur de l'elmtpq
					temparbre=arbre_remplace->pere;
					if (arbre_valeur->ad!=arbre_remplace)arbre_remplace->pere->ag=anouv();//comme on va suppr cet arbre, on met null à gauche du père
					else arbre_remplace->pere->ad=anouv();
					free(arbre_remplace);

					}
					//affichage_avl(arbre);

		//2eme partie : reequilibrer l'arbre
			//temparbre=equilibre(temparbre);
			while(temparbre!=NULL){
				temparbre=equilibre(temparbre);
				temparbre=temparbre->pere;
				}
			}

	return arbre;
	}
}

Avl dea_key_avl(Avl arbre, S valeur, int nouv_poids, S nouv_antecedant){
	arbre=suppression(arbre,valeur);//on supprime l'ancienne
	elmtpq *nouvelle=(elmtpq*)malloc(sizeof(elmtpq));
	nouvelle->priority=nouv_poids;
	nouvelle->antecedant=nouv_antecedant;
	nouvelle->courant=valeur;
	arbre=insertion(nouvelle,arbre);
	return arbre;
	}

**---------------------FONCTIONS SUPLEMENTAIRES ----------**
Liste desg (Avl a,Liste p){
	Avl temp=a;
	while(temp!=NULL){
		p=empiler(p,temp->elemt);
		temp=temp->ag;
		}
	return p;
}

elmtpq *infixe(Avl a){
	Avl temp=a;
	Liste p=nouv();
	p=desg(temp,p);
	int continuer=1;
	elmtpq *ar=NULL;
	while(p!=NULL&&continuer){
		//printf("%d\n",p->elemt->courant);
		ar=p->a;//pas sure
		if(ar->fait==0)continuer=0;
		else {
			temp=rech_sous_avl(a,ar->courant);
			p=desg(temp->ad,depiler(p));
		}
	}
	return ar;
}*/
