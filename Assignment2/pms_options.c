/***************************************************************************
* COSC1283/1284 - Programming Techniques
* Semester 1 2013 Assignment #2 - SCSIT Program Management System
* Full Name        : Hartanto Poniman Noerdjaja
* Student Number   : s3420572
* Yallara Username : s3420572
* Course Code      : COSC1284
* Program Code     : BP162
* Start up code provided by Paul Miller and Xiaodong Li
***************************************************************************/

#include "pms.h"
#include "pms_options.h"
#include "pms_utility.h"

/****************************************************************************
* Menu option #1 and #2: Summary of Programs
* Allows the user to display a summary of all undergrad or postgrad programs
* and associated courses.
****************************************************************************/
void displaySummary(PMSType* pms, char* programType)
{
    if(strcmp(programType,"UG") == 0)
    {
        printf("\nSummary of Undergrad Programs\n");
        printf("-----------------------------\n\n");
        
        printf("%d\n", pms->numPrograms);
        
        /* search and print UG programs */
        
        displayProgramSummary(pms,programType);
        
    }
    else if( strcmp(programType,"PG") == 0)
    {
        printf("\nSummary of Postgrad Programs\n");
        printf("----------------------------\n\n");
        
        /* search and print PG programs */
        
        displayProgramSummary(pms,programType);
        
    }
}


/****************************************************************************
* Menu option #3: Detailed Program Report
* Allows the user to make a new report file for a chosen program.
****************************************************************************/
void programReport(PMSType* pms)
{
    char menuPrompt[PROMPT_LENGTH+1];
    char progID[PROG_ID_LEN+1];
    
    printf("\nDETAILED PROGRAM REPORT\n");
    printf("\n-----------------------\n");
    
    
    sprintf(menuPrompt,"Enter program id (5 Characters):");
    if(getString(progID,PROG_ID_LEN,menuPrompt))
    {
        produceProgramReport(pms,progID);
    }
}


