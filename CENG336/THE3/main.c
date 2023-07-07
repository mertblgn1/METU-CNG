// Group-70
// Member1: Mert Can Bilgin - 2655181
// Member2: Sena Nur Şengül - 2310498

#include "lcd.h"
#include "the3.h"
#include <stdio.h>

// 0 for 400ms, 1 for 800ms, 2 for 1200ms and 3 for 1600ms
volatile unsigned short interval;
volatile char CONVERT = 0;
unsigned short frisbee_blink=0;
// Initial coordinates of frisbee
volatile unsigned short frisbee_x = 9;
volatile unsigned short frisbee_y = 2;
volatile unsigned short frisbee_target_x;
volatile unsigned short frisbee_target_y;

// Initial coordinates of teamA
volatile unsigned short teamA_player1_x = 3;
volatile unsigned short teamA_player1_y = 2;
volatile unsigned short teamA_player2_x = 3;
volatile unsigned short teamA_player2_y = 3;

// Initial coordinates of teamB
volatile unsigned short teamB_player1_x = 14;
volatile unsigned short teamB_player1_y = 2;
volatile unsigned short teamB_player2_x = 14;
volatile unsigned short teamB_player2_y = 3;

// condition variables
unsigned int portBpressed = 0;
enum game_mode {
    INACTIVE_MODE, ACTIVE_MODE
};
enum game_mode current_mode = INACTIVE_MODE;

unsigned short player_holds_frisbee = 0;
volatile unsigned short teamA_score = 0;
volatile unsigned short teamB_score = 0;
// 0 and 1 for teamA, 2 and 3 for teamB
volatile int player_selected;

void displayInitialConfiguration();
void initADC();
void init_interrupts();
void init_ports();
void movePlayer(short, short);
void moveFrisbee();
void updateDisplay();
void moveRandomPlayer();
void updateScore();
void displayOn7Segment(unsigned short);
void update7Segment();
void clearDisplay();
void __interrupt() isr(void);

int main()
{
    RCON = 0;
    INTCON = 0;
    initADC();
    InitLCD();
    displayInitialConfiguration();
    init_interrupts();
    init_ports();
    RBIE = 0;
    INT0IE = 0;
    GIE = 1;
    PORTB = PORTB;
    RBIF = 0;
    INT0IF = 0;
    RBIE = 1;
    INT0IE = 1;
    //RBIE = 1;
    //RBIF = 0;
    //INT0IF = 0;

    // Enable Timer1 to generate random numbers
    T1CONbits.TMR1ON = 1;
    //T1CONbits.RD16 = 1;
    // Set Timer0 with prescaler 16
    T0CON = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;
    // Preload the timer
    TMR0H = (3036 >> 8) & 0xFF;
    TMR0L = 3036 & 0xFF;
    
    while(1){
        update7Segment();
    };

    return 0;
}

