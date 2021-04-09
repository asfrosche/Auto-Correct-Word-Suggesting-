//Header files
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "cs136-trace.h"

struct triple_s {
  struct llnode *front;
  struct llnode *back;
  int len;
};

struct llnode {
  char *item;
  struct llnode *next;
};


struct triple_s *sss_create(void) {
  struct triple_s *lst = malloc(sizeof(struct triple_s));
  lst->front = NULL;
  lst->back = NULL;
  lst->len = 0;
  return lst;
}; 


void sss_destroy(struct triple_s *sss) {
  //asserts
  assert(sss);

  //code
  struct llnode *curnode = sss->front;
  struct llnode *nextnode = NULL;
  while (curnode) {
    nextnode = curnode->next;
    free(curnode->item);
    free(curnode);
    curnode = nextnode;
  }
  free(sss);
}


// sss_search(sss, s) finds the index of s in sss
// note: returns -1 if s does not appear in the sss
// time: O(nm) [MODIFIED FROM A8]
int sss_search(const struct triple_s *sss, const char *s){
  //asserts
  assert(sss);
  assert(s);

  //code
  struct llnode *curnode = sss->front;
  int i = 0;
  while (curnode) {
    if(strcmp(s,curnode->item) == 0) {
      return i;
    } else {
      i++;
      curnode = curnode->next;
    }
  }
  return -1;
}


// sss_add_follows(sss, s) adds s to the "end" of the sss
// requires: s lexicographically follows all strings already in sss
// effects: modifies sss
// time: O(m)
void sss_add_follows(struct triple_s *sss, const char *s){
  //asserts
  assert(sss);
  assert(s);
  assert(strcmp(s,sss->back->item) > 0);
  //asssert me

  //code
  int len = strlen(s);
  struct llnode *newnode = malloc(sizeof(struct llnode));
  char *data = malloc((len + 1) * sizeof(char));
  strcpy(data,s);
  newnode->item = data;
  //strcpy(newnode->item, s);
  newnode->next = NULL;
  if (sss->front == NULL) {
    // queue was empty
    sss->front = newnode;
  } else {
    sss->back->next = newnode;
  }

  sss->back = newnode;
  sss->len ++;
}

//add_front(sss,s) adds a node with string data s at the front of 
// the sss
//time: O(m)
void add_front(struct triple_s *sss, const char *s) {
  //asserts
  assert(sss);
  assert(s);

  //code
  int len = strlen(s);
  struct llnode *newnode = malloc(sizeof(struct llnode));
  char *data = malloc((len + 1) * sizeof(char));
  strcpy(data,s);
  newnode->item = data;
  newnode->next = sss->front;
  sss->front = newnode;
  sss->len ++;
}


void sss_add(struct triple_s *sss, const char *s) {
  //asserts
  assert(sss);
  assert(s);

  //code
  if (sss_search(sss,s) != -1) {
    return;
  }
  if (sss->front == NULL) {
    add_front(sss,s);
    sss->back = sss->front;
  }
  else if(strcmp(s,sss->front->item) < 0) { 
    add_front(sss,s);
  } else {
    // find the node that will be "before" our insert
    struct llnode *before = sss->front;

    while (before->next && (strcmp(s,before->next->item) > 0)) {
      before = before->next;
    }
    sss->len ++;
    // now do the insert
    if(before == sss->back) {
      sss_add_follows(sss,s);
      return;
    }
    struct llnode *newnode = malloc(sizeof(struct llnode));
    int len = strlen(s);
    char *data = malloc((len + 1) * sizeof(char));
    strcpy(data,s);
    newnode->item = data;
    // strcpy(newnode->item, s);
    newnode->next = before->next;
    before->next = newnode;
  }
}

//remove_front(sss,s) removes a node with string data s at the
// front of the sss
//time: O(1)
void remove_front(struct triple_s *sss) {
  //asserts
  assert(sss);
  assert(sss->front);

  //code
  struct llnode *old_front = sss->front;
  sss->front = sss->front->next;
  free(old_front->item);
  free(old_front);
  sss->len --;
  if (sss->front == NULL) {
    // queue is now empty
    sss->back = NULL;
  }
}


void sss_remove(struct triple_s *sss, const char *s) {
  //asserts
  assert(sss);
  assert(s);

  //code
  if (strcmp(s,sss->front->item) == 0) {
    remove_front(sss);
  }
  struct llnode *before = sss->front;
  while (before->next && (strcmp(s,before->next->item) > 0)) {
    before = before->next;
  }
  if(before->next == sss->back) {
    sss->back  = before;
  }
 
  if (before->next == NULL) {
    return; // doesnt exist in sss
  }
  assert(before->next);
  struct llnode *old_node = before->next;
  before->next = before->next->next;
  sss->len --;
  free(old_node->item);
  free(old_node);
}


int sss_count(const struct triple_s *sss){
  //asserts
  assert(sss);

  //code
  return sss->len;
} 


const char *sss_get(const struct triple_s *sss, int idx) {
  //asserts
  assert(sss);
  assert(idx >= 0 && idx < sss_count(sss));

  //code
  struct llnode *curnode = sss->front;
  while (idx) {
    curnode = curnode->next;
    idx --;
  }
  return curnode->item;
} 
