///////////////////////////////////////////////////////////////////////////// 

#include "suggest.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constants:
const int SUGGEST_MAX_STRLEN = 63;
/////////////////////////////////////////////////////////////////////////////


struct triple_s *sss_check(const struct triple_s *dict, char *temp,
                           struct triple_s *sss) {
  //struct triple_s *sss = sss_create();
  int result = sss_search(dict, temp);
  if(result != -1) {
    sss_add(sss, temp);
  }
  return sss;
}


void asserts(int len, const struct triple_s *dict, const char *word) {
  assert(len <= SUGGEST_MAX_STRLEN);
  assert(dict && word);
}


void deletions(const struct triple_s *dict, const char *word,
               struct triple_s *sss) {
  int pos = 0;
  char temp[63];
  int len = strlen(word);
  for(int i = 0; i < len; i++) {
    for(int j = 0; j < len - 1; j++) {
      //printf("pos = %d\n", pos);
      if(j < pos) {
        temp[j] = word[j];
      }
      else if(j >= pos) {
        temp[j] = word[j + 1];
      }
    }
    pos++;
    sss_check(dict, temp, sss);
    //printf("%s\n", temp);
    //int result = sss_search(dict, temp);
    //printf("result = %d\n", result);
  }
}


void insertion(const struct triple_s *dict, const char *word,
               struct triple_s *sss) {
  int pos = 0;
  char temp[63];
  char c = 97;
  int len = strlen(word);
  for(int k = 0; k < 26; k++) {
    pos = 0;
    for(int i = 0; i <= len; i++) {
      for(int j = 0; j <= len; j++) {
        if(j < pos) {
          temp[j] = word[j];
        }
        else if(j == pos) {
          temp[j] = c;
        }
        else if(j > pos) {
          temp[j] = word[j - 1];
        }
      } 
      pos++;
      sss_check(dict, temp, sss);
      //printf("%s\n", temp);
    }
    c++;
  }
}


void substitution(const struct triple_s *dict, const char *word,
                 struct triple_s *sss) {
  int pos = 0;
  char temp[63];
  char letter_ascii = 97;
  int len = strlen(word);
  for(int k = 0; k < 26; k++) {
    pos = 0;
    for(int i = 0; i < len; i++) {
      for(int j = 0; j < len; j++) {
        if(j != pos) {
          temp[j] = word[j];
        }
        else {
          temp[j] = letter_ascii;
        }
      }
      sss_check(dict, temp, sss);
      //printf("%s\n", temp);
      pos++;
    }
    letter_ascii++;
  }
}


void swap(const struct triple_s *dict, const char *word, 
         struct triple_s *sss) {
  int len = strlen(word);
  char temp[63];
  for(int i = 0; i < len; i ++) {
    temp[i] = word[i];
  }
  for(int i = 0; i < len - 1; i++) {
    for(int i = 0; i < len; i ++) {
      temp[i] = word[i];
    }
    char a = temp[i];
    temp[i] = temp[i + 1];
    temp[i + 1] = a;
    sss_check(dict, temp, sss);
    //printf("%s\n", temp);
  }
}


// suggest(dict, word) creates a new SSS that contains suggestions
//   from the provided dict[ionary] for possible misspellings of word
// note: the word itself should not appear in the returned SSS
//       the returned SSS will be empty if no suggestions can be found
//         (the returned SSS must still be destroyed)
//       see assignment text for more details regarding
//         which words should be suggested
// requires: dict, word are valid (not NULL)
//           length of word <= SUGGEST_MAX_STRLEN
//           word only contains lowercase letters (or numbers) [not asserted]
// effects: allocates memory (an SSS) (you must call sss_destroy)
// time: O(n^2)
//       n -> the number of letters in a word
struct triple_s *suggest(const struct triple_s *dict, const char *word) {
  int len = strlen(word);
  assert(len <= SUGGEST_MAX_STRLEN);
  assert(dict);
  assert(word);
  asserts(len, dict, word);
  struct triple_s *sss = sss_create();
  insertion(dict, word, sss);
  deletions(dict, word, sss);
  substitution(dict, word, sss);
  swap(dict, word, sss);
  sss_remove(sss, word);
  return sss;
}
