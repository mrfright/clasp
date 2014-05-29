#ifndef TOKEN
#define TOKEN

typedef struct tok Token;

struct tok{
  char *p;
  Token *next;
};

Token* tokenizeStr(char *s);

Token *newToken(void);
void deleteNextToken(Token *);
#endif /*TOKEN*/
