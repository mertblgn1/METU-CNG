PROCESSOR    18F4620

#include <xc.inc>

; CONFIGURATION (DO NOT EDIT)
CONFIG OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
CONFIG FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
CONFIG IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
; CONFIG2L
CONFIG PWRT = ON        ; Power-up Timer Enable bit (PWRT enabled)
CONFIG BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
CONFIG BORV = 3         ; Brown Out Reset Voltage bits (Minimum setting)
; CONFIG2H
CONFIG WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
; CONFIG3H
CONFIG PBADEN = OFF     ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
CONFIG LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
CONFIG MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
; CONFIG4L
CONFIG LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
CONFIG XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; GLOBAL SYMBOLS
; You need to add your variables here if you want to debug them.
GLOBAL counter1
GLOBAL speed_level
GLOBAL state 
GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL current_portB
GLOBAL latest_portB   
GLOBAL current_beat
GLOBAL bar_length
GLOBAL max_speed_level
GLOBAL min_speed_level
GLOBAL temp_speed_level
GLOBAL min_bar_length
GLOBAL max_bar_length
GLOBAL temp_bar_length

; Define space for the variables in RAM
PSECT udata_acs
counter1:
  DS 1 
speed_level:
    DS 1
state: ; state = 0 means PAUSE, state = 1 means RUN
    DS 1
var1:
    DS 1
var2:
    DS 1
var3:
    DS 1
current_portB:
    DS 1
latest_portB:
    DS 1
current_beat:
    DS 1
bar_length:
    DS 1
max_speed_level:
    DS 1
min_speed_level:
    DS 1
temp_speed_level:
    DS 1
min_bar_length:
    DS 1
max_bar_length:
    DS 1
temp_bar_length:
    DS 1

PSECT CODE
org 0x0000
  goto main


org 0x0008
interrupt_service_routine:
  ; Check RB interrupt
  btfsc INTCON, 0
  goto rb_interrupt
  
  btfsc INTCON, 2
  goto timer0_interrupt
  
  btfsc PIR1, 0
  goto timer1_interrupt
  
  retfie  1                 ; No match

timer0_interrupt:
    bcf INTCON, 2 ;clear the flag
    
    ; advance current_beat by 1
    movf current_beat, 0, 0 ; WREG = current_beat
    cpfsgt bar_length
    call new_bar_begins
    incf current_beat
    
    ; light up RC0
    bsf LATC, 0
    ; turn on timer1
    bsf T1CON, 0
    
    call set_timer0
    
    retfie 1

timer1_interrupt:
    ; clear the flag
    bcf PIR1, 0
    ; load the initial value 15536
    movlw 00111100B
    movwf TMR1H
    movlw 10110000B
    movwf TMR1L
    
    clrf LATC
    
    ; turn off timer1
    bcf T1CON, 0
    retfie 1
    
rb_interrupt:
    movff PORTB, current_portB ; read PORTB
    nop ; wait 1 instruction cycle
    bcf INTCON, 0 ; clear the interrupt flag
    
    ; check which button is pressed
    
    btfsc latest_portB, 4
    call rb4_clicked
    
    btfsc latest_portB, 6
    call rb6_clicked
    
    btfsc latest_portB, 5
    call rb5_clicked
    
    btfsc latest_portB, 7
    call rb7_clicked
    
    movff current_portB, latest_portB
    retfie 1
  
main:
  clrf counter1
  clrf current_portB
  clrf latest_portB
  
  ; OUTPUT CONFIGURATION
  clrf TRISD ; set PORTD as output
  movlw 11110000B ; set RA0-RA3 as output
  movwf TRISA
  movlw 11111100 ; set RC0 and RC1 as output
  movwf TRISC
  
  ; INPUT CONFIGURATION
  movlw 11110000B ; set RB7-RB4 as input
  movwf TRISB
  
  ; INTERRUPT CONFIGURATION
  clrf INTCON
  ; enable global, peripheral and RB interrupts
  movlw 11101000B
  movwf INTCON
  movlw 10000101B
  movwf INTCON2
  
  ; enable prescaler and set it as 16 for TIMER0
  ; it is not enabled because the initial state is pause
  movlw 00000011B
  movwf T0CON
  
  ; set the timer 500ms because the speed level is 6
  call set_timer0_500ms
  
  ; enable Timer 1 and set it as high-priority
  bsf PIE1, 0
  bsf IPR1, 0
  ; enable 16-bit operation
  bsf T1CON, 7
  
  
  clrf LATA
  clrf LATB
  clrf LATC
  clrf LATD
  
  ; SET THE INITIAL VALUES OF speed levels
  movlw 6
  movwf speed_level
  movlw 9
  movwf max_speed_level
  movlw 1
  movwf min_speed_level
  clrf temp_speed_level
  
  ; set the default value of state
  clrf state
  
  ; set the default value of the bar length
  movlw 4
  movwf bar_length
  movlw 2
  movwf min_bar_length
  movlw 8
  movwf max_bar_length
  
  ; set the initial value of the current beat
  movlw 1
  movwf current_beat
  
