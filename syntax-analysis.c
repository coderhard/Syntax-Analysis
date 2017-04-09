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
char line_input[100];
int line_input_pos;
int line_input_count;

FILE * in_fp;

/* Function Declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

void x();

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
void addChar()
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

void getChar()
{
    if ((nextChar = line_input[line_input_pos++]) != 0)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
    {
        charClass = EOF;
    }
}

void getNonBlank()
{
    while (isspace(nextChar) && nextChar != '\r' && nextChar != '\n')
        getChar();
}

int lookup(char ch)
{
    switch (ch)
    {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
            
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
            
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
            
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
            
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
            
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
            
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    
    return nextToken;
}

int lex()
{
    lexLen = 0;
    getNonBlank();
    
    switch(charClass)
    {
        /* Parse Identifiers */
        case LETTER:
            addChar();
            getChar();
            while(charClass == LETTER || charClass == DIGIT)
            {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
            
        /* Parse Integer Literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT)
            {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
            
        /* Parentheses and Operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
            
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of Switch */
    
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}

void error()
{
    printf("Error: line %d, column %d: \n%s\n", line_input_count, line_input_pos, line_input);
    // Hassan Karim
    // The next line error() caused an infinite recursive loop when a syntax error was encountered.
    // Commenting it out made program work as expected
    //error();
}

/* Parse: factor */
void factor()
{
    if (nextToken == IDENT || nextToken == INT_LIT)
        /* Return nextToken */
        lex();
    else
    {
        if (nextToken == LEFT_PAREN)
        {
            /* Return nextToken */
            lex();
            x();
            if (nextToken == RIGHT_PAREN)
            {
                /* Return nextToken */
                lex();
            }
            else
                /* Expected a ) */
                error();
        }
        else
            /* Expected id, integer literal, or ( */
            error();
    }
}

/* Parse: z */
void z()
{
    factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP)
    {
        /* Return nextToken */
        lex();
        factor();
    }
}

void x()
{
    z();
    while (nextToken == ADD_OP || nextToken == SUB_OP)
    {
        /* Return nextToken */
        lex();
        /* Parse nextToken */
        z();
    }
}

/* Main Driver */
int main (int argc, char** argv) {
    if (argc < 2)
    {
        return 1;
    }
    
    in_fp = fopen(argv[1], "r");
    
    /* File is NULL */
    if (in_fp == NULL)
    {
        printf("Error: Input file failed to open %s.", argv[1]);
        return 1;
    }
    
    line_input_count = 0;
    while ( fgets(line_input, sizeof(line_input), in_fp) != NULL)
    {
        line_input_count += 1;
        line_input_pos = 0;
        
        /* Return first character */
        getChar();
        
        do
        {
            /* Return nextToken */
            lex();
            x();
        } while (nextToken != EOF);
    }
    
    /* Close File */
    fclose(in_fp);
    
    return 0;
    
}
