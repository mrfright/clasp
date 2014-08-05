#ifndef TOKEN
#define TOKEN

typedef struct tok Token;

struct tok{
  char *p;
  Token *next;
};

void printToken(Token* token);
Token* tokenizeStr(char *s);

Token *newToken(void);
void deleteNextToken(Token *);
#endif /*TOKEN*/
