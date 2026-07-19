

#include "ts.h"


TypeTS TS[TAILLE_TS];
TypeSM tabM[TAILLE_SM];
TypeSM tabS[TAILLE_SM];


int hachage(char entite[])
{
    int somme = 0;
    int i;
    for (i = 0; entite[i] != '\0'; i++)
        somme += (int)entite[i];
    return somme % TAILLE_TS;
}


void initialization(void)
{
    int i;
    for (i = 0; i < TAILLE_TS; i++)
        TS[i].state = 0;
    for (i = 0; i < TAILLE_SM; i++)
    {
        tabM[i].state = 0;
        tabS[i].state = 0;
    }
}


void inserer(char entite[], char code[], char type[], char val[], int i, int y)
{
    switch (y)
    {
        case 1:
            TS[i].state = 1;
            strcpy(TS[i].name, entite);
            strcpy(TS[i].code, code);
            strcpy(TS[i].type, type);
            strcpy(TS[i].val,  val);
            break;
        case 2:
            tabM[i].state = 1;
            strcpy(tabM[i].name, entite);
            strcpy(tabM[i].code, code);
            break;
        case 3:
            tabS[i].state = 1;
            strcpy(tabS[i].name, entite);
            strcpy(tabS[i].code, code);
            break;
    }
}


int Rechercher(char entite[], char code[], char type[], char val[], int y)
{
    int i, idx, sonde;

    switch (y)
    {
        
        case 1:
            idx = hachage(entite);
            for (sonde = 0; sonde < TAILLE_TS; sonde++)
            {
                i = (idx + sonde) % TAILLE_TS;
                if (TS[i].state == 0)
                {
                    inserer(entite, code, type, val, i, 1);
                    return i;
                }
                if (strcmp(entite, TS[i].name) == 0)
                    return -1;  
            }
            printf(">>>> Table des symboles pleine, impossible d'inserer %s\n", entite);
            return -2;

        
        case 2:
            for (i = 0; i < TAILLE_SM; i++)
            {
                if (tabM[i].state == 0)
                {
                    inserer(entite, code, type, val, i, 2);
                    return i;
                }
                if (strcmp(entite, tabM[i].name) == 0)
                    return -1;  /* deja presente */
            }
            printf(">>>> Table mots-cles pleine\n");
            return -2;

        
        case 3:
            for (i = 0; i < TAILLE_SM; i++)
            {
                if (tabS[i].state == 0)
                {
                    inserer(entite, code, type, val, i, 3);
                    return i;
                }
                if (strcmp(entite, tabS[i].name) == 0)
                    return -1;  /* deja presente */
            }
            printf(">>>> Table separateurs pleine\n");
            return -2;
    }
    return -2;
}


int chercher(char entite[])
{
    int idx = hachage(entite);
    int sonde, i;

    for (sonde = 0; sonde < TAILLE_TS; sonde++)
    {
        i = (idx + sonde) % TAILLE_TS;
        if (TS[i].state == 0)
            return -1;
        if (strcmp(entite, TS[i].name) == 0)
            return i;
    }
    return -1;
}


void afficher(void)
{
    int i;

    printf("\n/************* Table des symboles IDF et CONST *************/\n");
    printf("________________________________________________________________\n");
    printf("\t| %-14s | %-10s | %-10s | %-10s |\n",
           "Nom_Entite", "Code", "Type", "Val");
    printf("________________________________________________________________\n");
    for (i = 0; i < TAILLE_TS; i++)
        if (TS[i].state == 1)
            printf("\t| %-14s | %-10s | %-10s | %-10s |\n",
                   TS[i].name, TS[i].code, TS[i].type, TS[i].val);

    printf("\n/************* Table des symboles Mots-cles *****************/\n");
    printf("_________________________________________\n");
    printf("\t| %-14s | %-10s |\n", "NomEntite", "CodeEntite");
    printf("_________________________________________\n");
    for (i = 0; i < TAILLE_SM; i++)
        if (tabM[i].state == 1)
            printf("\t| %-14s | %-10s |\n", tabM[i].name, tabM[i].code);

    printf("\n/************* Table des symboles Separateurs ***************/\n");
    printf("_________________________________________\n");
    printf("\t| %-14s | %-10s |\n", "NomEntite", "CodeEntite");
    printf("_________________________________________\n");
    for (i = 0; i < TAILLE_SM; i++)
        if (tabS[i].state == 1)
            printf("\t| %-14s | %-10s |\n", tabS[i].name, tabS[i].code);
}
