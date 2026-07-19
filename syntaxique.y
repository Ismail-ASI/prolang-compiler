
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ts.h"
#include "quad.h"
#include "optim.h"
#include "codegen.h"

extern int nb_ligne;
extern int tok_col;

char SauvType[20];
int  SauvVal = -1;
int  bz_quad = -1;
int  bz_quad_and = -1;
int  bz_or_true  = -1;

static int tc = 0;
static char tmp[20];

typedef struct {
    char type[20];
    char val[40];
} Noeud;

static Noeud* new_noeud(const char *type, const char *val)
{
    Noeud *n = malloc(sizeof(Noeud));
    strncpy(n->type, type ? type : "", 19);
    strncpy(n->val,  val  ? val  : "", 39);
    return n;
}

static char* new_tmp()
{
    static char buf[20];
    sprintf(buf, "T%d", tc++);
    return buf;
}

int yylex(void);
int yyerror(const char *msg);
%}

%union {
    int    entier;
    float  reel;
    char  *chaine;
    struct {
        char type[20];
        char val[40];
    } noeud;
}

%token BEGINPROJECT MIV ENDPROJECT SETUP RUN DEFINE CONST INTEGER FLOAT
%token IF THEN ELSE ENDIF LOOP WHILE ENDLOOP FOR IN TO ENDFOR
%token MC_OUT AND OR NON MC_IN
%token AFFECTATION INFEGAL SUPEGAL EGAL DIFF INF SUP EGALE_INIT
%token PLUS MOINS MULT DIV
%token PVIR DPTS BARRE PARG PARD CROG CROD ACCOG ACCOD VIRG
%token <chaine> IDF
%token <entier> UINT SINT
%token <reel>   UFLOAT SFLOAT
%token <chaine> CHAINE
%type  <noeud>  expr terme facteur val_init val_limit cst
%type  <chaine> liste_idfs
%left OR
%left AND
%right NON
%%

programme
    : BEGINPROJECT MIV PVIR SETUP DPTS partie_decl RUN DPTS ACCOG liste_instrs ACCOD ENDPROJECT PVIR
    ;

partie_decl
    : /* vide */
    | partie_decl decl
    ;

decl
    : decl_var
    | decl_const
    ;

decl_var
    : DEFINE IDF DPTS type PVIR
        {
            int pos = chercher($2);
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, $2);
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, $2);
            else
            {
                strcpy(TS[pos].type, SauvType);
                quadr(":", SauvType, "vide", $2);
            }
        }

    | DEFINE IDF DPTS type EGALE_INIT expr PVIR
        {
            int pos = chercher($2);
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, $2);
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, $2);
            else
            {
                strcpy(TS[pos].type, SauvType);
                if ($6.type[0] != '\0' && strcmp(SauvType, $6.type) != 0)
                    printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s attend %s mais recoit %s\n",
                           nb_ligne, tok_col, $2, SauvType, $6.type);
                quadr(":", SauvType, $6.val, $2);
            }
        }

    | DEFINE IDF DPTS CROG type PVIR cst CROD PVIR
        {
            int pos = chercher($2);
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, $2);
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, $2);
            else
            {
                strcpy(TS[pos].type, SauvType);
                strcpy(TS[pos].code, "TABLEAU");
                int taille = atoi($7.val);
                if (taille > 0)
                {
                    sprintf(TS[pos].val, "%d", taille);
                    char upper[20];
                    sprintf(upper, "%d", taille - 1);
                    quadr("BOUNDS", "0", upper, "vide");
                    quadr("ADEC", $2, "vide", "vide");
                }
                else
                    printf("Erreur semantique, ligne %d, colonne %d, taille de tableau invalide pour %s\n",
                           nb_ligne, tok_col, $2);
            }
        }

    | DEFINE IDF BARRE liste_idfs DPTS type PVIR
        {
            /* liste_idfs contains identifiers AFTER the first BARRE, $2 is the first one */
            /* emit ":" quad for each identifier in liste_idfs (all except $2: no init) */
            char *liste = strdup($4);
            char *tok = strtok(liste, "|");
            while (tok != NULL)
            {
                int p = chercher(tok);
                if (p == -1)
                    printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                           nb_ligne, tok_col, tok);
                else if (TS[p].type[0] != '\0')
                    printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                           nb_ligne, tok_col, tok);
                else
                {
                    strcpy(TS[p].type, SauvType);
                    quadr(":", SauvType, "vide", tok);
                }
                tok = strtok(NULL, "|");
            }
            free(liste);
            /* $2 is the first identifier declared (define $2 | liste_idfs : type) - no init */
            int pos = chercher($2);
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, $2);
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, $2);
            else
            {
                strcpy(TS[pos].type, SauvType);
                quadr(":", SauvType, "vide", $2);
            }
        }

    ;
