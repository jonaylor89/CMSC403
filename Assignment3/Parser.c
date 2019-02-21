
#include "Parser.h"
#include "Givens.h"

/**************************************************
 * Helper function to move along the token buffer 
 **************************************************/
void nextToken(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  static int position = 0; 

  *curLex = (lexs[position]);
  *peekLex = (lexs[position+1]);

  // printf("[DEBUG] %d, %d\n", curLex->token, peekLex->token);

  position++;
}

/************************************************************************
 * Helper function to compare tokens and advance along the token buffer
 ***********************************************************************/
_Bool compareToken(struct lexics *curLex, struct lexics *peekLex , struct lexics *lexs, int expectedToken) {

  // printf("[DEBUG] %d == %d\n", curLex->token, expectedToken);
  _Bool equal = curLex->token == expectedToken;
  nextToken(curLex, peekLex, lexs); // consume token

  return equal;
}

/**************************
 * function -> header body 
 **************************/
_Bool parseFunction(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {

  // Header
  _Bool first = parseHeader(curLex, peekLex, lexs);

  // Body
  _Bool second = parseBody(curLex, peekLex, lexs);

  // Function parsed properly if each piece does
  return first && second;
}

/******************************************************
 * header -> VARTYPE IDENT LEFT_PAR arg-decl RIGHT_PAR
 *******************************************************/
_Bool parseHeader(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {

  // VARTYPE
  _Bool first = compareToken(curLex, peekLex, lexs, VARTYPE);

  // IDENT
  _Bool second = compareToken(curLex, peekLex, lexs, IDENTIFIER);

  // LEFT_PAR
  _Bool third = compareToken(curLex, peekLex, lexs, LEFT_PARENTHESIS);

  _Bool fourth = TRUE;
  if (curLex->token == VARTYPE) {
    // arg-decl
    fourth = fourth && parseArgDecl(curLex, peekLex, lexs);
  }

  // RIGHT_PAR
  _Bool fifth = compareToken(curLex, peekLex, lexs, RIGHT_PARENTHESIS);

  // Return TRUE if all requirements are satisfied 
  return first && second && third && fourth && fifth;
}

/*****************************************************
 * arg-decl -> VARYPE IDENT {COMMA VARTYPE INDENT}
 *****************************************************/
_Bool parseArgDecl(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  
  // VARTYPE
  _Bool first = compareToken(curLex, peekLex, lexs, VARTYPE);

  // IDENT
  _Bool second = compareToken(curLex, peekLex, lexs, IDENTIFIER);

  _Bool third = TRUE;

  // COMMA
  while (curLex->token == COMMA) {
    nextToken(curLex, peekLex, lexs);

    // VARTYPE
    third = third && compareToken(curLex, peekLex, lexs, VARTYPE);

    // IDENT
    third = third && compareToken(curLex, peekLex, lexs, IDENTIFIER);
  }

  // printf("[DEBUG:ARGDECL] %d, %d, %d, (%d)\n", first, second, third, curLex->token);
  return first && second && third;
}

/***********************************************
 * body -> LEFT_BRA statement-list RIGHT_BRA
 **********************************************/
_Bool parseBody(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  
  // LEFT_BRA
  _Bool first = compareToken(curLex, peekLex, lexs, LEFT_BRACKET);

  _Bool second = TRUE;
    
  if (curLex->token == WHILE_KEYWORD || curLex->token == RETURN_KEYWORD || curLex->token == IDENTIFIER) {
        // statement-list
        second = second && parseStatementList(curLex, peekLex, lexs);
  }
  
  // RIHT_BRA
  _Bool third = compareToken(curLex, peekLex, lexs, RIGHT_BRACKET);

  return first && second && third;

}

/*******************************************
 * statement-list -> statement {statement}
 *******************************************/
_Bool parseStatementList(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  _Bool first = TRUE;
  
  do {

    first = first && parseStatement(curLex, peekLex, lexs);

  } while ((curLex->token == WHILE_KEYWORD ||
            curLex->token == RETURN_KEYWORD ||
            curLex->token == IDENTIFIER ||
            curLex->token == LEFT_BRACKET) && first);

  return first;
}

/***********************************************************
 * statement -> while-loop | return | assignement | body
 ***********************************************************/
_Bool parseStatement(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  _Bool first;
  
  // switch to figure out how to parse
  switch (curLex->token) {

  case WHILE_KEYWORD:
    first = parseWhileLoop(curLex, peekLex, lexs);
    break;
  case RETURN_KEYWORD:
    first = parseReturn(curLex, peekLex, lexs);
    break;
  case IDENTIFIER:
    first = parseAssignment(curLex, peekLex, lexs);
    break;
  case LEFT_BRACKET:
    first = parseBody(curLex, peekLex, lexs);
    break;
  default:
    first = FALSE;
  }

  return first;
}

/******************************************************************
 * while-loop -> WHILE_KEY LEFT_PAR expression RIGHT_PAR statement
 ******************************************************************/
_Bool parseWhileLoop(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  // while-loop -> WHILE_KEY LEFT_PAR expression RIGHT_PAR statement

  // WHILE_KEY
  _Bool first = compareToken(curLex, peekLex, lexs, WHILE_KEYWORD);

  // LEFT_PAR
  _Bool second = TRUE;
  second = compareToken(curLex, peekLex, lexs, LEFT_PARENTHESIS);

  // expression
  _Bool third = parseExpression(curLex, peekLex, lexs);

  // RIGHT_PAR
  _Bool fourth = TRUE;
  fourth = compareToken(curLex, peekLex, lexs, RIGHT_PARENTHESIS);

  // statement
  _Bool fifth = parseStatement(curLex, peekLex, lexs);

  // printf("[DEBUG:WHILE] %d, %d, %d, %d, %d\n", first, second, third, fourth, fifth);

  return first && second && third && fourth && fifth;
}

/***************************************
 * return -> RETURN_KEY expression EOL
 ***************************************/
_Bool parseReturn(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {

  // RETURN_KEY
  _Bool first = compareToken(curLex, peekLex, lexs, RETURN_KEYWORD);

  // expression
  _Bool second = parseExpression(curLex, peekLex, lexs);

  // EOL
  _Bool third = compareToken(curLex, peekLex, lexs, EOL);

  return first && second && third;
}

/********************************************
 * assignment -> IDENT EQUAL expression EOL
 ********************************************/
_Bool parseAssignment(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {
  
  // IDENT
  _Bool first = compareToken(curLex, peekLex, lexs, IDENTIFIER);

  // EQUAL
  _Bool second = compareToken(curLex, peekLex, lexs, EQUAL);

  // expression
  _Bool third = parseExpression(curLex, peekLex, lexs);

  // EOL
  _Bool fourth = compareToken(curLex, peekLex, lexs, EOL);

  return first && second && third && fourth;

}

/*******************************************************************
 * expression -> term {BINOP term} | LEFT_PAR expression RIGHT_PAR 
 *******************************************************************/
_Bool parseExpression(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {

    _Bool first = TRUE;
    _Bool second = TRUE;
    _Bool third = TRUE;

    if (curLex->token == LEFT_PARENTHESIS) {
        nextToken(curLex, peekLex, lexs);

        second = second && parseExpression(curLex, peekLex, lexs);

        third = third && compareToken(curLex, peekLex, lexs, RIGHT_PARENTHESIS);
    
    } else {
        first = first && parseTerm(curLex, peekLex, lexs);

        while (curLex->token == BINOP) {
            nextToken(curLex, peekLex, lexs);
            second = second && parseTerm(curLex, peekLex, lexs);
        }
    }

  // printf("[DEBUG:EXPRESSION] %d, %d, %d, cur: %d\n", first, second, third, curLex->token);
  return first && second && third;
}

/**************************
 * term -> IDENT | NUMBER
 **************************/
_Bool parseTerm(struct lexics *curLex, struct lexics *peekLex, struct lexics *lexs) {

  _Bool ret = curLex->token == IDENTIFIER || curLex->token == NUMBER;
  // printf("[DEBUG:TERM] %d\n", curLex->token);
  nextToken(curLex, peekLex, lexs);

  return ret;
}

_Bool parser(struct lexics *someLexics, int numOfLexics) {

  struct lexics curLex;
  struct lexics peekLex;

  // Load the parser
  nextToken(&curLex, &peekLex, someLexics);

  return parseFunction(&curLex, &peekLex, someLexics); // Everything parsed correctly
}
