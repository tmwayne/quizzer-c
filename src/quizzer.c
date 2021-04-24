//
// -----------------------------------------------------------------------------
// Quizzer
// -----------------------------------------------------------------------------
//
// Tyler Wayne © 2021
//

#include <stdio.h>  // printf, fopen
#include <stdlib.h> // srand, rand, RAND_MAX, EXIT_FAILURE
#include <time.h>   // time
#include <limits.h> // LINE_MAX
#include <string.h> // strdup
#include "argparse.h"
#include "c-strings.h"

#define NLINES 100

struct pair {
  char *a;
  char *b;
};

void shuffle_quiz(struct pair **quiz, int n) {

  srand(time(NULL));

  for(size_t i=n-1; i>0; i--) {
    size_t j = rand() / (RAND_MAX / n);
    struct pair *t = quiz[j];
    quiz[j] = quiz[i];
    quiz[i] = t;
  }

}

int main(int argc, char** argv) {

  struct pair *quiz_data[NLINES];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Prepare data structures
  FILE *fin = fopen(argv[1], "r");
  char *line = calloc(LINE_MAX+1, sizeof(char));
  // for (int i=0; i<NLINES; i++) lines[i] = calloc(LINE_MAX+1, sizeof(char));
  
  // Load quiz
  int nlines = 0;
  // for ( ; nlines<NLINES && get_line(quiz_data[nlines].line, LINE_MAX, fin)>0; nlines++) {
    // quiz_data[nlines] = calloc(1, sizeof(struct pair));
    // get_delim_t(

  for ( ; nlines<NLINES ; nlines++ ) {
    if (get_line(line, LINE_MAX, fin) <= 0) break;
    quiz_data[nlines] = calloc(1, sizeof(struct pair));
    char *saveptr = NULL;
    quiz_data[nlines]->a = strdup(get_delim_r(line, '|', &saveptr));
    quiz_data[nlines]->b = strdup(get_delim_r(NULL, '|', &saveptr));
  }

  // Prepare quiz
  shuffle_quiz(quiz_data, nlines);

  // Give quiz
  for (int i=0; i<nlines; i++)
    printf("1: %s, 2: %s\n", quiz_data[i]->a, quiz_data[i]->b);

}
