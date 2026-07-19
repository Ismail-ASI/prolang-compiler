#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "optim.h"


static int est_temporaire(const char *s)
{
    int i;
    if (!s || s[0] != 'T') return 0;
    if (strchr(s, '[') != NULL) return 0;
    for (i = 1; s[i] != '\0'; i++)
        if (s[i] < '0' || s[i] > '9') return 0;
    return (s[1] != '\0');
}

static int est_entier(const char *s, int *val)
{
    if (!s || s[0] == '\0') return 0;
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0') return 0;
    *val = (int)v;
    return 1;
}


static int est_effet_de_bord(int i)
{
    const char *op = quad[i].oper;
    return (strcmp(op, ":")      == 0 ||
            strcmp(op, "BOUNDS") == 0 ||
            strcmp(op, "ADEC")   == 0 ||
            strcmp(op, "BR")     == 0 ||
            strcmp(op, "BGE")    == 0 ||
            strcmp(op, "BLE")    == 0 ||
            strcmp(op, "BG")     == 0 ||
            strcmp(op, "BL")     == 0 ||
            strcmp(op, "BE")     == 0 ||
            strcmp(op, "BNE")    == 0 ||
            strcmp(op, "OUT")    == 0 ||
            strcmp(op, "IN")     == 0);
}

static int est_saut_op(const char *op)
{
    return (strcmp(op,"BR") ==0 || strcmp(op,"BGE")==0 ||
            strcmp(op,"BLE")==0 || strcmp(op,"BG") ==0 ||
            strcmp(op,"BL") ==0 || strcmp(op,"BE") ==0 ||
            strcmp(op,"BNE")==0);
}


static int extraire_index_tableau(const char *champ, char *buf)
{
    const char *debut = strchr(champ, '[');
    if (debut == NULL) return 0;
    debut++;
    int len = 0;
    while (debut[len] && debut[len] != ']' && len < 99)
    { buf[len] = debut[len]; len++; }
    buf[len] = '\0';
    return (len > 0);
}


static int remplacer_dans_quad(int i, const char *ancien, const char *nouveau)
{
    int modif = 0;
    if (!est_saut_op(quad[i].oper) && strcmp(quad[i].op1, ancien) == 0)
    { strcpy(quad[i].op1, nouveau); modif = 1; }
    if (strcmp(quad[i].op2, ancien) == 0)
    { strcpy(quad[i].op2, nouveau); modif = 1; }
    return modif;
}


static int compter_utilisations(const char *nom, int debut, int fin)
{
    int cnt = 0;
    char idx[100];
    int i;

    for (i = debut; i < fin; i++)
    {
        int saut = est_saut_op(quad[i].oper);

        /* 1. op1 exact (sauf sauts) */
        if (!saut && strcmp(quad[i].op1, nom) == 0)
            cnt++;

        /* 2. op2 exact */
        if (strcmp(quad[i].op2, nom) == 0)
            cnt++;

        /* 3. index de tableau dans op1 (ex: op1="Tabfloat[T25]") */
        if (!saut && extraire_index_tableau(quad[i].op1, idx))
            if (strcmp(idx, nom) == 0) cnt++;

        /* 4. index de tableau dans op2 (ex: op2="Tabfloat[T25]") */
        if (extraire_index_tableau(quad[i].op2, idx))
            if (strcmp(idx, nom) == 0) cnt++;

        /* 5. index de tableau dans res (ex: res="Tabint[T19]") */
        if (extraire_index_tableau(quad[i].res, idx))
            if (strcmp(idx, nom) == 0) cnt++;
    }
    return cnt;
}


static int est_reaffecte(const char *nom, int debut, int fin)
{
    int i;
    for (i = debut; i < fin; i++)
        if (strcmp(quad[i].res, nom) == 0) return 1;
    return 0;
}


static void supprimer_quad(int idx)
{
    int i;
    for (i = idx; i < qc - 1; i++)
        quad[i] = quad[i + 1];
    qc--;

    for (i = 0; i < qc; i++)
    {
        if (est_saut_op(quad[i].oper))
        {
            int cible;
            if (sscanf(quad[i].op1, "%d", &cible) == 1 && cible > idx)
                sprintf(quad[i].op1, "%d", cible - 1);
        }
    }
}

