#ifndef TOKEN
#define TOKEN

typedef struct tok Token;

struct tok{
	char *p;
	Token *next;
};

void putToken();
Token *getHead();
Token *getTail();
void tokenize(char c);

Token *newToken(void);
void deleteNext(Token *);
#endif /*TOKEN*/
