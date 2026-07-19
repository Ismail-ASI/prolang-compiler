flex lexical.l
bison -d syntaxique.y
gcc lex.yy.c syntaxique.tab.c quad.c ts.c optim.c codegen.c -o lexere
./lexere source_eval.txt 