/* Note: "define k | l : integer = 10;" is intentionally NOT supported.
   With multiple identifiers it is impossible to know which one receives
   the initial value, so initialization must be done with a single
   identifier: "define k : integer = 10;" */

liste_idfs
    : IDF
        { $$ = strdup($1); }
    | liste_idfs BARRE IDF
        {
            char *buf = malloc(strlen($1) + 1 + strlen($3) + 1);
            sprintf(buf, "%s|%s", $1, $3);
            $$ = buf;
        }
    ;

type
    : INTEGER  { strcpy(SauvType, "integer"); }
    | FLOAT    { strcpy(SauvType, "float");   }
    ;

decl_const
    : CONST IDF DPTS type EGALE_INIT cst PVIR
        {
            int pos = chercher($2);
            if (pos == -1)
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non trouve dans TS\n",
                       nb_ligne, tok_col, $2);
            else if (TS[pos].type[0] != '\0')
                printf("Erreur semantique, ligne %d, colonne %d, double declaration de %s\n",
                       nb_ligne, tok_col, $2);
            else
            {
                strcpy(TS[pos].type, SauvType);
                strcpy(TS[pos].code, "CONST");
                quadr(":", SauvType, $6.val, $2);
            }
        }
    ;

cst
    : UINT   { SauvVal = $1; strcpy($$.type,"integer"); sprintf($$.val,"%d",$1); }
    | SINT   { SauvVal = $1; strcpy($$.type,"integer"); sprintf($$.val,"%d",$1); }
    | UFLOAT { strcpy($$.type,"float");   sprintf($$.val,"%g",$1); }
    | SFLOAT { strcpy($$.type,"float");   sprintf($$.val,"%g",$1); }
    ;

liste_instrs
    : /* vide */
    | liste_instrs instr
    ;

instr
    : instr_affectation
    | instr_condition
    | instr_loop_while
    | instr_for
    | instr_input
    | instr_out
    ;

instr_affectation
    : IDF AFFECTATION expr PVIR
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
            else if (strcmp(TS[pos].code, "CONST") == 0)
                printf("Erreur semantique, ligne %d, colonne %d, modification d'une constante %s\n",
                       nb_ligne, tok_col, $1);
            else if ($3.type[0] != '\0' && strcmp(TS[pos].type, $3.type) != 0
                     && !(strcmp(TS[pos].type, "float") == 0 && strcmp($3.type, "integer") == 0))
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s est %s mais recoit %s\n",
                       nb_ligne, tok_col, $1, TS[pos].type, $3.type);
            quadr("<--", $3.val, "vide", $1);
        }

    | IDF CROG expr { $<entier>$ = SauvVal; } CROD AFFECTATION expr PVIR
        {
            int pos = chercher($1);
            int idx_sauve = $<entier>4;
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
            else if (strcmp(TS[pos].code, "CONST") == 0)
                printf("Erreur semantique, ligne %d, colonne %d, modification d'une constante %s\n",
                       nb_ligne, tok_col, $1);
            else if (strcmp(TS[pos].code, "TABLEAU") == 0 && TS[pos].val[0] != '\0')
            {
                int taille = atoi(TS[pos].val);
                if (idx_sauve < 0 || idx_sauve >= taille)
                    printf("Erreur semantique, ligne %d, colonne %d, index hors limites pour %s\n",
                           nb_ligne, tok_col, $1);
            }
            if ($7.type[0] != '\0' && TS[pos].type[0] != '\0' && strcmp(TS[pos].type, $7.type) != 0
                && !(strcmp(TS[pos].type, "float") == 0 && strcmp($7.type, "integer") == 0))
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : %s est %s mais reçoit %s\n",
                       nb_ligne, tok_col, $1, TS[pos].type, $7.type);
            char dest[60];
            sprintf(dest, "%s[%s]", $1, $3.val);
            quadr("<--", $7.val, "vide", dest);
        }
    ;

