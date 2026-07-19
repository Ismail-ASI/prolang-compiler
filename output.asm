TITLE ProLang_8086

;; Virgule fixe SCALE=10 : ex 2.5->25, 3.1->31

PILE SEGMENT STACK
    DW 100 DUP (?)
PILE ENDS

DATA SEGMENT
    Tabint DW 50 DUP (?)
    Tabfloat DW 30 DUP (?)
    Max DW 0
    a DW 0
    b DW 0
    i DW 0
    j DW 0
    k DW 0
    x DW 0
    y DW 0
    z DW 0
    somme DW 0
    moyenne DW 0
    Pi DW 0
    T0 DW 0
    T2 DW 0
    T4 DW 0
    T6 DW 0
    T9 DW 0
    T16 DW 0
    T17 DW 0
    T18 DW 0
    T19 DW 0
    T22 DW 0
    T23 DW 0
    T25 DW 0
    T27 DW 0
    T28 DW 0
    T31 DW 0
    T32 DW 0
    T33 DW 0
DATA ENDS

CODE SEGMENT
MAIN:
    ASSUME CS:CODE, DS:DATA, SS:PILE
    MOV AX, DATA
    MOV DS, AX

L0:
    ;; quad 0 : ( : , integer , vide , y )
L1:
    ;; quad 1 : ( : , integer , vide , z )
L2:
    ;; quad 2 : ( : , integer , vide , x )
L3:
    ;; quad 3 : ( : , integer , vide , j )
L4:
    ;; quad 4 : ( : , integer , vide , k )
L5:
    ;; quad 5 : ( : , integer , vide , i )
L6:
    ;; quad 6 : ( : , float , vide , b )
L7:
    ;; quad 7 : ( : , float , vide , a )
L8:
    ;; quad 8 : ( : , integer , 0 , somme )
    MOV AX, 0
    MOV somme, AX
L9:
    ;; quad 9 : ( : , float , 0 , moyenne )
    MOV AX, 0
    MOV moyenne, AX
L10:
    ;; quad 10 : ( BOUNDS , 0 , 49 , vide )
L11:
    ;; quad 11 : ( ADEC , Tabint , vide , vide )
L12:
    ;; quad 12 : ( BOUNDS , 0 , 29 , vide )
L13:
    ;; quad 13 : ( ADEC , Tabfloat , vide , vide )
L14:
    ;; quad 14 : ( : , float , 3.14159 , Pi )
    MOV AX, 31
    MOV Pi, AX
L15:
    ;; quad 15 : ( : , integer , 100 , Max )
    MOV AX, 100
    MOV Max, AX
L16:
    ;; quad 16 : ( <-- , 10 , vide , x )
    MOV AX, 10
    MOV x, AX
L17:
    ;; quad 17 : ( <-- , 5 , vide , y )
    MOV AX, 5
    MOV y, AX
L18:
    ;; quad 18 : ( <-- , 2 , vide , z )
    MOV AX, 2
    MOV z, AX
L19:
    ;; quad 19 : ( <-- , 2.5 , vide , a )
    MOV AX, 25
    MOV a, AX
L20:
    ;; quad 20 : ( + , a , Pi , T0 )
    MOV AX, a
    ADD AX, Pi
    MOV T0, AX
L21:
    ;; quad 21 : ( + , T0 , T0 , b )
    MOV AX, T0
    MOV BX, 10
    IMUL BX
    PUSH AX
    MOV AX, T0
    MOV BX, 10
    IMUL BX
    MOV CX, AX
    POP AX
    ADD AX, CX
    MOV b, AX
L22:
    ;; quad 22 : ( * , y , z , T2 )
    MOV AX, y
    MOV BX, z
    IMUL BX
    MOV T2, AX
L23:
    ;; quad 23 : ( + , x , T2 , Tabint[0] )
    MOV AX, x
    ADD AX, T2
    MOV BX, 0
    ADD BX, BX
    MOV Tabint[BX], AX
L24:
    ;; quad 24 : ( + , b , 3.5 , T4 )
    MOV AX, b
    ADD AX, 35
    MOV T4, AX
L25:
    ;; quad 25 : ( / , T4 , 2 , Tabfloat[1] )
    MOV AX, T4
    MOV BX, 10
    IMUL BX
    MOV BX, 10
    IMUL BX
    CWD
    MOV BX, 2
    IDIV BX
    MOV BX, 1
    ADD BX, BX
    MOV Tabfloat[BX], AX
