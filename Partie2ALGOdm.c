/*
AUBRY Pierre
CHANNOUFI Badreddine
L3 INFO - Algo

*******************************************************************************
*                                                                             *
*                      DEVOIR MAISON ALGO en Autonomie                        *
*                                                                             *
*******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
    *L = ajoute(x,*L) ;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
        return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
// *L non NULL ie liste non vide
{
    if ( ((**L).suivant) == NULL )
        depile(L) ;   // moralement : depile(& (*L)) ;
    else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
    if ( (*L) ISNOT NULL )
        VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
            L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
    }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }

}


/******************************************************************************/
/*                                                                            */
/*                          Implementation perso                              */
/*                                                                            */
/******************************************************************************/

/*exercice 1*/
bool ZeroEnPositionUnDeuOuTrois(Liste l){
    for(int i=0; i<=2; i++){
        if(NOT estVide(l)){
            if(l->nombre == 0) return TRUE;
            l = l->suivant;
        }else return FALSE;
    }
    return FALSE;
}

/*exercice 2*/
bool Pluscourte(Liste l1, Liste l2){
    /*
    if(!l1 OR !l2) return !l1 AND l2;
    else Pluscourte(l1->suivant, l2->suivant);
     */
    return longueur_rec(l1) < longueur_rec (l2);
}

/*exerice 3*/
//ITERATIVE SIMPLE
int NombreDe0AvantPositionK1(Liste l, int k){
        Liste bis = l;
        int res = 0;
        for (int i = 0; i < k; i++) {
            if(estVide(l))
                break;
            if (bis->nombre == 0) res++;
            bis = suite(bis);
        }
        return res;
}

//RECURSIF SIMPLE
int NombreDe0AvantPositionK2(Liste l, int k){
    int res = 0;
    if(k == 0 || estVide(l)) return 0;
    else {
        if(l->nombre == 0) res++;
        return NombreDe0AvantPositionK2(l->suivant, k-1) + res;
    }
}

//RECURSIF avec sous sous-fonction
int aux_Nb0avK3(Liste l, int k, int res){
    if(k == 0 || estVide(l)) return res;
    else {
        if(l->nombre == 0) aux_Nb0avK3(l->suivant, k-1, res+1);
        else aux_Nb0avK3(l->suivant, k-1, res);
    }    
}

int NombreDe0AvantPositionK3(Liste l, int k){
    return aux_Nb0avK3(l, k, 0);
}

//RECURSIF avec sous-procedure
void aux_Nb0avK4(Liste l, int k, int *res){
    if(k == 0 || estVide(l)) ;
    else {
        if(l->nombre == 0) *res += 1;
        aux_Nb0avK4(l->suivant, k-1, res);
    }
    
}
int NombreDe0AvantPositionK4(Liste l, int k){
    int res = 0;
    aux_Nb0avK4(l, k, &res);
    return res;
    
}

/*exercice 4*/
int auxNbapK(Liste l, int k, int res){
    if(!l) return res;
    if(k > 0) auxNbapK(l->suivant, k-1, res);
    else if (l->nombre == 0) auxNbapK(l->suivant, k, res+1);
    else auxNbapK(l->suivant, k, res);
}
int NombreDe0ApresRetroPositionK(Liste l, int k){
    return auxNbapK(l, k, 0);
}


/*exercice 5*/
Liste FctBegayeRec(Liste l){
    if(l == NULL) return NULL;
    Liste Lbis = FctBegayeRec(l->suivant);
    if(l->nombre > 0){
        empile(l->nombre, &Lbis);
        empile(l->nombre, &Lbis);
    }
    return Lbis;
}

Liste FctBegayeIter(Liste l) {
    Liste R;
    Liste* Q = &R;
    Liste P = l;
    while (P != NULL) {
        if(P->nombre > 0){
            *Q = malloc(sizeof(Liste));
            (*Q)->nombre = P->nombre;
            Q = &((*Q)->suivant);
            *Q = malloc(sizeof(Liste));
            (*Q)->nombre = P->nombre;
            P = P->suivant;                        
            Q = &((*Q)->suivant);
        }else P = P->suivant;
    }
    return R;
}


