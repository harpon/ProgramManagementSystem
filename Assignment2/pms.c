/***************************************************************************
 * COSC1283/1284 - Programming Techniques
 * Semester 1 2013 Assignment #2 - SCSIT Program Management System
 * Full Name        : Hartanto Poniman Noerdjaja
 * Student Number   : s3420572
 * Yallara Username : s3420572
 * Course Code      : COSC1284
 * Program Code     : BP162
 * Start up code provided by Paul Miller,and Xiaodong Li
 **************************************************************************/

#include "pms.h"
#include "pms_options.h"
#include "pms_utility.h"

int main(int argc, char* argv[])
{
    PMSType pms;

    int initFlag, dataFlag;

    char menuPrompt[PROMPT_LENGTH+1];
    int menuInput;
    
    if( argv[1] == NULL || argv[2] == NULL )
    {
        printf("\nError: Missing argument! \n");
        printf("--------------------------\n\n");
        printf("./pms <program file> <course file>\n\n");
        exit(EXIT_FAILURE);
    }
    
    /* Initialise the program management system to a safe empty state. */
    initFlag = systemInit(&pms);
    
    /*Populate the program management system with data from the data files. 
      Uncomment this line when you are ready to use command line 
      arguments: */
    
    dataFlag = loadData(&pms, argv[1], argv[2]);

    /* Testing to see if both systemInit(.) and loadData(.) are ok */
    if (initFlag == FAILURE || dataFlag == FAILURE)
        exit(EXIT_FAILURE); 

    /* Interactive menu providing user with access to the 9 menu options */
    do
    {
    	sprintf(menuPrompt,"Main Menu:\n1)Summary of Undergrad Programs\n2)Summary of Postgrad Programs\n3)Detailed Program Report\n4)Add Program\n5)Delete Program\n6)Add Course\n7)Delete Course\n8)Save & Exit\n9)Abort\n\nSelect Your Option (1-9):");
    
        getInteger(&menuInput,MAX_OPTION_INPUT_LENGTH,menuPrompt,1,9);
        
	switch(menuInput)
	{
	   	case 1:
		{
			/* Display summary of undergraduate programs */	
            displaySummary(&pms, "UG");
            break;
		}
		case 2:
		{
			/* Display Summary of post graduate programs */
			displaySummary(&pms, "PG");
            break;
		}
		case 3:
		{
			/* Detailed program report */
            programReport(&pms);
            break;
		}
		case 4:
		{
            addProgram(&pms);
            break;
		}
		case 5:
		{
			/* Delete Program */
            deleteProgram(&pms);
            break;
		}
		case 6:
		{
			/* Add course */
            addCourse(&pms);
            break;
		}
		case 7:
		{
			/* Delete course */
            deleteCourse(&pms);
            break;
		}
		case 8:
		{
			/* Save and exit */
            saveData(&pms,argv[1],argv[2]);
            break;
		}
		case 9:
		{
			break;
		}
	}
    }
    while( menuInput < 8 );
    
    /* Deallocate all dynamically allocated memory. */
    systemFree(&pms);

    exit(EXIT_SUCCESS);

}
