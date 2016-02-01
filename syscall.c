#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static inline unsigned long long tick() 
{
    unsigned a, d;
    __asm__ __volatile__("rdtsc": "=a" (a), "=d" (d) );
    return (((unsigned long long)a) | (((unsigned long long)d) << 32));
}

int main(int argc, char* argv[])
{
    int loops;
    if (argc <= 1) {
        exit(0);
    }
    else {
        loops = atoi (argv[1]);
        if (loops <= 0) {
            printf ("Invalid arguments.\n");
            exit(0);
        }
    }

    unsigned long long start, end;
    int i;
    start = tick();
    for(i=0; i < loops; i++) {
        getpid();
    }
    end = tick();
    printf("argv: %d, overhead: %f\n", loops, (double)(end- start) / (double)loops);
    return 0;
}