instr_condition
    : IF PARG condition PARD THEN DPTS ACCOG
        {
            /* Patch OR true-branch BR toward then-body entry */
            if (bz_or_true >= 0)
            {
                sprintf(tmp, "%d", qc);
                updateQuad(bz_or_true, 1, tmp);
                bz_or_true = -1;
            }
            /* Save bz_quad & bz_quad_and NOW before the then-body overwrites them */
            $<entier>$ = bz_quad;
        }
      liste_instrs ACCOD
        {
            int saved_bz     = $<entier>8;
            int saved_bz_and = bz_quad_and;
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            /* Patch condition false-branch(es) → else entry */
            sprintf(tmp, "%d", qc);
            updateQuad(saved_bz, 1, tmp);
            if (saved_bz_and >= 0) { updateQuad(saved_bz_and, 1, tmp); bz_quad_and = -1; }
            $<entier>$ = br_quad;
        }
      ELSE ACCOG liste_instrs ACCOD ENDIF PVIR
        {
            sprintf(tmp, "%d", qc);
            updateQuad($<entier>11, 1, tmp);
        }
    ;

instr_loop_while
    : LOOP WHILE
        {
            $<entier>$ = qc;   /* slot 3: debut */
        }
      PARG condition PARD
        {
            if (bz_or_true >= 0)
            {
                char buf[20]; sprintf(buf, "%d", qc);
                updateQuad(bz_or_true, 1, buf);
                bz_or_true = -1;
            }
            $<entier>$ = bz_quad;     /* slot 7: bz_quad after condition */
        }
        {
            $<entier>$ = bz_quad_and; /* slot 8: bz_quad_and after condition */
        }
      ACCOG liste_instrs ACCOD ENDLOOP PVIR
        {
            int debut        = $<entier>3;
            int saved_bz     = $<entier>7;
            int saved_bz_and = $<entier>8;
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            char buf[20];
            sprintf(buf, "%d", debut);
            updateQuad(br_quad, 1, buf);
            sprintf(buf, "%d", qc);
            updateQuad(saved_bz, 1, buf);
            if (saved_bz_and >= 0) { updateQuad(saved_bz_and, 1, buf); bz_quad_and = -1; }
        }
    ;

instr_for
    : FOR IDF IN val_init TO val_limit 
        {
            int pos = chercher($2);
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $2);
            else if (strcmp(TS[pos].type, "integer") != 0)
                printf("Erreur semantique, ligne %d, colonne %d, incompatibilite de type : compteur de boucle %s doit etre integer\n",
                       nb_ligne, tok_col, $2);
            if ($4.val[0] != '\0' && $6.val[0] != '\0')
            {
                char *end1, *end2;
                long v_init  = strtol($4.val, &end1, 10);
                long v_limit = strtol($6.val, &end2, 10);
                if (*end1 == '\0' && *end2 == '\0' && v_limit <= v_init)
                    printf("Erreur semantique, ligne %d, colonne %d, valeur de fin (%ld) doit etre superieure a valeur de depart (%ld)\n",
                           nb_ligne, tok_col, v_limit, v_init);
            }
            quadr("=", $4.val, "vide", $2);
            int saved_bz_for = qc;
            bz_quad = qc;
            quadr("BG", "vide", $2, $6.val);
            $<entier>$ = saved_bz_for;
        }
      ACCOG liste_instrs ACCOD ENDFOR PVIR
        {
            int test_quad = $<entier>7;
            char *t = new_tmp();
            quadr("+", $2, "1", t);
            quadr("=", t, "vide", $2);
            int br_quad = qc;
            quadr("BR", "vide", "vide", "vide");
            sprintf(tmp, "%d", test_quad);
            updateQuad(br_quad, 1, tmp);
            sprintf(tmp, "%d", qc);
            updateQuad(test_quad, 1, tmp);
        }
    ;

val_init
    : UINT
        {
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
        }
    | SINT
        {
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
            if ($1 < 0)
                printf("Erreur semantique, ligne %d, colonne %d, valeur de depart negative (%d) dans for\n",
                       nb_ligne, tok_col, $1);
        }
    | IDF
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
                strcpy($$.type, "");
            }
            else
                strcpy($$.type, TS[pos].type);
            strcpy($$.val, $1);
        }
    ;