void __interrupt() isr(void)
{
    unsigned short current_portB, latest_portB;
    current_portB = PORTB;
    update7Segment();
    // __delay_ms(25);
    update7Segment();
    if (TMR0IF)
    {
        TMR0IF = 0; // Clear Timer0 interrupt flag
        
        // Preload the timer
        TMR0H = (3036 >> 8) & 0xFF;
        TMR0L = 3036 & 0xFF;
        if(frisbee_blink % 2 == 0) {
            LATA = 0;
            LCDGoto(frisbee_target_x, frisbee_target_y);
            LCDDat(7);
            update7Segment();
        } else {
            LATA = 0;
            LCDGoto(frisbee_target_x, frisbee_target_y);
            LCDStr(" ");
            update7Segment();
        }
        frisbee_blink++;   
    }
    
    if (PIR1bits.ADIF)
    {
        unsigned short convertion_value;
        convertion_value = ADRESH << 8 | ADRESL;
        if(convertion_value >= 0 && convertion_value < 256) {
            interval = 0;
        } else if (convertion_value < 512) {
            interval = 1;
        } else if (convertion_value < 768) {
            interval = 2;
        } else if (convertion_value < 1024) {
            interval = 3;
        }
        PIR1bits.ADIF = 0; // Clear ADC interrupt flag
        //ADCON0bits.GO = 1; // Start next ADC conversion
    }
    
    if(INTCONbits.INT0IF == 1){
        CONVERT = 1;
        INTCONbits.INT0IF = 0;
        __delay_ms(100);
        if(current_mode == INACTIVE_MODE){
            // check for Team A players
            if(player_selected == 0 && frisbee_x == teamA_player1_x && frisbee_y == teamA_player1_y){
                current_mode = ACTIVE_MODE;
                moveFrisbee();
            }
            if(player_selected == 1 && frisbee_x == teamA_player2_x && frisbee_y == teamA_player2_y){
                current_mode = ACTIVE_MODE;
                moveFrisbee();
            }
            // check for Team B players
            if(player_selected == 2 && frisbee_x == teamB_player1_x && frisbee_y == teamB_player1_y){
                current_mode = ACTIVE_MODE;
                moveFrisbee();
            }
            if(player_selected == 3 && frisbee_x == teamB_player2_x && frisbee_y == teamB_player2_y){
                current_mode = ACTIVE_MODE;
                moveFrisbee();
            }
            updateScore();
        }
        updateDisplay();
        update7Segment();
    }

    // RB1
    if(INTCON3bits.INT1IF){
        //INT1IE = 0;
        update7Segment();
        __delay_ms(100);
        INTCON3bits.INT1IF = 0;
        //if(latest_portB & 0xFD == 0xFD){
        if(!(current_mode == INACTIVE_MODE && player_holds_frisbee)){
            // Clear old selected player
            if(player_selected == 0){
                LATA = 0;
                LCDGoto(teamA_player1_x, teamA_player1_y);
                LCDDat(0);
                update7Segment();
            } else if(player_selected == 1) {
                LATA = 0;
                LCDGoto(teamA_player2_x, teamA_player2_y);
                LCDDat(0);
                update7Segment();
            } else if(player_selected == 2) {
                LATA = 0;
                LCDGoto(teamB_player1_x, teamB_player1_y);
                LCDDat(1);
                update7Segment();
            } else if(player_selected == 3) {
                LATA = 0;
                LCDGoto(teamB_player2_x, teamB_player2_y);
                LCDDat(1);
                update7Segment();
            }
            player_selected = player_selected + 1;
            player_selected = player_selected % 4;
            // Display new selected player
            if(player_selected == 0){
                LATA = 0;
                LCDGoto(teamA_player1_x, teamA_player1_y);
                LCDDat(2);
                update7Segment();
            } else if(player_selected == 1) {
                LATA = 0;
                LCDGoto(teamA_player2_x, teamA_player2_y);
                LCDDat(2);
                update7Segment();
            } else if(player_selected == 2) {
                LATA = 0;
                LCDGoto(teamB_player1_x, teamB_player1_y);
                LCDDat(3);
                update7Segment();
            } else if(player_selected == 3) {
                LATA = 0;
                LCDGoto(teamB_player2_x, teamB_player2_y);
                LCDDat(3);
                update7Segment();
            }
            updateDisplay();
        }
        //}
        //latest_portB = current_portB;
    }

    // PORT B
    if(INTCONbits.RBIF){
        update7Segment();
        INTCONbits.RBIF = 0;
        // Check which RB caused interrupt
        //__delay_ms(20);
        if(!PORTBbits.RB6){
            __delay_ms(100);
            movePlayer(0, 1);
        } else if(!PORTBbits.RB7){
            __delay_ms(100);
            movePlayer(-1, 0);
        } else if(!PORTBbits.RB5){
            __delay_ms(100);
            movePlayer(1, 0);
        } else if(!PORTBbits.RB4){
            __delay_ms(100);
            movePlayer(0, -1);
        }
        update7Segment();
        updateDisplay();
    }

}

