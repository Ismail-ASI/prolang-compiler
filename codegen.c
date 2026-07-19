#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"
#include "ts.h"
#include "codegen.h"

/*
   VIRGULE FIXE : tous les floats sont multiplies par SCALE (10)
   1 decimale : 3.1, 2.5, 0.5 ...
   On utilise SCALE=10 pour eviter l'overflow 16 bits (max 32767).
   Avec SCALE=10, la valeur float max representable est 3276.7
   ce qui est suffisant pour ce programme.
*/
#define SCALE 10

/* ================================================================
   Fonctions utilitaires
   ================================================================ */

static int est_constante_entiere(const char *s)
{
    if (!s || s[0] == '\0') return 0;
    int i = 0;
    if (s[0] == '-' || s[0] == '+') i = 1;
    if (s[i] == '\0') return 0;
    for (; s[i] != '\0'; i++)
        if (s[i] < '0' || s[i] > '9') return 0;
    return 1;
}

static int est_constante_float(const char *s)
{
    if (!s) return 0;
    return (strchr(s, '.') != NULL);
}

static int est_tableau(const char *s)
{
    if (!s) return 0;
    return (strchr(s, '[') != NULL);
}

static const char *get_type_variable(const char *nom)
{
    int pos = chercher((char *)nom);
    if (pos == -1) return "";
    return TS[pos].type;
}

static int est_float_var(const char *nom)
{
    const char *t = get_type_variable(nom);
    return (strcmp(t, "float") == 0);
}

/* Convertit constante float en entier virgule fixe (x SCALE) */
static int float_to_fixed(const char *s)
{
    double v = atof(s);
    return (int)(v * SCALE + (v >= 0 ? 0.5 : -0.5));
}

/* ================================================================
   Table des temporaires en virgule fixe
   Un temporaire Txx est en virgule fixe si et seulement si
   il a ete produit par une operation dont est_float_op etait True.
   On construit cette table a la premiere passe (pre-scan) sur tous
   les quadruplets, avant la generation du code.
   ================================================================ */

#define MAX_TEMP_FLOAT 500
static char temp_float_table[MAX_TEMP_FLOAT][20];
static int  nb_temp_float = 0;

static int est_temp_float(const char *op)
{
    int i;
    if (!op || op[0] != 'T') return 0;
    /* verifie que c'est bien un Txx (T suivi de chiffres, pas de '[') */
    int k;
    for (k = 1; op[k] != '\0'; k++)
        if (op[k] < '0' || op[k] > '9') return 0;
    if (k == 1) return 0; /* juste 'T' sans chiffre */
    for (i = 0; i < nb_temp_float; i++)
        if (strcmp(temp_float_table[i], op) == 0) return 1;
    return 0;
}

static void marquer_temp_float(const char *op)
{
    if (!op || op[0] != 'T') return;
    int k;
    for (k = 1; op[k] != '\0'; k++)
        if (op[k] < '0' || op[k] > '9') return;
    if (k == 1) return;
    /* ne pas dupliquer */
    int i;
    for (i = 0; i < nb_temp_float; i++)
        if (strcmp(temp_float_table[i], op) == 0) return;
    if (nb_temp_float < MAX_TEMP_FLOAT)
    {
        strncpy(temp_float_table[nb_temp_float], op, 19);
        temp_float_table[nb_temp_float][19] = '\0';
        nb_temp_float++;
    }
}

/* Determine si un operande est de type float (TS ou table des temporaires) */
static int operande_est_float(const char *op)
{
    if (!op || strcmp(op, "vide") == 0) return 0;
    if (est_constante_float(op)) return 1;
    if (est_temp_float(op)) return 1;
    if (est_tableau(op)) {
        char nom_tab[50];
        sscanf(op, "%[^[]", nom_tab);
        return est_float_var(nom_tab);
    }
    return est_float_var(op);
}