/*exercice 6*/
void ProcBegaye(Liste* l) {
    if (*l == NULL) return ;
    if ((*l)->nombre <= 0) {
        depile(l);
        ProcBegaye(l);
    } else {
        empile((*l)->nombre, l);
        l = &((*l)->suivant->suivant);
        ProcBegaye(l);
    }
}

/*exercice 7*/





/******************************************************************************/
/*                                                                            */
/*                                    TEST                                    */
/*                                                                            */
/******************************************************************************/
// La fonctionAfficheTest affiche le resultat de chaques fonctions implémentées 
// ci-dessus (ca fait plus propre dans la main)
void fonctionAfficheTest2(Liste l1, Liste l2, Liste l3, Liste l4, int k){
    printf("________________Declaration Listes__________________\n");
    printf("Liste 1 : "); affiche_iter(l1); 
    printf("Liste 2 : "); affiche_iter(l2);
    printf("Liste 3 : "); affiche_iter(l3);
    printf("Liste 4 : "); affiche_iter(l4);
    printf("________________Tests Fonctions_____________________\n");

    
    if(ZeroEnPositionUnDeuOuTrois(l1)) printf("ZeroEnPositionUnDeuOuTrois(Liste 1): OUI\n"); //OK
                                       else printf ("ZeroEnPositionUnDeuOuTrois(Liste 1): NON\n");
    if(ZeroEnPositionUnDeuOuTrois(l3)) printf("ZeroEnPositionUnDeuOuTrois(Liste 3): OUI\n"); //OK
                                       else printf ("ZeroEnPositionUnDeuOuTrois(Liste 3): NON\n");
                                       
    if(Pluscourte(l1, l2)) printf("Pluscourte(Liste 1,Liste 2)        : OUI\n");
                                      else printf ("Pluscourte(Liste 1,Liste 2)        : NON\n");
    printf("ND0AvPK(Liste 1), iteratif simple             : %d\n", NombreDe0AvantPositionK1(l1,k)); //OK
    printf("ND0AvPK(Liste 1), recursif simple             : %d\n", NombreDe0AvantPositionK2(l1,k)); //OK
    printf("ND0AvPK(Liste 1), recursif avec sous-fonction : %d\n", NombreDe0AvantPositionK3(l1,k)); //OK
    printf("ND0AvPK(Liste 1), recursif avec sous-procedure: %d\n", NombreDe0AvantPositionK4(l1,k)); //NUL
    printf("ND0ApPK(Liste 1)                              : %d\n", NombreDe0ApresRetroPositionK(l1, k)); //OK
    printf("FctBegayeRec(Liste 4)                         : "); affiche_iter(FctBegayeRec(l4));
    printf("FctBegayeIter(Liste 4)                        : "); affiche_iter(FctBegayeIter(l4));
    printf("ProcBegaye(Liste 4)                           : "); ProcBegaye(&l4); affiche_iter(l4);

    printf("_____________________________________________________\n");

}

/******************************************************************************/
/*                                                                            */
/*                                    MAIN                                    */
/*                                                                            */
/******************************************************************************/
int main(int argc, char** argv)
{
    Liste l1;
    Liste l2;
    Liste l3;
    Liste l4;
    
    initVide (&l1) ;
    initVide (&l2) ;
    initVide (&l3) ;
    initVide (&l4);
    
    empile(0, &l1) ;
    empile(1, &l1) ;
    empile(0, &l1) ;
    empile(0, &l1) ;
    empile(0, &l1) ;
    empile(9, &l1) ;
    empile(6, &l1) ;
    empile(5, &l1) ;
    empile(0, &l1) ;
    empile(2, &l1) ;

    empile(0, &l2) ;
    empile(7, &l2) ;
    empile(5, &l2) ;
    empile(9, &l2) ;
    
    empile(2, &l3) ;
    empile(9, &l3) ;
    
    empile(8, &l4);
    empile(8, &l4);
    empile(-2, &l4);
    empile(6, &l4);
    empile(0, &l4);
    empile(1, &l4);
    empile(2, &l4);

    fonctionAfficheTest2(l1, l2, l3,l4, 6);
    
    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    
    return 0;
}




