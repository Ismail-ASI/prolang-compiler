
#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    int  state;       
    char name[20];    
    char code[20];    
    char type[20];    
    char val[20];     
} TypeTS;

typedef struct
{
    int  state;
    char name[20];
    char code[20];
} TypeSM;

#define TAILLE_TS  200
#define TAILLE_SM   50


extern TypeTS TS[TAILLE_TS];
extern TypeSM tabM[TAILLE_SM];
extern TypeSM tabS[TAILLE_SM];

int  hachage(char entite[]);
void initialization(void);
void inserer(char entite[], char code[], char type[], char val[], int i, int y);
int  Rechercher(char entite[], char code[], char type[], char val[], int y);
int  chercher(char entite[]);
void afficher(void);

#endif 
