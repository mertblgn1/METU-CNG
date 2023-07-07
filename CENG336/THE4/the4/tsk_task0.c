#include "define.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/


/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 *
 * Task that sends sends commands every 50 ms.
 *
 **********************************************************************/
TASK(TASK0)
{
	SetRelAlarm(ALARM_TSK0, 0, 50);
	int i;
	unsigned char index;
	while(1) {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        
        if(currentGameState == STATE_END) {
        	break;
        } else if(currentGameState == STATE_ACTIVE) {
        	// Check if toss command needed
        	for(i = 0; i < 4; i++) {
        		if(customer1Status[1] != ingredientSlot[i] && customer1Status[2] != ingredientSlot[i] && ingredientSlot[i] != 'N') {
        			currentCommand = TOSS;
        			char c = (char)i;
        			sprintf(commandString, "$T%c:", c);
        		} else if (customer2Status[1] != ingredientSlot[i] && customer2Status[2] != ingredientSlot[i] && ingredientSlot[i] != 'N') {
        			currentCommand = TOSS;
        			char c = (char)i;
        			sprintf(commandString, "$T%c:", c);
        		} else if (customer3Status[1] != ingredientSlot[i] && customer3Status[2] != ingredientSlot[i] && ingredientSlot[i] != 'N') {
        			currentCommand = TOSS;
        			char c = (char)i;
        			sprintf(commandString, "$T%c:", c);
        		}
        	}

        	// Check if Cook Command needed
        	for(i = 0; i < 4; i++) {
        		if(customer1Status[1] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer1Status[0], ingredientSlot[i], 'N');
        			currentCommand = COOK;
        		} else if (customer1Status[2] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer1Status[0], 'N', ingredientSlot[i]);
        			currentCommand = COOK;
        		} else if (customer2Status[1] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer2Status[0], ingredientSlot[i], 'N');
        			currentCommand = COOK;
        		} else if (customer2Status[2] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer2Status[0], 'N', ingredientSlot[i]);
        			currentCommand = COOK;
        		} else if (customer3Status[1] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer3Status[0], ingredientSlot[i], 'N');
        			currentCommand = COOK;
        		} else if (customer3Status[2] == ingredientSlot[i]) {
        			// cook the ingredient in this index
        			sprintf(commandString, "$C%c%c%c:", customer3Status[0], 'N', ingredientSlot[i]);
        			currentCommand = COOK;
        		}
        	}

        	// Check if Slow-Cook command needed
        	for(i = 0; i < 4; i++) {
        		if(customer1Status[1] == 'F' && customer1Status[2] == 'J') {
        			// Slow cook for this customer
        			sprintf(commandString, "$S%c%c:", customer1Status[0], ingredientSlot[i]);
        			currentCommand = SLOW_COOK;
        		} else if(customer2Status[1] == 'F' && customer2Status[2] == 'J') {
        			// Slow cook for this customer
        			sprintf(commandString, "$S%c%c:", customer2Status[0], ingredientSlot[i]);
        			currentCommand = SLOW_COOK;
        		} else if(customer3Status[1] == 'F' && customer3Status[2] == 'J') {
        			// Slow cook for this customer
        			sprintf(commandString, "$S%c%c:", customer3Status[0], ingredientSlot[i]);
        			currentCommand = SLOW_COOK;
        		}
        	}

        	// Check if Hash-reply command needed
        	if(hashingCompleted) {
        		sprintf(commandString, "$H%s:", hash);
        		currentCommand = HASH_REPLY;
        		hashingCompleted = 0;
        	}
        }
        else {
        	currentCommand = WAIT;
        }

	}
	TerminateTask();
}


/* End of File : tsk_task0.c */