/* Pre-scan: construit la table des temporaires float en parcourant
   tous les quadruplets UNE FOIS avant la generation de code.
   Repete jusqu'a stabilisation (propagation transitive). */
static void construire_table_temp_float(void)
{
    nb_temp_float = 0;
    int changement;
    do {
        changement = 0;
        int i;
        for (i = 0; i < qc; i++)
        {
            const char *op  = quad[i].oper;
            const char *o1  = quad[i].op1;
            const char *o2  = quad[i].op2;
            const char *res = quad[i].res;

            int f1 = operande_est_float(o1);
            int f2 = operande_est_float(o2);
            int fr = operande_est_float(res);
            int est_float_op = f1 || f2 || fr;

            /* Pour les operations arithmetiques et les affectations:
               si est_float_op, le resultat Txx est en virgule fixe */
            if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
                strcmp(op, "*") == 0 || strcmp(op, "/") == 0 ||
                strcmp(op, "<--") == 0 || strcmp(op, "=") == 0 ||
                strcmp(op, ":") == 0)
            {
                if (est_float_op && res && res[0] == 'T')
                {
                    int avant = nb_temp_float;
                    marquer_temp_float(res);
                    if (nb_temp_float > avant) changement = 1;
                }
            }
        }
    } while (changement);
}

/* ================================================================
   Emission de code bas niveau
   ================================================================ */

/*
   Charge 'op' dans AX.
   - constante float  -> valeur * SCALE  (virgule fixe)
   - constante entiere -> valeur brute
   - variable float   -> deja stockee * SCALE
   - variable entiere -> valeur brute
   - tableau          -> valeur dans le tableau (deja au bon format)
*/
static void emit_load_ax(FILE *f, const char *op)
{
    if (strcmp(op, "vide") == 0) return;

    if (est_tableau(op))
    {
        char nom_tab[50], idx[50];
        sscanf(op, "%[^[][%[^]]", nom_tab, idx);
        fprintf(f, "    MOV BX, %s\n", idx);
        fprintf(f, "    ADD BX, BX\n");
        fprintf(f, "    MOV AX, %s[BX]\n", nom_tab);
    }
    else if (est_constante_float(op))
        fprintf(f, "    MOV AX, %d\n", float_to_fixed(op));
    else if (est_constante_entiere(op))
        fprintf(f, "    MOV AX, %s\n", op);
    else
        fprintf(f, "    MOV AX, %s\n", op);
}

/*
   Charge 'op' dans AX en s'assurant que la valeur est en virgule fixe.
   Si op est une variable/tableau entier, multiplie par SCALE.
   Si op est deja float (var ou constante), charge normalement.
*/
static void emit_load_ax_as_float(FILE *f, const char *op)
{
    if (strcmp(op, "vide") == 0) return;

    if (est_constante_float(op)) {
        fprintf(f, "    MOV AX, %d\n", float_to_fixed(op));
        return;
    }

    /* constante entiere dans contexte float */
    if (est_constante_entiere(op)) {
        fprintf(f, "    MOV AX, %d\n", atoi(op) * SCALE);
        return;
    }

    /* tableau */
    if (est_tableau(op)) {
        char nom_tab[50], idx[50];
        sscanf(op, "%[^[][%[^]]", nom_tab, idx);
        fprintf(f, "    MOV BX, %s\n", idx);
        fprintf(f, "    ADD BX, BX\n");
        fprintf(f, "    MOV AX, %s[BX]\n", nom_tab);
        /* si tableau entier dans contexte float, convertir */
        if (!est_float_var(nom_tab)) {
            fprintf(f, "    MOV BX, %d\n", SCALE);
            fprintf(f, "    IMUL BX\n");
        }
        return;
    }

    /* variable */
    fprintf(f, "    MOV AX, %s\n", op);
    if (!est_float_var(op)) {
        /* variable entiere dans contexte float */
        fprintf(f, "    MOV BX, %d\n", SCALE);
        fprintf(f, "    IMUL BX\n");
    }
}

