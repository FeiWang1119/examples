#ifndef TLPI_HDR_H
#define TLPI_HDR_H           /* Prevent accidental double inclusion */
#include "error_functions.h" /* Declares our error_handling functions */
#include "get_num.h" /* Declares our functions for handling numeric arguments (getInt(), getLong()) */

#include <errno.h>     /* Declares errno and defines errors constants */
#include <stdio.h>     /* Standard I/O functions */
#include <stdlib.h>    /* Prototypes of commonly used library functions,
                       plus EXIT_SUCCESS and EXIT_FALURE constans */
#include <string.h>    /* Commonly used string-handling functions */
#include <sys/types.h> /* Type definitions used by many programs */
#include <unistd.h>    /* Prototypes for many system calls */

typedef enum { FALSE, TRUE } Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))

#endif // !TLPI_HDR_H