void moveFrisbee()
{
    unsigned short number_of_steps;
    number_of_steps = compute_frisbee_target_and_route(frisbee_x, frisbee_y);
    unsigned short i = 0;
    RBIE = 0;
    GIE = 1;
    RBIF = 0;
    RBIE = 1;
    // get the frisbee's target coordinates to display
    frisbee_target_x = frisbee_steps[number_of_steps - 1][0];
    frisbee_target_y = frisbee_steps[number_of_steps - 1][1];
    // Turn on timer0
    TMR0ON = 1;
    for(i; i < number_of_steps; i++){
        // Update LCD for frisbee's old coordinate
        if(i == 0){
            if(player_selected == 0){
                LATA = 0;
                LCDGoto(teamA_player1_x, teamA_player1_y);
                LCDDat(2);
            } else if(player_selected == 1) {
                LATA = 0;
                LCDGoto(teamA_player2_x, teamA_player2_y);
                LCDDat(2);
            } else if(player_selected == 2) {
                LATA = 0;
                LCDGoto(teamB_player1_x, teamB_player1_y);
                LCDDat(3);
            } else if(player_selected == 3) {
                LATA = 0;
                LCDGoto(teamB_player2_x, teamB_player2_y);
                LCDDat(3);
            }
        } else {
            LATA = 0;
            LCDGoto(frisbee_x, frisbee_y);
            LCDStr(" ");
        }
        update7Segment();
        frisbee_x = frisbee_steps[i][0];
        frisbee_y = frisbee_steps[i][1];
        // Display new coordinates
        //updateDisplay();
        LATA = 0;
        LCDGoto(frisbee_x, frisbee_y);
        LCDDat(6);
        update7Segment();
        moveRandomPlayer();
        updateDisplay();
        if(i == number_of_steps)
            updateScore();
        
        if(interval == 0) {
            __delay_ms(400);
        } else if (interval == 1) {
            __delay_ms(800);
        } else if (interval == 2) {
            __delay_ms(1200);
        } else if (interval == 3) {
            __delay_ms(1600);
        }
        update7Segment();
        // Start next acquisition
        ADCON0bits.GO = 1;
        //updateDisplay();
    }

    // Update the game mode at the last step
    if(frisbee_x == frisbee_target_x && frisbee_y == frisbee_target_y) {
        current_mode = INACTIVE_MODE;
        // Turn off TMR0
        TMR0ON = 0;
    }
    clearDisplay();
}

void movePlayer(short dx, short dy)
{
    unsigned short new_x, new_y;

    // Determine the requested coordinate
    if (player_selected == 0) {
        new_x = teamA_player1_x + dx;
        new_y = teamA_player1_y + dy;
        update7Segment();
    } else if (player_selected == 1) {
        new_x = teamA_player2_x + dx;
        new_y = teamA_player2_y + dy;
        update7Segment();
    } else if (player_selected == 2) {
        new_x = teamB_player1_x + dx;
        new_y = teamB_player1_y + dy;
        update7Segment();
    } else if (player_selected == 3) {
        new_x = teamB_player2_x + dx;
        new_y = teamB_player2_y + dy;
        update7Segment();
    }

    // Check if the new position is valid and does not contain another player
    if (new_x >= 1 && new_x <= 16 && new_y >= 1 && new_y <= 4 &&
        (new_x != teamA_player1_x || new_y != teamA_player1_y) &&
        (new_x != teamA_player2_x || new_y != teamA_player2_y) &&
        (new_x != teamB_player1_x || new_y != teamB_player1_y) &&
        (new_x != teamB_player2_x || new_y != teamB_player2_y)) {

        // Move the player to the new position
        if (player_selected == 0) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamA_player1_x, teamA_player1_y);
            LCDStr(" ");
            teamA_player1_x = new_x;
            teamA_player1_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(2);
            update7Segment();
        } else if (player_selected == 1) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamA_player2_x, teamA_player2_y);
            LCDStr(" ");
            teamA_player2_x = new_x;
            teamA_player2_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(2);
            update7Segment();
        } else if (player_selected == 2) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamB_player1_x, teamB_player1_y);
            LCDStr(" ");
            teamB_player1_x = new_x;
            teamB_player1_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(3);
            update7Segment();
        } else if (player_selected == 3) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamB_player2_x, teamB_player2_y);
            LCDStr(" ");
            teamB_player2_x = new_x;
            teamB_player2_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(3);
            update7Segment();
        }
    }
    update7Segment();
    updateDisplay();
}

void init_interrupts()
{
    INTCON = 0x78;

    // set timer0 and RB as high priority interrupt
    INTCON2 = 0x00;
    INTCON2bits.TMR0IP = 1;
    INTCON2bits.RBIP = 1;
    INTCON2bits.RBPU = 1;

    // RB1
    INTCON3 = 0x00;
    INTCON3bits.INT1E = 1;
    //INTCON3bits.INT1IP = 1;
    
    // Enable A/D conversion
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;
}

void init_ports()
{
    TRISB = 0xFF;
    TRISA = 0x00;
}

