#ifndef LISTE
#define LISTE
/*
#define initialisation initialisationListe
#define minimum extract_min_liste
#define recherche recherche_Liste
#define deacreasekey dea_key_liste
*/
/**
*\file listechainee.c
*\author Mathilde BOLTENHAGEN
*/

/** -----------------FONCTIONS DE BASES -----------------**/

//renvoie null
Liste nouv();

/**
*\fn desallocation d'une liste
* specif :
* tant que non vide(l)
* desalloue(l), l->suiv
*/
//desalloue une liste
Liste desalloueliste(Liste l);

//affichage des aretes
void affichage_liste(Liste l);

/** -----------------INITIALISATION DIJKSTRA -------------------**/

//ajoute à la tete de la liste l'elmtpq d'courant 'val', d'antécedant -1 (pas d'antecedant), et de priority=INFINI
Liste adjt_init(Liste l, S val);

//ajoute à la tete l'elmtpq d'courant 'val', d'antecedant -1, priority =0
Liste adjt_init_depart(Liste l, S val);

/**
*\fn initialisation de la liste dijkstra
*\fn voir Liste adjt_init_depart(Liste l, S val) et Liste adjt_init(Liste l, S val)
*\brief on ajoute tous les sommets à la liste avec comme priorité INF sauf le depart à zero
* specif
* tant que non vide(g)
* 	si sommet de g= depart
		alors adjonction en tete du depart (c'est à dire avec priority =0)
	sinon adjonction en tete normale (priority = INF)
	fsi
  ftq
*/
//initialise la liste avec les INIFINI et le depart
Liste initialisationListe(Graphe g, S depart);

/**-----------------EXTRAIRE LE MINIMUM----------------**/


/**
*\fn extraire le minimum et le supprimer
* specif :
* extract_min_liste(adjt(nouv(),x)) = x;
* extract_min_liste(adjt(l,x))= min
	avec (l,min) = init (supt(l),x)
					ttq non vide(l)
					rep si tete(l)<min alors (supt(l), tete(l))
						sinon (supt(l),min)
					frep
*/
//renvoie l'elmtpq dont le priority et le mini en verfiant qu'il est encore dans g
elmtpq* extract_min_liste(Liste l/*,Graphe g*/);

/** --------------RECHERCHE DANS LA LISTE ----------**/

/**
*\fn recherche dans une liste un element
* specif :
* recherche_liste(nouv(),x)=null;
* recherche_liste(adjt(l,y),x)= si y==x alors y
								sinon recherche_liste(l,x)
								fsi
*/
//renvoie null si pas trouve
elmtpq* recherche_Liste(Liste l,S valeur);


/** ----------------MODIFICATION DE VALEURS------------**/

/**
*\fn modifier un element de PQ dans la liste
* specif:
* dea_key_liste(l,val,nouv_priority,nouv_antecedant)= l
		avec recherche_Liste(l,valeur)->priority=nouv_priority
		     recherche_liste(l,valeur)->antecedant=nouv_antecedant
*/
//modifie les valeurs de la liste
void dea_key_liste(Liste l, S valeur, int nouv_poids, S nouv_antecedant);


/** -----------fonction inutile, utilisé dans desg pour infixe -------------**/
/**
*\brief Quand je n'avais pas totalement bien compris le sujet, nous gardions le minimum et on le notait 'fait' =1 si le sommet avait déjà été calculé
* Pour trouver le minimum dans un AVL, j'avais donc du implémenter infixe et j'utilisais une pile (mais la structure etant la même que la liste, je n'avais
* pas refait de structure.
*/
//met a en tete de pile
Liste empiler(Liste l,elmtpq*a);

//supprime la tete de l
Liste depiler(Liste l);

#endif // LISTE_CHAINEE

