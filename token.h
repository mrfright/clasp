#ifndef TOKEN
#define TOKEN

typedef struct tok Token;

struct tok{
  char *p;
  Token *next;
};

void putToken();
Token *getHeadToken();
Token *getTailToken();
void tokenize(char c);

Token *newToken(void);
void deleteNextToken(Token *);
#endif /*TOKEN*/
