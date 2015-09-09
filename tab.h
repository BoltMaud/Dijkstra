#ifdef TAB

#define minimum mintab
#define recherche recht
#define deacreasekey deacrease_keyt

//déclaration d'un tableau vide
table *tabnouv();

//reallocation de place quand on en plus ( car bufferisation pour eviter un realloc a chaque valeur)
table *realloctab(table *t);

//insertion dans un tableau
table *insert_tab (table *t, elmtpq val);

//init pour tous les noeuds
table *t_init_all(table *t,S val);

//init pour le noeud de départ
table *t_init_first(table *t, S val);

//init tableau
table *init_table (Graphe g, S depart);

//suppression d'une valeur dans le tableau
table *supr (table *t, int val);

//selection du minimum et suppression du minimum
elmtpq mintab (table *t);

//samet test si deux poids sont egaux
bool samet (elmtpq a1, elmtpq a2);

//recherche d'une elmtpq dans le tableau
elmtpq recht (table *t, S val);

//deacrease key
table *deacrease_keyt(table *t, S val, int nouv_poids, S nouv_antecedent);

//free du tableau
void freetab (table *t);

//affichage_table
void affichage_table(table *t);
#endif
