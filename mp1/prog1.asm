;
; The code given to you here implements the histogram calculation that
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of
; code to print the histogram to the monitor.
;
; If you finish your program,
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string
; terminated by a NUL character.  Lower case and upper case should
; be counted together, and a count also kept of all non-alphabetic
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance)
; should be stored starting at x3F00, with the non-alphabetic count
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram

	; fill the histogram with zeroes
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; To print the histogram the code from lab1 which converts binary into hexadecimal characters
;had to be implemented and edited into the code given from mp1. Lab1 code had to be changed
;by adding a loop and two counters in which after printing the first four hexadecimal characters,
;the program would return to printing the next line and then printing the next character by adding
;to the label AT (which represents ‘@’” ) and then printing a space. To print the next count of
;characters we added to the pointer (which pointed to where the address for the start of the
;histogram was) and then made sure to return back and convert the memory at that new
;address into hexadecimal and print those characters out and then repeat until all 27 characters
;have been printed with their corresponding counts.
;partners: airra2, nroger5
;use of registers in this part of the code


;use of registers in this part of the code
;R0 used for outputs
;R1 bit counter
;R2 destination register / TEMP A mem storage
;R3 holds the current address of the histogram / TEMP increment storage
;R4 Address of data
;R5 Bit Group counter (4)
;R6 loop counter (holds 27)



AND R6, R6, #0; clear the bin counter
ADD R6, R6, #13; set the bin counter to 27
ADD R6, R6, #14; set the bin counter to 27

OUTER
	LD R4, HIST_ADDR ; load the histogram address into R4
	LD R3, ADDA ; use the value stored in memory to update R4
	ADD R4, R4, R3; add the value stored in memory to R4

	LD R2, AT ; intially loads the ascii @ into R2 to print
	LD R3, ADDA ; used to increment the ASCII character the program will print
	ADD R0, R3, R2; set R0 equal to the character value to output
	OUT
	LD R0, SPACE ;	set R0 to space so it can be outputted
	OUT
	LDR R3, R4, #0; load the value held in memory at R4 into R3

	AND R2, R2, #0; clear destination
	AND R1, R1, #0; clear bit counter
	ADD R1, R1, #4; initialize bit counter

EXTRACT
	AND R5, R5, #0; clear bit group counter
	ADD R5, R5, #4; initialize bit group counter

EXTRACT_LOOP
	ADD R2, R2, R2 ;shift R2 to make space for next bit
	ADD R3, R3, #0 ;Look at R3
	BRzp SHIFT 	;if highest bit is 0, jump to SHIFT
	ADD R2, R2, #1 ;add 1 to R2
	SHIFT   ADD R3, R3, R3 ;shift R3 to the left
	ADD R1, R1, #-1; decrement counter
	BRp EXTRACT_LOOP ; if there's still more bits
SECOND_HALF
	ADD R0, R2, #-9 ;compare digit with 9
	BRnz PRINT_NUMERICAL ;if digit is 0-9, got to print_numerical
	LD R0, A   	;otherwise, load ASCII of 'A'
	ADD R0, R0, R2  ;R0<-R2 +'A' -10
	ADD R0, R0, #-10 ;R0 <-R2 + 'A' -10
	BRnzp DIG_LOOP_DONE ;use OUT trap
PRINT_NUMERICAL
	LD R0, ZERO ;Load ASCII of '0'
	ADD R0, R0, R2 ;R0<-R2 + '0'
	DIG_LOOP_DONE OUT ;use OUT trap


;ADDITION AFTER

	AND R2, R2, #0; clear destination
	AND R1, R1, #0; clear bit counter
	ADD R1, R1, #4; initialize bit counter to 4
	ADD R5, R5, #-1
	BRp EXTRACT_LOOP ; as long as R5 is positive go back to convert the next four bits
	LD R0, NEXT_LINE ; load a new line character into R0
	OUT

	LD R0, ADDA ; load the value held in this label to R0
	ADD R0, R0, #1 ; increment the value in R0
	ST R0, ADDA ; store the value in R0 into memory at label ADDA, allows a counter to be kept while not wasting a register
	ADD R6, R6, #-1 ; decrement the loop counter for the number of bins
	BRp OUTER ; if the loop counter is still positive restart the process of printing out letters with their numbers
	ADD R6, R6, #0 ; perform a negligible function on R6 so that the branch can operate on it
	BRnz DONE ; if R6 is 0, end the program.
;ADDITION AFTER END


AT	  .FILL #64
A	  .FILL #65
ZERO 	  .FILL #48
SPACE   .FILL #32
NEXT_LINE .FILL x000A
ADDA .FILL x0000

DONE	HALT			; done


; the data needed by the program
FIRST_CHAR .FILL #64; first character needed to be read
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
