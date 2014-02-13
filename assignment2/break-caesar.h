#ifndef BREAK_CAESAR_H
#define BREAK_CAESAR_H

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
int help(void);

int getArgs(int argc, char **argv, char *freqfile, char *cipherfile);

int readFreq(char *freqfile, float *freqs);

#endif /* BREAK_CAESAR_H */
