/*

                              A T L A S T

          Autodesk Threaded Language Application System Toolkit

                     Program Linkage Definitions

     Designed and implemented in January of 1990 by John Walker.

     This  module  contains  the  definitions  needed by programs that
     invoke the ATLAST system.  It does contain the  definitions  used
     internally   within  ATLAST  (which  might  create  conflicts  if
     included in calling programs).

*/

typedef long atl_int;                 /* Stack integer type */
typedef double atl_real;              /* Real number type */

/*  External symbols accessible by the calling program.  */

extern atl_int atl_stklen;            /* Initial/current stack length */
extern atl_int atl_rstklen;           /* Initial/current return stack length */
extern atl_int atl_heaplen;           /* Initial/current heap length */
extern atl_int atl_ltempstr;          /* Temporary string buffer length */
extern atl_int atl_ntempstr;          /* Number of temporary string buffers */

extern atl_int atl_trace;             /* Trace mode */
extern atl_int atl_walkback;          /* Error walkback enabled mode */
extern atl_int atl_comment;           /* Currently ignoring comment */
extern atl_int atl_redef;             /* Allow redefinition of words without
                                         issuing the "not unique" warning. */
extern atl_int atl_errline;           /* Line number where last atl_load()
                                         errored or zero if no error. */

/*  ATL_EVAL return status codes  */

#define ATL_SNORM       0             /* Normal evaluation */
#define ATL_STACKOVER   -1            /* Stack overflow */
#define ATL_STACKUNDER  -2            /* Stack underflow */
#define ATL_RSTACKOVER  -3            /* Return stack overflow */
#define ATL_RSTACKUNDER -4            /* Return stack underflow */
#define ATL_HEAPOVER    -5            /* Heap overflow */
#define ATL_BADPOINTER  -6            /* Pointer outside the heap */
#define ATL_UNDEFINED   -7            /* Undefined word */
#define ATL_FORGETPROT  -8            /* Attempt to forget protected word */
#define ATL_NOTINDEF    -9            /* Compiler word outside definition */
#define ATL_RUNSTRING   -10           /* Unterminated string */
#define ATL_RUNCOMM     -11           /* Unterminated comment in file */
#define ATL_BREAK       -12           /* Asynchronous break signal received */
#define ATL_DIVZERO     -13           /* Attempt to divide by zero */
#define ATL_APPLICATION -14           /* Application primitive atl_error() */

/*  Entry points  */

extern void atl_init(), atl_mark(), atl_unwind(), atl_break();
extern int atl_eval(), atl_load();
extern void atl_memstat();
