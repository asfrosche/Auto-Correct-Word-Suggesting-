
#include "suggest.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

// Constants
const int SUGGEST_MAX_STRLEN = 63;



//add_sss(dict, array,sss) checks whether array is an element of dict and
//updates sss accoridingly and returns the final sss
//effects: modifies sss
//time: O(m*logn*(n + m*logn))
struct triple_s *add_sss(const struct triple_s *dict, char *array,
                         struct triple_s *sss) {
  if(sss_search(dict, array) != -1) {
    sss_add(sss, array);
  }
  return sss;
}


//time: O(p^2*m*logn*(n + m*logn)), p is length of dict
struct triple_s *suggest(const struct triple_s *dict, const char *word) {
  //asserts
  assert(dict);
  assert(word);
  assert (strlen(word) <= SUGGEST_MAX_STRLEN);

  struct triple_s *suggested = sss_create(); 
  int len = strlen(word);

  // single deletion
  for(int i = 0; i < len; i++) {
    char delete[64] = {0};
    strcpy(delete, word);
    for(int k = 0; k < len; k++) {
      delete[i + k] = delete[i + k + 1];
    }
    delete[len] = '\0';  
    add_sss(dict,delete,suggested);  
  }

   // single insertion
  char insert[64] = {0};
  for (int k = 97; k < 123; k++) {
     for(int i = 0; i <= len; i++) {
        for(int j = 0; j <= len; j++) {
          if (j < i) {
            insert[j] = word[j];
          } else if (i == j) {
            insert[j] = k;
          } else {
            insert[j]= word[j - 1];
          }
        }
       add_sss(dict,insert,suggested);
     }
  }
       
  // single substitution
  for(int i = 0; i < len; ++i) {
    char subs[64] = {0};
    strcpy(subs, word);
    for(int  j = 0; j < 27; ++j) {
      subs[i] = 97 + j;
      add_sss(dict,subs,suggested);
    }
  }

  // adjacent swap
  for(int i = 0; i < len - 1; ++i) {
    char swap[63] = {0};
    strcpy(swap, word);
    char temp = swap[i];
    swap[i] = swap[i + 1];
    swap[i + 1] = temp;
    add_sss(dict,swap,suggested);
  }
  return suggested;
}
