
#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool parseFunction(struct lexics *, struct lexics *, struct lexics *);
_Bool parseHeader(struct lexics *, struct lexics *, struct lexics *);
_Bool parseArgDecl(struct lexics *, struct lexics *, struct lexics *);
_Bool parseBody(struct lexics *, struct lexics *, struct lexics *);
_Bool parseStatementList(struct lexics *, struct lexics *, struct lexics *);
_Bool parseStatement(struct lexics *, struct lexics *, struct lexics *);
_Bool parseWhileLoop(struct lexics *, struct lexics *, struct lexics *);
_Bool parseReturn(struct lexics *, struct lexics *, struct lexics *);
_Bool parseAssignment(struct lexics *, struct lexics *, struct lexics *);
_Bool parseExpression(struct lexics *, struct lexics *, struct lexics *);
_Bool parseTerm(struct lexics *, struct lexics *, struct lexics *);

_Bool parser(struct lexics *someLexics, int numOfLexics);

#endif