L26:
    ;; quad 26 : ( BLE , 30 , x , y )
    MOV AX, x
    CMP AX, y
    JLE L30
L27:
    ;; quad 27 : ( + , x , y , T6 )
    MOV AX, x
    ADD AX, y
    MOV T6, AX
L28:
    ;; quad 28 : ( BGE , 30 , z , T6 )
    MOV AX, z
    CMP AX, T6
    JGE L30
L29:
    ;; quad 29 : ( BR , 31 , vide , vide )
    JMP L31
L30:
    ;; quad 30 : ( BNE , 46 , y , 0 )
    MOV AX, y
    CMP AX, 0
    JNE L46
L31:
    ;; quad 31 : ( BR , 32 , vide , vide )
    JMP L32
L32:
    ;; quad 32 : ( + , T6 , z , somme )
    MOV AX, T6
    ADD AX, z
    MOV somme, AX
L33:
    ;; quad 33 : ( = , 0 , vide , i )
    MOV AX, 0
    MOV i, AX
L34:
    ;; quad 34 : ( BG , 45 , i , 10 )
    MOV AX, i
    CMP AX, 10
    JG  L45
L35:
    ;; quad 35 : ( <-- , Tabint[i] , vide , T9 )
    MOV BX, i
    ADD BX, BX
    MOV AX, Tabint[BX]
    MOV T9, AX
L36:
    ;; quad 36 : ( + , T9 , i , Tabint[i] )
    MOV AX, T9
    ADD AX, i
    MOV BX, i
    ADD BX, BX
    MOV Tabint[BX], AX
L37:
    ;; quad 37 : ( BGE , 41 , i , 5 )
    MOV AX, i
    CMP AX, 5
    JGE L41
L38:
    ;; quad 38 : ( BLE , 41 , Tabint[i] , 10 )
    MOV BX, i
    ADD BX, BX
    MOV AX, Tabint[BX]
    CMP AX, 10
    JLE L41
L39:
    ;; quad 39 : ( * , Tabint[i] , 1.5 , Tabfloat[i] )
    MOV BX, i
    ADD BX, BX
    MOV AX, Tabint[BX]
    MOV BX, 10
    IMUL BX
    MOV BX, 15
    IMUL BX
    MOV BX, i
    ADD BX, BX
    MOV Tabfloat[BX], AX
L40:
    ;; quad 40 : ( BR , 42 , vide , vide )
    JMP L42
L41:
    ;; quad 41 : ( / , Tabint[i] , 2 , Tabfloat[i] )
    MOV BX, i
    ADD BX, BX
    MOV AX, Tabint[BX]
    MOV BX, 10
    IMUL BX
    MOV BX, 10
    IMUL BX
    CWD
    MOV BX, 2
    IDIV BX
    MOV BX, i
    ADD BX, BX
    MOV Tabfloat[BX], AX
L42:
    ;; quad 42 : ( + , i , 1 , T16 )
    MOV AX, i
    ADD AX, 1
    MOV T16, AX
L43:
    ;; quad 43 : ( = , T16 , vide , i )
    MOV AX, T16
    MOV i, AX
L44:
    ;; quad 44 : ( BR , 34 , vide , vide )
    JMP L34
L45:
    ;; quad 45 : ( BR , 47 , vide , vide )
    JMP L47
L46:
    ;; quad 46 : ( <-- , 0 , vide , somme )
    MOV AX, 0
    MOV somme, AX
L47:
    ;; quad 47 : ( BG , 63 , x , Max )
    MOV AX, x
    CMP AX, Max
    JG  L63
L48:
    ;; quad 48 : ( BE , 50 , y , 0 )
    MOV AX, y
    CMP AX, 0
    JE  L50
L49:
    ;; quad 49 : ( BR , 51 , vide , vide )
    JMP L51
L50:
    ;; quad 50 : ( BGE , 63 , z , 10 )
    MOV AX, z
    CMP AX, 10
    JGE L63
L51:
    ;; quad 51 : ( + , x , 1 , T17 )
    MOV AX, x
    ADD AX, 1
    MOV T17, AX
L52:
    ;; quad 52 : ( <-- , T17 , vide , x )
    MOV AX, T17
    MOV x, AX
L53:
    ;; quad 53 : ( BNE , 62 , x , y )
    MOV AX, x
    CMP AX, y
    JNE L62
L54:
    ;; quad 54 : ( BR , 55 , vide , vide )
    JMP L55
L55:
    ;; quad 55 : ( + , y , 1 , T18 )
    MOV AX, y
    ADD AX, 1
    MOV T18, AX