val_limit
    : UINT
        {
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
        }
    | SINT
        {
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
            if ($1 < 0)
                printf("Erreur semantique, ligne %d, colonne %d, valeur de fin negative (%d) dans for\n",
                       nb_ligne, tok_col, $1);
        }
    | IDF
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
                strcpy($$.type, "");
            }
            else
                strcpy($$.type, TS[pos].type);
            strcpy($$.val, $1);
        }
    ;

instr_input
    : MC_IN PARG IDF PARD PVIR
        {
            int pos = chercher($3);
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $3);
            quadr("IN", "vide", "vide", $3);
        }
    ;

instr_out
    : MC_OUT PARG liste_out_args PARD PVIR
    ;

liste_out_args
    : out_arg
    | liste_out_args VIRG out_arg
    ;

out_arg
    : CHAINE
        { quadr("OUT", $1, "vide", "vide"); }
    | IDF
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
            quadr("OUT", $1, "vide", "vide");
        }
    ;

condition
    : expr_comp
    | PARG condition PARD
    | condition AND
        {
            /* A faux → bz_quad de A saute au else (laissé non patché, sera patché par instr_condition).
               A vrai → tombe dans B. On sauvegarde bz_quad de A pour que instr_condition le patche. */
            $<entier>$ = bz_quad;
        }
      condition
        {
            /* bz_quad final = quad de B (si B faux → else).
               Le quad de A (sauvé dans $3) sera aussi patché vers else par instr_condition
               via la variable globale bz_quad qu'on met à jour ici avec le dernier. */
            /* On garde bz_quad = quad de B (déjà mis à jour par expr_comp de B).
               Le quad de A reste non patché avec "vide" ; instr_condition doit patcher les deux.
               Pour rester sur le même format, on stocke le quad de A dans un second global. */
            bz_quad_and = $<entier>3;
        }
    | condition OR
        {
            /* A vrai → BR inconditionnel vers then-body.
               On émet le BR EN PREMIER pour que l'entrée de B soit APRÈS lui. */
            if (bz_or_true >= 0)
            {
                /* Chaîner un bz_or_true précédent vers ce BR */
                char buf[20]; sprintf(buf, "%d", qc);
                updateQuad(bz_or_true, 1, buf);
            }
            bz_or_true = qc;
            quadr("BR", "vide", "vide", "vide");
            /* A faux → évalue B. Patche bz_quad ET bz_quad_and vers entrée de B (= qc, après le BR). */
            sprintf(tmp, "%d", qc);
            updateQuad(bz_quad, 1, tmp);
            if (bz_quad_and >= 0) { updateQuad(bz_quad_and, 1, tmp); bz_quad_and = -1; }
        }
      condition
        {
            /* bz_quad final = quad de B (si B faux → else). Mis à jour par expr_comp de B. */
        }
    | NON PARG condition PARD
        {
            /* C vrai → bz_quad de C saute → else  (NON faux)
               C faux → tombe → BR → then-body            (NON vrai) */
            int br_then = qc;
            quadr("BR", "vide", "vide", "vide");
            /* Si un bz_or_true existait déjà (mis par un OR parent), on le chaîne
               vers br_then pour ne pas le perdre. */
            if (bz_or_true >= 0)
            {
                char buf[20];
                sprintf(buf, "%d", br_then);
                updateQuad(bz_or_true, 1, buf);
            }
            bz_or_true = br_then;
        }
    ;

expr_comp
    : expr INF     expr  { bz_quad = qc; quadr("BGE", "vide", $1.val, $3.val); }
    | expr SUP     expr  { bz_quad = qc; quadr("BLE", "vide", $1.val, $3.val); }
    | expr INFEGAL expr  { bz_quad = qc; quadr("BG",  "vide", $1.val, $3.val); }
    | expr SUPEGAL expr  { bz_quad = qc; quadr("BL",  "vide", $1.val, $3.val); }
    | expr EGAL    expr  { bz_quad = qc; quadr("BNE", "vide", $1.val, $3.val); }
    | expr DIFF    expr  { bz_quad = qc; quadr("BE",  "vide", $1.val, $3.val); }
    ;

