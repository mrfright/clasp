#ifndef SEXPR
#define SEXPR
typedef struct sexpr Sexpr;

struct sexpr{
  char *atom;
  Sexpr *inner;
  Sexpr *next;
};

void deleteSexpr(Sexpr *s);
#endif /*SEXPR*/