/****************************************************************************
* Menu option #4: Add Program
* Allows the user to add a new "program" record to the linked list.
****************************************************************************/
void addProgram(PMSType* pms)
{
    char menuPrompt[PROMPT_LENGTH+1];
    
    /* pointer to store new program information */
    char progTitle[MAX_TITLE_LEN+1];
    char progType[PROG_TYPE_LEN+1];
    char progMajor[PROG_MAJOR_LEN+1];
    char progCode[PROG_CODE_LEN+1];
    char progDuration[PROG_DURATION_LEN+1];
    char progMode[MODE_LEN+1];
    char progDescription[MAX_DESC_LEN+1];
    char majorDescription[MAX_DESC_LEN+1];
    
    /* variable to calculate next program ID */
    char nextProgIDNum[NUM_PROGRAM_LEN+1];
    char *nextProgID = malloc(sizeof(char)*MAX_TITLE_LEN);
    unsigned numPrograms = pms->numPrograms;
    
    printf("\nADD NEW PROGRAM\n");
    printf("------------------------\n\n");
    
    
    sprintf(nextProgIDNum,"%d",++numPrograms);
    
    strcat(nextProgID,"P000");
    strcat(nextProgID,nextProgIDNum);
    
    printf("The next program ID is %s",nextProgID);
    
    /* Getting information for the new program */
    sprintf(menuPrompt,"\nProgram title ( 1-50 Character )\t: ");
    if(getString(progTitle,MAX_TITLE_LEN,menuPrompt))
    {
        sprintf(menuPrompt,"Undergrad(UG) or Postgrad(PG) program\t: ");
        if(getString(progType,PROG_TYPE_LEN,menuPrompt))
        {
            sprintf(menuPrompt,"Program major\t\t\t\t: ");
            if(getString(progMajor,PROG_MAJOR_LEN,menuPrompt))
            {
                sprintf(menuPrompt,"Program code\t\t\t\t: ");
                if(getString(progCode,PROG_CODE_LEN,menuPrompt))
                {
                    sprintf(menuPrompt,"Program Duration(years)\t\t\t: ");
                    if(getString(progDuration,PROG_DURATION_LEN,menuPrompt))
                    {
                        sprintf(menuPrompt,"Program Mode\t\t\t\t: ");
                        if(getString(progMode,MODE_LEN,menuPrompt))
                        {
                            sprintf(menuPrompt,"Program Description (1-250 Character)\t: ");
                            if(getString(progDescription,MAX_DESC_LEN,menuPrompt))
                            {
                                sprintf(menuPrompt,"Major description (1-250 Character)\t: ");
                                if(getString(majorDescription,MAX_DESC_LEN,menuPrompt))
                                {
                                    /* insert new program to linked list */
                                    if(addNewPrograms(pms,progTitle,progType,progMajor,progCode, progDuration,progMode,progDescription,majorDescription,nextProgID))
                                    {
                                        printf("\nNew Program added!\n");
                                    }
                                   
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


/****************************************************************************
* Menu option #5: Delete Program
* Deletes a "prorgam" and all corresponding courses.
****************************************************************************/
void deleteProgram(PMSType* pms)
{
    char menuPrompt[PROMPT_LENGTH+1];
    
    char progID[PROG_ID_LEN+1];
    
    printf("\nDELETE PROGRAM\n");
    printf("------------------------\n\n");
    
    sprintf(menuPrompt,"Program ID :");
    
    if(getString(progID,PROG_ID_LEN,menuPrompt))
    {
        deleteSpecificPrograms(pms,progID);
    }
}


/****************************************************************************
* Menu option #6: Add Course
* Allows the user to add a new course to an existing "program". An error 
* message is given if the "program" doesn't exist.
****************************************************************************/
void addCourse(PMSType* pms)
{
    char menuPrompt[PROMPT_LENGTH+1];
    
    /* variable to handle course information */
    char progID[PROG_ID_LEN+1];
    char courseTitle[MAX_TITLE_LEN+1];
    char courseCode[COURSE_CODE_LEN+1];
    int creditPoints;
    int teachingSemester;
    int teachingYear;
    char courseCoordinator[MAX_TITLE_LEN+1];
    char courseDescription[MAX_DESC_LEN+1];
    
    /* variable to calculate nextCourseID */
    ProgramTypePtr currentProgram = NULL;
    char nextCourseIDNum[NUM_PROGRAM_LEN+1];
    char *nextCourseID = malloc(sizeof(char)*MAX_TITLE_LEN);
    unsigned totalCourses = 0;
    
    
    
    sprintf(menuPrompt,"%-40s:","Program ID (5 Characters)");
    if(getString(progID,PROG_ID_LEN,menuPrompt))
    {
        
        /* Search specific program and Calculate next course ID */
        currentProgram = pms->headProgram;
        
        while(currentProgram != NULL)
        {
            totalCourses += currentProgram->numCourses;
            currentProgram = currentProgram->nextProgram;
        }
        
        sprintf(nextCourseIDNum,"%d",++totalCourses);
        
        strcat(nextCourseID,"C000");
        strcat(nextCourseID,nextCourseIDNum);
        
        printf("The next Course ID is %s\n",nextCourseID);
        
        sprintf(menuPrompt,"%-40s:","Course Title(1-25 Characters)");
        if(getString(courseTitle,MAX_TITLE_LEN,menuPrompt))
        {
            sprintf(menuPrompt,"%-40s:","Course Code");
            if(getString(courseCode,COURSE_CODE_LEN,menuPrompt))
            {
                sprintf(menuPrompt,"%-40s:","Credit Points");
                if(getInteger(&creditPoints,CREDIT_POINT_LEN,menuPrompt,1,100))
                {
                    sprintf(menuPrompt,"%-40s:","Teaching Semester");
                    if(getInteger(&teachingSemester,SEMESTER_LEN,menuPrompt,1,2))
                    {
                        sprintf(menuPrompt,"%-40s:","Teaching Year");
                        if(getInteger(&teachingYear,YEAR_LEN,menuPrompt,1,9999))
                        {
                            sprintf(menuPrompt,"%-40s:","Course Coordinator");
                            if(getString(courseCoordinator,MAX_TITLE_LEN,menuPrompt))
                            {
                                sprintf(menuPrompt,"%-40s:","Description(1-250 Characters)");
                                if(getString(courseDescription,MAX_DESC_LEN,menuPrompt))
                                {
                                    addNewCourse(pms,progID,nextCourseID,courseTitle,courseCode,creditPoints,teachingSemester,teachingYear,courseCoordinator,courseDescription);
                                }
                            }
                        }
                    }
                }
            }

        }

    }
    
    /* dereference pointer */
    currentProgram = NULL;
}


/****************************************************************************
* Menu option #7: Delete Course
* Deletes a single course from a particular "program".
****************************************************************************/
void deleteCourse(PMSType* pms)
{
    char menuPrompt[PROMPT_LENGTH+1];
    
    char progID[MAX_TITLE_LEN+1];
    char courseID[MAX_TITLE_LEN+1];
    
    
    printf("\nDELETE COURSE\n");
    printf("------------------------\n\n");
    
    sprintf(menuPrompt,"Program ID:");
    if(getString(progID,MAX_TITLE_LEN,menuPrompt))
    {
        sprintf(menuPrompt,"course ID:");
        if(getString(courseID,MAX_TITLE_LEN,menuPrompt))
        {
            deleteSpecificCourse(pms,progID,courseID);
        }
    }
}


/****************************************************************************
* Menu option #8: Save and Exit
* Saves all system data back to the original files. This function does not
* terminate the program - this is left to the main() function instead.
****************************************************************************/
void saveData(PMSType* pms, char* programFile, char* courseFile)
{
    saveProgramData(pms,programFile);
    saveCourseData(pms,courseFile);
}
