#include <stdio.h>
#include <stdlib.h>

extern double asqrt();

int main(argc, argv)
  int argc;
  char *argv[];
{
    unsigned long int i;
    char a[300];

printf("Int = %ld\n", sizeof(long));

    fputs("Ready to test: ", stdout);
    if (fgets(a, 132, stdin)) {

        for (i = 0; i < 6000000000lu; i++) {
            asqrt(2.0);
        }
        printf("Done.\n");

    }
    return 0;
}
