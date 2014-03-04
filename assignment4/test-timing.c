/*
 * Simple program that shows how to use the timing functions clock()
 * and getrusage().
 *
 * Both functions are used to time:
 * 1. sleeping 3 seconds.
 * 2. simple loop
 * 3. serie of malloc calls in a loop.
 *
 * Both functions measure cpu time, not wall clock time.
 * getrusage measures system and user cpu seperately. clock() combines
 * both into 1 number.
 *
 * For more information see:
 * man 3 clock
 * man getrusage
 *
 * Compile with -O0?
 */

#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>


// Number and Size of the memory allocation done.
#define NMALLOC 100000000
#define SMALLOC 1000000

// declarations
double get_sec(struct timeval data);
void print_elapsed_ru(struct rusage start, struct rusage stop);
void print_elapsed_clock(clock_t start, clock_t stop);

int main() {

    clock_t start, stop;
    int i, j;

    struct rusage start_tdata, stop_tdata;

    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);

    /****************  Timing: Loop with simple calculation ***************/
    printf("Timing loop\n");
    start = clock(); //start
    getrusage(RUSAGE_SELF, &start_tdata);
    for (i = 0, j = 0; i < 100000000; i++) {
        j += i * i;
        j %= 100000000;
    }
    stop = clock(); //stop
    getrusage(RUSAGE_SELF, &stop_tdata);
    printf("Need to use result, otherwise loop will be optimized away: %d\n", j);

    printf("clock() timing:\n");
    print_elapsed_clock(start, stop);
    printf("rusage() timing:\n");
    print_elapsed_ru(start_tdata, stop_tdata);

    /*********************  Timing malloc/free in loop  ********************/
    printf("\nTiming malloc\n");
    start = clock();
    getrusage(RUSAGE_SELF, &start_tdata);
    for (i = 0; i < NMALLOC; i++)
        free(malloc(sizeof(int)*SMALLOC));
    stop = clock();
    getrusage(RUSAGE_SELF, &stop_tdata);

    printf("clock() timing:\n");
    print_elapsed_clock(start, stop);
    printf("rusage() timing:\n");
    print_elapsed_ru(start_tdata, stop_tdata);

    /*********************  Timing sleep(3)  ********************/
    printf("\nTiming sleep(3)\n");
    // sleep takes no cpu time
    start = clock();
    getrusage(RUSAGE_SELF, &start_tdata);
    sleep (3);
    stop = clock();
    getrusage(RUSAGE_SELF, &stop_tdata);

    printf("clock() timing:\n");
    print_elapsed_clock(start, stop);
    printf("rusage() timing:\n");
    print_elapsed_ru(start_tdata, stop_tdata);

    return 0;
}

/* Helper functions */
void print_elapsed_ru(struct rusage start, struct rusage stop) {
    double tuser, tsystem;
    tuser = get_sec(stop.ru_utime) - get_sec(start.ru_utime);
    tsystem = get_sec(stop.ru_stime) - get_sec(start.ru_stime);
    printf("User cpu time (s):     %f\n", tuser);
    printf("System cpu time (s):   %f\n", tsystem);
    printf("Total cpu time (s):    %f\n", tuser + tsystem);
}

double get_sec(struct timeval data) {
    return data.tv_sec + data.tv_usec/1000000.0;
}

void print_elapsed_clock(clock_t start, clock_t stop) {
    printf("seconds:               %f\n",
            (float)(stop - start)/CLOCKS_PER_SEC);
}
