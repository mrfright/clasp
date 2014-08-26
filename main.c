#include <stdio.h>
#include "token.h"
#include "parse.h"
#include "eval.h"

char line[100];

int main(void){
  Sexpr* parsedSexpr;
  Sexpr* evaledSexpr;
  Env* env = newEnv(NULL);
  
  /*load from file
  readline(fopen("testreadline.txt", "r"), EOF, testReadFromFile);
  
  use this instead
  readline(stdin, '\n', testTokenize);
  */
  
  printf(">");
  while(gets(line)){
    parsedSexpr = parseStr(line);
    evaledSexpr = eval(parsedSexpr, env);
    printSexpr(evaledSexpr);
    deleteSexpr(parsedSexpr);
    deleteSexpr(evaledSexpr);
    printf("\n>");
  }
  return 0;
}
