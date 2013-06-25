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

#include "pms_program.h"

/* provide the implementation of functions to manage the pms_program list 
 * data structure here.
 */

void displayProgramSummary(PMSType* pms, char* programType)
{
    /* pointer for traverse in ProgramType and Course Type node */
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    
    /* variable used for alignment */
    char courseTitleAndCP[MAX_DISPLAY_LEN+1];
    
    currentProgram = pms->headProgram;
    
    while(currentProgram != NULL)
    {
        /* Search specific program type */
        if(strcmp(currentProgram->data->progType,programType) == 0)
        {
            printf("%s - %s \n\t( %s ) ( %.0f Courses )\n",currentProgram->data->progID,currentProgram->data->progTitle,currentProgram->data->progMajor,currentProgram->data->progDuration);
            printf("---------------------------------------------------------------------\n");
            printf("\t%-10s%-40s%-20s\n","ID","Course Title","Teach Periods");
            printf("\t%-10s%-40s%-20s\n","---","-----------","-----------");
            
            
            currentCourse = currentProgram->headCourse;
            while( currentCourse != NULL)
            {
                sprintf(courseTitleAndCP,"%s(%uPS)",currentCourse->data->courseTitle,currentCourse->data->creditPoints);

                printf("\t%-10s%-40s",currentCourse->data->courseID,courseTitleAndCP);
                printf("Semester %d, %d\n",currentCourse->data->teachPeriods[0].semester,currentCourse->data->teachPeriods[0].year);
                
                currentCourse = currentCourse->nextCourse;
            }
            
            printf("\n\n");
        }
        
        currentProgram = currentProgram->nextProgram;
        
    }
    /* de-reference pointer*/
    currentProgram = NULL;
    currentCourse = NULL;
    
}

BOOLEAN addNewPrograms(PMSType* pms, char* progTitle, char* progType, char* progMajor, char* progCode, char* progDuration,char* progMode, char* progDescription, char* majorDescription,char* progID)
{
    ProgramTypePtr tempProg;
    
    /* pointer used to traverse and insert new node to sorted link-list */
    ProgramTypePtr currentProgram = NULL;
    
    int i;
    
    /* allocate memory for new Program node */
    tempProg = malloc(sizeof(ProgramType));
    
    if(tempProg == NULL)
    {
        printf("\nCannot allocate memory\n");
        return FALSE;
    }
    
    tempProg->data = malloc(sizeof(struct program_data));
    
    if(tempProg->data == NULL)
    {
        printf("\nCannot allocate memory for program data\n");
        return FALSE;
    }
    
    
    i = 0;
    
    while ( i < MAX_DATA_SUBJECT )
    {
        if(i == 0)
        {
            strcpy(tempProg->data->progID,progID);
        }
        else if ( i == 1 )
        {
            strcpy(tempProg->data->progType,progType);
        }
        else if ( i == 2 )
        {
            strcpy(tempProg->data->progTitle,progTitle);
        }
        else if ( i == 3 )
        {
            strcpy(tempProg->data->progMajor,progMajor);
        }
        else if ( i == 4 )
        {
            strcpy(tempProg->data->progCode,progCode);
        }
        else if ( i == 5 )
        {
            tempProg->data->progDuration = atof(progDuration);
        }
        else if ( i == 6 )
        {
            strcpy(tempProg->data->progMode,progMode);
        }
        else if ( i == 7 )
        {
            strcpy(tempProg->data->progDescription,progDescription);
        }
        else if ( i == 8 )
        {
            strcpy(tempProg->data->majorDescription,majorDescription);
        }
        
        i++;
    }
    /* initialize ProgramType node */
    
    tempProg->headCourse = NULL;
    tempProg->numCourses = 0;
    
    currentProgram = pms->headProgram;
    
    if(currentProgram == NULL)
    {
        tempProg->nextProgram = pms->headProgram;
        pms->headProgram = tempProg;
    }
    else
    {
        while(strcmp(tempProg->data->progID, currentProgram->data->progID) > 1 && currentProgram->nextProgram != NULL )
        {
            currentProgram = currentProgram->nextProgram;
        }
        
        tempProg->nextProgram = currentProgram->nextProgram;
        currentProgram->nextProgram = tempProg;
    }
    
    pms->numPrograms++;
    
    
    /* dereference pointer */
    tempProg = NULL;
    currentProgram = NULL;
    
    return TRUE;
}

