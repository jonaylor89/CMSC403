
#include "Tokenizer.h"

#define ERROR 666 // My very own error token
#define readChar(ch, x); if ((ch = fgetc(x)) == EOF) { \
                            return NULL; \
                          } 

#define isLetter(ch) ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_')

#define isDigit(ch)  ('0' <= ch && ch <= '9')

#define isWhitespace(ch) (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') 

char peekChar(FILE* inf) {
  // pos contains the information needed from
    //   the stream's position indicator to restore
    //   the stream to its current position. 
    fpos_t pos;
    char ch; 
    
    // Get the current position
    fgetpos(inf, &pos);

    // Get the next char
    readChar(ch, inf);

    // Restore the position
    fsetpos(inf, &pos);

    return ch;
}

/*********************
* Read in a number
**********************/
int readNumber(FILE* inf, char ch, char* number) {

  int size = 1;
  number[0] = ch;

  while (isDigit(ch)) {
    readChar(ch, inf);
    if ((number = (char *)realloc(number, sizeof(char) * size)) == NULL) {
      return 666;
    }
    number[size] = ch;
    size++;
  }

  number[size] = '\0';
}

/**********************************
* Read in an identifier 
***********************************/
int readIdentifier(FILE *inf, char ch, char* indent) {

  int size = 1;
  indent[0] = '\0';

  while (isLetter(ch)) {
    readChar(ch, inf);
    indent[size] = ch;
    size++;
  }

  indent[size] = '\0';

  return IDENTIFIER;
}

/****************************************
* Return the next token in the buffer
*****************************************/
struct lexics *nextLex(FILE *inf) {

  int tok;
  char ch;
  char* buf;
  struct lexics *lexy; // Her name is lexy and she is beautiful

  if ((lexy = malloc(sizeof(struct lexics))) == NULL) {
    return NULL;
  }
  
  // Read Character
  readChar(ch, inf);

  // Exhaust whitespace
  while (isWhitespace(ch)) {
    readChar(ch, inf);
  }

  switch(ch) {

  case '(':
    tok = LEFT_PARENTHESIS;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case ')':
    tok = RIGHT_PARENTHESIS;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '{':
    tok = LEFT_BRACKET;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '}':
    tok = RIGHT_BRACKET;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '=':
    tok = EQUAL;
    lexy->token = tok;

    if (peekChar(inf) == '=') {
      readChar(ch, inf);
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = ch;
      lexy->lexeme[2] = '\0';
    } else {
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = '\0';
    }
    break;
  case ';':
    tok = EOL;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case ',':
    tok = COMMA;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '*':
    tok = BINOP;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '+':
    tok = BINOP;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '-':
    tok = BINOP;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  case '/':
    tok = BINOP;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
  default:
    
    if ((buf = malloc(sizeof(char) * LEXEME_MAX)) == NULL) {
      return NULL;
    }

    if (isDigit(ch)) {
      tok = NUMBER;
      readNumber(inf, ch, buf);
      lexy->token = tok;
      strcpy(lexy->lexeme, buf);
    } else if (isLetter(ch)) {
      tok = readIdentifier(inf, ch, buf);
      lexy->token = tok;
      strcpy(lexy->lexeme, buf);;
    } else {
      tok = ERROR;
      lexy->token = tok;
      lexy->lexeme[0] = '\0';
    }

  }

  return lexy;
}

/*************************************************************
* Create token from file buffer and add them to lexics array
**************************************************************/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf) {

  int current = 0;
  struct lexics *lex;

  while ((lex = nextLex(inf)) != NULL) {

    if (lex->token == ERROR) {
      return FALSE;
    }

    (*numLex)++;
    aLex[current] = *lex; // Reposibility of the parser to free the memory
  } 
  
  return TRUE;
}

