
	; Name: Subhei Shaar
	; Creation date: 1/29/2015
	; Last modified: 2/1/2015 13:00
	;
	; 
	; Name of file: hw3.asm
	;
	; Description: This file contains all 3 problems of hw 3.
	;
	;				Problem 1 displays fibonacci numbers to 46 terms.
	;					- number of terms are specified by the user
	;				Problem 2 displays the average of non-negative inputs until a negative number is entered	
	;					-special message displays when only a negative number is input
	;				Problem 3 uses a counted loop to display numbers 9 through 5 without any spaces in between
	;			
	;				Bonus:  - Modularize your program using procedures/functions
	;						- Create all of the above as a single program with a menu to select which problem (must use functions).
	;
	; Assemble:	nasm -f elf -l hw2.lst  hw2.asm
	; Link:		gcc -o hw2  hw2.o
	; Run:		hw3
	; Output:  Problem 1, Problem 2, Problem 3


	
	max_fib equ   46							;set max fib number of terms as 46
	
	extern printf								; the C function, to be called
	extern scanf								; C user input function
	
	
	

SECTION .data									; Data section, initialized variables

												; Data for Printf function
								
	output_menu: db 10,"Choose an option.",10,10,"1. Problem 1: Fibbonaci numbers",10,10,"2. Problem 2: Rounded Integer Average",10,10, "3. Problem 3: Simple loop",10,0	
	
	output2: db "Number of terms:  %d ",10,"Sum:  %d",10,"Average: %d",10,0
	
	introduction:  db "Programmer: Subhei Shaar", 10, "Assignment: Homework 2",10,10,0 
	
	specialmsg: db "No non-negative numbers were entered...",10,0
	
	instruction1: db "This program calculates the fibonacci sequence", 10,"up to 46 terms.",10,10, "Enter how many terms you want displayed. <1 - 46>",10, 0  
	
	instruction2: db "Enter in a non-negative number. <0-100>",10,0
	
	get_name: db "What is your name?",10,0
	
	greet: db "Hello %s!",10,10,0
	
	invalid_fib: db "Invalid input. Try again.",10,0
	
	output: db "%d   ",0
	
	fib_goodbye: db "Problem One is complete. Goodbye %s!",10,0
	
	average_goodbye: db "Problem Two is complete. Goodbye %s!",10,0
	
	endl db "",10,0
	
	invalid_big: db "The number you entered was greater than 100. Please try again.",10,0
	
	
	
												;Data for scanf function
												
												
	input1: db "%d",0			 
	
	input_name: db "%s", 0
	
	output3: db "%d",0
	

SECTION .bss									; BSS, uninitialized variables

	sum					resd 1					;used in problem 2
	average				resd 1					;used in problem 2
	int1:				resd 1					;used in problem 1 (user input for number of terms in fib sequence)
	int2:				resd 1					;used in problem 2 (user input for non-negative numebrs)
	fibFirst			resd 1					;used in problem 1 (n-2 term in fib sequence)
	fibSecond			resd 1					;used in problem 1 (n-1 term in fib sequence)
	fibNext				resd 1					;used in problem 1 (nth term in fib sequence)
	username			resd 1					;used in problem 1 and 2 (name of user)
	counter2 			resd 1					;used in problem 2 (counter for number of non-negative numbers)
	menu				resd 1					;used in main (selection for which program to run)
	
		