main_loop:
  btfss state, 0
  call pause
  
  btfsc state, 0
  call run
  
  goto main_loop

rb4_clicked:
    btg state, 0
    ; enable/disable the timer0
    btg T0CON, 7
    
    ; disable the timer1
    bcf T1CON, 0
       
    ; set current beat to 1
    movlw 1
    movwf current_beat
    
    ; if it is the first run, light up RC0 and RC1
    btfsc state, 0
    call first_run
 
    return
    
rb5_clicked:
    btfss state, 0
    call rb5_clicked_in_pause
    
    btfsc state, 0
    call rb5_clicked_in_run
       
    return
    
rb6_clicked:
    btfss state, 0
    call rb6_clicked_in_pause
    
    btfsc state, 0
    call rb6_clicked_in_run
    
    return
    
rb7_clicked:
    btfss state, 0
    call rb7_clicked_in_pause
    
    btfsc state, 0
    call rb7_clicked_in_run
    
    return

run:
    ; display current beat and wait 1ms
    call display_current_beat
    call busy_wait
    call busy_wait
    ; display a dash and wait 1ms
    call display_dash
    call busy_wait
    call busy_wait
    ; display the bar length and wait 1ms
    call display_bar_length
    call busy_wait
    call busy_wait
    
    return
    
pause:
    ; display P and display_level
    call displayP
    ; wait 1ms
    call busy_wait
    call busy_wait
    call display_speed_level 
    ; wait 1ms
    call busy_wait
    call busy_wait
    
    return
 
display_speed_level:
    ; bsf LATA, 3
    movlw 00001000B
    movwf LATA
    
    movf speed_level, 0, 0
    sublw 1
    btfsc STATUS, 2
    call display1
    
    movf speed_level, 0, 0
    sublw 2
    btfsc STATUS, 2
    call display2
    
    movf speed_level, 0, 0
    sublw 3
    btfsc STATUS, 2
    call display3
    
    movf speed_level, 0, 0
    sublw 4
    btfsc STATUS, 2
    call display4
    
    movf speed_level, 0, 0
    sublw 5
    btfsc STATUS, 2
    call display5
    
    movf speed_level, 0, 0
    sublw 6
    btfsc STATUS, 2
    call display6
    
    movf speed_level, 0, 0
    sublw 7
    btfsc STATUS, 2
    call display7
    
    movf speed_level, 0, 0
    sublw 8
    btfsc STATUS, 2
    call display8
    
    movf speed_level, 0, 0
    sublw 9
    btfsc STATUS, 2
    call display9
    
    return
    
display_current_beat:
    movlw 00000010B
    movwf LATA
    
    movf current_beat, 0, 0
    sublw 1
    btfsc STATUS, 2
    call display1
    
    movf current_beat, 0, 0
    sublw 2
    btfsc STATUS, 2
    call display2
    
    movf current_beat, 0, 0
    sublw 3
    btfsc STATUS, 2
    call display3
    
    movf current_beat, 0, 0
    sublw 4
    btfsc STATUS, 2
    call display4
    
    movf current_beat, 0, 0
    sublw 5
    btfsc STATUS, 2
    call display5
    
    movf current_beat, 0, 0
    sublw 6
    btfsc STATUS, 2
    call display6
    
    movf current_beat, 0, 0
    sublw 7
    btfsc STATUS, 2
    call display7
    
    movf current_beat, 0, 0
    sublw 8
    btfsc STATUS, 2
    call display8
    
    return
    
display_bar_length:
    movlw 00001000B
    movwf LATA
    
    movf bar_length, 0, 0
    sublw 2
    btfsc STATUS, 2
    call display2
    
    movf bar_length, 0, 0
    sublw 3
    btfsc STATUS, 2
    call display3
    
    movf bar_length, 0, 0
    sublw 4
    btfsc STATUS, 2
    call display4
    
    movf bar_length, 0, 0
    sublw 5
    btfsc STATUS, 2
    call display5
    
    movf bar_length, 0, 0
    sublw 6
    btfsc STATUS, 2
    call display6
    
    movf bar_length, 0, 0
    sublw 7
    btfsc STATUS, 2
    call display7
    
    movf bar_length, 0, 0
    sublw 8
    btfsc STATUS, 2
    call display8
    
    return
 
busy_wait:
    movlw 100
    movwf var1 
	
    loop_start:
	incfsz var1
	goto loop_start
	
    return
 
display_dash:
    movlw 00000100B
    movwf LATA
    movlw 01000000B
    movwf LATD
    
    return
    
