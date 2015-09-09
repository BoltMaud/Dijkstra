#ifndef AVL
#define AVL
/*
#define minimum min_arbre
#define recherche recherche_avl
#define deacreasekey dea_key_avl
*/
/**
*\author Mathilde BOLTENHAGEN
* pour les specifications, on supposera que :
* d(arbre) est le sous-arbre droit
* g(arbre) est le sous-arbre gauche
*/

/**----------------- FONCTIONS DE BASES -----------------**/
//renvoie null
Avl anouv();

//enracinement de deux arbres
Avl e(Avl ad, elmtpq* ar ,Avl ag);

//utilisee dans la hauteur
int max(int a , int b);

/**
*\param a : un arbre
* en specif :
* h(anouv())=-1
* h(e(a1,x,a2)=1+ max(h(a1),h(a2))
*/
int h(Avl a);

/**
*\fn insertion d'un element de priorité en fonction de la priorité
*\fn voir Avl equilibre(Avl a)
* specif :
* si vide(a) on creer
* si priorite inférieur alors
	equilibre(insertion(ar,g(a)))
  sinon equilibre(insertion(ar,d(a)))

  fsi
*/
Avl insertion(elmtpq *ar,Avl a);

//affichage d'un arbre
void affichage_avl(Avl arbre);

/** ------------ EQUILIBRE ----------**/

/**
*\fn rotation à droite
* specif :
* d(a)=g(d(a))
* g(d(a))=a
* renvoie d(a)
*/
Avl rot_droite(Avl arbre);

/**
*\fn rotation à gauche
* specif :
* g(a)=d(g(a))
* d(g(a))=a
* renvoie g(a)
*/
Avl rot_gauche (Avl arbre);

/**
*\fn equilibre de l'arbre present
* L'équilibre est à faire à chaque insertion
* L'équilibre est à faire au noeud de la supression
* specif:
* si h(g(a)) - h(d(a)) = 2 alors
	si h(g(g(a))<h(d(g(a))) alors
		rot_gauche(g(a))
	fsi
    rot_droite(a)
  sinon si h(g(a)) -h(d(a)) = -2 alors
	si h(g(d(a))<h(d(d(a))) alors
		rot_droite(d(a))
	fsi
  fsi
*/
Avl equilibre(Avl a);


/** ---------------- FONCTIONS POUR DIJKSTRA -----------**/

/**
*\fn initisalisation de l'avl
*\fn voir Avl insertion(elmtpq *ar,Avl a) et Avl anouv()
*\return l'avl rempli d'element de priorité avec INF pour tous sauf le depart (=0)
* specif :
  arbre=anouv()
  tant que non vide(g)
  	si le sommet de g == depart
  		alors elemt->priority = 0
  		sinon elemt->priority =INF
  	fsi
  	insertion(elemt, arbre)
   ftq
*/
Avl initialisationAvl(Graphe g,S depart);

/**
*\fn recherche d'un elemt dans un avl
*\brief ici on ne cherche pas en fonction de la priorité,
		donc la recherche se fait sur tout l'arbre
* specif :
* si vide(a) alors null
* sinon
* 	si val = etiquette(a) alors val
		sinon si (recherche_avl(g(a),val)==NULL
				alors recherche_avl(d(a),val)
				fsi
		fsi
	fsi
*fsi
*/
//renvoie un element de priorité
elmtpq* recherche_avl(Avl a,S valeur);
//renvoie le sous arbre de l'elemt de priorité
Avl rech_sous_avl(Avl a,S valeur);

/**
*\fn minimum d'un arbre
*  condition : arbre non vide
* c'est l'élement le plus à gauche
* specif :
* tant que non vide (g(arbre))
* 	arbre=g(arbre)
  ftq
*/
//donne la feuille à gauche
Avl min_arbre (Avl arbre);

/**
*\fn maximum d'un arbre
* condition : arbre non vide
* c'est l'élement le plus à droite
* specif :
* tant que non vide (d(arbre))
* 	arbre=d(arbre)
  ftq
*/
//donne la feuille à droite
Avl max_arbre(Avl arbre);

/**
*\fn extraire le minimum d'un arbre, cette fonction ne le supprime pas
* car ma suppression ne marche pas totalement bien
*\return l'element prioritaire
* specif :
*  tant que non vide (g(arbre))
* 	arbre=g(arbre)
  ftq
*/
elmtpq * extract_min_avl(Avl arbre);


/**
*\fn suppression d'un element dans l'avl
* condition : valeur appartient à l'arbre
* suppression(e(anouv(),x,anouv(),x))= anouv();
* suppression(e(a1,x,a2),y)=arbre
* 	avec si (recherche_avl(arbre,y)=arbre_de_y) est une feuille
				alors arbre_de_y=anouv()
				sinon si non vide (g(arbre_de_y))
							alors avec maxi=max_avl(g(arbre_de_y))
										arbre_de_y->elemt = maxi->elemt
										maxi=anouv();
							sinon avec mini=min_avl(d(arbre_de_y))
										arbre_de_y->elemt = mini->elemt
										mini=anouv();
							fsi
					tant que non vide (arbre_de_y)
							equilibre(arbre_de_y)
							arbre_de_y=arbre_de_y->pere
					ftq
				fsi
*/
//suppression d'une valeur dans l'arbre
//C'est cette fonction qui ne marche pas
Avl suppression(Avl arbre, S valeur);

/**
*\fn modification d'une valeur dans l'avl
* j'ai choisit de supprimer la valeur et la réinsérer
*\fn voir Avl suppression(Avl arbre, S valeur) et Avl insertion(elmtpq *ar,Avl a)
* condition : la valeur doit être dans l'arbre
* specif :
* supression(arbre,valeur) , inverstion(arbre,nouvelle)
*/
Avl dea_key_avl(Avl arbre, S valeur, int nouv_poids, S nouv_antecedant);



/**---------------------FONCTIONS SUPLEMENTAIRES ----------**/

/**
* Au debut de notre projet, je n'avais pas compris qu'il fallait supprimer les minimums.
* Ainsi, comme l'algorithme de Dijkstra le dit, je notais 'fait' =1 les minimums que j'avais déjà etudié
* Le minimum que l'on cherchait devait avoir un fait= 0
* Dans un avl, cette demarche implique l'utilisation de infixe que j'ai décidé de vous laisser
*/
//descente a gauche en empilant la racine
Liste desg (Avl a,Liste p);

//infixe c'est enfait min
elmtpq *infixe(Avl a);


#endif // binary_search_tree