static void emit_store_ax(FILE *f, const char *res)
{
    if (strcmp(res, "vide") == 0) return;

    if (est_tableau(res)) {
        char nom_tab[50], idx[50];
        sscanf(res, "%[^[][%[^]]", nom_tab, idx);
        fprintf(f, "    MOV BX, %s\n", idx);
        fprintf(f, "    ADD BX, BX\n");
        fprintf(f, "    MOV %s[BX], AX\n", nom_tab);
    } else
        fprintf(f, "    MOV %s, AX\n", res);
}

/* ================================================================
   Segments DATA et PILE
   ================================================================ */

static void ecrire_data_segment(FILE *f)
{
    int i;
    fprintf(f, "DATA SEGMENT\n");

    for (i = 0; i < TAILLE_TS; i++)
    {
        if (TS[i].state != 1) continue;

        const char *nom  = TS[i].name;
        const char *type = TS[i].type;
        const char *code = TS[i].code;
        const char *val  = TS[i].val;

        if (nom[0] == '"') continue;
        if (nom[0] >= '0' && nom[0] <= '9') continue;
        if (nom[0] == '(') continue;

        if (strcmp(code, "TABLEAU") == 0)
        {
            int taille = (val[0] != '\0') ? atoi(val) : 1;
            fprintf(f, "    %s DW %d DUP (?)\n", nom, taille);
        }
        else if (strcmp(type, "float") == 0)
        {
            if (val[0] != '\0' && strcmp(code, "CONST") == 0)
                fprintf(f, "    %s DW %d\n", nom, float_to_fixed(val));
            else
                fprintf(f, "    %s DW 0\n", nom);
        }
        else if (strcmp(type, "integer") == 0)
        {
            if (val[0] != '\0' && strcmp(code, "CONST") == 0)
                fprintf(f, "    %s DW %s\n", nom, val);
            else
                fprintf(f, "    %s DW 0\n", nom);
        }
    }

    /* variables temporaires */
    {
        char temps[500][20];
        int  nb_temps = 0;
        int j;

        for (j = 0; j < qc; j++)
        {
            const char *r = quad[j].res;
            if (r[0] == 'T' && r[1] >= '0' && r[1] <= '9'
                && strchr(r, '[') == NULL)
            {
                int deja = 0, k;
                for (k = 0; k < nb_temps; k++)
                    if (strcmp(temps[k], r) == 0) { deja = 1; break; }
                if (!deja && nb_temps < 500)
                {
                    strcpy(temps[nb_temps], r);
                    nb_temps++;
                }
            }
        }
        for (j = 0; j < nb_temps; j++)
            fprintf(f, "    %s DW 0\n", temps[j]);
    }

    fprintf(f, "DATA ENDS\n\n");
}

static void ecrire_pile(FILE *f)
{
    fprintf(f, "PILE SEGMENT STACK\n");
    fprintf(f, "    DW 100 DUP (?)\n");
    fprintf(f, "PILE ENDS\n\n");
}

/* ================================================================
   Traduction des quadruplets
   ================================================================ */

