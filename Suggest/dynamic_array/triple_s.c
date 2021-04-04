//Headers
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cs136-trace.h"
#include <string.h>

// Description - Writing a program to perform operations on a 
//  Sorted Set of Strings(SSS)
struct triple_s {
  int len;
  int maxlen;
  char **data;
};


struct triple_s *sss_create(void) {
  struct triple_s *sss = malloc(sizeof(struct triple_s));
  sss->len = 0;
  sss->maxlen = 1;
  sss->data = malloc(sss->maxlen * sizeof(char *)); 
  // dynamically initializing data
  return sss;
} 


void sss_destroy(struct triple_s *sss) {
  assert(sss);
  for (int i = 0; i < sss->len ; i++) {
    free(sss->data[i]); //freeing each element of array data
  }
  free(sss->data);
  free(sss);
}


int sss_search(const struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  int low = 0;
  int high = sss->len - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (strcmp(sss->data[mid], s) == 0) {
      return mid; //returning address of element if found
    } else if (strcmp(sss->data[mid], s) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1; //element not found
}


void sss_add(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  if(sss_search(sss,s) != -1) {
    return;
  } 
  char *str = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(str,s);
  // Increasing size of array of pointers(doubling strategy)
  if (sss->len == sss->maxlen) {
    sss->maxlen *= 2;
    sss->data = realloc(sss->data, sss->maxlen * sizeof(char *));
  }
  int pos = sss->len;
  for(int i = 0; i < sss->len; i++) {
    if(strcmp (sss->data[i], s) > 0) {
      pos = i; //finding positon for where element gets added
      break;
    }
  }
  for(int i = sss->len; i > pos; i--) {
    sss->data[i] = sss->data[i - 1]; //shifting elements
  }
  sss->data[pos] = str;
  sss->len += 1;
}


void sss_add_follows(struct triple_s *sss, const char *s) {
  assert((strcmp(sss->data[sss->len - 1], s) < 0));
  // checks if elemts is to be placed at the end, lexographically 
  // bigger than last element of sss as it is sorted
  assert(sss);
  assert(s);
  if(sss_search(sss,s) != -1) {
    return;
  } 
  char *str = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(str,s);
  if (sss->len == sss->maxlen) {
    sss->maxlen *= 2;
    sss->data = realloc(sss->data, sss->maxlen * sizeof(char *));
    // doubling startegy
  }
  sss->data[sss->len] = str; //storing string at the end
  sss->len += 1;
}


void sss_remove(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  int pos = sss_search(sss,s);
  if(pos == -1) {
    return;
  }
  free(sss->data[pos]);
  for (int i = pos; i < sss->len - 1; i++) {
    sss->data[i] = sss->data[i+1];  //shifting elements
  }
  sss->len -=1; //changing length of sss
}


int sss_count(const struct triple_s *sss) {
  assert(sss);
  return sss->len;
}


const char *sss_get(const struct triple_s *sss, int idx) {
  assert(sss);
  assert(idx >= 0 && idx < sss_count(sss));
  return sss->data[idx];
}
