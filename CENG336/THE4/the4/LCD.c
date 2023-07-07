#include "define.h"
#include <p18cxxx.h>
#include <p18f4620.h>
#include "LCD.h"
#include <stdlib.h>

/**********************************************************************
 * ----------------------- LCD USER SETTINGS --------------------------
 **********************************************************************/
#define COLUMN            16              /* Character number per line */
#define LINE              2               /*      Number of line       */


/**********************************************************************
 * --------------- LCD function prototypes -----------------
 **********************************************************************/
void InitLCD(void);
void ToggleEpinOfLCD(void);
void WriteDataToLCD(char value);
void WriteStringToLCD(const char *s);
void WriteCommandToLCD(unsigned char Command);
void Delay_LCD_ms(unsigned int delay);
void Lcd_refresh(void);
void WaitState(void);
void ClearLCDScreen(void);
void Lcd_position(unsigned char type, unsigned char value);
void LcdPrintData(unsigned char value, unsigned char positionX, unsigned char positionY);
void LcdPrintString(const char *s, unsigned char positionX,  unsigned char positionY);
void updateLCD(void);

/**********************************************************************
 * ---------------------- LCD global variables ------------------------
 **********************************************************************/
EventMaskType LCDevent;
unsigned char LCDchar[LINE][COLUMN];
unsigned char currentMoney[5];
unsigned char numberOfCustomersOnLCD[1];

/**********************************************************************
 * ----------------------------- LCD TASK -----------------------------
 * 
 * Refresh LCD screen whenever an LCD_EVENT is fired!
 * 
 **********************************************************************/
TASK(LCD)
{
    ADCON1 = 0x8E;
    ADCON0 = 0x00;
    InitLCD();
    SetRelAlarm(LCD_ALARM_ID, 0, 500);
    while(1)
    {
        WaitEvent(LCD_EVENT);
        ClearEvent(LCD_EVENT);
        Lcd_refresh();
        updateLCD();
    }
    TerminateTask();
}

/**********************************************************************
 * Update the values on the LCD
 **********************************************************************/
void updateLCD(void)
{
  int i;
  memset(currentMoney, 0, 5);
  memset(numberOfCustomersOnLCD, 0, 1);
  itoa(money, currentMoney); // Convert the money to string to display on LCD
  itoa(numberOfCustomers, numberOfCustomersOnLCD); // Convert the #customers to string to display on LCD

  // Update first line of LCD
  for(i = 11; i < 16; i++)
    firstLineOfLCD[i] = currentMoney[i - 11];
  // Update second line of LCD
  secondLineOfLCD[3] = numberOfCustomersOnLCD[0];
  for(i = 12; i < 16; i++)
    secondLineOfLCD[i] = ingredientSlot[i - 12];

  LcdPrintString(firstLineOfLCD, 0, 0);
  LcdPrintString(secondLineOfLCD, 0, 1);

}

/**********************************************************************
 * Print at screen what is on the LCDchar buffer (both lines).
 *
 * @param  void
 * @return void 
 **********************************************************************/
void Lcd_position(unsigned char line, unsigned char pos)
{
    switch(line)
    {
        case 0:
            WriteCommandToLCD(0x80+pos);
            break;
        case 1:
            WriteCommandToLCD(0xc0+pos);
            break;
    };
    
}

void Lcd_refresh(void)
{
  unsigned char i, j;
  
  /* GO HOME LCD command */
  WriteCommandToLCD(0x02);
  for (i = 0; i < LINE; i++)
  {
    Lcd_position(i, 0);
    for (j = 0; j < COLUMN; j++)
      WriteDataToLCD(LCDchar[i][j]);
  }
}

/**********************************************************************
 * Write a command or data on the LCD bus.
 *
 * @param  value     IN  value of the data placed on the bus
 * @return void 
 **********************************************************************/
void WriteCommandToLCD(unsigned char Command)
{
    LATEbits.LATE2 = 0;                 // It is a command

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD |(Command&0xF0);      // Write Upper nibble of data
    ToggleEpinOfLCD();                  // Give pulse on E pin

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | ((Command<<4)&0xF0);// Write Lower nibble of data

    ToggleEpinOfLCD();                  // Give pulse on E pin
}

void WriteStringToLCD(const char *s)
{
    while(*s)
        WriteDataToLCD(*s++);   // print first character on LCD
}

/**********************************************************************
 * Write the data on the bus (8 bits mode only).
 *
 * @param  c         IN  data written 
 * @return void 
 **********************************************************************/