static void traduire_quad(FILE *f, int i)
{
    const char *op  = quad[i].oper;
    const char *o1  = quad[i].op1;
    const char *o2  = quad[i].op2;
    const char *res = quad[i].res;

    int f1 = operande_est_float(o1);
    int f2 = operande_est_float(o2);
    int fr = operande_est_float(res);
    int est_float_op = (f1 || f2 || fr);

    fprintf(f, "    ;; quad %d : ( %s , %s , %s , %s )\n", i, op, o1, o2, res);

    /* ------ affectations ------ */
    if (strcmp(op, ":") == 0 || strcmp(op, "=") == 0 || strcmp(op, "<--") == 0)
    {
        const char *src;
        if (strcmp(op, "=") == 0)       src = o1;
        else if (strcmp(op, "<--") == 0) src = o1;
        else                             src = o2;

        if (strcmp(src, "vide") != 0 && strcmp(res, "vide") != 0)
        {
            if (fr)
                /* destination float : s'assurer que src est en virgule fixe */
                emit_load_ax_as_float(f, src);
            else
                emit_load_ax(f, src);
            emit_store_ax(f, res);
        }
        return;
    }

    if (strcmp(op, "BOUNDS") == 0 || strcmp(op, "ADEC") == 0)
        return;

    /* ------ addition ------ */
    if (strcmp(op, "+") == 0)
    {
        if (est_float_op)
            emit_load_ax_as_float(f, o1);
        else
            emit_load_ax(f, o1);

        /* ajouter o2 */
        if (est_constante_float(o2))
            fprintf(f, "    ADD AX, %d\n", float_to_fixed(o2));
        else if (est_constante_entiere(o2))
            fprintf(f, "    ADD AX, %d\n", est_float_op ? atoi(o2)*SCALE : atoi(o2));
        else if (est_tableau(o2)) {
            char nom_tab[50], idx[50];
            sscanf(o2, "%[^[][%[^]]", nom_tab, idx);
            fprintf(f, "    MOV BX, %s\n", idx);
            fprintf(f, "    ADD BX, BX\n");
            if (est_float_op && !est_float_var(nom_tab)) {
                /* tableau entier dans contexte float : charger dans CX et convertir */
                fprintf(f, "    MOV CX, %s[BX]\n", nom_tab);
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, CX\n");
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV CX, AX\n");
                fprintf(f, "    POP AX\n");
                fprintf(f, "    ADD AX, CX\n");
            } else
                fprintf(f, "    ADD AX, %s[BX]\n", nom_tab);
        } else {
            if (est_float_op && !f2 && !est_constante_entiere(o2)) {
                /* variable entiere dans contexte float */
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, %s\n", o2);
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV CX, AX\n");
                fprintf(f, "    POP AX\n");
                fprintf(f, "    ADD AX, CX\n");
            } else
                fprintf(f, "    ADD AX, %s\n", o2);
        }

        emit_store_ax(f, res);
        return;
    }

    /* ------ soustraction ------ */
    if (strcmp(op, "-") == 0)
    {
        if (est_float_op)
            emit_load_ax_as_float(f, o1);
        else
            emit_load_ax(f, o1);

        if (est_constante_float(o2))
            fprintf(f, "    SUB AX, %d\n", float_to_fixed(o2));
        else if (est_constante_entiere(o2))
            fprintf(f, "    SUB AX, %d\n", est_float_op ? atoi(o2)*SCALE : atoi(o2));
        else if (est_tableau(o2)) {
            char nom_tab[50], idx[50];
            sscanf(o2, "%[^[][%[^]]", nom_tab, idx);
            fprintf(f, "    MOV BX, %s\n", idx);
            fprintf(f, "    ADD BX, BX\n");
            if (est_float_op && !est_float_var(nom_tab)) {
                fprintf(f, "    MOV CX, %s[BX]\n", nom_tab);
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, CX\n");
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV CX, AX\n");
                fprintf(f, "    POP AX\n");
                fprintf(f, "    SUB AX, CX\n");
            } else
                fprintf(f, "    SUB AX, %s[BX]\n", nom_tab);
        } else {
            if (est_float_op && !f2 && !est_constante_entiere(o2)) {
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, %s\n", o2);
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV CX, AX\n");
                fprintf(f, "    POP AX\n");
                fprintf(f, "    SUB AX, CX\n");
            } else
                fprintf(f, "    SUB AX, %s\n", o2);
        }

        emit_store_ax(f, res);
        return;
    }

    /* ------ multiplication ------ */
    /*
       Regles virgule fixe :
       float * float : (A*10) * (B*10) = A*B*100  -> diviser par SCALE
       int   * float : A * (B*10) = A*B*10         -> pas de correction
       float * int   : (A*10) * B = A*B*10         -> pas de correction
       int   * int   : A * B                        -> pas de correction
    */
    if (strcmp(op, "*") == 0)
    {
        if (est_float_op)
            emit_load_ax_as_float(f, o1);
        else
            emit_load_ax(f, o1);

        if (est_constante_float(o2)) {
            fprintf(f, "    MOV BX, %d\n", float_to_fixed(o2));
            fprintf(f, "    IMUL BX\n");
        } else if (est_constante_entiere(o2)) {
            fprintf(f, "    MOV BX, %s\n", o2);
            fprintf(f, "    IMUL BX\n");
        } else if (est_tableau(o2)) {
            char nom_tab[50], idx[50];
            sscanf(o2, "%[^[][%[^]]", nom_tab, idx);
            fprintf(f, "    MOV CX, %s\n", idx);
            fprintf(f, "    ADD CX, CX\n");
            fprintf(f, "    MOV BX, %s[CX]\n", nom_tab);
            /* si tableau entier dans contexte float, convertir BX */
            if (est_float_op && !est_float_var(nom_tab)) {
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, BX\n");
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV BX, AX\n");
                fprintf(f, "    POP AX\n");
            }
            fprintf(f, "    IMUL BX\n");
        } else {
            fprintf(f, "    MOV BX, %s\n", o2);
            /* variable entiere dans contexte float -> convertir BX */
            if (est_float_op && !f2) {
                fprintf(f, "    PUSH AX\n");
                fprintf(f, "    MOV AX, BX\n");
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
                fprintf(f, "    MOV BX, AX\n");
                fprintf(f, "    POP AX\n");
            }
            fprintf(f, "    IMUL BX\n");
        }

        /* correction : si les deux operandes etaient float, diviser par SCALE */
        if (f1 && f2) {
            fprintf(f, "    CWD\n");
            fprintf(f, "    MOV BX, %d\n", SCALE);
            fprintf(f, "    IDIV BX\n");
        }

        emit_store_ax(f, res);
        return;
    }

    /* ------ division ------ */
    /*
       float / float : (A*10) / (B*10) = A/B  -> multiplier A par SCALE avant
       float / int   : (A*10) / B = (A/B)*10  -> correct
       int   / float : A / (B*10) -> convertir A en float d'abord
       int   / int   : A / B      -> correct
    */
    if (strcmp(op, "/") == 0)
    {
        if (est_float_op)
            emit_load_ax_as_float(f, o1);
        else
            emit_load_ax(f, o1);

        /* si float/float ou int/float : multiplier le dividende par SCALE */
        if (f1 && f2) {
            /* float/float: (A*10)/(B*10) = A/B sans unite
               Ne PAS pre-multiplier. On post-multiplie par SCALE apres IDIV.
               L'ancien code pre-multipliait -> overflow 16 bits. */
        } else if (f2 || (est_float_op && est_constante_float(o2))) {
            /* int/float ou x/constante_float: convertir dividende en vf */
            fprintf(f, "    MOV BX, %d\n", SCALE);
            fprintf(f, "    IMUL BX\n");
        } else if (est_float_op && fr && !f1) {
            /* int / int mais resultat float */
            fprintf(f, "    MOV BX, %d\n", SCALE);
            fprintf(f, "    IMUL BX\n");
        }

        fprintf(f, "    CWD\n");

        if (est_constante_float(o2)) {
            int v = float_to_fixed(o2);
            if (v == 0) v = 1;
            fprintf(f, "    MOV BX, %d\n", v);
            fprintf(f, "    IDIV BX\n");
        } else if (est_constante_entiere(o2)) {
            int v = atoi(o2);
            if (v == 0) v = 1;
            fprintf(f, "    MOV BX, %d\n", v);
            fprintf(f, "    IDIV BX\n");
        } else if (est_tableau(o2)) {
            char nom_tab[50], idx[50];
            sscanf(o2, "%[^[][%[^]]", nom_tab, idx);
            fprintf(f, "    MOV CX, %s\n", idx);
            fprintf(f, "    ADD CX, CX\n");
            fprintf(f, "    MOV BX, %s[CX]\n", nom_tab);
            fprintf(f, "    IDIV BX\n");
        } else {
            fprintf(f, "    MOV BX, %s\n", o2);
            fprintf(f, "    IDIV BX\n");
        }

        /* float/float: quotient = A/B (entier), remettre en virgule fixe */
        if (f1 && f2) {
            fprintf(f, "    MOV BX, %d\n", SCALE);
            fprintf(f, "    IMUL BX\n");
        }

        emit_store_ax(f, res);
        return;
    }

    /* ------ saut inconditionnel ------ */
    if (strcmp(op, "BR") == 0)
    {
        fprintf(f, "    JMP L%s\n", o1);
        return;
    }

    /* ------ sauts conditionnels ------ */
    if (strcmp(op, "BGE") == 0 || strcmp(op, "BLE") == 0 ||
        strcmp(op, "BG")  == 0 || strcmp(op, "BL")  == 0 ||
        strcmp(op, "BE")  == 0 || strcmp(op, "BNE") == 0)
    {
        int o2_float = operande_est_float(o2);
        int res_float = operande_est_float(res);

        emit_load_ax(f, o2);

        if (est_constante_float(res))
            fprintf(f, "    CMP AX, %d\n", float_to_fixed(res));
        else if (est_constante_entiere(res))
            /* si o2 est float, comparer avec res converti en virgule fixe */
            fprintf(f, "    CMP AX, %d\n", o2_float ? atoi(res)*SCALE : atoi(res));
        else if (est_tableau(res)) {
            char nom_tab[50], idx[50];
            sscanf(res, "%[^[][%[^]]", nom_tab, idx);
            fprintf(f, "    MOV BX, %s\n", idx);
            fprintf(f, "    ADD BX, BX\n");
            fprintf(f, "    CMP AX, %s[BX]\n", nom_tab);
        } else
            fprintf(f, "    CMP AX, %s\n", res);

        if      (strcmp(op, "BGE") == 0) fprintf(f, "    JGE L%s\n", o1);
        else if (strcmp(op, "BLE") == 0) fprintf(f, "    JLE L%s\n", o1);
        else if (strcmp(op, "BG")  == 0) fprintf(f, "    JG  L%s\n", o1);
        else if (strcmp(op, "BL")  == 0) fprintf(f, "    JL  L%s\n", o1);
        else if (strcmp(op, "BE")  == 0) fprintf(f, "    JE  L%s\n", o1);
        else if (strcmp(op, "BNE") == 0) fprintf(f, "    JNE L%s\n", o1);
        return;
    }

    /* ------ sortie ------ */
    if (strcmp(op, "OUT") == 0)
    {
        if (o1[0] == '"') {
            fprintf(f, "    ;; OUT chaine : %s\n", o1);
        } else {
            emit_load_ax(f, o1);
            if (operande_est_float(o1)) {
                fprintf(f, "    ;; afficher float (virgule fixe /SCALE) : %s\n", o1);
                fprintf(f, "    CALL PRINT_FLOAT\n");
            } else {
                fprintf(f, "    ;; afficher entier : %s\n", o1);
                fprintf(f, "    CALL PRINT_AX\n");
            }
        }
        return;
    }

    /* ------ entree ------ */
    if (strcmp(op, "IN") == 0)
    {
        /* Le parseur genere quadr("IN","vide","vide", variable) -> destination = RES */
        const char *dest_in = (strcmp(res, "vide") != 0) ? res : o1;
        fprintf(f, "    ;; IN : saisie dans %s\n", dest_in);
        fprintf(f, "    CALL READ_INT\n");
        if (strcmp(dest_in, "vide") != 0) {
            if (est_float_var(dest_in)) {
                fprintf(f, "    MOV BX, %d\n", SCALE);
                fprintf(f, "    IMUL BX\n");
            }
            emit_store_ax(f, dest_in);
        }
        return;
    }

    fprintf(f, "    ;; [non traduit] %s %s %s %s\n", op, o1, o2, res);
}