static int passe_simplification_algebrique(void)
{
    int modif = 0;
    int i;
    for (i = 0; i < qc; i++)
    {
        const char *op = quad[i].oper;
        if (strcmp(op,"+")!=0 && strcmp(op,"-")!=0 &&
            strcmp(op,"*")!=0 && strcmp(op,"/")!=0) continue;

        char *o1 = quad[i].op1, *o2 = quad[i].op2;
        int v1, v2, c1 = est_entier(o1,&v1), c2 = est_entier(o2,&v2);
        //cas ou de deux constant par ex : T = 3+4 twli T=7
        if (c1 && c2) {
            int r = 0;
            if      (strcmp(op,"+")==0) r=v1+v2;
            else if (strcmp(op,"-")==0) r=v1-v2;
            else if (strcmp(op,"*")==0) r=v1*v2;
            else if (strcmp(op,"/")==0 && v2!=0) r=v1/v2;
            else continue;
            char buf[20]; sprintf(buf,"%d",r);
            strcpy(quad[i].oper,"<--"); strcpy(quad[i].op1,buf); strcpy(quad[i].op2,"vide");
            modif=1; continue;
        }
        if (strcmp(op,"+")==0) {//cas ou x+0 puis 0+x
            if (c2&&v2==0) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op2,"vide"); modif=1; }
            else if (c1&&v1==0) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op1,o2); strcpy(quad[i].op2,"vide"); modif=1; }
        } else if (strcmp(op,"-")==0) {//cas ou x-0 , si 0-x , mat9derch tsimplifia 
            if (c2&&v2==0) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op2,"vide"); modif=1; }
        } else if (strcmp(op,"*")==0) {//x*1 twli x puis x*0 twli  0 puis cas ou multiplication twli addition just ki tkon *2 apres x/1 twli 1 
            if      (c2&&v2==1) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op2,"vide"); modif=1; }
            else if (c1&&v1==1) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op1,o2); strcpy(quad[i].op2,"vide"); modif=1; }
            else if (c2&&v2==0) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op1,"0"); strcpy(quad[i].op2,"vide"); modif=1; }
            else if (c1&&v1==0) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op1,"0"); strcpy(quad[i].op2,"vide"); modif=1; }
            else if (c2&&v2==2) { strcpy(quad[i].oper,"+"); strcpy(quad[i].op2,o1); modif=1; }
            else if (c1&&v1==2) { strcpy(quad[i].oper,"+"); strcpy(quad[i].op1,o2); strcpy(quad[i].op2,o2); modif=1; }
        } else if (strcmp(op,"/")==0) {
            if (c2&&v2==1) { strcpy(quad[i].oper,"<--"); strcpy(quad[i].op2,"vide"); modif=1; }
        }
    }
    return modif;
}


static int passe_propagation_expression(void)
{
    int modif = 0;
    int i, j, k;
    for (i = 0; i < qc; i++)
    {
        const char *op = quad[i].oper;
        if (strcmp(op,"+")!=0 && strcmp(op,"-")!=0 &&
            strcmp(op,"*")!=0 && strcmp(op,"/")!=0) continue;

        const char *tmp = quad[i].res;
        if (!est_temporaire(tmp)) continue;//si ilest tomporarie 
        if (compter_utilisations(tmp, i+1, qc) != 1) continue;//combien de fois est utliser 

        j = -1;
        for (k = i+1; k < qc; k++) {
            if (!est_saut_op(quad[k].oper) && strcmp(quad[k].op1, tmp)==0) { j=k; break; }
            if (strcmp(quad[k].op2, tmp)==0) { j=k; break; }
        }//verifer est ce qeu le tomporarie est tuliser plusieurs fois on peut peut pasa pallique ca 
        if (j == -1) continue;
        if (est_reaffecte(quad[i].op1, i+1, j+1)) continue;
        if (est_reaffecte(quad[i].op2, i+1, j+1)) continue;
        if (est_reaffecte(tmp,          i+1, j))   continue;
        // verfier ausiis si les velurs des operandes utlises ce change netre le premire et la deuxieme utlisation
        if (strcmp(quad[j].oper,"<--")==0 && strcmp(quad[j].op2,"vide")==0
            && strcmp(quad[j].op1, tmp)==0)
        {
            strcpy(quad[j].oper, quad[i].oper);
            strcpy(quad[j].op1,  quad[i].op1);
            strcpy(quad[j].op2,  quad[i].op2);
            supprimer_quad(i);
            i--; modif = 1;
        }
    }//si oui on fusionne
    return modif;
}