void WriteDataToLCD(char value)
{
    LATEbits.LATE2 = 1;                 // It is data

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | (value&0xF0);       // Write Upper nibble of data
    ToggleEpinOfLCD();                  // Give pulse on E pin

    PORTD = PORTD & 0x0F;               // Make Data pins zero
    PORTD = PORTD | ((value<<4)& 0xF0); // Write Lower nibble of data

    ToggleEpinOfLCD();                  // Give pulse on E pin
}

/**********************************************************************
 * Enable the data present on the bus.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void ToggleEpinOfLCD(void)
{
    LATEbits.LATE1 = 1;                // Give a pulse on E pin
    //Delay_LCD_ms(E_Delay);           // so that LCD can latch the
    LATEbits.LATE1 = 0;                // data from data bus
}

/**********************************************************************
 * Generic routine to create a delay of many milliseconds.
 *
 * @param  delay     IN  time to wait in ms
 * @return void 
 **********************************************************************/
void Delay_LCD_ms(unsigned int delay)
{
  SetRelAlarm(LCD_ALARM_ID, delay, 0);
  WaitEvent(ALARM_EVENT);
  GetEvent(LCD_ID, &LCDevent);
  if (LCDevent & ALARM_EVENT)
    ClearEvent(ALARM_EVENT);
  return;
}

/**********************************************************************
 * Init phase of the LCD.
 * Do not modify this sequence.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void InitLCD(void)
{
    TRISE = 0;
    PORTE = 0;

    LATEbits.LATE1  = 0;   // E  = 0
    LATEbits.LATE2  = 0;   // RS = 0
    LATDbits.LATD4  = 0;   // Data bus = 0
    LATDbits.LATD5  = 0;   // Data bus = 0
    LATDbits.LATD6  = 0;   // Data bus = 0
    LATDbits.LATD7  = 0;   // Data bus = 0
    TRISBbits.TRISB5 = 0;   // Make Output
    TRISBbits.TRISB2 = 0;   // Make Output
    TRISDbits.TRISD4 = 0;   // Make Output
    TRISDbits.TRISD5 = 0;   // Make Output
    TRISDbits.TRISD6 = 0;   // Make Output
    TRISDbits.TRISD7 = 0;   // Make Output
    LATEbits.LATE1   = 0;   // E  = 0
    LATEbits.LATE2   = 0;   // RS = 0

        ///////////////// Reset process from datasheet //////////////

    PORTD &= 0x0F;            // Make Data pins zero
    PORTD |= 0x30;            // Write 0x3 value on data bus
    ToggleEpinOfLCD();        // Give pulse on E pin

    PORTD &= 0x0F;            // Make Data pins zero
    PORTD |= 0x30;            // Write 0x3 value on data bus
    ToggleEpinOfLCD();        // Give pulse on E pin

    PORTD &= 0x0F;            // Make Data pins zero
    PORTD |= 0x30;            // Write 0x3 value on data bus
    ToggleEpinOfLCD();        // Give pulse on E pin

    PORTD &= 0x0F;            // Make Data pins zero
    PORTD |= 0x20;            // Write 0x2 value on data bus
    ToggleEpinOfLCD();        // Give pulse on E pin

  /////////////// Reset Process End ////////////////
    WriteCommandToLCD(0x2C);    //function set  //2C ya da 2D
    WriteCommandToLCD(0x0C);    //display on,cursor off,blink off //OxOC cursor offf
    WriteCommandToLCD(0x01);    //clear display


}

/**********************************************************************
 * Copy a string of characters into the LCDchar buffer.
 *
 * @param  s         IN  string to copy into the buffer
 * @param  positionX IN  column selection
 * @param  positionY IN  line selection
 * @return void 
 **********************************************************************/
void LcdPrintString(const char *s,  unsigned char positionX, unsigned char positionY)
{
  while (*s)
  {
    LCDchar[positionY][positionX] = *s++;
    positionX++;
  }
  SetEvent(LCD_ID, LCD_EVENT);
}

/**********************************************************************
 * Convert a data (8 bits only) into a string of 2 characters.
 *
 * @param  value     IN  Value converted in string of characters
 * @param  positionX IN  column selection
 * @param  positionY IN  line selection
 * @return void
 **********************************************************************/
void LcdPrintData(unsigned char value, unsigned char positionX, unsigned char positionY)
{
  LCDchar[positionY][positionX] = 0x30 + (value / 10);
  LCDchar[positionY][positionX+1] = 0x30 + (value % 10);
  SetEvent(LCD_ID, LCD_EVENT);
}

/**********************************************************************
 * Erase the local buffer LCDchar.
 *
 * @param  void
 * @return void 
 **********************************************************************/
void ClearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
    WriteCommandToLCD(0x01);    // Clear the screen
    SetEvent(LCD_ID, LCD_EVENT);
}

/* End of File : LCD.c */