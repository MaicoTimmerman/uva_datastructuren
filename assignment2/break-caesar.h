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

/*
 * Function: getArgs()
 * -------------------
 * Get all the arguments from the command line and place them in the given parameters.
 *
 * @param argc; number of commandline parameters.
 * @param argv; array of commandline parameters with length argc.
 * @param freqFile; location for the filepath to the frequency file.
 * @param cipherFile; location for the filepath to the encrypted file.
 * @returns; Succes after printing the help of this program.
 */
int getArgs(int argc, char **argv, char *freqfile, char *cipherfile);

/*
 * Function: readFreq()
 * -------------------
 * Read all the correct frequencies from a file specified with freqFile.
 *
 * @param freqFile; location for the filepath to the frequency file.
 * @param freqs; location of the array for correct frequencies for comparision
 * @returns; Succes after printing the help of this program.
 */
int readFreq(char *freqfile, float *freqs);

/*
 * Function: readCipherFreq()
 * -------------------
 * Read all the letter frequencies from a encrypted file specified with cipherFile.
 *
 * @param cipherFile; location for the filepath to the encrypted file.
 * @param cipherFreqs; location of the array for the encrypted frequencies.
 * @returns; Succes after printing the help of this program.
 */
int readCipherFreqs(char *cipherfile, float *cipherFreqs);

/*
 * Function: getShift()
 * -------------------
 * Calculate the shift by trying all shifts and calculating a score.
 * The score is based on the difference in frequencies.
 *
 * @param correctFreqs; An array with correct letter frequencies.
 * @param cipherFreqs; An array with encrypted letter frequencies.
 * @returns shift; The shift of the original message.
 */
int getShift(float correctFreqs[], float cipherFreqs[]);

/*
 * Function: printDecryptedMessage()
 * -------------------
 * Prints the entire message, deciphering it with the specified shift.
 *
 * @param cipherFile; Location to the encrypted file
 * @param shift; The shift of the original message which resulted in the encrypted message.
 * @returns; Succes after printing the help of this program.
 */
int printDecryptedMessage(char *cipherfile, int shift);
#endif /* BREAK_CAESAR_H */