/* ================================================================
   Procedures assembleur
   ================================================================ */

/* PRINT_AX : affiche AX en entier decimal */
static void ecrire_procedure_print_ax(FILE *f)
{
    fprintf(f,
        ";; ---- PRINT_AX : affiche AX en entier decimal ----\n"
        "PRINT_AX PROC\n"
        "    PUSH BX\n"
        "    PUSH CX\n"
        "    PUSH DX\n"
        "    CMP  AX, 0\n"
        "    JNE  PA_NONZERO\n"
        "    MOV  DL, '0'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    JMP  PA_NEWLINE\n"
        "PA_NONZERO:\n"
        "    CMP  AX, 0\n"
        "    JGE  PA_POS\n"
        "    PUSH AX\n"
        "    MOV  DL, '-'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    POP  AX\n"
        "    NEG  AX\n"
        "PA_POS:\n"
        "    MOV  BX, 10\n"
        "    MOV  CX, 0\n"
        "PA_LOOP:\n"
        "    MOV  DX, 0\n"
        "    CWD\n"
        "    IDIV BX\n"
        "    PUSH DX\n"
        "    INC  CX\n"
        "    CMP  AX, 0\n"
        "    JNE  PA_LOOP\n"
        "PA_PRINT:\n"
        "    POP  DX\n"
        "    ADD  DL, 48\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    LOOP PA_PRINT\n"
        "PA_NEWLINE:\n"
        "    MOV  DL, 13\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    MOV  DL, 10\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    POP  DX\n"
        "    POP  CX\n"
        "    POP  BX\n"
        "    RET\n"
        "PRINT_AX ENDP\n\n"
    );
}

