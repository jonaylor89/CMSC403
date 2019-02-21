
#include "Tokenizer.h"

#define readChar(ch, x); (ch = fgetc(x)) 

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

  while (isDigit(peekChar(inf))) {
    readChar(ch, inf);
    if ((number = (char *)realloc(number, sizeof(char) * size)) == NULL) {
      return ERROR;
    }
    number[size] = ch;
    size++;
  }

  number[size] = '\0';

  return NUMBER;

}

/**********************************
* Read in an identifier 
***********************************/
int readIdentifier(FILE *inf, char ch, char* ident) {

  int size = 1;
  ident[0] = ch;

  while (isLetter(peekChar(inf)) || isDigit(peekChar(inf))) {
    readChar(ch, inf);
    ident[size] = ch;
    size++;
  }
  
  ident[size] = '\0';

  if (strcmp(ident, "while") == 0) {
    return WHILE_KEYWORD;
  } else if (strcmp(ident, "return") == 0) {
    return RETURN_KEYWORD;
  } else if (strcmp(ident, "int") == 0 || strcmp(ident, "void") == 0) {
    return VARTYPE;
  } else {
    return IDENTIFIER;
  }

}

/****************************************
* Return the next token in the buffer
*****************************************/
struct lexics *nextLex(FILE *inf) {

  int tok;
  char ch;
  char* buf;
  struct lexics *lexy; // Her name is lexy and she is beautiful
  

  // Read Character
  readChar(ch, inf);

  if (feof(inf)) {
    return NULL; 
  }

  // Exhaust whitespace
  while (isWhitespace(ch)) {
    readChar(ch, inf);
    
    if (feof(inf)) {
        return NULL; 
    }
  }

  if ((lexy = (struct lexics *) malloc(sizeof(struct lexics))) == NULL) {
    tok = ERROR;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    return lexy;
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

    if (peekChar(inf) == '=') {
      tok = BINOP;
      readChar(ch, inf);
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = ch;
      lexy->lexeme[2] = '\0';
    } else {
      tok = EQUAL;
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = '\0';
    }
    lexy->token = tok;
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
  case '%':
    tok = BINOP;
    lexy->token = tok;
    lexy->lexeme[0] = ch;
    lexy->lexeme[1] = '\0';
    break;
   case '!':
    if (peekChar(inf) == '=') {
      readChar(ch, inf);
      lexy->token = BINOP;
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = '=';
      lexy->lexeme[2] = '\0';
    } else {
      tok = ERROR;
      lexy->lexeme[0] = ch;
      lexy->lexeme[1] = '\0';
    }
    break;
  default:
    
    if ((buf = (char *) malloc(sizeof(char) * LEXEME_MAX)) == NULL) {
      return NULL;
    }

    if (isDigit(ch)) {
      tok = readNumber(inf, ch, buf);
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

  (*numLex) = 0;
  struct lexics *lex;

  while ((lex = nextLex(inf)) != NULL) {

    if (lex->token == ERROR) {
      return FALSE;
    }

    aLex[(*numLex)] = *lex; // Resposibility of the parser to free the memory
    (*numLex)++;
  } 

  struct lexics *lexy;
  if ((lexy = (struct lexics *) malloc(sizeof(struct lexics))) == NULL) {
    lexy->token = EOP;
    lexy->lexeme[0] = ' ';
    lexy->lexeme[1] = '\0';
  }
  
  aLex[(*numLex)] = *lexy;

  /*
  int i;
  for (i = 0; i < *numLex; i++) {
    printf("[DEBUG] %d\n", aLex[i].token);
  }
  */

  return TRUE;
}








