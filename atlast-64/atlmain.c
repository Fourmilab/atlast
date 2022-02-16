/*                            ATLMAIN.C

              Main driver program for interactive ATLAST

     Designed and implemented in January of 1990 by John Walker.

                This program is in the public domain.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <signal.h>
#include "atldef.h"

#define FALSE   0
#define TRUE    1

#define V   (void)

/*  Globals imported  */

/*  CTRLC  --  Catch a user console break signal.  If your C library
               does not provide this Unix-compatibile facility
               (registered with the call on signal() in main()),
               just turn this code off or, better still, replace it
               with the equivalent on your system.  */

static void ctrlc(sig)
  int sig;
{
    if (sig == SIGINT)
        atl_break();
}

/*  MAIN  --  Main program.  */

int main(argc, argv)
  int argc;
  char *argv[];
{
    int i;
    int fname = FALSE, defmode = FALSE;
    FILE *ifp;
    char *include[20];
    int in = 0;
#define PR(x) (void) fprintf(stderr, x)

    PR("ATLAST 2.0 (2014-07-04) [64-bit] This program is in the public domain.\n");
    ifp = stdin;
    for (i = 1; i < argc; i++) {
        char *cp, opt;

        cp = argv[i];
        if (*cp == '-') {
            opt = *(++cp);
            if (islower(opt))
                opt = toupper(opt);
            switch (opt) {

                case 'D':
                    defmode = TRUE;
                    break;

                case 'H':
                    atl_heaplen = atol(cp + 1);
                    break;

                case 'I':
                    include[in++] = cp + 1;
                    break;

                case 'R':
                    atl_rstklen = atol(cp + 1);
                    break;

                case 'S':
                    atl_stklen = atol(cp + 1);
                    break;

                case 'T':
                    atl_trace = TRUE;
                    break;

                case '?':
                case 'U':
                    PR("Usage:  ATLAST [options] [inputfile]\n");
                    PR("        Options:\n");
                    PR("           -D     Treat file as definitions\n");
                    PR("           -Hn    Heap length n\n");
                    PR("           -Ifile Include named definition file\n");
                    PR("           -Rn    Return stack length n\n");
                    PR("           -Sn    Stack length n\n");
                    PR("           -T     Set TRACE mode\n");
                    PR("           -U     Print this message\n");
                    return 0;
            }
        } else {
            char fn[132];

            if (fname) {
                PR("Duplicate file name.\n");
                return 1;
            }
            fname = TRUE;
            V strcpy(fn, cp);
            if (strchr(fn, '.') == NULL)
                V strcat(fn, ".atl");
            ifp = fopen(fn, "r");
            if (ifp == NULL) {
                V fprintf(stderr, "Unable to open file %s\n", fn);
                return 1;
            }
        }
     }

    /* If any include files were named, load each in turn before
       we execute the program. */

    for (i = 0; i < in; i++) {
        int stat;
        char fn[132];
        FILE *fp;

        V strcpy(fn, include[i]);
        if (strchr(fn, '.') == NULL)
            V strcat(fn, ".atl");
        fp = fopen(fn,
#ifdef FBmode
                        "rb"
#else
                        "r"
#endif
                  );
        if (fp == NULL) {
            V fprintf(stderr, "Unable to open include file %s\n",
                include[i]);
            return 1;
        }
        stat = atl_load(fp);
        V fclose(fp);
        if (stat != ATL_SNORM) {
            V printf("\nError %d in include file %s\n", stat, include[i]);
        }
    }

    /* Now that all the preliminaries are out of the way, fall into
       the main ATLAST execution loop. */

    V signal(SIGINT, ctrlc);
    while (TRUE) {
        char t[132];

        if (!fname)
            V printf(atl_comment ? "(  " :  /* Show pending comment */
                /* Show compiling state */
                (((heap != NULL) && state) ? ":> " : "-> "));
        if (fgets(t, 132, ifp) == NULL) {
            if (fname && defmode) {
                fname = defmode = FALSE;
                ifp = stdin;
                continue;
            }
            break;
        }
        V atl_eval(t);
    }
    if (!fname)
        V printf("\n");
    return 0;
}
