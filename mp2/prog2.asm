; nroger5, airra2, davidrs3
; This code inputs a char from the keyboard accepting only 0-9 or
; +, - ,/ , *, ^, if none are detected it prints out invalid input
; If numerical values are read it will push them to STACk
; if operands are read it will pop numerical values and perform an operation
; after operations or values are stored it will return to receive another input
; until an equal sign is read.
; once that equal sign is read it will pop the value in the stack, if its the
;only value then it was a successful operation. if not then it was an Invalid
; operation so another invalid input will read to screen and program will HALT
; If it was a successful operation then the printing loop will convert the
; popped value to hex and output to screen.
; For you to find Multiplication loop is labeled MULT
; ADD Loop is labeled SRADD
; Subtract loop is labeled SUB
; Division loop is labeled DIV
; Power loop is labeled EXP
.ORIG x3000
 
;your code goes here
; fills for values to check whether it is a certain number or operator
EQUALS .FILL x3D
SPACE .FILL x20
NUM9 .FILL x0039
NUM8 .FILL x38
NUM7 .FILL x0037
NUM6 .FILL x36
NUM5 .FILL x35
NUM4 .FILL x34
NUM3 .FILL x33
NUM2 .FILL x32
NUM1 .FILL x31
NUM0 .FILL x30
ADDS  .FILL x2B
SUBS  .FILL x2D
MULTS  .FILL x2A
DIVS  .FILL x2F
EXPS  .FILL x5E
 
 
AND R0, R0, #0 ; initialize R0
ENTERIN IN
AND R1, R1, #0 ; initialize R1 for new input
ADD R1, R1, R0 ; set R1 to character (For Saving)
AND R2, R2, #0 ; initialize R2 for new input
ADD R2, R2, R0 ; set R2 to char (For inverting/changing)
OUT ; Prints character to Screen (ECHO)
NOT R2, R2 ;Change R2 to negative R2
ADD R2, R2, #1
LD R6, EQUALS ;load value of equals
ADD R6, R6, R2 ; add equals and negative value of input
BRz PRINT_HEX ; if its zero then it was an equals so go to printing loop
LD R6, SPACE ; load value of space
ADD R6, R6, R2 ; add space and negative value of input
BRz ENTERIN ; if space then return to get new input
 
 
 
LD R6, NUM9
ADD R6, R6, R2 ; Check if 9
BRnp CHECK8 ; if nine then = 0 si no branch and will push value of 9 to stack
; if it isnt nine it will continue to check for other valid operands
; if not another valid operand it will check for operators and if not then
; will eventually print out invalid output
AND R0, R0, #0
ADD R0, R0,#9
JSR PUSH ; push the value of 9 onto stack
BRnzp ENTERIN ; pushed value successfully and returns for a new input
; this grouping for LD num9 and checking if it is 9 is identical for the
; next groupings of code checking for all numbers 0-9
 
 
 
CHECK8 LD R6, NUM8
ADD R6, R6, R2
BRnp CHECK7 ;
 
AND R0, R0, #0
ADD R0, R0, #8
JSR PUSH
BRnzp ENTERIN
 
CHECK7 LD R6, NUM7
ADD R6, R6, R2
BRnp CHECK6
 
AND R0, R0, #0
ADD R0, R0, #7
JSR PUSH
BRnzp ENTERIN
 
CHECK6 LD R6, NUM6
ADD R6, R6, R2
BRnp CHECK5
 
AND R0, R0, #0
ADD R0, R0, #6
JSR PUSH
BRnzp ENTERIN
 
CHECK5 LD R6, NUM5
ADD R6, R6, R2
BRnp CHECK4
 
AND R0, R0, #0
ADD R0, R0, #5
JSR PUSH
BRnzp ENTERIN
 
CHECK4 LD R6, NUM4
ADD R6, R6, R2
BRnp CHECK3
AND R0, R0, #0
ADD R0, R0, #4
JSR PUSH
BRnzp ENTERIN
 
