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
#ifndef PMS_PROGRAM_H
#define PMS_PROGRAM_H
#include "pms.h"

struct program_data
{
    char progID[ID_LEN + 1];   /* Unique ID for a program */
    char progTitle[MAX_TITLE_LEN + 1];
    char progMajor[MAX_TITLE_LEN + 1];
    char progCode[PROG_CODE_LEN + 1];
    float progDuration;
    char progType[PROG_TYPE_LEN+1];    /* Undergrade(UG) or Postgrad (PG) */
    char progMode[MODE_LEN+1];  /* Full-time (FT) or Part-time (PT) */
    char progDescription[MAX_DESC_LEN+1];
    char majorDescription[MAX_DESC_LEN+1];
};

typedef struct program
{
    struct program_data * data;
    ProgramTypePtr nextProgram;
    CourseTypePtr headCourse;
    unsigned numCourses;
} ProgramType;

/* create any function prototypes required for managing the pms_program list
 * here.
 */

void displayProgramSummary(PMSType* pms, char* programType);
BOOLEAN addNewPrograms(PMSType* pms, char* progTitle, char* progType, char* progMajor, char* progCode, char* progDuration,char* progMode, char* progDescription, char* majorDescription,char* progID);
void deleteSpecificPrograms(PMSType* pms,char* progID);
void produceProgramReport(PMSType* pms,char* fileName);
void saveProgramData(PMSType* pms,char* programFile);

#endif