expr
    : terme
        { $$ = $1; }
    | expr PLUS terme
        {
            if ($1.type[0] == '\0' || $3.type[0] == '\0')
                strcpy($$.type, "");
            else if (strcmp($1.type, $3.type) == 0)
                strcpy($$.type, $1.type);
            else
                strcpy($$.type, "float");
            char *t = new_tmp();
            strcpy($$.val, t);
            quadr("+", $1.val, $3.val, t);
        }
    | expr MOINS terme
        {
            if ($1.type[0] == '\0' || $3.type[0] == '\0')
                strcpy($$.type, "");
            else if (strcmp($1.type, $3.type) == 0)
                strcpy($$.type, $1.type);
            else
                strcpy($$.type, "float");
            char *t = new_tmp();
            strcpy($$.val, t);
            quadr("-", $1.val, $3.val, t);
        }
    ;

terme
    : facteur
        { $$ = $1; }
    | terme MULT facteur
        {
            if ($1.type[0] == '\0' || $3.type[0] == '\0')
                strcpy($$.type, "");
            else if (strcmp($1.type, $3.type) == 0)
                strcpy($$.type, $1.type);
            else
                strcpy($$.type, "float");
            char *t = new_tmp();
            strcpy($$.val, t);
            quadr("*", $1.val, $3.val, t);
        }
    | terme DIV facteur
        {
            if (SauvVal == 0)
                printf("Erreur semantique, ligne %d, colonne %d, division par zero\n",
                       nb_ligne, tok_col);
            if ($1.type[0] == '\0' || $3.type[0] == '\0')
                strcpy($$.type, "");
            else if (strcmp($1.type, $3.type) == 0)
                strcpy($$.type, $1.type);
            else
                strcpy($$.type, "float");
            char *t = new_tmp();
            strcpy($$.val, t);
            quadr("/", $1.val, $3.val, t);
        }
    ;

facteur
    : IDF
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
                strcpy($$.type, "");
            }
            else
                strcpy($$.type, TS[pos].type);
            strcpy($$.val, $1);
        }
    | UINT
        {
            SauvVal = $1;
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
        }
    | SINT
        {
            SauvVal = $1;
            strcpy($$.type, "integer");
            sprintf($$.val, "%d", $1);
        }
    | UFLOAT
        {
            strcpy($$.type, "float");
            sprintf($$.val, "%g", $1);
        }
    | SFLOAT
        {
            strcpy($$.type, "float");
            sprintf($$.val, "%g", $1);
        }
    | IDF CROG expr { $<entier>$ = SauvVal; } CROD
        {
            int pos = chercher($1);
            if (pos == -1 || TS[pos].type[0] == '\0')
            {
                printf("Erreur semantique, ligne %d, colonne %d, identificateur %s non declare\n",
                       nb_ligne, tok_col, $1);
                strcpy($$.type, "");
                strcpy($$.val, "vide");
            }
            else
            {
                if (strcmp(TS[pos].code, "TABLEAU") == 0 && TS[pos].val[0] != '\0')
                {
                    int taille = atoi(TS[pos].val);
                    int idx_sauve = $<entier>4;
                    if (idx_sauve < 0 || idx_sauve >= taille)
                        printf("Erreur semantique, ligne %d, colonne %d, index hors limites pour %s\n",
                               nb_ligne, tok_col, $1);
                }
                char *t = new_tmp();
                strcpy($$.type, TS[pos].type);
                strcpy($$.val, t);
                char operande[60];
                sprintf(operande, "%s[%s]", $1, $3.val);
                quadr("<--", operande, "vide", t);
            }
        }
    | PARG expr PARD { $$ = $2; }
    ;

%%

int yyerror(const char *msg)
{
    printf("Erreur syntaxique, ligne %d, colonne %d : %s\n", nb_ligne, tok_col, msg);
    return 1;
}

int main(int argc, char *argv[])
{
    extern FILE *yyin;

    initialization();

    if (argc > 1)
    {
        FILE *f = fopen(argv[1], "r");
        if (!f) { perror(argv[1]); return 1; }
        yyin = f;
    }

    yyparse();

    afficher();
    printf("\n****** Code intermédiaire AVANT optimisation ******\n");
    afficher_qdr();
 
    optimiser_quadruplets();

    printf("\n****** Code intermédiaire APRÈS optimisation ******\n");
    afficher_qdr();
    generer_code_8086("output.asm");
    return 0;
}