CHECK3 LD R6, NUM3
ADD R6, R6, R2
BRnp CHECK2
AND R0, R0, #0
ADD R0, R0, #3
JSR PUSH
BRnzp ENTERIN
 
CHECK2 LD R6, NUM2
ADD R6, R6, R2
BRnp CHECK1
AND R0, R0, #0
ADD R0, R0, #2
JSR PUSH
BRnzp ENTERIN
 
CHECK1 LD R6, NUM1
ADD R6, R6, R2
BRnp CHECK0
AND R0, R0, #0
ADD R0, R0, #1
JSR PUSH
BRnzp ENTERIN
 
CHECK0 LD R6, NUM0
ADD R6, R6, R2
BRnp CHECKADD
AND R0, R0, #0
ADD R0, R0, #0
JSR PUSH
BRnzp ENTERIN
 
CHECKADD LD R6, ADDS ;load value of ADD into R6
ADD R6, R6, R2 ; checks if input was add
BRnp CHECKSUB ; if not it moves to check if it was another operand
JSR SRADD ; if it is then it jumps to add subroutine
BRnzp ENTERIN ; successful sr and will return for new inputs
 
; This group is identical to other operator checks but they will use
; values for division symbol, subtraction symbol etc.
 
CHECKSUB LD R6, SUBS
ADD R6, R6, R2
BRnp CHECKMULT
JSR SUB
BRnzp ENTERIN
 
CHECKMULT LD R6, MULTS
ADD R6, R6, R2
BRnp CHECKDIV
JSR MULT
BRnzp ENTERIN
 
CHECKDIV LD R6, DIVS
ADD R6, R6, R2
BRnp CHECKPOWER
JSR DIV
BRnzp ENTERIN
 
CHECKPOWER LD R6, EXPS
ADD R6, R6, R2
BRnp PRINTINVALID
JSR EXP
BRnzp ENTERIN
 
PRINTINVALID ; this loop executes if all valid operator and operand checks
; have failed so the input was an invalid or unrecognized input
; this may also be called if there was an invalid operation such as 34+-
; for example
LEA R0, INVALIDENTRY ; loads the string where invalid input is located
PUTS
BRnzp PROGHALT ; invalid input will halt the program
 
 
 
 
 
 
 
 
 
 
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
;R3 has value inside of it. LOAD into R3 the value to be converted
; R5 is where it will be stored
CHECK
   LD R5, STACK_TOP
   LD R1, STACK_ONE
NOT R1, R1 ;
ADD R1, R1, #1 ;
ADD R5, R5, R1 ; STACK_TOP-STACK_ONE
BRnp PRINTINVALID
 
EXTRACT
AND R6, R6, #0; clear bit group counter
ADD R6, R6, #4; initialize bit group counter
AND R5, R5, #0
   JSR POP ;pop value in stack
   AND R3, R0, #0
   ADD R3, R3, R0
 
 
  RETURNHERE
  AND R5, R5, #0
AND R1, R1, #0
   ADD R1, R1, #4 ;initialize bit counter
EXTRACT_LOOP
   ADD R5, R5, R5 ;shift R5 to make room
   ADD R3, R3, #0 ;Look at R3
   BRzp SHIFT 	;if highest bit is 0, jump to SHIFT
   ADD R5, R5, #1 ;add 1 to R5
SHIFT   ADD R3, R3, R3 ;shift R3 to the left
   ADD R1, R1, #-1; decrement counter
   BRp EXTRACT_LOOP ; if there's still more
 
SECOND_HALF
AND R0, R0, #0
   ADD R0, R5, #-9 ;compare digit with 9
   BRnz PRINT_NUMERICAL ;if digit is 0-9, got to print_n
   LD R0, LETA   	;otherwise, load ASCII of 'A'
   ADD R0, R0, R5  ;R0<-R5 +'A' -10
   ADD R0, R0, #-10 ;R0 <-R5 + 'A' -10
   BRnzp DIG_LOOP_DONE ;use OUT trap
