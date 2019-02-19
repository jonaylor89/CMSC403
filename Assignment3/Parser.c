
#include "Parser.h"
#include "Givens.h"

void parseFunction() {
  // function -> header body
  parseHeader();
  parseBody();
}

void parseHeader() {
  // header -> VARTYPE INDENT LEFT_PAR arg-decl RIGHT_PAR

}

void parseArgDecl() {
  // arg-decl -> VARYPE IDENT {COMMA VARTYPE INDENT}

}

void parseBody() {
  // body -> LEFT_BAR Statement-list RIGHT_BRA

}

void parseStatementList() {
  // statement-list -> statement {statement}

}

void parseStatement() {
  // statement -> while-loop | return | assignment | body



}

void parseWhileLoop() {
  // while-loop -> WHILE_KEY LEFT_PAR expression RIGHT_PAR statement

}

void parseReturn() {
  // RETURN_KEY EXPRESSION EOL

}

void parseAssignment() {
  // INDENT EQUAL expression EOL

}

void parseExpression() {
  // term {BINOP term} | LEFT_PAR expression RIGHT_PAR

}

void parseTerm() {
  // INDENT | NUMBER

}

_Bool parser(struct lexics *someLexics, int numOfLexics) {

  struct lexics curLex;

  for (int i = 0; i < LEXEME_MAX; i++) {

    curLex = someLexics[i];
    
    if (curLex.token != EOP) {

      // printf("%s", curLex.lexeme);

      switch (curLex.token) {

      case LEFT_PARENTHESIS:
        break;
      case RIGHT_PARENTHESIS:
        break;
      case LEFT_BRACKET:
        break;
      case RIGHT_BRACKET:
        break;
      case WHILE_KEYWORD:
        break;
      case RETURN_KEYWORD:
        break;
      case EQUAL:
        break;
      case COMMA:
        break;
      case EOL:
        break;
      case VARTYPE:
        break;
      case IDENTIFIER:
        break;
      case BINOP:
        break;
      case NUMBER:
        break;
      default:
        break;

      }
    } else {
      break;
    }
  
  }

  return TRUE;
}