/*
   PRINT_FLOAT : affiche AX/SCALE sous forme entier.decimale(s)
   SCALE=10 -> 1 decimale  (ex: 25 -> "2.5")
   Gere : zero (-> "0.0"), negatif, positif
*/
static void ecrire_procedure_print_float(FILE *f)
{
    fprintf(f,
        ";; ---- PRINT_FLOAT : affiche AX/%d (virgule fixe, 1 decimale) ----\n"
        "PRINT_FLOAT PROC\n"
        "    PUSH BX\n"
        "    PUSH CX\n"
        "    PUSH DX\n"
        "    ;; cas zero\n"
        "    CMP  AX, 0\n"
        "    JNE  PF_NONZERO\n"
        "    MOV  DL, '0'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    MOV  DL, '.'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    MOV  DL, '0'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    JMP  PF_NEWLINE\n"
        "PF_NONZERO:\n"
        "    ;; signe\n"
        "    CMP  AX, 0\n"
        "    JGE  PF_POS\n"
        "    PUSH AX\n"
        "    MOV  DL, '-'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    POP  AX\n"
        "    NEG  AX\n"
        "PF_POS:\n"
        "    ;; diviser par SCALE : AX=partie entiere, DX=decimale\n"
        "    MOV  BX, %d\n"
        "    MOV  DX, 0\n"
        "    CWD\n"
        "    IDIV BX\n"
        "    PUSH DX\n"
        "    ;; afficher partie entiere\n"
        "    MOV  BX, 10\n"
        "    MOV  CX, 0\n"
        "PF_INT_LOOP:\n"
        "    MOV  DX, 0\n"
        "    CWD\n"
        "    IDIV BX\n"
        "    PUSH DX\n"
        "    INC  CX\n"
        "    CMP  AX, 0\n"
        "    JNE  PF_INT_LOOP\n"
        "PF_INT_PRINT:\n"
        "    POP  DX\n"
        "    ADD  DL, 48\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    LOOP PF_INT_PRINT\n"
        "    ;; afficher '.'\n"
        "    MOV  DL, '.'\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    ;; afficher 1 chiffre decimal\n"
        "    POP  DX\n"
        "    ADD  DL, 48\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "PF_NEWLINE:\n"
        "    MOV  DL, 13\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    MOV  DL, 10\n"
        "    MOV  AH, 2\n"
        "    INT  21h\n"
        "    POP  DX\n"
        "    POP  CX\n"
        "    POP  BX\n"
        "    RET\n"
        "PRINT_FLOAT ENDP\n\n",
        SCALE, SCALE
    );
}

