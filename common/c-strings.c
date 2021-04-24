//
// -----------------------------------------------------------------------------
// string.c
// -----------------------------------------------------------------------------
//
// Tyler Wayne © 2021
//

#include <stdio.h>    // fgetc
#include <stdlib.h>   // calloc
#include <limits.h>   // PATH_MAX
#include <ctype.h>    // isspace, tolower
#include <stdbool.h>  // bool, true, false
#include <string.h>   // strlen

// get_line is similar to getline in string.h
// except that it doesn't include the newline
// character in the returned string
ssize_t get_line(char *s, size_t n, FILE *fd) {

  if (s == NULL || n == 0 || fd == NULL) return -1;

  ssize_t len = 0;
  char c;

  while ((c = (char) fgetc(fd)) != EOF) {
    if (c == '\n') break;       // ignore new-line
    if (len == n - 1) continue; // ignore the rest of the line once buf is full
    else  s[len] = c;
    len++;
  }
  s[len] = '\0';                // ensure line is null-terminated

  return len;

}

// get_tok_r is like strtok_r in string.h except that it
// doesn't include the newline character
char *get_tok_r(char *str, const char delim, char **saveptr) {

  if (*saveptr == NULL) *saveptr = str;

  char *field = *saveptr;
  bool in_quote = false;

  for ( int i=0; ; i++) {
    switch(field[i]) {
      case '\0':
        if (i == 0) return NULL;
        else {
          *saveptr += i;
          return field;
        }
      case '\n':
        field[i] = '\0';
        *saveptr += i;
        return field;
      case '"': case '\'':
        in_quote = in_quote ? false : true;
        break;
      default:
        if (field[i]==delim && !in_quote) {
          field[i] = '\0';
          *saveptr += (i+1);
          return field;
        }
    }
  }

  return NULL;

}


int strmatch(const char *str, const char *target) {

  // assert(str && target);

  do {
    if (*str != *target) return 0;
  } while (*str++ && *target++);

  return 1;

}

int extmatch(const char *path, const char *ext) {

  // assert(path && ext);

  int path_len = strlen(path);
  int ext_len = strlen(ext);

  if (ext_len == 0 || ext_len > path_len)
    return 0;

  path += (path_len - ext_len);

  return strmatch(path, ext);
  
}

char *strtrim(char *str) {

  // assert(str);
  char *start = NULL, *end = str;

  for ( ; *str ; str++) {
    if (!isspace(*str)) {
      if (!start) start = str;
      else end = str+1;
    }
  }
  *end = '\0';
  return start ? start : end;

}

void strlower(char *str) {
  // assert(str);
  for ( ; *str; str++) *str = tolower(*str);
}

// Concatenate two paths, ensuring there is proper
// directory delimiters (e.g., /this/is + some/path = /this/is/some/path)
char *pathcat(char *path1, char *path2) {

  // assert(path1 && path2);

  int path_max = PATH_MAX - 1; // Ensure we have room for null-terminator
  // char *path = CALLOC(PATH_MAX, sizeof(char));
  char *path = calloc(PATH_MAX, sizeof(char));
  char *head = path;

  // Copy first path
  for ( ; path_max && *path1; path_max--, path++, path1++)
    *path = *path1;

  // Ensure there is one and only one slash between paths
  // But don't add anything if one of the two paths are empty
  if (*head == '\0' || *path2 == '\0') ;
  else if (*(path1-1) != '/' && *path2 != '/')
    *path++ = '/';
  else if (*(path1-1) == '/' && *path2 == '/')
    path2++;

  // Copy second path
  for ( ; path_max && *path2; path_max--, path++, path2++)
    *path = *path2;

  // Add null-terminator
  *path = 0;

  return head;

}