PRINT_NUMERICAL LD R0, ZERO ;Load ASCII of '0'
   ADD R0, R0, R5  ;R0<-R5 + '0'
 
DIG_LOOP_DONE
OUT ;use OUT trap
ADD R6, R6, #-1
BRp RETURNHERE
BRnzp PROGHALT
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
 
;your code goes here
 
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
SRADD
;your code goes here
ST R7, R7SAVE
AND R4, R4, #0  ; initialize R4
JSR POP
ADD R4, R4, R0  ; set R4 to the popped value
AND R5, R5, #0  ; initialize R5
JSR POP
ADD R5, R5, R0  ; set R5 to popped value
ADD R4, R4, R5  ; add the two poppe values
AND R0, R0, #0  ; reset R0
ADD R0, R4, #0  ; set R0 to the sum
AND R5, R5, #0 ; Set R5 to sum
ADD R5, R5, R0 ;
JSR PUSH
LD R7, R7SAVE   ; restore the value of R7 to jump back to the main function
RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
SUB
;your code goes here
ST R7, R7SAVE   ; store the value of R7 to return to the main function
AND R4, R4, #0  ; initialize R4
JSR POP
ADD R4, R4, R0  ; set R4 to the popped value
AND R5, R5, #0  ; initialize R5
JSR POP
ADD R5, R5, R0 ;set R5 to Popped value
ADD R4, R4, #0
BRz STORER5 ; if second value is 0 then just store R5
NOT R4, R4 ; make second value negative
ADD R4, R4, #1
ADD R5, R5, R4 ; ADD R5 and negative R4
STORER5
AND R0, R0, #0 ;set R0 to sum/ subtraction value
ADD R0, R5, #0
AND R5, R5, #0 ; Set R5 to final value
ADD R5, R5, R0
JSR PUSH
LD R7, R7SAVE
RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MULT
;your code goes here
ST R7, R7SAVE
AND R6, R6, #0 ; initialize R6
AND R4, R4, #0 ; initialize R4
JSR POP
ADD R4, R4, R0 ;Set R4 to popped value
BRz MSTORER6
AND R5, R5, #0 ; initialize R5
JSR POP
ADD R5, R5, R0 ;set R5 to Popped value
BRz MSTORER6
MLOOP ADD R6, R6, R4
ADD R5, R5, #-1 ;decrement mult counter
BRp MLOOP
MSTORER6
AND R0, R0, #0 ;set R0 to R6
ADD R0, R6, #0
AND R5, R5, #0 ; Set R5 to final value
ADD R5, R5, R0
JSR PUSH
LD R7, R7SAVE
RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
;your code goes here
ST R7, R7SAVE
 
