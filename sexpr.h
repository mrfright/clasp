#ifndef SEXPR
#define SEXPR
typedef struct sexpr Sexpr;

struct sexpr{
  char *atom;
  Sexpr *inner;
  Sexpr *next;
};

void printSexpr(Sexpr* sexpr);
void deleteSexpr(Sexpr *s);
char* get_atom(Sexpr* s);
void create_atom_from_int(Sexpr* s, int atom);
void create_atom_from_float(Sexpr* s, float atom);
void create_atom(Sexpr* s, char* atom);
Sexpr* copy_sexpr(Sexpr* s);
void create_inner(Sexpr* s);
Sexpr* newSexpr(void);
Sexpr* get_inner(Sexpr* s);
#endif /*SEXPR*/