/* READ_INT : lit un entier multi-chiffres -> AX */
static void ecrire_procedure_read_int(FILE *f)
{
    fprintf(f,
        ";; ---- READ_INT : lit un entier au clavier -> AX ----\n"
        "READ_INT PROC\n"
        "    PUSH BX\n"
        "    PUSH CX\n"
        "    PUSH DX\n"
        "    MOV  AX, 0\n"
        "    MOV  BX, 10\n"
        "RI_LOOP:\n"
        "    PUSH AX\n"
        "    MOV  AH, 1\n"
        "    INT  21h\n"
        "    CMP  AL, 13\n"
        "    JE   RI_DONE\n"
        "    CMP  AL, 48\n"
        "    JL   RI_IGNORE\n"
        "    CMP  AL, 57\n"
        "    JG   RI_IGNORE\n"
        "    SUB  AL, 48\n"
        "    CBW\n"
        "    MOV  CX, AX\n"
        "    POP  AX\n"
        "    IMUL BX\n"
        "    ADD  AX, CX\n"
        "    JMP  RI_LOOP\n"
        "RI_IGNORE:\n"
        "    POP  AX\n"
        "    JMP  RI_LOOP\n"
        "RI_DONE:\n"
        "    POP  CX\n"
        "    POP  DX\n"
        "    POP  CX\n"
        "    POP  BX\n"
        "    RET\n"
        "READ_INT ENDP\n\n"
    );
}