void displayInitialConfiguration()
{
    // Define the 8 custom characters
    LATA = 0;
    LCDAddSpecialCharacter(0, teamA_player);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(1, teamB_player);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(2, selected_teamA_player);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(3, selected_teamB_player);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(4, selected_teamA_player_with_frisbee);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(5, selected_teamB_player_with_frisbee);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(6, frisbee);
    update7Segment();
    LATA = 0;
    LCDAddSpecialCharacter(7, frisbee_target);
    update7Segment();

    player_selected = 0;
    // player1 of teamA
    LATA = 0;
    LCDGoto(3,2);
    LCDDat(2);
    update7Segment();
    // player2 of teamA
    LATA = 0;
    LCDGoto(3,3);
    LCDDat(0);
    update7Segment();
    // player1 of teamB
    LATA = 0;
    LCDGoto(14,2);
    LCDDat(1);
    update7Segment();
    // player2 of team B
    LATA = 0;
    LCDGoto(14,3);
    LCDDat(1);
    update7Segment();
    // frisbee
    LATA = 0;
    LCDGoto(9,2);
    LCDDat(6);
    update7Segment();
}

void initADC()
{
    // AN1, AN2 and AN3 are configured as analog
    ADCON1 = 0x0C;

    // set RA0, RA1, RA2 as input
    TRISA = 0x07;

    // for 10MHZ -> Tosc = 1/10 us
    // min Tad 0.7 us - max 25 us
    // The closest one to min is 8*Tosc = 0.8
    // minimum acquisition time we can set = 4*Tad = 3.2
    ADCON2 = 0x91;

    // ADC is enabled
    ADCON0 = 0x01;
    ADCON0bits.GO = 1;
}

void updateDisplay()
{
    for (unsigned short y = 1; y < 5; y++) {
        for (unsigned short x = 1; x < 17; x++) {
            if (x == frisbee_x && y == frisbee_y) {
                LATA = 0;
                LCDGoto(x, y);  // Set the cursor position
                if(x == teamA_player1_x && y == teamA_player1_y && player_selected == 0) {
                    LCDDat(4);
                } else if(x == teamA_player2_x && y == teamA_player2_y && player_selected == 1) {
                    LCDDat(4);
                } else if(x == teamB_player1_x && y == teamB_player1_y && player_selected == 2) {
                    LCDDat(5);
                } else if(x == teamB_player2_x && y == teamB_player2_y && player_selected == 3) {
                    LCDDat(5);
                } else {
                    LCDDat(6);  // Display frisbee
                }
                update7Segment();
            } else if (x == frisbee_target_x && y == frisbee_target_y && current_mode == ACTIVE_MODE){
                LATA = 0;
                LCDGoto(x, y);  // Set the cursor position
                LCDDat(7);
                update7Segment();
            }
        }
        update7Segment();
    }
}

