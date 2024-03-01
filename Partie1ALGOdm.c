/*
AUBRY Pierre
CHANNOUFI Badreddine
L3 INFO - Algo

*******************************************************************************
*                                                                             *
*                      DEVOIR MAISON ALGO en Autonomie                        *
*                                                                             *
******************************************************************************/

#include <stdio.h>
/******************************************************************************/
/*                                                                            */
/*                 PARTIE 1  - Quelques calculs simples                       */
/*                                                                            */
/******************************************************************************/

/*Exercice 1 - calcul de e */
float calculE(int max){
    float res = 1.;
    float facto = 1.;
    for(int i=1; i<max; i++){
        facto = facto * (float)i;
        res = res + (1./facto);
    }
    return res;
}

/*Exercice 2 - suite avec e*/
//pas sûr du resultat
float exercice2(double e){
    double en = e - 1.;
    for(int i=0; i<=50; i++){
        printf("n:%d en:%f\n", i, en );
        en = (double)i*en - 1.;
    }
}

/*Exercice 3 - la fonction power*/
//1.RECURSIVE SIMPLE OK
float power1(float x, int n){
    if(n == 0) return 1;
    else if(n < 0) return 1/power1(x, -n);
    else return power1(x, n-1)*x;
}

//2.a)ITERATIVE, par (n-1) OK
float power2a(float x, int n){ 
    float res = 1.;
    if(n > 0){
        for(int i=1; i<=n; i++){
            res = res * x;
        }
    }else{
        for(int i=1; i<=-n; i++){
            res = res / x;
        }
    }
    return res;
}

//2.b)ITERATIVE, par (n-1) avec while
float power2b(float x, int n){
    float res = 1.;
    int i = n;
    if(n > 0){
        while(i>0){
            res = res*x;
            i--;
        }
    }else{
        while(i<0){
            res = res/x;
            i++;
        }
    }
    return res;
}

//3. RECURSIVE TERMINALE, avec sous procédure par (n-1) OK
void pow3(float x, int n, float *r){
    if(n == 0) ;
    else {
        *r = *r * x;
        //printf("%f, ", r);
        pow3(x, n-1, r);
    }
}
float power3(float x, int n){ 
    float res = 1.;
    pow3(x, n, &res);
    return res;
}

//4.RECURSIVE TERMINALE, avec sous fonction par (n-1) OK
float pow4(float x, int n, float r){
    if(n == 0) return r;
    else pow4(x, n-1, r*x);
}
float power4(float x, int n){
    return pow4(x, n, 1);
}

//5.RECURSIVE SIMPLE, par (n/2) mais bourde OK
float power5(float x, int n){
    if(n == 0) return 1;
    else{
        if(n % 2 == 0) return ( power4(x, n/2) * power4(x, n/2) );
        else return ( power4(x, n/2) * power4(x, n/2) * x );
    }
}

//6.RECURSIVE SIMPLE, par (n-2) ok OK
float power6(float x, int n){
    if(n == 0) return 1;
    else{
        float y = power6(x, n/2);
        if(n % 2 == 0) return (y * y);
        else return (y * y * x);
    }
}

//7.RECURSIVE SIMPLE, par (n-2), variante ok OK
float power7(float x, int n){
    if(n == 0) return 1;
    else{
        if( n % 2 == 0) return power7(x*x, n/2);
        else return ( power7(x*x, n/2) * x );
    }
}

//8.RECURSIVE SIMPLE, par (n/2), avec sous fonction OK
float pow8(float x, int n, float r){
    if(n == 0) return r;
    else {
        if(n % 2 == 0) return pow8(x*x, n/2, r);
        else return pow8(x*x, n/2, r*x); 
    }
}
float power8(float x, int n){
    return pow8(x, n, 1);
}

//9.RECURSIVE SIMPLE, par (n/2), avec sous procedure NON :(
void pow9(float x, int n, float *r){
    if(n == 0) ;
    else {
        if(n % 2 == 1) *r = *r * x;
        //printf("%d - ", r);
        pow9(x*x, n/2, r);
    }

}
float power9(float x, float n){
    float res =  1;
    pow9(x, n, &res);
    return res;
}

//10.ITERATIF, par (n/2)
float power10(float x, int n){
    float res = 1.;
    while(n != 0){
        if(n % 2 == 1) res = res * x;
        n = n / 2;
        x = x * x;
    }
    return res;
}


void suiteN(){
    for(int i=1; i<=5; i++){
        double N = power1(10, i); 
        double res = power1(1 +(double)(1./ N), N);
        printf("suiteN(10^%d) = %f\n", i, res);
    }
    printf("\n");
}
/*La fonction semble tendre vers 2.7; mais peut tourner dans le vide ou planter (ex: SegFault)
avec certaines fonctions power. 
Le compilateur ne semble pas effectuer l'optimisation du récursif terminal */


