#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

// errMsg prints a message on standard error.
void errMsg(const char *format, ...);

#ifdef __GNUC__
/* This macro stops 'gc -Wall' complaining that "control reaches
 * end of non-void function" if we use the following functions to
 * terminate main() or some other non-void function.*/

#  define NORETURN __attribute__((__noreturn__))
#else
#  define NORETURN
#endif

// errExit operates like errmsg, but also terminates the program.
void errExit(const char *format, ...) NORETURN;

void err_exit(const char *format, ...) NORETURN;

void errExitEN(int errnum, const char *format, ...) NORETURN;

// fatal is used to diagnose general errors, including errors from library functions that don't set
// errno.
void fatal(const char *format, ...) NORETURN;

// usageErr is used to diagnose errors in command-line argument usage.
void usageErr(const char *format, ...) NORETURN;

// cmdLineErr is intended for diagnosing errors  in the command-line arguments specified to a
// program.
void cmdLineErr(const char *format, ...) NORETURN;

#endif // DEBUG