SECTION .text									; Code section.

	global main									; the standard gcc entry point
	
	
	intro:										;intro for problems 1 and 2
	
		push ebp
		mov ebp, esp
		
		
		
		push dword introduction					; print programmer name and assignment
		call printf								
		add esp,4


		push dword get_name						;ask for username
		call printf
		add esp, 4

		
		
		push dword username						;store name of the user in "username"
		push dword input_name
		call scanf
		add esp, 8
		
		
		push dword username						;greet user by using username
		push dword greet
		call printf
		add esp, 8
		
		
		mov esp, ebp							; takedown stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret										; return
		
		
	user_instructions1:							;instructions for the user for problem 1
		
		push ebp
		mov ebp, esp
		
		push dword instruction1					
		call printf								; output intro one to screen
		add esp, 4	
		
		
		
		mov esp, ebp							; takedown stack frame
		pop ebp									; same as "leave" op

		mov eax, 0								; normal, no error, return value
		ret										; return
		
	user_instructions2:
		
		push ebp
		mov ebp, esp
		
		push dword instruction2
		call printf
		add esp, 4
		
		
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
		
		
	get_user_data:
		
		push ebp
		mov ebp, esp
		
		
		
		
		.loop:									;post test loop (test at end)
		
		push dword int1
		push dword input1
		call scanf
		add esp, 8
		
		mov eax, [int1]
		mov ebx, 1
		mov ecx, max_fib						;copy max_fib into ecx
		
		cmp eax, ebx							; if input < 1  
		jl get_user_data.invalid				;short circuit if input in less than 1
		cmp eax, ecx							; else if input > max_fib
		jg get_user_data.invalid				;jump to invalid label
		jmp get_user_data.valid					;input is valid! jump to valid label
		
		.invalid:
		
		push dword invalid_fib
		call printf		
		add esp, 4
		jmp get_user_data.loop					;jump back to loop to get valid input
		
		.valid:
		
		mov eax, 0								;clear registers and end
		mov ebx, 0
		mov ecx, 0
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
	
	get_user_data2:
	
		push ebp
		mov ebp, esp
		
		mov eax, 0
		mov [average], eax
		
		mov eax, 0
		mov [counter2], eax
		
		.loop:
		call user_instructions2					;ask for input of a number less than 100
		
		push dword int2
		push dword input1
		call scanf
		
		mov eax, [int2]							; if int2 > 100 -> invalid: print error and jump to top of loop
		mov ebx, 100
		cmp eax, ebx
		jg get_user_data2.invalid
		mov ebx, 0								; if int 2 < 0 -> end loop and if no non-negatives were entered print a special message
		cmp eax, ebx
		jl get_user_data2.negative
		jmp get_user_data2.valid				; if int2 < 100 and int2 > 0 -> keep entering in non-negatives
		
		.invalid:
		
		push dword invalid_big
		call printf
		add esp, 4
		
		jmp get_user_data2.loop
		
		.valid:
		
		mov ebx, [sum]							;sum = sum + int2
		add ebx, eax
		mov [sum], ebx
		
		mov eax, [counter2]						;counter2 = counter2 + 1
		inc eax				
		mov [counter2], eax
		
		
		jmp get_user_data2.loop
		
		
		
		
		.negative:
		
		mov eax, [counter2]
		mov ebx, 0
		cmp eax, ebx
		jne get_user_data2.display
		
		push dword specialmsg					;if counter is 0 which means no non-negatives were entered, then print special message
		call printf
		add esp, 4
		jmp get_user_data2.end
		
		.display:								;jump here to display #of terms, sum, and avg of non-negative input
		
		mov eax, [sum]
		mov ebx, [counter2]
		div ebx
		mov [average],eax
		
		push dword [average]
		push dword [sum]
		push dword [counter2]
		push dword output2
		call printf
		add esp, 16
		
		
		
												;validate number
												;check if negative
												;if negative jump out of the loop
												;if non-negative jump to top of loop
		.end:
			
			
			
			
		mov esp, ebp							; takedown stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
		
	display_fibs:
	
		push ebp
		mov ebp, esp
	
		
		
		
		mov eax, 0
		mov eax, 1
		mov [fibFirst], eax
		mov [fibSecond], eax 
		mov eax, 0
	
		mov ecx, [int1]
	
		.loop:
		
		push ecx
		mov eax, 0
		mov ebx, 0
		
		mov ebx, [int1]
		sub ebx, ecx
		mov eax, 1
		cmp ebx, eax
		jle display_fibs.true
		
		.false:
												; fibNext = fibFirst + fibSecond
		mov eax, 0
		add eax, [fibFirst]
		add eax, [fibSecond]				
		mov [fibNext], eax
		mov eax, 0
												; fibFirst = fibSecond
		mov eax, [fibSecond]
		mov [fibFirst], eax
		mov eax, 0
												;fibSecond = fibNext
		mov eax, [fibNext]
		mov [fibSecond], eax
		
		
		jmp display_fibs.next
		
		.true:									;jump here if counter in loop is 0 or 1 (first 2 iterations)
		
		mov eax, 1
		mov [fibNext], eax						; 1st and 2nd term are both set to 1
		mov eax, 0
		
		.next:
	
		push dword [fibNext]
		push dword output
		call printf								; output intro one to screen
		add esp, 8	
		
		
		pop ecx
		loop display_fibs.loop					;dec ecx then go back to start of the loop
		
		push dword endl
		call printf
		add esp, 4
		
		
	
		
		mov esp, ebp							; takedown stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
	
	farewell_one:
	
		push ebp								;set up stack frame
		mov ebp, esp
		
		push dword username
		push dword fib_goodbye
		call printf
		add esp, 8
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
	
	farewell_two:
	
		push ebp								;set up stack frame
		mov ebp, esp
		
		push dword username
		push dword average_goodbye
		call printf
		add esp, 8
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
	
	
	ProblemOne:
		
		push ebp
		mov ebp, esp
		
		call intro
		
		call user_instructions1
		
		call get_user_data
		
		call display_fibs
		
		call farewell_one
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret	
		
		
		
	ProblemTwo:
	
		push ebp
		mov ebp, esp
		
		call intro
	
		call get_user_data2
		
		call farewell_two
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op
		
		mov eax,0								; normal, no error, return value
		ret
	
	ProblemThree:
		
		push ebp
		mov ebp, esp
		
		mov ecx, 9								;set loop count down to 9
		
		.loop:
		push ecx
		
		mov eax, 5
		cmp ecx, eax
		jge ProblemThree.true
	
		.false:									;if false, do nothing
		
		jmp ProblemThree.next
		
		.true:									;if true, print number
		
		push dword output3
		call printf
		add esp, 4
	
		
		
		.next:
	
		pop ecx
		loop ProblemThree.loop
		
		push dword endl
		call printf
		add esp, 4
		
		
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op
		
		mov eax,0								; normal, no error, return value
		ret
	
	
	
	
	
	
	
	main:										; the program label for the entry point
	
		push ebp								; set up stack frame
		mov ebp,esp
		
		push dword output_menu					; print out menu to display
		call printf
		add esp, 4
		
		
		push dword menu							;get input of menu from user
		push dword input1
		call scanf
		add esp, 8
		
		mov eax ,[menu]							;  if menu == 1  ->  run program 1
		mov ebx, 1
		cmp eax, ebx
		je main.One
		mov ebx, 2								; if menu == 2 -> run program 2
		cmp eax, ebx
		je main.Two
		mov ebx, 3 
		cmp eax, ebx							; if menu == 3 -> run program 3
		je main.Three
		jmp main.end
		
		.One:
		call ProblemOne
		jmp main.end
		
		.Two:
		call ProblemTwo
		jmp main.end
		
		.Three:	
		call ProblemThree
		jmp main.end
		
		.end:									;jump point when selected function call has ended
		
		
		mov esp, ebp							; take down stack frame
		pop ebp									; same as "leave" op

		mov eax,0								; normal, no error, return value
		ret										; return
		
		

		
		
		
		
		
		
		
		
	