L56:
    ;; quad 56 : ( <-- , T18 , vide , y )
    MOV AX, T18
    MOV y, AX
L57:
    ;; quad 57 : ( + , x , 1 , T19 )
    MOV AX, x
    ADD AX, 1
    MOV T19, AX
L58:
    ;; quad 58 : ( + , Tabint[0] , Tabint[1] , T22 )
    MOV BX, 0
    ADD BX, BX
    MOV AX, Tabint[BX]
    MOV BX, 1
    ADD BX, BX
    ADD AX, Tabint[BX]
    MOV T22, AX
L59:
    ;; quad 59 : ( - , x , y , T23 )
    MOV AX, x
    SUB AX, y
    MOV T23, AX
L60:
    ;; quad 60 : ( * , T22 , T23 , Tabint[T19] )
    MOV AX, T22
    MOV BX, T23
    IMUL BX
    MOV BX, T19
    ADD BX, BX
    MOV Tabint[BX], AX
L61:
    ;; quad 61 : ( BR , 53 , vide , vide )
    JMP L53
L62:
    ;; quad 62 : ( BR , 47 , vide , vide )
    JMP L47
L63:
    ;; quad 63 : ( = , 1 , vide , j )
    MOV AX, 1
    MOV j, AX
L64:
    ;; quad 64 : ( BG , 74 , j , 20 )
    MOV AX, j
    CMP AX, 20
    JG  L74
L65:
    ;; quad 65 : ( - , j , 1 , T25 )
    MOV AX, j
    SUB AX, 1
    MOV T25, AX
L66:
    ;; quad 66 : ( <-- , Tabfloat[j] , vide , T27 )
    MOV BX, j
    ADD BX, BX
    MOV AX, Tabfloat[BX]
    MOV T27, AX
L67:
    ;; quad 67 : ( + , Tabfloat[T25] , T27 , T28 )
    MOV BX, T25
    ADD BX, BX
    MOV AX, Tabfloat[BX]
    PUSH AX
    MOV AX, T27
    MOV BX, 10
    IMUL BX
    MOV CX, AX
    POP AX
    ADD AX, CX
    MOV T28, AX
L68:
    ;; quad 68 : ( / , T28 , 2 , Tabfloat[j] )
    MOV AX, T28
    MOV BX, 10
    IMUL BX
    MOV BX, 10
    IMUL BX
    CWD
    MOV BX, 2
    IDIV BX
    MOV BX, j
    ADD BX, BX
    MOV Tabfloat[BX], AX
L69:
    ;; quad 69 : ( + , moyenne , Tabfloat[j] , T31 )
    MOV AX, moyenne
    MOV BX, j
    ADD BX, BX
    ADD AX, Tabfloat[BX]
    MOV T31, AX
L70:
    ;; quad 70 : ( <-- , T31 , vide , moyenne )
    MOV AX, T31
    MOV BX, 10
    IMUL BX
    MOV moyenne, AX
L71:
    ;; quad 71 : ( + , j , 1 , T32 )
    MOV AX, j
    ADD AX, 1
    MOV T32, AX
L72:
    ;; quad 72 : ( = , T32 , vide , j )
    MOV AX, T32
    MOV j, AX
L73:
    ;; quad 73 : ( BR , 64 , vide , vide )
    JMP L64
L74:
    ;; quad 74 : ( / , moyenne , 20 , T33 )
    MOV AX, moyenne
    CWD
    MOV BX, 20
    IDIV BX
    MOV T33, AX
L75:
    ;; quad 75 : ( <-- , T33 , vide , moyenne )
    MOV AX, T33
    MOV BX, 10
    IMUL BX
    MOV moyenne, AX
L76:
    ;; quad 76 : ( IN , vide , vide , x )
    ;; IN : saisie dans x
    CALL READ_INT
    MOV x, AX
L77:
    ;; quad 77 : ( OUT , "Valeur finale de x: " , vide , vide )
    ;; OUT chaine : "Valeur finale de x: "
L78:
    ;; quad 78 : ( OUT , x , vide , vide )
    MOV AX, x
    ;; afficher entier : x
    CALL PRINT_AX
L79:
    ;; quad 79 : ( OUT , "Somme: " , vide , vide )
    ;; OUT chaine : "Somme: "
L80:
    ;; quad 80 : ( OUT , somme , vide , vide )
    MOV AX, somme
    ;; afficher entier : somme
    CALL PRINT_AX