/* ================================================================
   Point d'entree
   ================================================================ */

void generer_code_8086(const char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "w");
    if (!f) {
        printf("Erreur : impossible de creer le fichier %s\n", nom_fichier);
        return;
    }

    printf("\n========== GENERATION DU CODE 8086 ==========\n");
    printf("Fichier genere : %s\n", nom_fichier);
    printf("Mode float     : virgule fixe x%d (1 decimale)\n", SCALE);

    fprintf(f, "TITLE ProLang_8086\n\n");
    fprintf(f, ";; Virgule fixe SCALE=%d : ex 2.5->%d, 3.1->%d\n\n",
            SCALE, (int)(2.5*SCALE+0.5), (int)(3.1*SCALE+0.5));

    ecrire_pile(f);
    ecrire_data_segment(f);

    fprintf(f, "CODE SEGMENT\n");
    fprintf(f, "MAIN:\n");
    fprintf(f, "    ASSUME CS:CODE, DS:DATA, SS:PILE\n");
    fprintf(f, "    MOV AX, DATA\n");
    fprintf(f, "    MOV DS, AX\n\n");

    int i;
    for (i = 0; i < qc; i++) {
        fprintf(f, "L%d:\n", i);
        traduire_quad(f, i);
    }

    fprintf(f, "L%d:\n", qc);
    fprintf(f, "\n    ;; Fin du programme\n");
    fprintf(f, "    MOV AH, 4Ch\n");
    fprintf(f, "    INT 21h\n\n");

    ecrire_procedure_print_ax(f);
    ecrire_procedure_print_float(f);
    ecrire_procedure_read_int(f);

    fprintf(f, "CODE ENDS\n");
    fprintf(f, "END MAIN\n");

    fclose(f);
    printf("Code 8086 genere avec succes dans : %s\n", nom_fichier);
    printf("=============================================\n");
}
