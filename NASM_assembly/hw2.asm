
	; Name: Subhei Shaar
	; Creation date: 1/22/2015
	; Last modified: 1/23/2015 20:00
	;
	; 
	; Name of file: hw2.asm
	;
	; Description: Do basic maths with two integers that the user enters. 
	;				Bonus: continue program until user quits
	;				Bonus: Validate 2nd number to be less than the first
	;	
	; Assemble:	nasm -f elf -l hw2.lst  hw2.asm
	; Link:		gcc -o hw2  hw2.o
	; Run:		hw2
	; Output:  sum, subtraction,multiplication, quotient,remainder of two integers
	;			standard format for the arithmetic:  int1 (operator) int2


	
	
	
	extern printf								; the C function, to be called
	extern scanf								; C user input function
	
	
	

SECTION .data									; Data section, initialized variables



	intro_one:  db "Subhei Shaar", 10, 0 		; The printf format, "\n",'0'  	NAME
	intro_two:  db "Homework 2", 10, 0 			; The printf format, "\n",'0'	ASSIGNMENT
	
	instruction: db "Enter in two integer values", 10, 0  ; The printf format, "\n",'0'
	
	continue: db "Enter in '1' to quit", 10, 0
	
	
	input: db "%d %d",0			 				; the scanf format
	input1: db "%d",0			 				; the scanf format
	
	values: db "Addition: %d ",10,"Subtraction: %d",10,"Multiplication: %d",10,"Quotient: %d ",10,"Remainder: %d ",10,0
	
	errmsg: db "Error Int 1 must be greater than or equal to Int 2",10,0
	

SECTION .bss									; BSS, uninitialized variables


	int1:				resd 1					; reserve 1 integer pointer for user input 1
	int2:				resd 1					; reserve 1 integer pointer for user input 2
	compare: 			resd 1
	
	addition:  			resd 1					; reserve 1 integer pointer for addition
	subtraction: 		resd 1					; reserve 1 integer pointer for subtraction
	mult:		 		resd 1					; reserve 1 integer pointer for multiplication
	division:			resd 1					; reserve 1 integer pointer for quotient
	rem:				resd 1					; reserve 1 integer pointer for remainder
	
		
SECTION .text									; Code section.

	global main									; the standard gcc entry point

	
	main:										; the program label for the entry point
	
		push ebp								; set up stack frame
		mov ebp,esp
		
		
		
								;introduction
								
								
								
		
		
		push dword intro_two					; write intro_two to stack
		push dword intro_one					; write intro_one on the stack
		call printf								; output intro one to screen
		add esp,4								; increment esp address by 4 bytes
		call printf								; output intro_two to screen
		add esp,4								; increment esp address by 4 bytes
		
	
	
	
								
	whileloop:									;jump here if user decides to continue..
	
	
								;instruction
								
								
								
								
		push dword instruction					; write instruction to stack
		call printf								; output instruction to screen
		add esp,4								; increment esp address by 4 bytes
		
		
		
		
		
	false:										;jump here after getting an error message from the failed comparison
	
	
								;get values
								
								
								
		push dword int2							;write int2 to stack
		push dword int1							;write int1 to stack
		push dword input						;write input to stack
		call scanf								;receive user input for int1 and int2
		add esp, 12								;increment esp address by 12 bytes
		
		
		

		mov eax,[int1]
		mov ebx,[int2]
		cmp eax,ebx
		jl errormsg							;jump to print an error message if input 1 is less than input 2
		
		
		
		

		
								;Addition
												
		mov eax,0								;set eax to 0
		mov eax,[int1]							;copy value of int1 into eax
		add eax,[int2]							;add int2 to eax ( eax = int1 + int2)
		mov [addition],eax						;copy eax into the value of addition
		mov eax,0								;set eax to 0
		
		
		
		
		
		
								;Subtraction
								
								

		mov eax,[int1]							;copy the value of int1 into eax	
		sub eax,[int2]							;subtract the value of int2 from eax (eax = int1 - int2)
		mov [subtraction],eax					;copy the value of eax as the value of subtraction
		mov eax,0								;set eax to 0
		
		
		
								;Multiplication
								
												
		mov ebx,0								;set ebx to 0
		mov eax,[int1]							;copy value of int1 to eax
		mov ebx,[int2]							;copy value of int 2 to ebx
		mul ebx									; eax = eax * ebx   where  ebx = [int2] and eax = [int1]
		mov [mult],eax							;copy value of eax into value of mult
		mov eax,0								;set eax to 0
		mov ebx,0								;set ebx to 0
		
		
		
								;division
								
								
		
		mov eax,[int1]							;copy value of int1 into eax
		mov ebx,[int2]							;copy value of int2 into ebx
		div ebx									; eax = eax / ebx   where  ebx = [int2] and eax = [int1]
		mov [division],eax						;copy value of eax into division
		mov eax,0								;set eax to 0
		mov ebx,0								;set ebx to 0
		
		
		
		
		
								;remainder
								
								
								
		mov eax,[int2]							;copy value of int2 into eax
		mov ebx,[division]						;copy value of division into ebx
		mul ebx									; eax = eax * ebx   where  ebx = [division] and eax = [int2]		
		mov ebx,[int1]							;copy value of int1 into ebx				
		sub ebx,eax								;subtract eax from ebx  ( ebx = [int1] - [int2]*[division])
		mov eax,ebx								;copy ebx into eax
		mov [rem],eax							;set value of rem to eax
		mov eax,0								;set eax to 0
		mov ebx,0								;set ebx to 0
		
	
	
	
	
		
		push dword [division]
		push dword[rem]							;write rem to stack
		push dword[division]					;write division to stack
		push dword[mult]						;write mult to stack
		push dword[subtraction]					;write subtraction to stack
		push dword[addition]					;write addition to stack
		push dword values						;write values to stack (print message)
		call printf								;print message values using variables rem, division, mult, subtraction, and rem
		add esp,24								;increment esp 24 bytes
		
		
		push dword continue
		call printf
		add esp,4
		
		push dword compare						;use compare as variable to accept input
		push dword input1						;write input to stack
		call scanf								;receive user input for int1 and int2
		add esp, 8								;increment esp address by 12 bytes
		
		mov eax,[compare]						;copy compare into eax
		
		
	
		
		cmp eax, 0x01 							; compare value of eax to 0x01(0x01 = 1) 
		jne whileloop							; jump to whileloop if false
		

		
		mov esp, ebp							; takedown stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret										; return
		
		
		
	errormsg:									;jump point for the comparison of int 1 and int 2
		
		push dword errmsg						
		call printf								;print error message to user
		add esp,4
		jmp false								;jump back to ask for input again
		
		
		
		
		
		
		
		
		
	