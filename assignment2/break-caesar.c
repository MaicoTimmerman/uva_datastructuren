/*
 * File: break-caesar.c
 *
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
#include <unistd.h>

#include "break-caesar.h"

int verbose = 0;

/*
 * Main program for breaking a caesar-ciphered message.
 *
 * @param argc; number of parameters given to the program
 * @param argv; array of all parameters given to the program
 */
int main(int argc, char *argv[]) {

    int opt;
    char *freqfile = NULL;
    char *cipherfile = NULL;
    extern char *optarg;
    extern int optind, optopt;

    while ((opt = getopt(argc, argv, "vhf:c:")) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'h':
                help();
                break;
            case 'f':
                freqfile = optarg;
                break;
            case 'c':
                cipherfile = optarg;
                break;
            case '?':
                if (optopt == 'c') {
                    printf("Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    printf("Unknown option `-%c'.\n", optopt);
                } else {
                    printf("Unkown option character `\\x%x'. \n", optopt);
                }
                break;
            default:
                printf("No arguments were given, use -h for help");
        }
    }

    printf("All arguments acquired:");
    printf("verbose = %d, freqfile = %s, cipherfile = %s\n", verbose, freqfile, cipherfile);
    return EXIT_SUCCESS;
}

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
int help() {
    printf("Usage: pi [ -v | -h | -f freqfile | -c cipherfile ]\n");
    printf("  iterations: [int] used to calculate pi\n");
    exit(EXIT_SUCCESS);
}
