/*
 * File: break-caesar.c
 *
 * @author: Maico Timmerman
 * @uvanetid: 10542590
 * @date: TODO
 * @version: 0.1
 */

#include <ctype.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "break-caesar.h"

int verbose = 0;

int main(int argc, char *argv[]) {

    int *freqs = NULL;
    char *freqfile = NULL;
    char *cipherfile = NULL;

    /* Acquire the arguments */
    if (!getArgs(argc, argv, freqfile, cipherfile)) {
        fprintf(stderr,"break-caesar: try 'break-caesar -h' for more information.\n");
        return EXIT_FAILURE;
    }

    if (verbose)
        printf("Freqfile in main()\t = %s\nCipherfile in main()\t = %s\n", freqfile, cipherfile);

    readFreq(freqfile, freqs);

    return EXIT_SUCCESS;
}

int readFreq(char *freqfile, int *freqs) {

    int err = 0;
    FILE *fp;

    fprintf(stdout, " Im supposed to read frequencies");
    fp = fopen(freqfile, "r");


    if (err)
        return 0;
    else
        return 1;
}

int getArgs(int argc, char **argv, char *freqfile, char *cipherfile) {

    int opt;
    int err = 0;
    extern char *optarg;
    extern int optind, optopt;

    /* Get all options from the command line */
    while ((opt = getopt(argc, argv, "vhf:c:")) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'h':
                help();
                break;
            case 'f':
                if (optarg) {
                    strcpy(freqfile, optarg);
                    break;
                }
            case 'c':
                if (optarg) {
                    strcpy(cipherfile, optarg);
                    break;
                }
        }
    }

    /* If no cipher file is found */
    if (!cipherfile) {
        fprintf(stderr, "specify a cipher file with [-c]\n");
        err++;
    }

    /* If no frequency file is found */
    if (!freqfile) {
        fprintf(stderr, "specify a frequency file with [-f]\n");
        err++;
    }

    if (verbose)
        printf("Freqfile in getArgs()\t = %s\nCipherfile in getArgs()\t = %s\n", freqfile, cipherfile);

    /* If errors are found in this function return */
    if (err) {
        return 0;
    } else {
        return 1;
    }
}

int help(void) {
    printf("Usage: break-caesar [ -v | -h ] [ -f freqfile ] [ -c cipherfile ]\n");
    printf("Obligatory: [ -f freqfile ] [ -c cipherfile ]\n");
    printf("Example: break-caesar -f freq.txt -c message1.txt\n\n");
    printf("\t-f filepath\t filepath to a file with letter frequencies.\n");
    printf("\t-c filepath\t filepath to a file encrypted with a caesar cipher.\n");
    printf("\t-v\t\t verbose: print more details.\n");
    printf("\t-h\t\t help: print this help page.\n");
    exit(EXIT_SUCCESS);
}