AND R6, R6, #0 ;initialize R6 to 0
AND R4, R4, #0 ; initialize R4
JSR POP
ADD R4, R4, R0 ;Set R4 to popped value
AND R5, R5, #0 ; initialize R5
JSR POP
ADD R5, R5, R0 ;set R5 to Popped value
NOT R4, R4 ; Set R4 to negative R4
ADD R4, R4, #1
DLOOP
ADD R5, R5, R4 ;Subtract R4 from R5
ADD R6, R6, #1 ; ADD 1 to the result
ADD R5, R5, #0 ;IF R5 still 0 or positive subtract again for another division
BRzp DLOOP
ADD R6, R6, #-1 ; since it can subtract again if its zero and go negative we need to remove
;one from counter because the last division (from subtraction) had a remainder
AND R0, R0, #0 ;Set R0 to R6
ADD R0, R6, #0
AND R5, R5, #0 ; Set R5 to final value
ADD R5, R5, R0
JSR PUSH
LD R7, R7SAVE
RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
ST R7, R7SAVE
AND R6, R6, #0
AND R1, R1, #0
JSR POP ;
ADD R1, R1, R0 ; Set R1 to popped value (exponent)
AND R2, R2, #0
JSR POP ;SET R2 to second popped value (base)
ADD R2, R2, R0
AND R5, R5, #0
ADD R5, R5, R2; Set R5 = R2 (Holds base value)
AND R3, R3, #0
AND R0, R0, #0
ADD R0, R2, R0 ; set R0 to R2
AND R4, R4, #0
ADD R4, R1, #-1 ; decrement exponent value
BRz POWERSTORER6
MoLOOP
ADD R3, R3, R4
AND R6, R6, #0 ;clears location of where addition will occur in loop
MiLOOP ; adds number to itself the base value amount of times
ADD R6, R6, R5
ADD R0, R0, #-1
BRp MiLOOP
AND R5, R5, #0
ADD R5, R6, R5 ; sets R5 to be the output of the addition/mult loop
ADD R0, R2, R0 ; set R0 to R2 to reset R0 counter back to base value
ADD R4, R4, #-1 ; decrements exponent counter (amount of times to complete loop)
 
BRp MoLOOP
ADD R4, R4, #0 ; point to R4 just to get brnzp
BRnzp PSIX
POWERSTORER6 ; if exponent is equal to one this prints out base value
ADD R6, R2, #0
PSIX AND R0, R0, #0 ; this will load final value of power into R0 to push
ADD R0, R6, #0
AND R5, R5, #0 ; Set R5 to final value
ADD R5, R5, R0
JSR PUSH
LD R7, R7SAVE
RET
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
   ST R3, PUSH_SaveR3  ;save R3
   ST R4, PUSH_SaveR4  ;save R4
   AND R5, R5, #0  	;
   LD R3, STACK_END	;
   LD R4, STACk_TOP	;
   ADD R3, R3, #-1 	;
   NOT R3, R3  	;
   ADD R3, R3, #1  	;
   ADD R3, R3, R4  	;
   BRz OVERFLOW    	;stack is full
   STR R0, R4, #0  	;no overflow, store value in the stack
   ADD R4, R4, #-1 	;move top of the stack
   ST R4, STACK_TOP	;store top of stack pointer
   BRnzp DONE_PUSH 	;
OVERFLOW
   ADD R5, R5, #1  	;
DONE_PUSH
   LD R3, PUSH_SaveR3  ;
   LD R4, PUSH_SaveR4  ;
   RET
 
 
PUSH_SaveR3 .BLKW #1	;
PUSH_SaveR4 .BLKW #1	;
 
 
;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
   ST R3, POP_SaveR3   ;save R3
   ST R4, POP_SaveR4   ;save R3
   AND R5, R5, #0  	;clear R5
   LD R3, STACK_START  ;
   LD R4, STACK_TOP	;
   NOT R3, R3  	;
   ADD R3, R3, #1  	;
   ADD R3, R3, R4  	;
   BRz UNDERFLOW   	;
   ADD R4, R4, #1  	;
   LDR R0, R4, #0  	;
   ST R4, STACK_TOP	;
   BRnzp DONE_POP  	;
UNDERFLOW
   ADD R5, R5, #1  	;
   BRp PRINTINVALID ;
DONE_POP
   LD R3, POP_SaveR3   ;
   LD R4, POP_SaveR4   ;
   RET
 
   PROGHALT HALT
 
 
 
INVALIDENTRY .STRINGZ "Invalid expression"
R7SAVE .FILL X0000
ZERO .FILL #48
LETA .FILL #65
STACK_ONE .FILL x3FFF
 
 
POP_SaveR3  .BLKW #1	;
POP_SaveR4  .BLKW #1	;
STACK_END   .FILL x3FF0 ;
STACK_START .FILL x4000 ;
STACK_TOP   .FILL x4000 ;
 
 
.END

