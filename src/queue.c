#include "queue.h"

/**************************************************

Définition d'une liste pour la suite

**************************************************/
/* Structure représentant un élément de la file */
typedef struct s_Cell {
	struct s_Cell* next;
	struct s_Cell* last;
	char* txt;
	int length;
} Cell;

/**************************************************

Créé une cellule avec pour valeur le paramère nb
@param la valeur du noeud à créer   
@sortie la cellule créer

**************************************************/
Cell* createCell (char* txt) {
	Cell* res = (Cell*)malloc(sizeof(Cell));
	res->next = NULL;
	res->last = NULL;
	res->txt = txt;
	res->length = strlen(txt);
	return res;
}

/**************************************************

Detruit la cellule passé en paramettre
@param la cellule a détruire

**************************************************/
void deleteCell (Cell* cell) {
	free(cell);
}

/* Structure représentant la file */
struct s_Queue {
	Cell* tete;
	Cell* queu;
	int size;
};

/**************************************************

Créé une file   
@sortie la file créé

**************************************************/
Queue createQueue () {
	Queue f = (Queue)malloc(sizeof(struct s_Queue));
	f->tete = NULL;
	f->queu = NULL;
	f->size = 0;
	return f;
}

/**************************************************

détruit la file passé en paramètre
@param la file a détruire

**************************************************/
void deleteQueue (Queue f) {
	Cell * c = f->tete;
	Cell * l = NULL;
	while (c != NULL) {
		l = c->last;
		deleteCell(c);
		c = l;
	}
	free(f);
}

/**************************************************

Renvois un booléen vrai si la file est vide faux si non
@param la file a varifier  
@sortie >0 si vide 0 sinon

**************************************************/
int emptyQ (Queue f) {
	return f->size == 0;
}

/**************************************************

Enfile une valeur dans une file
@param la file dans laquelle on enfile l'élément
@param la valeur de l'élément à enfiler  

**************************************************/
void enfiler (Queue f, char* elem) {
	Cell* cell = createCell(elem);
	if (emptyQ(f)) {
		f->tete = cell;
		f->queu = cell;
		f->size = 1;
		return;
	}
	Cell* tmp = f->queu;
	f->queu = cell;
	tmp->last = cell;
	cell->next = tmp;
	f->size = f->size + 1;
}

/**************************************************

Défile une valeur de la file.
On suppose que l'utilisateur ce chargera de désalouer la chaine de caractère grace au pointeur retourné par cette fonction.
@param La file a défiler 
@sortie La valeur de l'élément défilé

**************************************************/
char* defiler (Queue f) {
	assert (!emptyQ(f));
	Cell* tmp = f->tete;
	char* res = tmp->txt;
	f->tete = tmp->last;
	if (f->tete != NULL) f->tete->next = NULL;
	f->size = f->size - 1;
	deleteCell(tmp);
	return res;
}

int getSize (Queue f) {
	return f->size;
}

char ** getConcatChar (Queue f) {
	if (emptyQ(f)) return NULL;
	Cell * c = f->tete;
	char ** res = (char**)malloc(sizeof(char*)*f->size);
	int i;
	for (i = 0; i < f->size; i++) {
		res[i] = c->txt;
		c = c->last;
	}
	return res;
}