displayP:
    movlw 00000001B
    movwf LATA
    movlw 01110011B
    movwf LATD
    
    return
 
display1:
    movlw 00000110B
    movwf LATD
    return
    
display2:
    movlw 01011011B
    movwf LATD
    return
    
display3:
    movlw 01001111B
    movwf LATD
    return
    
display4:
    movlw 01100110B
    movwf LATD
    return
    
display5:
    movlw 01101101B
    movwf LATD
    return
    
display6:
    movlw 01111101B
    movwf LATD
    return
    
display7:
    movlw 00000111B
    movwf LATD
    return
    
display8:
    movlw 01111111B
    movwf LATD
    return
    
display9:
    movlw 01101111B
    movwf LATD
    return
    
set_timer0:
    ; if speed level is 1
    movf speed_level, 0, 0
    sublw 1
    btfsc STATUS, 2
    call set_timer0_1000ms
    
    ; if speed level is 2
    movf speed_level, 0, 0
    sublw 2
    btfsc STATUS, 2
    call set_timer0_900ms
    
    ; if speed level is 3
    movf speed_level, 0, 0
    sublw 3
    btfsc STATUS, 2
    call set_timer0_800ms
    
    ; if speed level is 4
    movf speed_level, 0, 0
    sublw 4
    btfsc STATUS, 2
    call set_timer0_700ms
    
    ; if speed level is 5
    movf speed_level, 0, 0
    sublw 5
    btfsc STATUS, 2
    call set_timer0_600ms
    
    ; if speed level is 6
    movf speed_level, 0, 0
    sublw 6
    btfsc STATUS, 2
    call set_timer0_500ms
    
    ; if speed level is 7
    movf speed_level, 0, 0
    sublw 7
    btfsc STATUS, 2
    call set_timer0_400ms
    
    ; if speed level is 8
    movf speed_level, 0, 0
    sublw 8
    btfsc STATUS, 2
    call set_timer0_300ms
    
    ; if speed level is 9
    movf speed_level, 0, 0
    sublw 9
    btfsc STATUS, 2
    call set_timer0_200ms
    
    return
    
set_timer0_1000ms:
    movlw 00001011B
    movwf TMR0H
    movlw 11011100B
    movwf TMR0L   
    return
    
set_timer0_900ms:
    movlw 00100100B
    movwf TMR0H
    movlw 01000110B
    movwf TMR0L
    return
    
set_timer0_800ms:
    movlw 00111100B
    movwf TMR0H
    movlw 10110000B
    movwf TMR0L
    return
    
set_timer0_700ms:
    movlw 01010101B
    movwf TMR0H
    movlw 00011010B
    movwf TMR0L
    return
    
set_timer0_600ms:
    movlw 01101101B
    movwf TMR0H
    movlw 10000100B
    movwf TMR0L
    return
    
set_timer0_500ms:
    movlw 10000101B
    movwf TMR0H
    movlw 11101110B
    movwf TMR0L
    return
    
set_timer0_400ms:
    movlw 10011110B
    movwf TMR0H
    movlw 01011000B
    movwf TMR0L
    return
    
set_timer0_300ms:
    movlw 10110110B
    movwf TMR0H
    movlw 11000010B
    movwf TMR0L   
    return
    
set_timer0_200ms:
    movlw 11001111B
    movwf TMR0H
    movlw 00101100B
    movwf TMR0L
    return
    
rb5_clicked_in_pause:
    movf speed_level, 0, 0
    addlw 1
    cpfslt max_speed_level
    incf speed_level
    
    ; set timer0 accordingly
    ; because the speed is changed
    call set_timer0
    return
    
rb6_clicked_in_pause:
    movff speed_level, temp_speed_level
    decf temp_speed_level
    movf temp_speed_level, 0, 0
    cpfsgt min_speed_level
    decf speed_level
    
    ; set timer0 accordingly
    ; because the speed is changed
    call set_timer0
    return
    
rb7_clicked_in_pause:
    movlw 6
    movwf speed_level
    return
    
rb5_clicked_in_run:
    movf bar_length, 0, 0
    addlw 1
    cpfslt max_bar_length
    incf bar_length
    
    return
    
rb6_clicked_in_run:
    movff bar_length, temp_bar_length
    decf temp_bar_length
    movf temp_bar_length, 0, 0
    cpfsgt min_bar_length
    decf bar_length
    
    return
    
rb7_clicked_in_run:
    movlw 4
    movwf bar_length
    return
    
new_bar_begins:
    clrf current_beat
    ; light up RC1
    bsf LATC, 1
    ; turn on timer1
    bsf T1CON, 0
    return

first_run:
    movlw 00000011B
    movwf LATC
    bsf T1CON, 0
    return
    