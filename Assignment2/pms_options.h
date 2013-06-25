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

#ifndef PMS_OPTIONS_H
#define PMS_OPTIONS_H

/* Function prototypes. */

void displaySummary(PMSType* pms, char* programType);
void programReport(PMSType* pms);
void addProgram(PMSType* pms);
void deleteProgram(PMSType* pms);
void addCourse(PMSType* pms);
void deleteCourse(PMSType* pms);
void saveData(PMSType* pms, char* programFile, char* courseFile);

#endif