void moveRandomPlayer()
{
    // Generate a random movement direction using the random_generator() function
    unsigned short random_direction;

    // Determine the movement offsets based on the random direction
    short dx = 0, dy = 0;

    unsigned short new_x, new_y;

    int i;
    for(i = 0; i < 4; i++){
        random_direction = random_generator(9);
        update7Segment();
        switch (random_direction) {
        case 0: // Move up
            dx = 0;
            dy = -1;
            break;
        case 1: // Move right
            dx = 1;
            dy = 0;
            break;
        case 2: // Move down
            dx = 0;
            dy = 1;
            break;
        case 3: // Move left
            dx = -1;
            dy = 0;
            break;
        case 4: // Move up-right crossing cell
            dx = 1;
            dy = -1;
            break;
        case 5: // Move down-right crossing cell
            dx = 1;
            dy = 1;
            break;
        case 6: // Move down-left crossing cell
            dx = -1;
            dy = 1;
            break;
        case 7: // Move up-left crossing cell
            dx = -1;
            dy = -1;
            break;
        case 8: // No move
            break;
    }

    // Determine the current player's coordinates based on player_selected
    if(i == 0 && player_selected != 0){
        new_x = teamA_player1_x + dx;
        new_y = teamA_player1_y + dy;
    } else if (i == 1 && player_selected != 1) {
        new_x = teamA_player2_x + dx;
        new_y = teamA_player2_y + dy;
    } else if(i == 2 && player_selected != 2) {
        new_x = teamB_player1_x + dx;
        new_y = teamB_player1_y + dy;
    } else if(i == 3 && player_selected != 3) {
        new_x = teamB_player2_x + dx;
        new_y = teamB_player2_y + dy;
    }
        update7Segment();
    // Check if the new position is valid and does not contain another player
    if ((new_x >= 1 && new_x <= 16 && new_y >= 1 && new_y <= 4) &&
        (new_x != teamA_player1_x || new_y != teamA_player1_y) &&
        (new_x != teamA_player2_x || new_y != teamA_player2_y) &&
        (new_x != teamB_player1_x || new_y != teamB_player1_y) &&
        (new_x != teamB_player2_x || new_y != teamB_player2_y) &&
        (new_x != frisbee_x || new_y != frisbee_y)) {

        // Move the player to the new position
        if (i == 0 && player_selected != 0) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamA_player1_x, teamA_player1_y);
            LCDStr(" ");
            teamA_player1_x = new_x;
            teamA_player1_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(0);
            update7Segment();
        } else if(i == 0 && player_selected == 0){
            // Display selected player
            LATA = 0;
            LCDGoto(teamA_player1_x, teamA_player1_y);
            LCDDat(2);
            update7Segment();
        } else if (i == 1 && player_selected != 1) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamA_player2_x, teamA_player2_y);
            LCDStr(" ");
            teamA_player2_x = new_x;
            teamA_player2_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(0);
            update7Segment();
        } else if(i == 1 && player_selected == 1){
            // Display selected player
            LATA = 0;
            LCDGoto(teamA_player2_x, teamA_player2_y);
            LCDDat(2);
            update7Segment();
        } else if (i == 2 && player_selected != 2) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamB_player1_x, teamB_player1_y);
            LCDStr(" ");
            teamB_player1_x = new_x;
            teamB_player1_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(1);
            update7Segment();
        } else if(i == 2 && player_selected == 2){
            // Display selected player
            LATA = 0;
            LCDGoto(teamB_player1_x, teamB_player1_y);
            LCDDat(3);
            update7Segment();
        } else if (i == 3 && player_selected != 3) {
            // Update LCD, delete the last position
            LATA = 0;
            LCDGoto(teamB_player2_x, teamB_player2_y);
            LCDStr(" ");
            teamB_player2_x = new_x;
            teamB_player2_y = new_y;
            update7Segment();
            // Update new location on LCD
            LATA = 0;
            LCDGoto(new_x, new_y);
            LCDDat(1);
            update7Segment();
        } else if(i == 3 && player_selected == 3){
            // Display selected player
            LATA = 0;
            LCDGoto(teamB_player2_x, teamB_player2_y);
            LCDDat(3);
            update7Segment();
        }
    }
        update7Segment();
    }
    //update7Segment();
    // updateDisplay();
}

void updateScore()
{
    if(player_selected == 0){
        if(teamA_player1_x == frisbee_target_x && teamA_player1_y == frisbee_target_y)
            teamA_score++;
    } else if(player_selected == 1) {
        if(teamA_player2_x == frisbee_target_x && teamA_player2_y == frisbee_target_y)
            teamA_score++;
    } else if(player_selected == 2) {
        if(teamB_player1_x == frisbee_target_x && teamB_player1_y == frisbee_target_y)
            teamB_score++;
    } else if(player_selected == 3) {
        if(teamB_player2_x == frisbee_target_x && teamB_player2_y == frisbee_target_y)
            teamB_score++;
    }
}

void displayOn7Segment(unsigned short x)
{
    switch(x) {
        case 0:
            LATD = 0x3F;
            break;
        case 1:
            LATD = 0x06;
            break;
        case 2:
            LATD = 0x5B;
            break;
        case 3:
            LATD = 0x4F;
            break;
        case 4:
            LATD = 0x66;
            break;
        case 5:
            LATD = 0x6B;
            break;
        case 6:
            // display dash
            LATD = 0x40;
            break;
        default:
            break;
    }
}

void update7Segment()
{
    LATA = 0x08;
    displayOn7Segment(teamA_score);
    // wait some time
    __delay_ms(1);
    LATA = 0x10;
    // display dash
    displayOn7Segment(6);
    __delay_ms(1);
    LATA = 0x20;
    displayOn7Segment(teamB_score);
    __delay_ms(1);
}

void clearDisplay()
{
    unsigned short x, y;
    for(y = 1; y < 5; y++) {
        for(x = 1; x < 17; x++){
            if(!(x == teamA_player1_x && y == teamA_player1_y) &&
               !(x == teamA_player2_x && y == teamA_player2_y) &&
               !(x == teamB_player1_x && y == teamB_player1_y) &&
               !(x == teamB_player2_x && y == teamB_player2_y) &&
               !(x == frisbee_x && y == frisbee_y) &&
               !(x == frisbee_target_x && y == frisbee_target_y)) {
                LATA = 0;
                LCDGoto(x, y);
                LCDStr(" ");
            }
        }
        update7Segment();
    }
}