/*exercice 4 - la fonction d'Ackermann*/
//VERSION RECURIVE
int AckermannRec(int m, int n){
    if(m == 0) return n+1;
    else {
        if(n == 0) return AckermannRec(m-1, 1);
        else return AckermannRec(m-1, AckermannRec(m, n-1));
    }
}

//VERSION RECURSIVE-ITERATIVE
int AckermannRecIte(int m, int n) {
  if (m == 0) return n + 1;
  else{
    for(int i=1; i < n+1; i++){
        AckermannRecIte(m, n-1);
    }
    if (m > 0 && n == 0) return AckermannRecIte(m - 1, 1);
    else if (m > 0 && n > 0) return AckermannRecIte(m - 1, AckermannRecIte(m, n - 1));
  }

  return 0;
}

/*
Lorsque l'on tente A(5,0), Rec: ça fonctionne mais ça prend du temps
                           RecIter: ça tourne dans le vide
Lorsque l'on tente A(6,0), le compilateur tourne sans donner de resultat.
*/


/*exercice 5 - suite X(n+1) = Xn + (2 / Xn)*/
//VERSION ITERATIVE
float suiteIt(int max){
    float res = 1.;
    for(int i=0; i<max; i++){
        //printf("%d: %f, ", i, res);
        res = res + (2 / res);
    }
    //printf("\n");
    return res;
}

//VERSION RECURSIVE: sans sous-fonctionnalites
float Rec(int max){
    float n;
    if(max == 0) return 1.;
    n = Rec(max-1);
    return n + 2/n;
}

//VERSION RECURSIVE TERMINALE 1: avec sous fonction
float auxRec1(int max, float r){
    if(max == 0) return r;
    else {
        auxRec1(max-1, r + (2/r));
    }
}

float suiteRec1(int max){
    return auxRec1(max, 1.);
}

//VERSION RECURSIVE TERMINALE 2: avec sous procédure
void auxRec2(int max, float *r){
    if(max == 0) ;
    else {
        *r = *r + (2./ *r);
        auxRec2(max-1, r);
    }
}

float suiteRec2(int max){
    float res = 1.;
    auxRec2(max, &res);
    return res;
}

/****************************************/
/*                                      */
/*                TEST                  */
/*                                      */
/****************************************/
void fonctionAfficheTest1(float e, int maxSuiteN){

    /*exo1*/
    printf("__________________________Valeur de e__________________________\n");
    printf("e vaut: %f\n", e); // 10 est suffisant comme max de la suite pour calculer e jusqu'aux 6 premières décimales
    
    /*exo2*/
    printf("_______________________50 premiers termes_______________________\n");
    exercice2(e); //pas  OK


    /*exo3*/
    printf("______________________fonctions Power(3, 5)______________________\n");
    printf("power1 : %f", power1(3, 5));   printf("  ====  power1(3,-5) : %f\n", power1(3, (-5)));
    printf("power2a: %f", power2a(3, 5));printf("  ====  power2a(3,-5) : %f\n", power2a(3, (-5)));
    printf("power2b: %f", power2b(3, 5));printf("  ====  power2b(3,-5) : %f\n", power2b(3, (-5)));
    printf("power3 : %f\n", power3(3, 5));
    printf("power4 : %f\n", power4(3, 5));
    printf("power5 : %f\n", power5(3, 5));
    printf("power6 : %f\n", power6(3, 5));
    printf("power7 : %f\n", power7(3, 5));
    printf("power8 : %f\n", power8(3, 5));
    printf("power9 : %f\n", power9(3, 5));
    printf("power10: %f\n", power10(3, 5));
    printf("_________________________(1 + 1/N )^N__________________________\n");    
    suiteN(maxSuiteN);


    /*exo4*/
    printf("\n________________________Ackermann(n,0)________________________\n");
    int maxAckermann = 3;
    for(int i=0; i<=maxAckermann; i++){
        printf("n = %d | AckermannRec(%d,0) = %d | AckermannRecIter(%d,0) = %d \n", i, i, AckermannRec(i,0), i, AckermannRecIte(i, 0));
    }

    /*exo5*/
    printf("___________________________Suite ex5____________________________\n");
    float Ite = suiteIt(100);
    float Re = Rec(100);
    float R1 = suiteRec1(100);
    float R2 = suiteRec2(100);
    printf("Soit X100 : \n Iteratif vaut : %f   \n Rec vaut      : %f   \n Recursif1 vaut: %f   \n Recursif2 vaut: %f", Ite, Re, R1, R2);
    printf("\n_______________________________________________________________\n");
}


/****************************************/
/*                                      */
/*                MAIN()                */
/*                                      */
/****************************************/

int main(){
    float e = calculE(10);
    int maxSuiteN = 5 ;

    fonctionAfficheTest1(e, maxSuiteN);
    return 0;
}
