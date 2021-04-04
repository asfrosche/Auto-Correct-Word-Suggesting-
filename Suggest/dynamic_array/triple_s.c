///////////////////////////////////////////////////////////////////////////// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct triple_s {
  char **data;
  int maxlen;
  int len;
};

void sss_print(struct triple_s *sss) {
  printf("%d\n", sss->len);
  for(int i = 0; i < sss->len; i++) {
    printf("%s\n", sss->data[i]);
  }
}


// sss_create() creates a new SSS ADT
// effects: allocates memory (you must call sss_destroy)
// time: O(1)
struct triple_s *sss_create(void) {
  struct triple_s *obj = malloc(sizeof(struct triple_s));
  obj->len = 0;
  obj->maxlen = 1;
  obj->data = malloc(obj->maxlen * sizeof(char *));
  return obj;
}



// sss_destroy(sss) destroys sss
// requires: sss is valid (not NULL)
// effects: sss is no longer valid
// time: O(n)
void sss_destroy(struct triple_s *sss) {
  assert(sss);
  for (int i = 0; i < sss->len ; i++) {
    free(sss->data[i]);
  }
  free(sss->data);
  free(sss);
}


// sss_search(sss, s) finds the index of s in sss
// note: returns -1 if s does not appear in the sss
// time: O(m*logn)
int sss_search(const struct triple_s *sss, const char *s) {
  int low = 0;
  int high = sss->len - 1;
  if(sss->len == 0) return -1;
  while (low <= high) {
    int mid = (low + high) / 2;
    int result = strcmp(sss->data[mid], s);
    if (result == 0) {
      return mid;
    } 
    else if (result < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// sss_add(sss, s) adds s to sss in the correct index (lexicographically)
// notes: if s already exists, there is no effect
//        when s is added, the indices of words that lexicographically
//          follow s will be changed (+1) because s is added into the "middle"
// effects: may modify sss
// time: O(n + m*logn)
void sss_add(struct triple_s *sss, const char *s) {
  //int present = 0;
  int lenm = strlen(s);
  int insert = sss->len;
  // creating array to copy original s into
  if(sss_search(sss, s) != -1) {
    return;
  }
  char *temp = malloc((lenm + 1) * sizeof(char));
  // copying s into temp
  strcpy(temp, s);
  // doubling strategy
  if(sss->len == sss->maxlen) {
    sss->maxlen *= 2;
    sss->data = realloc(sss->data, sss->maxlen * sizeof(char *));
  }
  //present = sss_search(sss, s);
  
  //if(sss_search(sss, s) == -1) {
  for(int i = 0; i < sss->len; i++) {
    int result = strcmp(sss->data[i], s);
    if(result > 0) {
      insert = i;
      break;
    }
  }
  // changing indices
  for(int i = sss->len; i > insert; i--) {
    sss->data[i] = sss->data[i - 1];
  }
  sss->data[insert] = temp;
  sss->len++;
}


// sss_add_follows(sss, s) adds s to the "end" of the sss
// requires: s lexicographically follows all strings already in sss
// effects: modifies sss
// time: O(m) [amortized]
void sss_add_follows(struct triple_s *sss, const char *s) {
  
  // doubling strategy
  if(sss->len == sss->maxlen) {
    sss->maxlen *= 2;
    sss->data = realloc(sss->data, sss->maxlen * sizeof(char *));
  }
  
  int lenm = strlen(s);
  char *temp = malloc((lenm + 1) * sizeof(char));
  sss->len++;
  strcpy(temp, s);
  sss->data[sss->len - 1] = temp;
}



// sss_remove(sss, s) removes s from sss (if it exists)
// notes: if s is removed, the indices of words that lexicographically
//          follow s will be changed (-1)
// effects: may modify sss
// time: O(n + m*logn)
void sss_remove(struct triple_s *sss, const char *s) {
  
  int index = sss_search(sss, s);
  if(index == -1) {
    return;
  }
  
  free(sss->data[index]);
  for(int i = index; i < sss->len - 1; i++) {
    //sss->data[i] = sss->data[i + 1];
    sss->data[i] = sss->data[i + 1];
  }
  //free(sss->data[sss->len - 1]);
  sss->len--;
  //sss->data = realloc(sss->data, sss->len * sizeof(char *));
}

// sss_count(sss) gets the number of strings in sss
// time: O(1)
int sss_count(const struct triple_s *sss) {
  return sss->len;
}


// sss_get(sss, idx) retrieves a pointer to the string in sss
//   at the given idx (index)
// requires: 0 <= idx < sss_count(sss)
// time: O(1)
const char *sss_get(const struct triple_s *sss, int idx) {
  assert((0 <= idx) && (idx < sss_count(sss)));
  return sss->data[idx];
}























