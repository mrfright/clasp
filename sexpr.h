
typedef struct sexpr Sexpr;

struct sexpr{
	char *atom;
	Sexpr *inner;
	Sexpr *next;
}