#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "re.h"

arena_t create_arena(int size) { 
  arena_t arena = malloc(sizeof(struct arena));
  arena->size=size;
  arena->current=0;
  arena->elts = malloc(size*sizeof(Regexp));
  return arena;
}

void arena_free(arena_t a) { 
  /* TODO */
  free(a->elts);
  free(a);
}

Regexp *re_alloc(arena_t a) { 
  /* TODO */
  if (a->current < a->size) {
	  Regexp *reg = a->elts + a->current;
	  a->current+=1;
	  return reg;
  } else {
	  return NULL;
  }
}

Regexp *re_chr(arena_t a, char c) { 
  /* TODO */
  Regexp *final = re_alloc(a);
  if(final==NULL) {
	  return NULL;
  } else {
	  final->type=CHR;
	  final->data.chr=c;
	  return final;
  }
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) { 
  /* TODO */
  Regexp *final = re_alloc(a);
  if(final==NULL) {
	  return NULL;
  } else {
	  final->type=ALT;
	  final->data.pair.fst = r1;
	  final->data.pair.snd = r2;
	  return final;
  }
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) { 
  /* TODO */
  Regexp *final = re_alloc(a);
  if(final==NULL) {
	  return NULL;
  } else {
	  final->type=SEQ;
	  final->data.pair.fst = r1;
	  final->data.pair.snd = r2;
	  return final;
  }
}

int re_match(Regexp *r, char *s, int i) { 
  /* TODO */
  if (s==NULL || i>=strlen(s)) {
	  return -1;
  }
  int fir;
  int sec;
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      if (s[i]==r->data.chr) {
		  return i+1;
	  } else {
		  return -1;
	  }
    case SEQ:
      fir = re_match(r->data.pair.fst,s,i);
      if (fir<0) {
		  return -1;
	  }
	  sec = re_match(r->data.pair.snd,s,fir);
	  return sec;
    case ALT:
      fir = re_match(r->data.pair.fst,s,i);
      sec = re_match(r->data.pair.snd,s,i);
      if (fir<0) {
		  return sec;
	  } else {
		  return fir;
	  }
      
    }
  } else {
	  return -1;
  }
  return -1;
  
}



void re_print(Regexp *r) { 
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) { 
	printf("(");
	re_print(r->data.pair.fst);
	printf(")");
      } else {
	re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) { 
	printf("(");
	re_print(r->data.pair.snd);
	printf(")");
      } else {
	re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else { 
    printf("NULL");
  }
}    


      
  
