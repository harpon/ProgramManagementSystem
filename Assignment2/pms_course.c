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

#include "pms_course.h"
/* provide implementations of functions to manage the pms_course list data
 * structure here
 */
BOOLEAN addNewCourse(PMSType* pms, char* progID, char* nextCourseID, char* courseTitle,char* courseCode, int creditPoints, int teachingSemester,int teachingYear , char* courseCoordinator, char* courseDescription)
{
    /* pointer to traverse in program and course List */
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    
    CourseTypePtr tempCourse = NULL;
    
    int i;
    
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
    
    i = 0;
    
    while(i < MAX_DATA_SUBJECT )
    {
        if( i == 0 )
        {
            strcpy(tempCourse->data->courseID,nextCourseID);
        }
        else if ( i == 1 )
        {
            strcpy(tempCourse->data->progID,progID);
        }
        else if ( i == 2 )
        {
            strcpy(tempCourse->data->courseTitle,courseTitle);
        }
        else if ( i == 3 )
        {
            strcpy(tempCourse->data->courseCode,courseCode);
        }
        else if ( i == 4 )
        {
            tempCourse->data->creditPoints = creditPoints;
        }
        else if ( i == 5 )
        {
            tempCourse->data->teachPeriods[0].semester = teachingSemester;
            tempCourse->data->teachPeriods[0].year = teachingYear;
        }
        else if ( i == 6 )
        {
            strcpy(tempCourse->data->courseCoordinator,courseCoordinator);
        }
        else if ( i == 7 )
        {
            strcpy(tempCourse->data->courseDescription,courseDescription);
        }
        
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
    
    return TRUE;
}

void deleteSpecificCourse(PMSType* pms,char* progID,char* courseID)
{
    /* pointer to traverse in program and course List */
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    CourseTypePtr previousCourse = NULL;
    
    
    currentProgram = pms->headProgram;
    
    
    
    while(currentProgram != NULL)
    {
        if(strcmp(currentProgram->data->progID,progID) == 0)
        {
            currentCourse = currentProgram->headCourse;
            
            while(currentCourse != NULL)
            {
                if (strcmp(currentCourse->data->courseID,courseID) == 0)
                {
                    if(strcmp(currentProgram->headCourse->data->courseID,courseID) == 0)
                    {
                        currentProgram->headCourse = currentCourse->nextCourse;
                        currentCourse->nextCourse = NULL;
                    }
                    else
                    {
                        previousCourse->nextCourse = currentCourse->nextCourse;
                        currentCourse->nextCourse = NULL;
                    }
                    
                    printf("Course \"%s - %s\" deleted from program \"%s(%s)\".\n\n",currentCourse->data->courseID, currentCourse->data->courseTitle,currentProgram->data->progTitle,currentProgram->data->progMajor);
                    free(currentCourse);
                    break;
                }
                else
                {
                    previousCourse = currentCourse;
                    currentCourse = currentCourse->nextCourse;
                }
            }
        }
        currentProgram = currentProgram->nextProgram;
    }
}

void saveCourseData(PMSType* pms,char* courseFile)
{
    FILE *outputFile;
    
    ProgramTypePtr currentProgram = NULL;
    CourseTypePtr currentCourse = NULL;
    
    if ((outputFile = fopen(courseFile,"w+")) == NULL) {
        printf("\n fopen failed - could not open file : %s\n", courseFile);
        exit(EXIT_FAILURE);
    }
    
    currentProgram = pms->headProgram;
    
    while(currentProgram != NULL)
    {
        currentCourse = currentProgram->headCourse;
        while( currentCourse != NULL)
        {
            fprintf(outputFile,"%s|%s|%s|%s|%u|Semester %u, %u|%s|%s\n",currentCourse->data->courseID,currentCourse->data->progID,currentCourse->data->courseTitle,currentCourse->data->courseCode,currentCourse->data->creditPoints,currentCourse->data->teachPeriods[0].semester,currentCourse->data->teachPeriods[0].year,currentCourse->data->courseCoordinator,currentCourse->data->courseDescription);
            currentCourse = currentCourse->nextCourse;
        }

        currentProgram = currentProgram->nextProgram;
    }
    
    
    
    fclose(outputFile);
    
    currentProgram = NULL;
    currentCourse = NULL;
}
