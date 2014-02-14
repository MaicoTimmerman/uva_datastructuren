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

int readCipherFreqs(char *cipherfile, float *cipherFreqs);

int getShift(float correctFreqs[], float cipherFreqs[]);

int printDecryptedMessage(char *cipherfile, int shift);
#endif /* BREAK_CAESAR_H */
