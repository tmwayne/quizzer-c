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

int load_quiz(struct pair **quiz, FILE *fd) {

  char line[LINE_MAX+1];
  int n = 0;

  for ( ; n<NLINES && get_line(line, LINE_MAX, fd)>0; n++ ) {
    if (!(quiz[n] = calloc(1, sizeof(struct pair)))) return -1;
    char *saveptr = NULL;
    quiz[n]->a = strdup(get_tok_r(line, '|', &saveptr));
    quiz[n]->b = strdup(get_tok_r(NULL, '|', &saveptr));
  }

  return n;

}

int main(int argc, char** argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  // Load quiz
  FILE *fin = fopen(argv[1], "r");
  struct pair *quiz[NLINES];

  int nlines = load_quiz(quiz, fin);
  if (nlines <= 0) {
    fprintf(stderr, "Failed to allocate memory for quiz...\n");
    exit(EXIT_FAILURE);
  }

  // Prepare quiz
  shuffle_quiz(quiz+1, nlines-1); // ignore header

  // Give quiz
  for (int i=0; i<nlines; i++)
    printf("1: %s, 2: %s\n", quiz[i]->a, quiz[i]->b);

  // Cleanup
  for (int i=0; i<nlines; i++) free(quiz[i]);

}
