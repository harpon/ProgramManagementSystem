/**********************************************************************************
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
* Function readRestOfLine() is used for buffer clearing. 
* Please refer to "test_fgets.c" on Blackboard: 
* "Course Documents"->"Function Examples"->"Input Validation Examples" 
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF);

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/****************************************************************************
* Initialises the system to a safe empty state.
****************************************************************************/
BOOLEAN systemInit(PMSType* pms)
{
    /* initialize headProgram to null */
    pms->headProgram = NULL;
    
    /* initialize numProgram to 0 */
    pms->numPrograms = 0;
    
    return TRUE;
}


/****************************************************************************
* Loads all data into the system.
****************************************************************************/
BOOLEAN loadData(PMSType* pms, char* programFile, char* courseFile)
{
    /* pointer to create a temporary ProgramType and CourseType node */
    ProgramTypePtr tempProg = NULL;
    CourseTypePtr tempCourse = NULL;
    
    /* pointer used to travers , insert to sorted link-list */
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    
    FILE *file;
    
    /* magic number */
    char line[1024];
    
    char *token;
    
    /* magic number */
    char year[5];
    
    int i,j;
    
    /* Open and read Program file */
    file = fopen(programFile,"r");
    
    if( file == NULL )
    {
        printf("\n fopen failed - could not open file:%s \n",programFile);
        return FALSE;
    }
    
    j = 0;
    
    while(fgets(line,1024, file) != NULL)
    {
         /* Allocate memory for programType ( creating new node ) */
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
        
        /* Splitting string into token */
        token = strtok(line,"|");
        i = 0;
        
        while(token != NULL)
        {
            
            /* Store tokenize string into linked list */
            if( i == 0 )
            {
                if(strlen(token) < ID_LEN)
                {
                    printf("\nERROR: Program ID in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progID,token);
            }
            else if ( i == 1 )
            {
                if(strlen(token) != PROG_TYPE_LEN)
                {
                    printf("\nERROR: Program type in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                strcpy(tempProg->data->progType,token);
            }
            else if ( i == 2 )
            {
                if(strlen(token) > MAX_TITLE_LEN)
                {
                    printf("\nERROR: Program title in %s is not valid (line %d) length may not exceed 50 characters\n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progTitle,token);
            }
            else if ( i == 3 )
            {
                if(strlen(token) > MAX_TITLE_LEN)
                {
                    printf("\nERROR: Program ID in %s is not valid (line %d) length may not exceed 50 characters\n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progMajor,token);
            }
            else if ( i == 4 )
            {
                if(strlen(token) > PROG_CODE_LEN)
                {
                    printf("\nERROR: Program code in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progCode,token);
            }
            else if ( i == 5 )
            {
                tempProg->data->progDuration = atof(token);
            }
            else if ( i == 6 )
            {
                if(strlen(token) != MODE_LEN)
                {
                    printf("\nERROR: Program mode in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progMode,token);
            }
            else if ( i == 7 )
            {
                if(strlen(token) > MAX_DESC_LEN)
                {
                    printf("\nERROR: Program description in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                
                strcpy(tempProg->data->progDescription,token);
            }
            else if ( i == 8 )
            {
                if(strlen(token) > MAX_DESC_LEN)
                {
                    printf("\nERROR: Major description in %s is not valid (line %d) \n\n",programFile,j+1);
                    return FALSE;
                }
                
                clearNewLine(token);
                strcpy(tempProg->data->majorDescription,token);
            }
            
            token = strtok(NULL,"|");
            
            i++;
            
        }
        /* initialize ProgramType node */
        tempProg->headCourse = NULL;
        tempProg->nextProgram = NULL;
        tempProg->numCourses = 0;
        
        /* Inserting node while sorting */
        currentProgram = pms->headProgram;
        
        if(currentProgram == NULL)
        {
            tempProg->nextProgram = pms->headProgram;
            pms->headProgram = tempProg;
            
            tempProg = NULL;
        }
        else
        {
            while(strcmp(tempProg->data->progID, currentProgram->data->progID) > 1 && currentProgram->nextProgram != NULL )
            {
                currentProgram = currentProgram->nextProgram;
            }
            
            tempProg->nextProgram = currentProgram->nextProgram;
            currentProgram->nextProgram = tempProg;
            
            tempProg = NULL;
        }
        
        /* increment Number of program */
        pms->numPrograms++;
        
        /* de-reference currentProgram */
        currentProgram = NULL;
        
        /*increment line number for error message */
        j++;
    }
    
    /* de-reference pointer and close file */
    tempProg = NULL;
    currentProgram = NULL;
    fclose(file);
    
    
    
    /* --------------------------------------------------------------- */
    
    /* Open and read Course file */
    file = fopen(courseFile,"r");
    
    if( file == NULL )
    {
        printf("\n fopen failed - could not open file:%s \n",programFile);
        return FALSE;
    }
    
    j=0;
    
    /* Read and store to linked list */
    while(fgets(line,1024, file) != NULL)
    {
        /* allocate memory for CourseType */
        tempCourse = malloc(sizeof(CourseType));
        
        if(tempCourse == NULL)
        {
            printf("\nCannot allocate memory\n");
            return FALSE;
        }
        
        tempCourse->data = malloc(sizeof(struct course_data));
        
        if(tempCourse->data == NULL)
        {
            printf("\nCannot allocate memory for program data\n");
            return FALSE;
        }
        
        token = strtok(line,"|");
        i = 0;
       
        while(token != NULL)
        {
            if( i == 0 )
            {
                if(strlen(token) < ID_LEN)
                {
                    printf("\nERROR: Course ID in %s is not valid (line %d) \n\n",courseFile,j+1);
                    return FALSE;
                }

                strcpy(tempCourse->data->courseID,token);
            }
            else if ( i == 1 )
            {
                if(strlen(token) < ID_LEN)
                {
                    printf("\nERROR: Program ID in %s is not valid (line %d) \n\n",courseFile,j+1);
                    return FALSE;
                }

                strcpy(tempCourse->data->progID,token);
            }
            
            else if ( i == 2 )
            {
                if(strlen(token) > MAX_TITLE_LEN)
                {
                    printf("\nERROR: Course title in %s is not valid (line %d) length may not exceed 50 characters\n\n",courseFile,j+1);
                    return FALSE;
                }

                strcpy(tempCourse->data->courseTitle,token);
            }
            else if ( i == 3 )
            {
                if(strlen(token) > COURSE_CODE_LEN)
                {
                    printf("\nERROR: Course code in %s is not valid (line %d)\n",courseFile,j+1);
                    printf("String : %s\n\n",token);
                    return FALSE;
                }
                
                strcpy(tempCourse->data->courseCode,token);
            }
            
            else if ( i == 4 )
            {
                tempCourse->data->creditPoints = atoi(token);
            }
            else if ( i == 5 )
            {
                strncpy(year,token+12,sizeof(year));
                
                tempCourse->data->teachPeriods[0].semester = token[9]-48;
                tempCourse->data->teachPeriods[0].year = atoi(year);
            }
            else if ( i == 6 )
            {
                if(strlen(token) > MAX_TITLE_LEN)
                {
                    printf("\nERROR: Course coordinator in %s is not valid (line %d) Length max not Exceed %d characters \n\n",courseFile,j+1,MAX_TITLE_LEN);
                    return FALSE;
                }
                
                strcpy(tempCourse->data->courseCoordinator,token);
            }
            else if (i == 7 )
            {
                if(strlen(token) > MAX_DESC_LEN)
                {
                    printf("\nERROR: Course Description in %s is not valid (line %d) Length max not Exceed %d characters \n\n",courseFile,j+1,MAX_DESC_LEN);
                    printf("String : %s\n\n",token);
                    return FALSE;
                }

                clearNewLine(token);
                strcpy(tempCourse->data->courseDescription,token);
            }
            
            
            token = strtok(NULL,"|");
            i++;
            
        }
        
        /* linking Program and course */
        currentProgram = pms->headProgram;
        
        while( currentProgram != NULL )
        {
            if(strcmp(tempCourse->data->progID,currentProgram->data->progID) == 0)
            {
                currentCourse = currentProgram->headCourse;
                
                if(currentCourse == NULL)
                {
                    tempCourse->nextCourse = currentProgram->headCourse;
                    currentProgram->headCourse = tempCourse;
                }
                else
                {
                    while( strcmp(tempCourse->data->courseID, currentCourse->data->courseID) > 1 && currentCourse->nextCourse != NULL )
                    {
                        currentCourse = currentCourse->nextCourse;
                    }
                    
                    tempCourse->nextCourse = currentCourse->nextCourse;
                    currentCourse->nextCourse = tempCourse;
                }
                
                currentProgram->numCourses++;
                break;
            }
            
            currentProgram = currentProgram->nextProgram;
        }
        
        j++;
    }
    /* de-reference pointer and close file */
    currentProgram = NULL;
    tempCourse = NULL;
    fclose(file);

    /* compile all program and course txt file to 1 linked list*/
    return TRUE;
}


/****************************************************************************
* Deallocates memory used in the program.
****************************************************************************/
void systemFree(PMSType* pms)
{
    
}

/****************************************************************************
 * Getting String input
 ****************************************************************************/
int getString(char* string, unsigned length, char* prompt)
{
    int finished = FALSE;
    char* tempString;
    
    /* Allocate temporary memory. */
    if ((tempString = malloc(sizeof(char) * (length+2))) == NULL)
    {
        fprintf(stderr, "Fatal error: malloc() failed in getString().\n");
        exit(EXIT_FAILURE);
    }
    
    /* Continue to interact with the user until the input is valid. */
    do
    {
        /* Provide a custom prompt. */
        printf("%s", prompt);
        
        /* Accept input. "+2" is for the \n and \0 characters. */
        fgets(tempString, length + 2, stdin);
        
        if ( tempString[0] == '\n')
        {
            return FAILURE;
        }
        
        /* A string that doesn't have a newline character is too long. */
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("\nERROR: Input was too long.\n\n");
            readRestOfLine();
        }
        else
        {
            finished = TRUE;
        }
        
    } while (finished == FALSE);
    
    /* Overwrite the \n character with \0. */
    tempString[strlen(tempString) - 1] = '\0';
    
    /* Make the result string available to calling function. */
    strcpy(string, tempString);
    
    /* Deallocate temporary memory. */
    free(tempString);
    
    return SUCCESS;
}

/****************************************************************************
 * Getting Integer input
 ****************************************************************************/
int getInteger(int* integer, unsigned length, char* prompt, int min, int max)
{
    int finished = FALSE;
    char* tempString;
    int tempInteger = 0;
    char* endPtr;
    
    /* Allocate temporary memory. */
    if ((tempString = malloc(sizeof(char) * (length+2))) == NULL)
    {
        fprintf(stderr, "Fatal error: malloc() failed in getString().\n");
        exit(EXIT_FAILURE);
    }
    
    /* Continue to interact with the user until the input is valid. */
    do
    {
        /* Provide a custom prompt. */
        printf("%s", prompt);
        
        /* Accept input. "+2" is for the \n and \0 characters. */
        fgets(tempString, length + 2, stdin);
        
        if ( tempString[0] == '\n')
        {
            return FAILURE;
        }
        
        /* A string that doesn't have a newline character is too long. */
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            readRestOfLine();
        }
        else
        {
            /* Overwrite the \n character with \0. */
            tempString[strlen(tempString) - 1] = '\0';
            
            /* Convert string to an integer. */
            tempInteger = (int) strtol(tempString, &endPtr, 10);
            
            /* Validate integer result. */
            if (strcmp(endPtr, "") != 0)
            {
                printf("Input was not numeric.\n");
            }
            else if (tempInteger < min || tempInteger > max)
            {
                printf("Input was not within range %d - %d.\n", min, max);
            }
            else
            {
                finished = TRUE;
            }
        }
    } while (finished == FALSE);
    
    /* Make the result string available to calling function. */
    *integer = tempInteger;
    
    /* Deallocate temporary memory. */
    free(tempString);
    
    return SUCCESS;
}

/****************************************************************************
 * Clear the the new line tags ( so it not doubles when we write to the file ) 
 ****************************************************************************/
void clearNewLine(char* rawString)
{
    char *nl;
    
    nl = strchr(rawString,'\n');
    if(nl) *nl = '\0';

}
