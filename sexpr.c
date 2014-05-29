#include <stdlib.h>
#include "sexpr.h"

void deleteSexpr(Sexpr *s){
  if(s == NULL) return;
  if(s->atom != NULL) free(s->atom);
  if(s->inner != NULL){
    deleteSexpr(s->inner->next);/*not deleting s->inner since is "HEAD", free("HEAD) would crash it*/
    free(s->inner);
  }
  deleteSexpr(s->next);
  free(s);
}