/*

                              A T L A S T

         Autodesk Threaded Language Application System Toolkit

                 Definitions for components of ATLAST

     Designed and implemented in January of 1990 by John Walker.


    This  file  contains the definitions for modules within the ATLAST
    language system itself.  Definitions used by programs that link to
    ATLAST   are   in   ATLAST.H,  which  is  included  by  this  file
    automatically.

*/

#include "atlast.h"                   /* Define user linkage structures */

typedef void (*codeptr)();            /* Machine code pointer */

/*  Dictionary word entry  */

typedef struct dw {
    struct dw *wnext;                 /* Next word in dictionary */
    char *wname;                      /* Word name.  The first character is
                                         actually the word flags, including
                                         the (IMMEDIATE) bit. */
    codeptr wcode;                    /* Machine code implementation */
} dictword;

/*  Word flag bits  */

#define IMMEDIATE   1                 /* Word is immediate */
#define WORDUSED    2                 /* Word used by program */
#define WORDHIDDEN  4                 /* Word is hidden from lookup */

/*  Data types  */

typedef long stackitem;
typedef dictword **rstackitem;

/* Stack items occupied by a dictionary word definition */
#define Dictwordl ((sizeof(dictword)+(sizeof(stackitem)-1))/sizeof(stackitem))

/* Token types */

#define TokNull     0                 /* Nothing scanned */
#define TokWord     1                 /* Word stored in token name buffer */
#define TokInt      2                 /* Integer scanned */
#define TokReal     3                 /* Real number scanned */
#define TokString   4                 /* String scanned */

/*  Primitive definition table entry  */

struct primfcn {
    char *pname;
    codeptr pcode;
};

/*  Internal state marker item  */

typedef struct {
    stackitem *mstack;                /* Stack position marker */
    stackitem *mheap;                 /* Heap allocation marker */
    dictword ***mrstack;              /* Return stack position marker */
    dictword *mdict;                  /* Dictionary marker */
} atl_statemark;

#ifdef EXPORT
#define Exported
#ifndef NOMANGLE
#define stk         atl__sp
#define stack       atl__sk
#define stackbot    atl__sb
#define stacktop    atl__st
#define rstk        atl__rp
#define rstack      atl__rk
#define rstackbot   atl__rb
#define rstacktop   atl__rt
#define heap        atl__hb
#define hptr        atl__hp
#define heapbot     atl__hs
#define heaptop     atl__ht
#define dict        atl__dh
#define dictprot    atl__dp
#define strbuf      atl__ts
#define cstrbuf     atl__tn
#define ip          atl__ip
#define curword     atl__cw
#define createword  atl__wd
#endif /* NOMANGLE */

#ifdef MEMSTAT
#ifndef NOMANGLE
#define stackmax    atl__sx
#define rstackmax   atl__rx
#define heapmax     atl__hx
#endif /* NOMANGLE */
extern stackitem *stackmax, *heapmax;
extern dictword ***rstackmax;
#endif

#ifdef ALIGNMENT
#ifndef NOMANGLE
#define rbuf0       atl__r0
#define rbuf1       atl__r1
#define rbuf2       atl__r2
#endif /* NOMANGLE */
extern atl_real rbuf0, rbuf1, rbuf2;  /* Real temporaries for alignment */
#endif

#define FmodeR      1                 /* Read mode */
#define FmodeW      2                 /* Write mode */
#define FmodeB      4                 /* Binary file mode */
#define FmodeCre    8                 /* Create new file */

extern stackitem *stack, *stk, *stackbot, *stacktop, *heap, *hptr,
                 *heapbot, *heaptop;
extern dictword ***rstack, ***rstk, ***rstackbot, ***rstacktop;
extern dictword *dict, *dictprot, *curword, *createword;
extern dictword **ip;
extern char **strbuf;
extern int cstrbuf;

#ifndef NOMANGLE
#define P_create    atl__Pcr
#define P_dodoes    atl__Pds
#endif /* NOMANGLE */
extern void P_create(), P_dodoes();
#else  /* EXPORT */
#define Exported static
#endif /* EXPORT */

#ifndef NOMEMCHECK
#ifdef EXPORT
#ifndef NOMANGLE
#define stakover    atl__Eso
#define rstakover   atl__Erso
#define heapover    atl__Eho
#define badpointer  atl__Ebp
#define stakunder   atl__Esu
#define rstakunder  atl__Ersu
#endif /* NOMANGLE */
extern
#endif
void stakover(), rstakover(), heapover(), badpointer(),
     stakunder(), rstakunder();
#endif

/* Functions called by exported extensions. */
extern void atl_primdef(), atl_error();
extern dictword *atl_lookup(), *atl_vardef();
extern stackitem *atl_body();
extern int atl_exec();
#ifdef EXPORT
extern char *atl_fgetsp();
#endif

/*  If explicit alignment is not requested, enable it in any case for
    known CPU types that require alignment.  */

#ifndef ALIGNMENT
#ifdef sparc
#define ALIGNMENT
#endif
#endif
#ifdef __TURBOC__
#define  Keyhit()   (kbhit() ? getch() : 0)
/* DOS needs poll to detect break */
#define  Keybreak() { static int n=0; if ((n = (n+1) & 127) == 0) V kbhit(); }
#ifdef __MSDOS__
#define MSDOS
#endif
#endif
#ifdef MSDOS
#define FBmode                        /* DOS requires binary file flag */
#endif
#ifdef Macintosh
#define FBmode                        /* Macintosh requires binary file flag */
#endif
#ifdef OS2                            /* OS/2 requires binary file flag */
#define FBmode
#endif

