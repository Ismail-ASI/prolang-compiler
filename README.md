# ProLang Compiler

A complete compiler for **ProLang**, a small imperative programming language, written in C with **Flex** and **Bison**.

It takes a ProLang source file and runs it through every classic stage of compilation — lexical analysis, parsing, semantic checking, intermediate code generation, optimization, and finally **Intel 8086 assembly** generation.

```
source.txt  →  Lexer  →  Parser  →  Symbol Table  →  Quadruples  →  Optimizer  →  8086 Assembly
                 ↓          ↓            ↓               ↓              ↓              ↓
             lexical.l  syntaxique.y   ts.c          quad.c         optim.c      codegen.c
```

---

## Who this project is for

This is a **university project** built for a Compiler Construction (*Compilation*) course, and it's aimed at:

- **Students** taking a compiler theory / compiler construction course who want a complete, working reference implementation that goes all the way from source text to real assembly — not just a toy parser.
- **Anyone learning Flex & Bison** who wants to see how a lexer spec, an LALR grammar, semantic actions, and a symbol table fit together in a single project.
- **Instructors and reviewers** evaluating the implementation.

It is a **teaching compiler**, not a production one. The language is deliberately small, and the generated 8086 assembly targets a simple, well-understood machine model so that the output is readable and easy to trace back to the source.

> **A note on language:** the compiler's own diagnostic messages and printed tables are in **French** (e.g. `Erreur lexicale`, `Table des symboles`, `Quadruplets`), since it was written for a French-language course. This README explains all of them in English, so you don't need French to use the project.

---

## What it actually does

| Stage | File(s) | What happens |
|---|---|---|
| **Lexical analysis** | `lexical.l` | Turns text into tokens. Tracks line & column for precise error messages. Handles keywords, identifiers, integers, floats, signed literals `(+5)` / `(-3)`, strings, and both comment styles. |
| **Syntax analysis** | `syntaxique.y` | LALR grammar for the whole language: declarations, assignment, `if/else`, `while`, `for`, boolean & arithmetic expressions, arrays, I/O. |
| **Semantic analysis** | `syntaxique.y` + `ts.c` | Detects undeclared variables, type mismatches, and out-of-bounds constant array indices. |
| **Symbol table** | `ts.c` / `ts.h` | Hash-based table storing every identifier and constant with its code, type, and value. |
| **Intermediate code** | `quad.c` / `quad.h` | Emits three-address code as **quadruples**: `(operator, operand1, operand2, result)`. |
| **Optimization** | `optim.c` / `optim.h` | Five passes, applied repeatedly until nothing changes (see below). |
| **Code generation** | `codegen.c` / `codegen.h` | Emits MASM/TASM-style 8086 assembly into `output.asm`. |

### The five optimization passes

They run in a loop until a full round produces no further change:

1. **Algebraic simplification, constant folding & strength reduction** — computes `3 + 4` into `7` at compile time, simplifies `x + 0`, `x - 0`, `x * 1`, `x * 0`, `x / 1`, and rewrites `x * 2` as `x + x` (addition is cheaper than multiplication on the 8086).
2. **Expression propagation** — folds a temporary that's used exactly once directly into the instruction that consumes it.
3. **Copy propagation** — removes redundant `a <-- b` copies by substituting the source directly.
4. **Common subexpression elimination (CSE)** — if the same expression is computed twice with unchanged operands, the second one reuses the first result.
5. **Dead code elimination** — deletes any instruction whose result is a temporary that is never read.

Jump targets are automatically renumbered whenever an instruction is deleted, so the control flow stays correct.

### About floats

The 8086 has no floating-point unit in this model, so floats are handled with **fixed-point arithmetic scaled by 10** (one decimal place). For example `3.14159` is stored as `31`, and `2.5` becomes `25`. This is a deliberate simplification typical of this kind of course project.

---

## Requirements

| Tool | Version used | Notes |
|---|---|---|
| **flex** | 2.6.4 | Any 2.6.x works |
| **bison** | 3.8.2 | **3.x required** — macOS's built-in bison 2.3 will not work |
| **gcc** | 13.3.0 | Any C99-capable compiler (clang works too) |

### Install on Linux (Debian / Ubuntu)

```bash
sudo apt-get update
sudo apt-get install flex bison gcc
```

### Install on Linux (Fedora / RHEL)

```bash
sudo dnf install flex bison gcc
```

### Install on macOS

