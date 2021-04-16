// 
// -----------------------------------------------------------------------------
// strings.h
// -----------------------------------------------------------------------------
//
// Common string functions
//
// Tyler Wayne © 2021
//


#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include <stdio.h>  // FILE
#include <stddef.h> // ssize_t

extern ssize_t  get_line(char *s, size_t n, FILE *fd);
extern char    *get_delim_r(char *str, const char delim, char **saveptr);

extern int      strmatch(const char *str, const char *target);
extern char    *strtrim(char *str);
extern void     strlower(char *);
extern int      extmatch(const char *path, const char *ext);
extern char    *pathcat(char *path1, char *path2);

#endif
