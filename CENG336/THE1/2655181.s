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
GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL barLength
GLOBAL barCounter
GLOBAL current_portB
GLOBAL latest_portB
GLOBAL pause
GLOBAL speed

; Define space for the variables in RAM
PSECT udata_acs
var1:
    DS 1 
var2:
    DS 1
var3:
    DS 1
barLength:
    DS 1
barCounter:
    DS 1
current_portB:
    DS 1
latest_portB:
    DS 1
pause:
    DS 1
speed:
    DS 1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto       main

PSECT CODE
main:
  clrf TRISA; it makes PORTA an output
  setf TRISB; it makes PORTB an input
  clrf current_portB
  clrf latest_portB
  clrf pause
  clrf var1 ; var1 = 0
  setf var2 ; var2 = 11111111B = 255
  clrf var3
  clrf barCounter
  clrf speed
  movlw 4
  movwf barLength ; default bar length
  ; to set working register WREG as a variable do the following
  movf var1, W ; WREG = var1 or you can say movf var1, 0
  ; TODO: light up LEDs
  movlw 00000011B ; light up RA1, RA2, RA3
  movwf LATA
  call busy_wait
  clrf LATA
  clrf var1
  clrf var2
main_loop:
  call check_buttons
  call metronome_update
  goto main_loop

busy_wait: 
  setf var2; var2 = 255
  clrf var1
  movlw 251
  movwf var3
most_outer_loop_start:
    outer_loop_start:
	loop_start:
	    incfsz var1 ; var1 += 1 if(var1 == 0) skip next instr
	    goto loop_start
	    ; it will be 0 because of the overflow at the end
	decf var2
	bnz outer_loop_start
incfsz var3
goto most_outer_loop_start   
return
    
check_buttons:
    movf PORTB, W
    movwf current_portB; current_portB = PORTB
    
    ;movf current_portB, W
    ;cpfseq latest_portB; check if current_portB = latest_portB
    btfsc latest_portB, 0
    call rb0_pressed ; it will be executed if they are different
      
    ;movf current_portB, W
    ;cpfseq latest_portB
    btfsc latest_portB, 1
    call rb1_pressed ; it will be executed if they are different
    
    btfsc latest_portB, 2
    call rb2_pressed
    
    btfsc latest_portB, 3
    call rb3_pressed
    
    btfsc latest_portB, 4
    call rb4_pressed
    
    movff current_portB, latest_portB ; latest_portB = current_portB
    return
    
rb4_pressed:
    btfss current_portB, 4
    call rb4_clicked
    return

rb4_clicked:
    incf barLength
    return
    
rb3_pressed:
    btfss current_portB, 3
    call rb3_clicked
    return
  
rb3_clicked:
    decf barLength
    return
    
rb2_pressed:
    btfss current_portB, 2
    call rb2_clicked
    return
    
rb2_clicked:
    movlw 4
    movwf barLength
    return
    
rb1_pressed:
    btfss current_portB, 1
    call rb1_clicked
    return
    
rb1_clicked:
    comf speed
    return
    
    
rb0_pressed:
    btfss current_portB, 0
    call rb0_clicked
    return

rb0_clicked:
    ; when pause = 0, it means resume
    btg pause, 0
    movlw 00000100B
     
    btfsc pause, 0
    movwf LATA; if pause = 1
    
    btfss pause, 0 ; if it is already paused
    bcf LATA, 2 ; clear RA2
    
    return
 
metronome_update:
    btfsc speed, 0
    movlw 2; if speed = 2x
    
    btfss speed, 0
    movlw 1 ; if speed = 1x
    
    addwf var1
    
    bc var1_overflown ; if var1 is overflown
 
    return ; otherwise return
 
var1_overflown:
    movlw 5
    addwf var2 ; var2+=4
    bc var2_overflown
    return
    
var2_overflown:
   btg LATA, 0
    
    movf barCounter, W
    bnz checkBarCounter
    btfsc LATA, 0
    bsf LATA, 1 ; if RA0 = 1
    btfss LATA, 0
    bcf LATA, 1 ; if RA0 = 0
    
    checkBarCounter:
	; check barCounter
	btfss LATA, 0
	call barCounter_update
         
    return
    
    
    
barCounter_update:
    movf barLength, W
    incf barCounter
    cpfslt barCounter
    clrf barCounter
    return
    
end resetVec
