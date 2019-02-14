
#include "Tokenizer.h"

#define ERROR 666 // My very own error token

_Bool isDigit(char c) {
  return TRUE;
}

_Bool isIdentifier(char c) {
  return TRUE;
}

int readNumber() {
  return 0;
}

int readIdentifier() {
  return 0;
}

/****************************************
* Return the next token in the buffer
*****************************************/
int nextToken(FILE inf) {

  int tok;
  char ch;
  
  // Read Character
  if ((ch = fgetc(inf)) == NULL) {
    return NULL;
  }

  // Exhaust whitespace
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    if ((ch = fgetc(inf)) == NULL) {
      return NULL;
    }
  }

  switch(ch) {

  case '(':
    tok = LEFT_PARENTHESIS;
    break;
  case ')':
    tok = RIGHT_PARENTHESIS;
    break;
  case '{':
    tok = LEFT_BRACKET;
    break;
  case '}':
    tok = RIGHT_BRACKET;
    break;
  case '=':
    tok = EQUAL;
    break;
  case ';':
    tok = EOL;
    break;
  case ',':
    tok = COMMA;
    break;
  default:
    if (isDigit(ch)) {
      tok = readNumber();
    } else if (isLetter(ch)) {
      tok = readIdentifier();
    } else {
      tok = ERROR;
    }

  }

  return tok;
}

/*************************************************************
* Create token from file buffer and add them to lexics array
**************************************************************/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE inf) {

  int current = 0;
  int tok;

  while ((tok = nextToken(inf)) != NULL) {

    if (tok == ERROR) {
      return FALSE;
    }

    *numLex++
    aLex[current] = tok;
  } 
  
  return TRUE;
}