static int passe_propagation_copie(void)
{
    int modif = 0;
    int i, j, sub;
    for (i = 0; i < qc; i++)
    {//verfier si la variable affecter a t a change de valeur apres etre affecte 
        if (strcmp(quad[i].oper,"<--")!=0 || strcmp(quad[i].op2,"vide")!=0) continue;
        const char *src = quad[i].op1, *dst = quad[i].res;
        if (strcmp(src,"vide")==0 || strcmp(dst,"vide")==0) continue;
        if (!est_temporaire(dst)) continue;   //verifer juste que c est un t       
        if (est_reaffecte(src, i+1, qc)) continue;//est ce qeu la valeur change ou pas de variable 
        if (est_reaffecte(dst, i+1, qc)) continue;//hna verifer est ce qeue le t est changer 
        sub = 0;
        for (j = i+1; j < qc; j++)
            sub += remplacer_dans_quad(j, dst, src);//si tout verfier remplacer le aud directe
        if (sub > 0) {
            modif = 1;
            supprimer_quad(i);
            i--;
        }
    }
    return modif;
}


static int passe_cse(void)
{
    int modif = 0;
    int i, j;
    for (i = 0; i < qc; i++)
    {
        const char *op = quad[i].oper;
        if (strcmp(op,"+")!=0 && strcmp(op,"-")!=0 &&
            strcmp(op,"*")!=0 && strcmp(op,"/")!=0) continue;
        if (strcmp(quad[i].op1,"vide")==0 || strcmp(quad[i].op2,"vide")==0) continue;

        for (j = i+1; j < qc; j++)
        {
            if (strcmp(quad[j].oper,quad[i].oper)!=0) continue;//meme opertion
            if (strcmp(quad[j].op1, quad[i].op1) !=0) continue;//meme operrande
            if (strcmp(quad[j].op2, quad[i].op2) !=0) continue; 
            if (est_reaffecte(quad[i].op1, i+1, j)) continue;//pas changement de valeurs 
            if (est_reaffecte(quad[i].op2, i+1, j)) continue;
            strcpy(quad[j].oper,"<--");
            strcpy(quad[j].op1, quad[i].res);
            strcpy(quad[j].op2, "vide");
            modif = 1;
        }
    }
    return modif;
}


static int passe_dead_code(void)
{
    int modif = 0;
    int i;
    for (i = 0; i < qc; i++)
    {
        if (est_effet_de_bord(i)) continue;//verfier si le quad conteotn pas un effetd bord ( insupprimable)
        const char *res = quad[i].res;
        if (strcmp(res,"vide")==0) continue;
        if (!est_temporaire(res)) continue;         //est ce que temp
        if (compter_utilisations(res, 0, qc) == 0) {
            supprimer_quad(i);
            i--; modif = 1;//ne ce reultilse pas donc suupp
        }
    }
    return modif;
}


void optimiser_quadruplets(void)
{
    printf("\n=================== OPTIMISATION ===================\n");
    printf("Quadruplets avant : %d\n", qc);

    int iteration = 0, changement;
    do {
        changement = 0;
        iteration++;
        changement |= passe_simplification_algebrique();
        changement |= passe_propagation_expression();
        changement |= passe_propagation_copie();
        changement |= passe_cse();
        changement |= passe_dead_code();
    } while (changement);

    printf("Quadruplets apres : %d\n", qc);
    printf("Iterations        : %d\n", iteration);
    printf("=====================================================\n");
}
