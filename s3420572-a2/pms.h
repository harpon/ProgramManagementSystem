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

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* program header files */
#include "pms_program.h"
#include "pms_course.h"
#ifndef PMS_H
#define PMS_H


/* System-wide constants. */
#define ID_LEN 5
#define PROG_ID_LEN 5
#define PROG_TYPE_LEN 2
#define MODE_LEN 2
#define MIN_TITLE_LEN 1
#define MAX_TITLE_LEN 50
#define PROG_MAJOR_LEN 50
#define PROG_CODE_LEN 6
#define PROG_DURATION_LEN 1
#define COURSE_ID_LEN 8
#define COURSE_CODE_LEN 8
#define MIN_DESC_LEN 1
#define MAX_DESC_LEN 250
#define NUM_TEACHPERIODS 1
#define SUCCESS 1
#define FAILURE 0



/* User input constant*/
#define PROMPT_LENGTH 254
#define MAX_OPTION_INPUT_LENGTH 1

/* system-wide constant */
#define MAX_DATA_SUBJECT 9
#define NUM_PROGRAM_LEN 1
#define DECIMAL 10
#define CREDIT_POINT_LEN 2
#define YEAR_LEN 4
#define SEMESTER_LEN 1
#define MAX_DISPLAY_LEN 40
#define MAX_FILE_NAME_LEN 50

/* enumeration that defines the BOOLEAN data type as two possible integers,
 * 0 and 1
 */
typedef enum truefalse
{
    FALSE=0,TRUE
} BOOLEAN;

/* predeclare the program and course structs */
typedef struct program* ProgramTypePtr;
typedef struct course* CourseTypePtr;

/* pointer to traverse ProgramType */


/* Structure definitions. */

typedef struct pms
{
    ProgramTypePtr headProgram;
    unsigned numPrograms;
} PMSType;

#endif

