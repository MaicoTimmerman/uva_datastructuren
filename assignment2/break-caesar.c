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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "break-caesar.h"

#define MAX_FILE_PATH_LEN 32
#define ALPHABET 26

int verbose = 0;

int main(int argc, char *argv[]) {

    float correctFreqs[ALPHABET] = {0};
    float cipherFreqs[ALPHABET] = {0};
    int shift;
    char freqFile[MAX_FILE_PATH_LEN] = "";
    char cipherFile[MAX_FILE_PATH_LEN] = "";

    /* Acquire the arguments */
    if (!getArgs(argc, argv, freqFile, cipherFile)) {
        fprintf(stderr,"break-caesar: try 'break-caesar -h' for more information.\n");
        return EXIT_FAILURE;
    }

    /* Read the frequency file given by the user */
    if (!readFreq(freqFile, correctFreqs))
        return EXIT_FAILURE;

    /* Read the frequency file given by the user */
    if (!readCipherFreqs(cipherFile, cipherFreqs))
        return EXIT_FAILURE;

    if (verbose) {
        for (int i = 0; i < ALPHABET; i++) {
            fprintf(stdout, "The correct letter frequency of %c is %f\n",(char)i + 'a', correctFreqs[i]);
        }

        for (int i = 0; i < ALPHABET; i++) {
            fprintf(stdout, "The cipher letter frequency of %c is %f\n",(char)i + 'a', cipherFreqs[i]);
        }
    }

    shift = getShift(correctFreqs, cipherFreqs);
    if (shift == -1) {
        fprintf(stdout, "\nNo best match is found using the algorithm, please give an proper text");
        return EXIT_FAILURE;
    }
    printf("\nBest matching shift: %d\n\n", shift);
    printDecryptedMessage(cipherFile, shift);

    return EXIT_SUCCESS;
}

int getArgs(int argc, char **argv, char freqFile[], char cipherFile[]) {

    int opt;
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
                if (optarg && (strlen(optarg) < MAX_FILE_PATH_LEN)) {
                    strcpy(freqFile, optarg);
                }
                break;
            case 'c':
                if (optarg && (strlen(optarg) < MAX_FILE_PATH_LEN)) {
                    strcpy(cipherFile, optarg);
                }
                break;
        }
    }

    /* If no cipher file is found */
    if (cipherFile[0] == '\0') {
        fprintf(stderr, "Error: specify a cipher file with [-c](maximum path length is 30 characters)\n");
        return 0;
    }

    /* If no frequency file is found */
    if (freqFile[0] == '\0') {
        fprintf(stderr, "Error: specify a frequency file with [-f](maximum path length is 30 characters)\n");
        return 0;
    }

    if (verbose)
        printf("Freqfile\t = %s\nCipherfile\t = %s\n", freqFile, cipherFile);

    return 1;
}

int readFreq(char *freqFile, float *freqs) {

    char ch;
    int charsFilled = 0;
    float charFreq;
    FILE *fp = NULL;

    fp = fopen(freqFile, "r");

    /* if opening the file failed, print the error and exit */
    if(fp == NULL) {
        perror("Error");
        return 0;
    }

    /* Read the frequency per line and count the total amount of characters read */
    while( fscanf(fp,"%c %f\n",&ch,&charFreq) == 2) {
        freqs[(int)ch - 'a'] = charFreq;
        charsFilled++;
    }

    fclose(fp);

    if (charsFilled != ALPHABET) {
        fprintf(stderr, "Did not found all letter frequencies!\nPlease provide a valid file with frequencies\n");
        fprintf(stderr, "Format the file the following:\n");
        fprintf(stderr, "\ta 18.00\n");
        fprintf(stderr, "\tb 1.23\n");
        fprintf(stderr, "\t...\n");
        fprintf(stderr, "\tz 0.00\n");
        return 0;
    }
    return 1;
}

int readCipherFreqs(char *cipherFile, float *cipherFreqs) {

    char ch;
    long int totalChars = 0;
    FILE *fp = NULL;

    fp = fopen(cipherFile, "r");

    /* if opening the file failed, print the error and exit. */
    if (fp == NULL) {
        perror("Error");
        return 0;
    }

    if (verbose)
        fprintf(stdout, "\nCipher file reading started\n");

    /* Retrieve characters one-by-one and add 1 to the correct to the total of that character. */
    while ((ch = fgetc(fp)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            cipherFreqs[(int)ch - 'a']++;
            totalChars++;
        }
    }

    /* If the end of file was found while reading the file. */
    if (feof(fp) && verbose) {
        fprintf(stdout, "End of file was reached\n");
    }

    /* If an error was found while reading the file. */
    if (ferror(fp)) {
        fprintf(stdout, "\nAn error happened while reading the file\n");
        fclose(fp);
        return 0;
    }

    /* All character should be converted to an percentage */
    for (int i = 0; i < ALPHABET; i++) {
        cipherFreqs[i] = (cipherFreqs[i] / totalChars) * 100;
    }

    fclose(fp);

    return 1;
}

int getShift(float correctFreqs[], float cipherFreqs[]) {

    int bestMatch = -1;
    float score;

    fprintf(stdout, "Trying offsets:\n");

    /* Test the score at every offset. */
    for (int i = 0; i < ALPHABET; i++) {
        score = 100;
        for (int j = 0; j < ALPHABET; j++) {
            /* Calculate the score using the absolute difference in frequency. */
            score = score - fabsf(correctFreqs[j] - cipherFreqs[(j+i) % ALPHABET]);
        }

        if (verbose) {
            fprintf(stdout, "The score of shift %d is: %f\n", i, score);
        } else {
            fprintf(stdout, " %d", i);
        }

        if (score > bestMatch) {
            if (verbose) {
                fprintf(stdout, "A new best match has been found!\n");
            } else {
                fprintf(stdout, "*");
            }
            bestMatch = i;
        }
    }
    return bestMatch;
}

int printDecryptedMessage(char *cipherFile, int shift) {

    char ch;
    FILE *fp = NULL;

    /* The encrypted file was shifted with n, so to decrypt shift with 26-n */
    int deshift = ALPHABET - shift;

    fp = fopen(cipherFile, "r");

    /* if opening the file failed, print the error and exit. */
    if (fp == NULL) {
        perror("Error");
        return 0;
    }

    fprintf(stdout, "Decrypted message from shift %d:\n\n", shift);

    /* Print every character unshifted. */
    while ((ch = tolower(fgetc(fp))) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            /* Wrap the alphabet */
            putchar(((ch + deshift - 'a') % ALPHABET) + 'a');
        } else {
            putchar(ch);
        }
    }
    fprintf(stdout,"\n");

    /* If the end of file was found while reading the file. */
    if (feof(fp) && verbose) {
        fprintf(stdout, "\nEnd of file was reached\n");
    } else if (ferror(fp)) {
        fprintf(stdout, "\nAn error happened while reading the file\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
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