void deleteSpecificPrograms(PMSType* pms, char* progID)
{
    /* pointer for traverse in ProgramType List */
    ProgramTypePtr currentProgram = NULL;
    ProgramTypePtr previousProgram = NULL;
    
    currentProgram = pms->headProgram;
    
    /* */
    while(currentProgram != NULL)
    {
        if(strcmp(currentProgram->data->progID,progID) == 0)
        {
            if(strcmp(pms->headProgram->data->progID,progID) == 0)
            {
                pms->headProgram = currentProgram->nextProgram;
                currentProgram->nextProgram = NULL;
            }
            else
            {
                previousProgram->nextProgram = currentProgram->nextProgram;
                currentProgram->nextProgram = NULL;
            }
            printf("Program\"%s - %s\" deleted from the system\n\n",currentProgram->data->progID,currentProgram->data->progTitle);
            free(currentProgram);
            break;
        }
        else
        {
            previousProgram = currentProgram;
            currentProgram = currentProgram->nextProgram;
        }
    }
}

void produceProgramReport(PMSType* pms,char* progID)
{
    FILE *outputFile;
    char outputFileName[MAX_FILE_NAME_LEN+1];
    
    /* pointer for traverse in program and course list */
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    
    currentProgram = pms->headProgram;
    
    while(currentProgram != NULL)
    {
        if(strcmp(currentProgram->data->progID,progID) == 0)
        {
            strcat(outputFileName,progID);
            strcat(outputFileName,".report");
            
            if ((outputFile = fopen(outputFileName,"w+")) == NULL) {
                printf("\n fopen failed - could not open file : %s\n", outputFileName);
                exit(EXIT_FAILURE);
            }

            fprintf(outputFile,"Program %s - %s \n\t\t (%s) - Detailed Report\n",currentProgram->data->progID,currentProgram->data->progTitle, currentProgram->data->progMajor);
            fprintf(outputFile,"-------------------------------------------------\n");
            
            currentCourse = currentProgram->headCourse;
            while( currentCourse != NULL)
            {
                fprintf(outputFile,"%-30s : %s\n","Course ID",currentCourse->data->courseID);
                fprintf(outputFile,"%-30s : %s\n","Course Title",currentCourse->data->courseTitle);
                fprintf(outputFile,"%-30s : %d\n","Credit Points", currentCourse->data->creditPoints);
                fprintf(outputFile,"%-30s : Semester %u , %u\n","Teaching Period",currentCourse->data->teachPeriods[0].semester,currentCourse->data->teachPeriods[0].year);
                fprintf(outputFile,"%-30s : %s\n\n","Description", currentCourse->data->courseDescription);
                currentCourse = currentCourse->nextCourse;
            }
            printf("File \"%s\" has been created\n\n",outputFileName);
            fclose(outputFile);
            break;
        }
        else
        {
            currentProgram = currentProgram->nextProgram;
        }
    }
    
   
    
    /* dereference pointer */
    currentProgram = NULL;
    currentCourse = NULL;
    
    
}

void saveProgramData(PMSType* pms,char* programFile)
{
    FILE *outputFile;
    
    ProgramTypePtr currentProgram = NULL;
    
    if ((outputFile = fopen(programFile,"w+")) == NULL) {
        printf("\n fopen failed - could not open file : %s\n", programFile);
        exit(EXIT_FAILURE);
    }
    
    currentProgram = pms->headProgram;
    
    while(currentProgram != NULL)
    {
        fprintf(outputFile,"%s|%s|%s|%s|%s|%.0f|%s|%s|%s\n",currentProgram->data->progID,currentProgram->data->progType,currentProgram->data->progTitle,currentProgram->data->progMajor,currentProgram->data->progCode,currentProgram->data->progDuration,currentProgram->data->progMode,currentProgram->data->progDescription,currentProgram->data->majorDescription);
        currentProgram = currentProgram->nextProgram;
    }
    
    
    
    fclose(outputFile);
    
    currentProgram = NULL;
}