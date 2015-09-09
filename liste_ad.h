#ifndef LISTE_ADJ
#define LISTE_ADJ

/**
*\file listechainee.c
*\author Mathilde BOLTENHAGEN
*/

/** ------------ FONCTION DE BASE --------- **/
//renvoie NULL
Graphe graphenouv();

/**
* dans cette initialisation, je crée un premier successeur de valeur -1
* cette méthode permet de ne pas perdre l'adresse de la liste lors d'une suppression
*/
ListeArc listenouv();

//desalloue le graphe
Graphe desalloue(Graphe g);

//affichage simple du graphe
void affichage (Graphe g);

/** ------- CONSTRUCTION D'UN GRAPHE ------**/

/**
*\param l : la liste des successeurs d'un sommet
*\param val : un nouveau successeur de ce sommet
*\param poids : la distance de ce successeur avec le sommet
*/
ListeArc inserl(ListeArc l, S val, int poids);


/**
*\param g : un graphe (ou liste de sommets)
*\param val : le nom de la nouvelle etiquette
*\param Lista : la liste des successeurs de ce sommet
*/
Graphe insersom(Graphe g, S val, ListeArc Lista);

/** ------------NOS GRAPHES ALEATOIRES ---------------------**/

/**
*\param max : le nombre de sommet (multiple de 10)
*\return un graphe aleatoire
* Cette fonction se divise en deux parties :
* ---- 1ere partie : j'initialise un petit graphe pas très aléatoire
* -----2eme partie : j'ai décidé de créer deux fois plus d'arete que de points
*-------------------- tant qu'on n'a pas créé autant d'arete que voulu on demande une arete aleatoire
*-------------------- si le sommet existe on rajoute que le successeur
* ------------------- sinon on crée le sommet et la liste des successeurs
* ------------------- ensuite, on crée l'arete inverse
*\fn voir les fonctions :  petit_graphe(Graphe g, int max) et  aleat_arete(int max)
*/
Graphe remplissage(int max);

/**
*\param g : graphe nul
*\param max : borne au valeur des sommets
* Dans cette fonction, j'ai choisit de faire un petit graphe tel que :
* 1 soit accroché à un quelconque point
* 4 autres aretes de bases tel que les sommets sont peu aléatoires
*/
Graphe petit_graphe(Graphe g, int max);


/**
*\param max : borne à l'aléatoire des sommets
*\return un tableau de trois entiers :
* - le sommet
* - son successeur
* - le poids de l'arete (entre 1 et 100)
*/
int* aleat_arete(int max);

/** ------------------FONCTIONS POURS DIJKSTRA ----------------------**/

/**
*\param val : le sommet qu'on veut supprimer
*/
Graphe suppression_sommet(Graphe g,S val);

/**
* Cette fonction est utile dans dijkstra lorsqu'on veut connaitre les poids des aretes
*/
Graphe recherche_graphe(Graphe g, S val);


/**
* Cette fonction est malheureusement obligatoire puisque notre dijkstra détruit le graphe
* avec la fonction suppression.
* Nous avons été obligée de faire ainsi car nos SD (la liste, comme le tableau, le tas et l'avl), une fois vide indiquait qu'ils ne l'étaient pas
* On pouvait alors afficher des valeurs absoluments inconnues alors que nos fonctions demandaient qu'elle soit = NULL ..
*/
Graphe copiage(Graphe g);

#endif // LISTE_ADJ

