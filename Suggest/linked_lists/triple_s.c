///////////////////////////////////////////////////////////////////////////// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// The following applies to all functions
// requires: all sss parameters are valid (not NULL) 
//           all s parameters are valid (not NULL)
// time: (n) is the number of strings in the sss
//       (m) is the length of the string s

struct tnode {
  char *data;
  struct tnode *next;
};

struct triple_s {
  struct tnode *front;
  struct tnode *end;
  int maxlen;
  int len;
};

void list_print(const struct triple_s *lst) {
  assert(lst);
  struct tnode *curnode = lst->front;
  if (curnode == NULL) {
    printf("[empty]\n");
    return;
  }
  while (curnode) {
    printf("%s\n", curnode->data);
    curnode = curnode->next;
  }
}

// sss_create() creates a new SSS ADT
// effects: allocates memory (you must call sss_destroy)
// time: O(1)
struct triple_s *sss_create(void) {
  struct triple_s *lst = malloc(sizeof(struct triple_s));
  lst->front = NULL;
  lst->end = NULL;  
  lst->len = 0;
  lst->maxlen = 1;
  return lst;
}

// sss_count(sss) gets the number of strings in sss
// time: O(1)
int sss_count(const struct triple_s *sss) {
  //printf("count = %d\n", sss->len);
  return sss->len;
}


void queue_remove_front(struct triple_s *sss) {
  assert(sss->front);
  struct tnode *old_front = sss->front;
  sss->front = sss->front->next;
  free(old_front->data);
  free(old_front);
  if (sss->front == NULL) {
    // queue is now empty
    sss->end = NULL;
  }
}

bool queue_is_empty(struct triple_s *sss) {
  return sss->front == NULL;
}

void sss_destroy(struct triple_s *sss) {
  while (!queue_is_empty(sss)) {
    queue_remove_front(sss);
  }
  free(sss);
}


// sss_add_follows(sss, s) adds s to the "end" of the sss
// requires: s lexicographically follows all strings already in sss
// effects: modifies sss
// time: O(m)
void sss_add_follows(struct triple_s *sss, const char *s) {
  assert(sss);
  int len = strlen(s);
  struct tnode *newnode = malloc(sizeof(struct tnode));
  char *temp = malloc((len + 1) * sizeof(char));
  strcpy(temp, s);
  newnode->data = temp;
  newnode->next = NULL;
  if (sss->front == NULL) {
  // queue was empty
    sss->front = newnode;
  } 
  else {
    sss->end->next = newnode;
  }
  sss->end = newnode;
  sss->len++;
  // testing
  //sss_count(sss);
  //list_print(sss);
}



void add_front(char *i, struct triple_s *lst) {
  struct tnode *newnode = malloc(sizeof(struct tnode));
  newnode->data = i;
  newnode->next = lst->front;
  lst->front = newnode;
}

/*
void insert(const char *i, struct triple_s *sss) {
  if (sss->front == NULL || i < sss->front->data) {
    add_front(i, slst);
  } 
  else {
    // find the node that will be "before" our insert
    struct llnode *before = slst->front;
    while (before->next && i > before->next->item) {
    before = before->next;
  }
  // now do the insert
  struct llnode *newnode = malloc(sizeof(struct llnode));
  newnode->item = i;
  newnode->next = before->next;
  before->next = newnode;
  }
}
*/


// sss_add(sss, s) adds s to sss in the correct index (lexicographically)
// notes: if s already exists, there is no effect
//        when s is added, the indices of words that lexicographically
//          follow s will be changed (+1) because s is added into the "middle"
// effects: may modify sss
// time: O(nm) [MODIFIED FROM A8]
void sss_add(struct triple_s *sss, const char *s) {
  assert(sss);
  int flag = 0;
  int len = strlen(s);
  char *temp = malloc((len + 1) * sizeof(char));
  strcpy(temp, s);
  
  struct tnode *newnode = malloc(sizeof(struct tnode));
  struct tnode *curnode = sss->front;//malloc(sizeof(struct tnode));
  //curnode = sss->front;
  
  if(sss->len == 0) {
    flag = 1;
    newnode->data = temp;
    newnode->next = NULL;
    sss->len++;
    sss->front = newnode;
    sss->end = newnode;
    return;
  }
  

  for(int i = 0; i < sss->len; i++) {
    int result = strcmp(curnode->data, s);
    if(result < 0 && flag != 1) {
      //printf("Im in!!!");
      newnode->next = curnode->next;
      curnode->next = newnode;
      newnode->data = temp;
      flag = 1;
      sss->len++;
      // if inserting at the end ------
      //sss->end->next = newnode;
      ///////// CHANGE LOGIC ////////
      //sss->end = newnode;
      //curnode = curnode->next;
      break;
    }
    curnode = curnode->next;
  }
  
  
  
  
  
  free(newnode);
  free(temp);
  //list_print(sss);
  //free(curnode);
  
}
















