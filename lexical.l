%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "syntaxique.tab.h"
#include "quad.h"
#include "ts.h"         

int nb_ligne = 1;
int nb_col   = 1;
int tok_col  = 1;

void skip_ml_comment(void);
%}

DIGIT    [0-9]
UINT     {DIGIT}+
UFLOAT   {DIGIT}+"."{DIGIT}+
SIGN     [+\-]
SINT     "("+{SIGN}{UINT}+")"
SFLOAT   "("+{SIGN}{UFLOAT}+")"
IDF_LIKE  [A-Za-z][a-z0-9]*
SL_CMT   "%%"[^\n]*

%%

[ ]         { nb_col++; }
[\t]        { nb_col += 4; }
\n          { nb_ligne++; nb_col = 1; }

{SL_CMT}    { nb_col += yyleng; }

"//*"       { skip_ml_comment(); }

"BeginProject"  {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return BEGINPROJECT;
                }
"M1_iv_2526"   {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return MIV;       
                }                  
"EndProject"    {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return ENDPROJECT;
                }
"Setup"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return SETUP;
                }
"Run"           {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return RUN;
                }
"define"        {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return DEFINE;
                }
"const"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return CONST;
                }
"integer"       {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return INTEGER;
                }
"float"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return FLOAT;
                }
"if"            {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return IF;
                }
"then"          {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return THEN;
                }
"else"          {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return ELSE;
                }
"endIf"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return ENDIF;
                }
"loop"          {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return LOOP;
                }
"while"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return WHILE;
                }
"endloop"       {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return ENDLOOP;
                }
"for"           {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return FOR;
                }
"in"         {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return IN;
                }
"to"            {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return TO;
                }
"endfor"        {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return ENDFOR;
                }
"out"        {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return MC_OUT;
                }

"input"      {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return MC_IN;
                }

"AND"           {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return AND;
                }
"OR"            {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return OR;
                }
"NON"           {
                    tok_col = nb_col; nb_col += yyleng;
                    Rechercher(yytext, "Mot-cle", "", "", 2);
                    return NON;
                }

{UFLOAT}    {
                tok_col = nb_col; nb_col += yyleng;
                yylval.reel = atof(yytext);
                Rechercher(yytext, "CONST", "float", yytext, 1);
                return UFLOAT;
            }
{UINT}      {
                tok_col = nb_col; nb_col += yyleng;
                yylval.entier = atoi(yytext);
                Rechercher(yytext, "CONST", "integer", yytext, 1);
                return UINT;
            }
{SFLOAT}    {
                tok_col = nb_col; nb_col += yyleng;
                yylval.reel = atof(yytext);
                Rechercher(yytext, "CONST", "float", yytext, 1);
                return SFLOAT;
            }
{SINT}      {
                tok_col = nb_col; nb_col += yyleng;
                int v; sscanf(yytext, "(%d)", &v);
                yylval.entier = v;
                Rechercher(yytext, "CONST", "integer", yytext, 1);
                return SINT;
            }

\"[^\"]*\"  {
                tok_col = nb_col;
                nb_col += yyleng;
                yylval.chaine = strdup(yytext);
                return CHAINE;
            }

\"[^\"\n]*  {
                tok_col = nb_col;
                nb_col += yyleng;
                printf("Erreur lexicale, ligne %d, colonne %d, entite chaine non fermee\n",
                       nb_ligne, tok_col);
            }

{IDF_LIKE}  {
                tok_col = nb_col;
                nb_col += yyleng;
                int len   = yyleng;
                int valid = 1;
                int i;

                
                if (len > 14) valid = 0;

                
                if (valid && yytext[len - 1] == '_') valid = 0;

                
                if (valid)
                {
                    for (i = 0; i < len - 1; i++)
                    {
                        if (yytext[i] == '_' && yytext[i+1] == '_')
                        {
                            valid = 0; break;
                        }
                    }
                }

                if (!valid)
                {
                    printf("Erreur lexicale, ligne %d, colonne %d, entite %s\n",
                           nb_ligne, tok_col, yytext);
                }
                else
                {
                    yylval.chaine = strdup(yytext);
                    Rechercher(yytext, "IDF", "", "", 1);
                    return IDF;
                }
            }

"<--"   { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return AFFECTATION; }
"<="    { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return INFEGAL; }
">="    { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return SUPEGAL; }
"=="    { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return EGAL; }
"!="    { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return DIFF; }
"<"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return INF; }
">"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return SUP; }
"+"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return PLUS; }
"-"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return MOINS; }
"*"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return MULT; }
"/"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return DIV; }
"="     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return EGALE_INIT; }
";"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return PVIR; }
":"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return DPTS; }
"|"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return BARRE; }
"("     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return PARG; }
")"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return PARD; }
"["     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return CROG; }
"]"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return CROD; }
"{"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return ACCOG; }
"}"     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return ACCOD; }
","     { tok_col = nb_col; nb_col += yyleng; Rechercher(yytext, "Sep", "", "", 3); return VIRG; }

.       {
            tok_col = nb_col;
            nb_col++;
            printf("Erreur lexicale, ligne %d, colonne %d, entite %s\n",
                   nb_ligne, tok_col, yytext);
        }

%%

int yywrap(void) { return 1; }

void skip_ml_comment(void)
{
    int c;
    int st = 0;
    nb_col += 3;
    while (1)
    {
        c = input();
        if (c == EOF || c == 0)
        {
            printf("Erreur lexicale, ligne %d, colonne %d, entite commentaire non ferme\n",
                   nb_ligne, nb_col);
            return;
        }
        if (c == '\n') { nb_ligne++; nb_col = 1; st = 0; continue; }
        nb_col++;
        if      (st == 0) { if (c == '*') st = 1; }
        else if (st == 1) { if (c == '/') st = 2; else if (c != '*') st = 0; }
        else if (st == 2) { if (c == '/') return; else if (c == '*') st = 1; else st = 0; }
    }
}
