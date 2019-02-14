
#include "Tokenizer.h"

#define ERROR 666 // My very own error token
#define readChar(ch, x); if ((ch = fgetc(x)) == NULL) { \
                            return NULL; \
                          } 

_Bool isDigit(char ch) {
  return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

_Bool isLetter(char ch) {
  return '0' <= ch && ch <= '9';
}

void readNumber(FILE inf, char ch, char* number) {

  int size = 1;
  number[0] = ch;

  while (isDigit(ch)) {
    readChar(ch, inf);
    if ((number = realloc(sizeof(char) * size)) == NULL) {
      return
    }
    number[size] = ch;
    size++;
  }

  number[size] = '\0';
}

void readIdentifier(FILE inf, char ch, char* indent) {

  int size = 1;
  indent[0] = '\0';

  while (isLetter(ch)) {
    readChar(ch, inf);
    if ((indent = realloc(sizeof(char) * size)) == NULL) {
      return
    }
    indent[size] = ch;
    size++;
  }

  indent[size] = '\0';
}

int isWhitespace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

/****************************************
* Return the next token in the buffer
*****************************************/
int nextToken(FILE inf) {

  int tok;
  char ch;
  char* buf;
  struct lexics lexy;
  
  // Read Character
  readChar(ch, inf);

  // Exhaust whitespace
  while (isWhitespace(ch)) {
    readChar(ch, inf);
  }

  switch(ch) {

  case '(':
    tok = LEFT_PARENTHESIS;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case ')':
    tok = RIGHT_PARENTHESIS;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case '{':
    tok = LEFT_BRACKET;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case '}':
    tok = RIGHT_BRACKET;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case '=':
    tok = EQUAL;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case ';':
    tok = EOL;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  case ',':
    tok = COMMA;
    lexy = struct lexics{token: tok, lexeme: char[2]{ch, '\0'}};
    break;
  default:
    if ((buf = malloc(sizeof(char) * 2)) == NULL) {
      return NULL;
    }

    if (isDigit(ch)) {
      tok = readNumber(inf, ch, buf);
      lexy = struct lexics{token: tok, lexeme: buf};
    } else if (isLetter(ch)) {
      tok = readIdentifier(inf, ch, buf);
      lexy = struct lexics{token: tok, lexeme: buf};
    } else {
      tok = ERROR;
      lexy = struct lexics{token: tok, lexeme: NULL};
    }

  }

  return lexy;
}

/*************************************************************
* Create token from file buffer and add them to lexics array
**************************************************************/
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE inf) {

  int current = 0;
  int lex;

  while ((lex = nextToken(inf)) != NULL) {

    if (lex.token == ERROR) {
      return FALSE;
    }

    *numLex++;
    aLex[current] = lex;
  } 
  
  return TRUE;
}

