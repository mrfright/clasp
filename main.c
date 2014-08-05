#include <stdio.h>
#include "token.h"
#include "parse.h"
#include "eval.h"

char line[100];





int main(void){
  Sexpr* parsedSexpr;
  Sexpr* evaledSexpr;
  Env* env = newEnv(NULL);
  printf(">");
  while(gets(line)){
    parsedSexpr = parseStr(line);
    evaledSexpr = eval(parsedSexpr, env);
    printSexpr(evaledSexpr);
    /*deleteSexpr(parsedSexpr);this fucks things up for now
    /*deleteSexpr(evaledSexpr);have tree insert copy node and value instead of just assign pointer of something that will be deleted by something else*/
    printf("\n>");
  }
  return 0;
}
