/* Syntax Analysis Programming Assignment */
/* syntax-analysis.c */
/* Morgan Williams */
/* CSCI 350 Structures of Programming Languages */

#include <stdio.h> 
#include <ctype.h>

/* Global Declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;

FILE * in_fp;

/* Function Declarations */

/* Character Classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token Codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* Function Definitions */

/* Main Driver */
main () {
    
}
