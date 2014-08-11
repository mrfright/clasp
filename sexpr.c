#include <stdlib.h>

/*for printf*/
#include <stdio.h>
#include <string.h>/*strcmp, strlen*/
#include "sexpr.h"

Sexpr* newSexpr(void){
  Sexpr* sexpr = (Sexpr*)malloc(sizeof(Sexpr));
  sexpr->inner = NULL;
  sexpr->next = NULL;
  sexpr->atom = NULL;
  return sexpr;
}

char* get_atom(Sexpr* s){
  if(s == NULL){
    printf("\nNull Sexpr in get_atom\n");
    return NULL;
  }
  return s->atom;
}

Sexpr* get_inner(Sexpr* s){
  if(s == NULL){
    printf("\nNull Sexpr in get_inner\n");
    return NULL;
  }
  if(s->inner == NULL){
    printf("\nNull inner Sexpr in get_inner\n");
    return NULL;
  }
  return s->inner->next;/*next because first inner is the linked list head*/
}

Sexpr* get_next(Sexpr* s){
  if(s == NULL){
    printf("\nNUll Sexpr in get_next\n");
    return NULL;
  }
  return s->next;
}


void create_atom_from_int(Sexpr* s, int atom){
  char temp_atom[20];
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %d\n", atom);
  s->atom = (char*)malloc(20);
  sprintf(temp_atom,"%d",atom);
  strcpy(s->atom,temp_atom);
}

void create_atom_from_float(Sexpr* s, float atom){
  char temp_atom[20];
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %f\n", atom);
  s->atom=(char*)malloc(20);
  sprintf(temp_atom,"%f",atom);
  strcpy(s->atom,temp_atom);
}

void create_atom(Sexpr* s, char* atom){
  if(s == NULL){
    printf("\nCreating atom on null Sexpr\n");
    return;
  }
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %s\n", atom);
  s->atom=(char*)malloc(strlen(atom) + 10);
  strcpy(s->atom,atom);
}

void create_inner(Sexpr* s){
  if(s == NULL){
    printf("\nCreating inner sexpr on null sexpr\n");
    return;
  }
  s->inner = newSexpr();
  create_atom(s->inner, "HEAD");
}

Sexpr* copy_sexpr(Sexpr* s){
  Sexpr* copys = NULL;
  Sexpr* lastInnerCopy;
  Sexpr* innerSexpr;
  if(s != NULL){
    copys = newSexpr();
    /*copy atom if there*/
    if(s->atom != NULL)
      create_atom(copys, s->atom);
    
    /*copy inner if there*/
    if(s->inner != NULL){
      create_inner(copys);
      
      /*recursive call on all inner members*/
      innerSexpr = get_inner(s);
      lastInnerCopy = copys->inner;
      while(innerSexpr != NULL){
        lastInnerCopy->next = copy_sexpr(innerSexpr);
        innerSexpr = innerSexpr->next;
        lastInnerCopy = lastInnerCopy->next;
      }
    }
  }
  return copys;
}

void printSexpr(Sexpr* sexpr){
  Sexpr* innerSexpr;
  char* space = "";
  if(sexpr == NULL){
    return;
  }
  if(get_atom(sexpr) != NULL)
    printf("%s", get_atom(sexpr));
  else{
    printf("(");
    innerSexpr = get_inner(sexpr);
    while(innerSexpr != NULL){
      printf(space);
      space = " ";
      printSexpr(innerSexpr);
      innerSexpr = innerSexpr->next;
    }
    /*printSexpr(sexpr->inner->next);*next to skip linked list head*/
    printf(")");
  }
  /*printf(" ");
  printSexpr(sexpr->next);*/
}

void deleteSexpr(Sexpr *s){
  if(s == NULL) return;
  if(get_atom(s) != NULL) free(get_atom(s));
  if(s->inner != NULL){
    deleteSexpr(s->inner);/*used to be s->inner->next since couldn't delete some "HEAD"*/
    /*free(s->inner);needed this if we were skipping the inner because couldn't delete "HEAD"*/
  }
  deleteSexpr(s->next);
  free(s);
}