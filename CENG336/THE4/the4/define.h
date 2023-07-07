#ifndef _DEFINE_H
#define _DEFINE_H

#include "device.h"
#include <string.h>

#define _XTAL_FREQ   10000000

/***********************************************************************
 * ------------------------ Timer settings -----------------------------
 **********************************************************************/
#define _10MHZ	63055
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/***********************************************************************
 * ----------------------------- Events --------------------------------
 **********************************************************************/
#define ALARM_EVENT       0x80 // It is used for sending commands every 50ms
#define LCD_EVENT      0x01 // It is used for refreshing LCD
#define START_HASHING	  0x02 // It is used for starting to hashing

/***********************************************************************
 * ----------------------------- Alarms --------------------------------
 **********************************************************************/
#define ALARM_TSK0          0       /* Alarm ID (index) in tascdesc.c */
#define LCD_ALARM_ID        1       /* Alarm ID (index) in tascdesc.c */

/***********************************************************************
 * ---------------------- Task ID & Priorities -------------------------
 **********************************************************************/
#define TASK0_ID            1
#define TASK1_ID			2
#define LCD_ID              5

#define TASK0_PRIO          10 // task0 and task1 have the same priority because
#define TASK1_PRIO          10 // hashing and the game control should work simultaneously
#define LCD_PRIO            11 // LCD needs to have higher priority because latest values should be shown all the time

/***********************************************************************
 * ---------------------- GLOBAL VARIABLES -------------------------
 **********************************************************************/
extern unsigned int money;
extern unsigned int numberOfCustomers;
extern unsigned int hashingCompleted; // 0 means haven't computed yet, 1 means it is computed
extern unsigned char hash[17]; // It is used for Hash-reply command
extern unsigned char hashResponse[8]; // It is the hash to be solved
extern unsigned char commandString[21]; // It is used to send the command

extern unsigned char firstLineOfLCD[17] = "MONEY:     0000";
extern unsigned char secondLineOfLCD[17] = "C: 0    ING:NNNN";
extern unsigned char ingredientSlot[4] = "NNNN";
extern unsigned char customer1Status[4];
extern unsigned char customer2Status[4];
extern unsigned char customer3Status[4];
extern unsigned char readMoney[4];

unsigned char receiveBuffer[21];
unsigned int receiveIndex = 0;
unsigned int insideCommand = 0; // It states if we are reading the command. 0 means false, 1 means true

enum Response {
	GO,
	END,
	STATUS,
	HASH
};

enum Command {
	WAIT,
	COOK,
	SLOW_COOK,
	HASH_REPLY,
	TOSS
};

enum GameState {
    STATE_IDLE,
    STATE_ACTIVE,
    STATE_END
};

enum GameState currentGameState = STATE_IDLE;
extern enum Command currentCommand = WAIT;
/***********************************************************************
 * ---------------------- Functions --------------------------------
 **********************************************************************/

#endif /* _DEFINE_H */


/* End of File : define.h */