L81:
    ;; quad 81 : ( OUT , "Moyenne: " , vide , vide )
    ;; OUT chaine : "Moyenne: "
L82:
    ;; quad 82 : ( OUT , moyenne , vide , vide )
    MOV AX, moyenne
    ;; afficher float (virgule fixe /SCALE) : moyenne
    CALL PRINT_FLOAT
L83:

    ;; Fin du programme
    MOV AH, 4Ch
    INT 21h

;; ---- PRINT_AX : affiche AX en entier decimal ----
PRINT_AX PROC
    PUSH BX
    PUSH CX
    PUSH DX
    CMP  AX, 0
    JNE  PA_NONZERO
    MOV  DL, '0'
    MOV  AH, 2
    INT  21h
    JMP  PA_NEWLINE
PA_NONZERO:
    CMP  AX, 0
    JGE  PA_POS
    PUSH AX
    MOV  DL, '-'
    MOV  AH, 2
    INT  21h
    POP  AX
    NEG  AX
PA_POS:
    MOV  BX, 10
    MOV  CX, 0
PA_LOOP:
    MOV  DX, 0
    CWD
    IDIV BX
    PUSH DX
    INC  CX
    CMP  AX, 0
    JNE  PA_LOOP
PA_PRINT:
    POP  DX
    ADD  DL, 48
    MOV  AH, 2
    INT  21h
    LOOP PA_PRINT
PA_NEWLINE:
    MOV  DL, 13
    MOV  AH, 2
    INT  21h
    MOV  DL, 10
    MOV  AH, 2
    INT  21h
    POP  DX
    POP  CX
    POP  BX
    RET
PRINT_AX ENDP

;; ---- PRINT_FLOAT : affiche AX/10 (virgule fixe, 1 decimale) ----
PRINT_FLOAT PROC
    PUSH BX
    PUSH CX
    PUSH DX
    ;; cas zero
    CMP  AX, 0
    JNE  PF_NONZERO
    MOV  DL, '0'
    MOV  AH, 2
    INT  21h
    MOV  DL, '.'
    MOV  AH, 2
    INT  21h
    MOV  DL, '0'
    MOV  AH, 2
    INT  21h
    JMP  PF_NEWLINE
PF_NONZERO:
    ;; signe
    CMP  AX, 0
    JGE  PF_POS
    PUSH AX
    MOV  DL, '-'
    MOV  AH, 2
    INT  21h
    POP  AX
    NEG  AX
PF_POS:
    ;; diviser par SCALE : AX=partie entiere, DX=decimale
    MOV  BX, 10
    MOV  DX, 0
    CWD
    IDIV BX
    PUSH DX
    ;; afficher partie entiere
    MOV  BX, 10
    MOV  CX, 0
PF_INT_LOOP:
    MOV  DX, 0
    CWD
    IDIV BX
    PUSH DX
    INC  CX
    CMP  AX, 0
    JNE  PF_INT_LOOP
PF_INT_PRINT:
    POP  DX
    ADD  DL, 48
    MOV  AH, 2
    INT  21h
    LOOP PF_INT_PRINT
    ;; afficher '.'
    MOV  DL, '.'
    MOV  AH, 2
    INT  21h
    ;; afficher 1 chiffre decimal
    POP  DX
    ADD  DL, 48
    MOV  AH, 2
    INT  21h
PF_NEWLINE:
    MOV  DL, 13
    MOV  AH, 2
    INT  21h
    MOV  DL, 10
    MOV  AH, 2
    INT  21h
    POP  DX
    POP  CX
    POP  BX
    RET
PRINT_FLOAT ENDP

;; ---- READ_INT : lit un entier au clavier -> AX ----
READ_INT PROC
    PUSH BX
    PUSH CX
    PUSH DX
    MOV  AX, 0
    MOV  BX, 10
RI_LOOP:
    PUSH AX
    MOV  AH, 1
    INT  21h
    CMP  AL, 13
    JE   RI_DONE
    CMP  AL, 48
    JL   RI_IGNORE
    CMP  AL, 57
    JG   RI_IGNORE
    SUB  AL, 48
    CBW
    MOV  CX, AX
    POP  AX
    IMUL BX
    ADD  AX, CX
    JMP  RI_LOOP
RI_IGNORE:
    POP  AX
    JMP  RI_LOOP
RI_DONE:
    POP  CX
    POP  DX
    POP  CX
    POP  BX
    RET
READ_INT ENDP

CODE ENDS
END MAIN