macOS ships with a very old bison (2.3) that **cannot build this project**. Install current versions with [Homebrew](https://brew.sh) and put them ahead of the system ones on your `PATH`:

```bash
brew install flex bison

# Apple Silicon (M1/M2/M3):
export PATH="/opt/homebrew/opt/bison/bin:/opt/homebrew/opt/flex/bin:$PATH"

# Intel Macs:
export PATH="/usr/local/opt/bison/bin:/usr/local/opt/flex/bin:$PATH"
```

Verify you picked up the right one before building:

```bash
bison --version   # must report 3.x, not 2.3
```

> Add the `export PATH=...` line to your `~/.zshrc` if you want it to persist between terminal sessions.

---

## Build & Run

The same three commands work on **Linux and macOS**:

```bash
flex lexical.l
bison -d syntaxique.y
gcc lex.yy.c syntaxique.tab.c quad.c ts.c optim.c codegen.c -o lexere
```

Then run it on the test file:

```bash
./lexere test_file.txt
```

That's it. The build is warning-free on GCC 13.

**Windows users** can either use WSL / MSYS2 and follow the Linux steps, or run the prebuilt `lexere.exe` included in the repo.

---

## The test file

**`test_file.txt`** is the main demonstration program. It is written specifically to exercise **every feature the compiler supports**, so running it is the fastest way to see the whole project work at once.

Here's what it covers:

| Feature | Where it appears in `test_file.txt` |
|---|---|
| Multi-variable declarations | `define x \| y \| z : integer;` |
| Both data types | `integer` and `float` declarations |
| Declaration with initialization | `define somme : integer = 0;` |
| Array declarations | `define Tabint : [integer; 50];` |
| Constants | `const Pi : float = 3.14159;` |
| Single-line comments | `%% variables simples` |
| Multi-line comments | `//* DECLARATIONS *//` |
| Assignment | `x <-- 10;` |
| Arithmetic & operator precedence | `Tabint[0] <-- x + y * z;` |
| Parenthesized expressions | `b <-- (a + Pi) * 2.0;` |
| Array read & write | `Tabfloat[j-1]`, `Tabint[i] <-- ...` |
| Computed array indices | `Tabint[x + 1] <-- ...` |
| Boolean operators `AND` / `OR` / `NON` | `if ((x > y AND (z < x + y)) OR NON(y == 0))` |
| All comparison operators | `>`, `<`, `<=`, `!=`, `==` |
| `if / then / else` | the large conditional block |
| **Nested** `if` inside a loop | the inner `if` within the `for` loop |
| `for ... in ... to` loops | `for i in 0 to 10` |
| `while` loops | `loop while ((x <= Max) AND ...)` |
| **Nested** `while` loops | the inner `loop while (NON(x == y))` |
| Input | `input(x);` |
| Output with strings and variables | `out("Somme: ", somme);` |

Because it uses nested loops, nested conditions, and mixed-type expressions, it also gives the optimizer plenty to work on — it reduces the program from **100 quadruples down to 83** in 3 passes.

> **Line endings matter.** `test_file.txt` uses Unix (LF) line endings. If you edit it on Windows and it gets saved with CRLF, the lexer will print a harmless `Erreur lexicale` for every line ending (the generated code is still correct). Fix it with:
> ```bash
> tr -d '\r' < test_file.txt > tmp && mv tmp test_file.txt
> ```

---

## What you'll see when you run it

Running `./lexere test_file.txt` prints four sections in order, then writes `output.asm`.

### 1. The symbol table

Every identifier and constant found, with its code, type and value:

```
/************* Table des symboles IDF et CONST *************/
________________________________________________________________
	| Nom_Entite     | Code       | Type       | Val        |
________________________________________________________________
	| Tabint         | TABLEAU    | integer    | 50         |
	| Tabfloat       | TABLEAU    | float      | 30         |
	| Max            | CONST      | integer    |            |
	| a              | IDF        | float      |            |
	| x              | IDF        | integer    |            |
	| somme          | IDF        | integer    |            |
```

*(`Nom_Entite` = entity name, `TABLEAU` = array, `IDF` = identifier, `CONST` = constant, `Val` = value/array size.)*

### 2. Intermediate code, before optimization

Each line is a quadruple `(operator, operand1, operand2, result)`:

```
 19 - ( <--  ,  2.5  ,  vide  ,  a )
 20 - ( +  ,  a  ,  Pi  ,  T0 )
 21 - ( *  ,  T0  ,  2  ,  T1 )
 22 - ( <--  ,  T1  ,  vide  ,  b )
 23 - ( *  ,  y  ,  z  ,  T2 )
 24 - ( +  ,  x  ,  T2  ,  T3 )
 25 - ( <--  ,  T3  ,  vide  ,  Tabint[0] )
```

*(`vide` means "empty/unused". `T0`, `T1`… are compiler-generated temporaries. `BR` = branch, `BG`/`BLE`/`BNE` = conditional branches.)*

### 3. Optimization summary and result

```
=================== OPTIMISATION ===================
Quadruplets avant : 100
Quadruplets apres : 83
Iterations        : 3
=====================================================
```

And the same region of code afterwards:

```
 19 - ( <--  ,  2.5  ,  vide  ,  a )
 20 - ( +  ,  a  ,  Pi  ,  T0 )
 21 - ( +  ,  T0  ,  T0  ,  b )
 22 - ( *  ,  y  ,  z  ,  T2 )
 23 - ( +  ,  x  ,  T2  ,  Tabint[0] )
```

Two things to notice, comparing with the "before" block above:

- Quadruple 21 changed from `T0 * 2` to `T0 + T0` — that's **strength reduction**.
- The separate copy `T1 → b` disappeared entirely; the addition now writes straight into `b`. Same for `T3 → Tabint[0]`. That's **expression propagation**. Seven instructions became five.

### 4. Assembly generation

```
========== GENERATION DU CODE 8086 ==========
Fichier genere : output.asm
Mode float     : virgule fixe x10 (1 decimale)
Code 8086 genere avec succes dans : output.asm
=============================================
```

The resulting **`output.asm`** is a complete 8086 program with stack, data and code segments:

```asm
DATA SEGMENT
    Tabint DW 50 DUP (?)
    Tabfloat DW 30 DUP (?)
    x DW 0
    Pi DW 0
DATA ENDS

CODE SEGMENT
MAIN:
    ASSUME CS:CODE, DS:DATA, SS:PILE
    MOV AX, DATA
    MOV DS, AX

    MOV AX, 31        ; Pi = 3.14159 scaled x10
    MOV Pi, AX
    MOV AX, a
    ADD AX, Pi
```

Every generated instruction is preceded by a comment naming the quadruple it came from (`;; quad 20 : ( + , a , Pi , T0 )`), so you can trace any line of assembly back to the intermediate code and from there to the original source.

---

## The ProLang language

A minimal but complete program:

```
BeginProject M1_iv_2526;

Setup:
    define x | y : integer;
    define a : float;
    const Pi : float = 3.14159;
    define Tab : [integer; 50];

Run:
{
    x <-- 10;

    if (x > 0) then:
    {
        out("positive");
    } else {
        out("negative or zero");
    } endIf;

    for i in 0 to 10
    {
        Tab[i] <-- i * 2;
    } endfor;
}
EndProject;
```

**Structure.** Every program is wrapped in `BeginProject M1_iv_2526;` … `EndProject;`. Declarations go in the `Setup:` block, executable statements go in the `Run:` block.

**Syntax reference:**

| Element | Syntax |
|---|---|
| Assignment | `x <-- 10;` |
| Initialization at declaration | `define n : integer = 0;` |
| Multiple declaration | `define x \| y \| z : integer;` |
| Array | `define Tab : [integer; 50];` |
| Constant | `const Pi : float = 3.14159;` |
| Conditional | `if (cond) then: { ... } else { ... } endIf;` |
| While loop | `loop while (cond) { ... } endloop;` |
| For loop | `for i in 0 to 10 { ... } endfor;` |
| Logical operators | `AND`, `OR`, `NON` |
| Comparison | `==`, `!=`, `<`, `>`, `<=`, `>=` |
| Arithmetic | `+`, `-`, `*`, `/` |
| Input / Output | `input(x);` / `out("text: ", x);` |
| Single-line comment | `%% comment` |
| Multi-line comment | `//* comment *//` |

**Identifier rules:** must start with a letter, max 14 characters, cannot end with `_`, and cannot contain two consecutive underscores. Violations are reported as lexical errors with exact line and column.

---

## Error reporting

All three classes of error are detected and reported with position information:

```
Erreur lexicale, ligne 12, colonne 5, entite <token>          → lexical error
Erreur syntaxique, ligne 20, colonne 3 : <message>            → syntax error
Erreur semantique, ligne 31, colonne 9, identificateur x non declare
Erreur semantique, ligne 45, colonne 12, index hors limites pour Tabint
```

*(`ligne` = line, `colonne` = column, `entite` = entity/token, `non declare` = undeclared, `index hors limites` = index out of bounds.)*

---

## Project structure

```
.
├── lexical.l              # Flex lexer specification
├── syntaxique.y           # Bison grammar, semantic actions, and main()
├── ts.c / ts.h            # Symbol table (hash-based)
├── quad.c / quad.h        # Quadruple (three-address code) generation
├── optim.c / optim.h      # The five optimization passes
├── codegen.c / codegen.h  # 8086 assembly generator
│
├── test_file.txt          # Full-coverage test program  ← start here
├── output.asm             # Sample generated assembly (reference output)
│
├── lex.yy.c               # Generated by flex — regenerated on every build
├── syntaxique.tab.c/.h    # Generated by bison — regenerated on every build
└── lexere.exe             # Prebuilt Windows binary (optional)
```

The generated files (`lex.yy.c`, `syntaxique.tab.*`) are committed for convenience, but the build regenerates them from `lexical.l` and `syntaxique.y`, so they always stay in sync with the sources.

---

## Authors

This compiler was designed and built collaboratively by two students, as a project for the Compiler Construction (*Compilation*) module, M1 Informatique Visuelle, 2025–2026:

- **[YOUR_NAME]** — [github.com/Ismail-ASI](https://github.com/Ismail-ASI)
- **Abdennour** — [github.com/abdennourbd](https://github.com/abdennourbd)

Questions, issues, and suggestions are welcome — feel free to open an issue on the repository.

## License

No license file is currently included. Consider adding one (MIT is a common choice for coursework you're happy to share).