#ifdef HIGHC
#define unlink(x) remove(x)           /* High C library is brain-dead */
pragma On(PCC_msgs);                  /* High C compiler is brain-dead */
#endif


/*  STATIC is defined as "static" on platforms which require this
    specification on declarations for forward-referenced functions.  */

#define STATIC static

#ifdef ADS                            /* Definitions if we're an ADS app */
#define printf ads_printf             /* Print through ADS */
#define Keybreak() {static int n=0; if ((n=(n+1)&127)==0) {UbI(); broken=ads_usrbrk();}}
#endif

/*  Dynamic storage manipulation primitives  */

/*  Stack access definitions  */

#define S0  stk[-1]                   /* Top of stack */
#define S1  stk[-2]                   /* Next on stack */
#define S2  stk[-3]                   /* Third on stack */
#define S3  stk[-4]                   /* Fourth on stack */
#define S4  stk[-5]                   /* Fifth on stack */
#define S5  stk[-6]                   /* Sixth on stack */
#define Pop stk--                     /* Pop the top item off the stack */
#define Pop2 stk -= 2                 /* Pop two items off the stack */
#define Npop(n) stk -= (n)            /* Pop N items off the stack */
#define Push *stk++                   /* Push item onto stack */

#ifdef MEMSTAT
#define Mss(n) if ((stk+(n))>stackmax) stackmax = stk+(n);
#define Msr(n) if ((rstk+(n))>rstackmax) rstackmax = rstk+(n);
#define Msh(n) if ((hptr+(n))>heapmax) heapmax = hptr+(n);
#else
#define Mss(n)
#define Msr(n)
#define Msh(n)
#endif

#ifdef NOMEMCHECK
#define Sl(x)
#define So(n)
#else
#define Memerrs
#define Sl(x) if ((stk-stack)<(x)) {stakunder(); return Memerrs;}
#define So(n) Mss(n) if ((stk+(n))>stacktop) {stakover(); return Memerrs;}
#endif

/*  Return stack access definitions  */

#define R0  rstk[-1]                  /* Top of return stack */
#define R1  rstk[-2]                  /* Next on return stack */
#define R2  rstk[-3]                  /* Third on return stack */
#define Rpop rstk--                   /* Pop return stack */
#define Rpush *rstk++                 /* Push return stack */
#ifdef NOMEMCHECK
#define Rsl(x)
#define Rso(n)
#else
#define Rsl(x) if ((rstk-rstack)<(x)) {rstakunder(); return Memerrs;}
#define Rso(n) Msr(n) if ((rstk+(n))>rstacktop){rstakover(); return Memerrs;}
#endif

/*  Heap access definitions  */

#ifdef NOMEMCHECK
#define Ho(n)
#define Hpc(n)
#else
#define Ho(n)  Msh(n) if ((hptr+(n))>heaptop){heapover(); return Memerrs;}
#define Hpc(n) if ((((stackitem *)(n))<heapbot)||(((stackitem *)(n))>=heaptop)){badpointer(); return Memerrs;}
#endif
#define Hstore *hptr++                /* Store item on heap */
#define state  (*heap)                /* Execution state is first heap word */

#define prim static void              /* Attributes of primitive functions */

/*  Real number definitions (used only if REAL is configured).  */

#define Realsize (sizeof(atl_real)/sizeof(stackitem)) /* Stack cells / real */
#define Realpop  stk -= Realsize      /* Pop real from stack */
#define Realpop2 stk -= (2 * Realsize) /* Pop two reals from stack */

#ifdef ALIGNMENT
#define REAL0 *((atl_real *) memcpy((char *) &rbuf0, (char *) &S1, sizeof(atl_real)))
#define REAL1 *((atl_real *) memcpy((char *) &rbuf1, (char *) &S3, sizeof(atl_real)))
#define REAL2 *((atl_real *) memcpy((char *) &rbuf2, (char *) &S5, sizeof(atl_real)))
#define SREAL0(x) rbuf2=(x); (void)memcpy((char *) &S1, (char *) &rbuf2, sizeof(atl_real))
#define SREAL1(x) rbuf2=(x); (void)memcpy((char *) &S3, (char *) &rbuf2, sizeof(atl_real))
#else
#define REAL0   *((atl_real *) &S1)   /* First real on stack */
#define REAL1   *((atl_real *) &S3)   /* Second real on stack */
#define REAL2   *((atl_real *) &S5)   /* Third real on stack */
#define SREAL0(x) *((atl_real *) &S1) = (x)
#define SREAL1(x) *((atl_real *) &S3) = (x)
#endif

/*  File I/O definitions (used only if FILEIO is configured).  */

#define FileSent    0x831FDF9DL       /* Courtesy Marinchip Radioactive
                                         random number generator */
#define Isfile(x) Hpc(x); if (*((stackitem *)(x))!=FileSent) {V printf("\nNot a file\n");return;}
#define FileD(x)  ((FILE *) *(((stackitem *) (x)) + 1))
#define Isopen(x) if (FileD(x) == NULL) {V printf("\nFile not open\n");return;}
