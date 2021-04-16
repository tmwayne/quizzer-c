//
// -----------------------------------------------------------------------------
// Quizzer
// -----------------------------------------------------------------------------
//
// Tyler Wayne © 2021
//

#include <stdio.h>  // printf, fopen
#include <stdlib.h> // srand, rand, RAND_MAX
#include <time.h>   // time
#include <limits.h> // LINE_MAX
#include "argparse.h"
#include "c-strings.h"

#define NLINES 10

void shuffle(char **arr, int n) {

  srand(time(NULL));

  for(size_t i=n-1; i>0; i--) {
    size_t j = rand() / (RAND_MAX / n);
    char *t = arr[j];
    arr[j] = arr[i];
    arr[i] = t;
  }

}

int main(int argc, char** argv) {

  char *lines[NLINES];
  for (int i=0; i<NLINES; i++) lines[i] = calloc(LINE_MAX+1, sizeof(char));

  FILE *fd = fopen("data.txt", "r");
  
  int nlines = 0;
  for ( ; nlines<NLINES && get_line(lines[nlines], LINE_MAX, fd)>0; nlines++) ;

  shuffle(lines, nlines);

  for (int i=0; i<nlines; i++) printf("%s\n", lines[i]);

}
