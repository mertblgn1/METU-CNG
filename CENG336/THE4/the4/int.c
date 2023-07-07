#include "define.h"

char received_value;
/**********************************************************************
 * Function you want to call when an IT occurs.
 **********************************************************************/
  extern void AddOneTick(void);
/*extern void MyOwnISR(void); */
  void InterruptVectorL(void);
  void InterruptVectorH(void);

/**********************************************************************
 * General interrupt vector. Do not modify.
 **********************************************************************/
#pragma code IT_vector_low=0x18
void Interrupt_low_vec(void)
{
   _asm goto InterruptVectorL  _endasm
}
#pragma code

#pragma code IT_vector_high=0x08
void Interrupt_high_vec(void)
{
   _asm goto InterruptVectorH  _endasm
}
#pragma code

/**********************************************************************
 * General ISR router. Complete the function core with the if or switch
 * case you need to jump to the function dedicated to the occuring IT.
 * .tmpdata and MATH_DATA are saved automaticaly with C18 v3.
 **********************************************************************/
#pragma	code _INTERRUPT_VECTORL = 0x003000
#pragma interruptlow InterruptVectorL 
void InterruptVectorL(void)
{
  EnterISR();

  if (INTCONbits.TMR0IF == 1)
    AddOneTick();

  // Sending
  if (PIR1bits.TXIF == 1) {
    TXREG = commandString;
  }
  
  // Receiving
  if (PIR1bits.RCIF == 1) {
    received_value = RCREG;
    
    if (received_value == '$') {
        insideCommand = 1;
        receiveIndex = 0; // Reset the receive index
    } else if (insideCommand == 1 && received_value == ':') {
        insideCommand = 0;
        receiveBuffer[receiveIndex] = '\0'; // Null-terminate the command in the buffer
        // Parse the buffer
        switch(receiveBuffer[0]) {
          case 'G': // GO response
            // Switch to ACTIVE state
            currentGameState = STATE_ACTIVE;
            break;
          case 'E': // END response
            currentGameState = STATE_END;
            break;
          case 'R': // STATUS response
            // Extract the customer status, ingredient status and money
            strncpy(customer1Status, receiveBuffer + 1, 3);
            strncpy(customer2Status, receiveBuffer + 5, 3);
            strncpy(customer3Status, receiveBuffer + 9, 3);
            strncpy(ingredientSlot, receiveBuffer + 13, 3);
            strncpy(readMoney, receiveBuffer + 17, 2);
            break;
          case 'H':
            strncpy(hashResponse, receiveBuffer + 1, 8);
            // Solve the hashstring and send a Hash-reply command
            SetEvent(TASK1_ID, START_HASHING);
            break;
          default:
            break;
        }
    } else if (insideCommand) {
        if (receiveIndex < 20) {
            receiveBuffer[receiveIndex] = received_value;
            receiveIndex++;
        }
    }

    // Clear the flag
    PIR1bits.RCIF = 0;
  }

  // Sometimes errors might happen, handle it by unsetting and then setting RCSTA.CREN to keep receiving
  if (RCSTAbits.OERR) {
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
  }

  LeaveISR();
}
#pragma	code

/* BE CARREFULL : ONLY BSR, WREG AND STATUS REGISTERS ARE SAVED  */
/* DO NOT CALL ANY FUNCTION AND USE PLEASE VERY SIMPLE CODE LIKE */
/* VARIABLE OR FLAG SETTINGS. CHECK THE ASM CODE PRODUCED BY C18 */
/* IN THE LST FILE.                                              */
#pragma	code _INTERRUPT_VECTORH = 0x003300
#pragma interrupt InterruptVectorH nosave=FSR0, TBLPTRL, TBLPTRH, TBLPTRU, TABLAT, PCLATH, PCLATU, PROD, section(".tmpdata"), section("MATH_DATA")
void InterruptVectorH(void)
{
  if (INTCONbits.INT0IF == 1)
    INTCONbits.INT0IF = 0;
}
#pragma	code



extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x003400
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code


/* End of file : int.c */