/***************************************************************************
 * COSC1283/1284 - Programming Techniques
 * Semester 1 2013 Assignment #2 - SCSIT Program Management System
 * Full Name        : Hartanto Poniman Noerdjaja
 * Student Number   : s3420572
 * Yallara Username : s3420572
 * Course Code      : COSC1284
 * Program Code     : BP162
 * Start up code provided by Paul Miller and Xiaodong Li
 **************************************************************************/

#include<string.h>

#ifndef PMS_UTILITY_H
#define PMS_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
BOOLEAN systemInit(PMSType* pms);
BOOLEAN loadData(PMSType* pms, char* programFile, char* courseFile);
void systemFree(PMSType* pms);

int getString(char *,unsigned length,char* );
int getInteger(int* integer, unsigned length, char* prompt, int min, int max);
void clearNewLine(char* rawString);

#endif
