
#include "Parser.h"
#include "Givens.h"

void nextToken(struct lexics *cur, struct lexics *next, struct lexics *lexs) {
  static int position = 1;

  cur = next;
  next = &lexs[position];

  position++;
}

_Bool parseFunction() {
  // function -> header body
  return parseHeader() && parseBody();
}

_Bool parseHeader() {
  // header -> VARTYPE INDENT LEFT_PAR arg-decl RIGHT_PAR

  return TRUE;
}

_Bool parseArgDecl() {
  // arg-decl -> VARYPE IDENT {COMMA VARTYPE INDENT}
  return TRUE;
}

_Bool parseBody() {
  // body -> LEFT_BAR Statement-list RIGHT_BRA
  return TRUE;
}

_Bool parseStatementList() {
  // statement-list -> statement {statement}
  return TRUE;
}

_Bool parseStatement() {
  // statement -> while-loop | return | assignment | body
  return TRUE;
}

_Bool parseWhileLoop() {
  // while-loop -> WHILE_KEY LEFT_PAR expression RIGHT_PAR statement
  return TRUE;
}

_Bool parseReturn() {
  // RETURN_KEY EXPRESSION EOL
  return TRUE;
}

_Bool parseAssignment() {
  // INDENT EQUAL expression EOL
  return TRUE;
}

_Bool parseExpression() {
  // term {BINOP term} | LEFT_PAR expression RIGHT_PAR
  return TRUE;
}

_Bool parseTerm() {
  // INDENT | NUMBER
  return TRUE;
}

_Bool parser(struct lexics *someLexics, int numOfLexics) {

  struct lexics curLex;
  struct lexics peekLex;

  // Load the parser with current and peek token
  nextToken(&curLex, &peekLex, someLexics);
  nextToken(&curLex, &peekLex, someLexics);

  while (curLex.token != EOP) {

    // printf("%s", curLex.lexeme);

    if (parseFunction() == FALSE) {
      return FALSE;
    }

    nextToken(&curLex, &peekLex, someLexics);
  
  }

  return TRUE;
}
