/********************************************
 * Le fichier system.h à été créé dans le but 
 * de regrouper les includes, les definitions
 * préprocesseurs, et les grandes structures 
 * du programme. Chaque fichier inclue system.h
 ********************************************/

#ifndef __SYSTEM_H
#define __SYSTEM_H

// LIBS C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

//Définitions pré processeur
#define nbelem 2
#define S int
#define MAX 8
#define INF 9999
#define MAXI 1000

//Structures
typedef enum {false,true} bool;

//structure d'une arête
typedef struct strPq{
	S antecedant; //antecedant de l'arête => je préférerai l'appelé antecédant
	int priority;  //priority sur l'arête
	S courant;//arrivée de l'arête, lieu que l'on étudie je préférerai l'apppeler n
	int fait; // 0 si pas passer, 1 sinon
	} elmtpq;

//structure liste
typedef struct strliste{
	elmtpq *a;
	struct strliste *suiv;
	}liste, *Liste;

//structure d'un tas binaire
typedef struct heap{
	int capacity;  //capacité max
	int size;      //taille courante du tableau
	elmtpq *tab;    //pointeur sur le tableau d'arêtes
	} heap;

//structure tableau
typedef struct table{
	int capacity;
	int size;
	elmtpq *tab; // pointeur sur le tableau
	} table;

//Structure de la liste des arcs avec le poids
//ATTENTION ici il y aura toujours la premiere valeur qu'il faut pas lire !! (question d'adressage)
typedef struct strArc {
	S vals;//valeur du sommet
	int poids;//poids entre le sommet et le précédeur (voir dans Graphe)
	struct strArc *succ;//successeur
}strArc, *ListeArc;


//Structure d'un graphe sous forme de liste de sommet
typedef struct strSom {
	S vals;//sommet du graphe
	ListeArc ls;//liste des sommets
	struct strSom *suiv;//suite des sommets
}strSom, *Graphe;

//Structure arbres de recherche binaires
typedef struct sAvl {
	elmtpq *elemt; //
	struct sAvl* ad;//arbre droit
	struct sAvl* ag;//arbre gauche
	struct sAvl* pere;
	} strAvl, * Avl;


/*POUR CHAQUE SD il faut faire :

SD extract_min(SD a,Graphe g);
qui renvoie le mini de a qui existe encore dans g, pour ça la fonction recherche_graphe renvoie null s'il existe plus dans g

fonction qui remplie notre SD avec des priority INFINIS, pas d'antécédants pour tout le monde et priority=0 pour depart

SD recherche_SD(SD arbre,S valeur);
fonction qui renvoie le sous-arbre à partir de S (SD veut dire qu'on renvoit un type de chaque structure diff)

void dea_key(SD arbre, S valeur, nouveau priority, nouvel antecedant)
on modifie notre structure de donnée
ATTENTION cette fonction fait parfois tout bouger

*/

//Tous les headers
#include "binary_heap.h"
#include "liste_ad.h"
#include "listechainee.h"
#include "dijkstra.h"
#include "binary_search_tree.h"
#include "tab.h"

void dijkstra_Liste (Graphe g, S depart, S courant); // il arrive pas à la lire sinon
void dijkstra_Avl (Graphe g, S depart, S courant);
void dijkstra_Tableau_simple(Graphe g, S depart, S courant);
void dijkstra_table(Graphe g,S depart, S courant);
void dijkstra_heap(Graphe g,S depart, S courant);
void dijkstra_gen(Graphe g,S depart, S courant);


#endif
