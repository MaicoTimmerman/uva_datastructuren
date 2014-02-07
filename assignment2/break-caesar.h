#ifndef __BREAK_CAESAR_H__
#define __BREAK_CAESAR_H__

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
int help(void);

int getArgs(int *argc, char ***argv, char *freqfile, char *cipherfile);

#endif /* __BREAK_CAESAR_H__ */
