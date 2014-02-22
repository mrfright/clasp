#include "readline.h"

void readline(FILE *fp, char terminal, void (*tokenfunc)(char)/*,  the token list, input stream or file?*/){
  int c;
  while((c=getc(fp))!=terminal && c!=EOF)
    (*tokenfunc)(c);
}
