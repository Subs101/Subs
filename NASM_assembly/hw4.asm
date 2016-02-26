
; Name:
	; Creation date: 2/6/16
	; Last modified: 2/9/15
	;
	; 
	; Name of file: hw4.asm
	; Description: Do the required 4 programs
	;				reverse an array
	;				rotate an array
	;				frequency table
	;				prime number calculator
		
	; Assemble:	nasm -f elf -l hw4.lst  hw4.asm
	; Link:		gcc -m32 -o hw4 hw4.o
	; Run:		./hw4
	; Output: lots

	
	

	; Declare needed external functions
	
	extern	printf							; the C function, to be called
	extern  scanf
	
	;ARRAY_SIZE equ 6
	;ARRAY_MAX equ 5
	STRING_MAX equ 100
	TABLE_SIZE equ 255
	;SIEVES_MAX equ 10000
	SQRT_SIEVES_MAX equ 100
	SIEVES_SIZE equ 99
	
	
SECTION .data								; Data section, initialized variables


p1_msg: db "Enter in array of %d elements",10,10,0

input1: db "%d",0,0
input2: db "%s",0,0
table_out: db "%d -> ",0
string_out:db "%s",10,0
string_output: db "Enter in a string to be analyzed.",10,0
output_shift: db "Which way do you want to shift the array?",10,"1. right",10,"2. left",10,0
output_shift_factor: db "Enter shift factor: <1 - %d > ",10,0
output_menu: db 10,"Choose an option.",10,10,"1. Problem 1: reverse array",10,10,"2. Problem 2: rotate array",10,10, "3. Problem 3: frequency table",10,10,"4. Problem 4: Sieve of Eratosthenes ",10,0	
output_string: db "%s",10,0
output_getARRAY_SIZE: db "Enter in how many elements are in your array <1 - 100>",10,0
endl: db "",10,0
array_output1: db "%d ",0


output_getSIEVES_MAX: db "This program calculates the prime numbers from 0 to n.",10,"Please input n.",10,0
 
SECTION .bss									; BSS, uninitialized variables

ARRAY_SIZE resd 1 								; reserve input for array size in rotate and reverse functions
SIEVES_MAX resd 1
array resd 1000									; up to 100 elements in the array
var1 resd 1
shift resd 1									; shift right or left ( right = 1, left = 0)		
shift_factor resd 1								; number of elements to shift by
menu resd 1										;menu selection variable 
var2 resb 1
table resd 256
k resd 1
m resd 1
sieves resd 100000								;this array contains the numbers to be marked
mark_array resd 100000							;this array contains the marks for the numbers
counter resd 1
string resd 1

ft resd 1
ft2 resd 1
	
ft3 resd 1
	
	
SECTION .text									; Code section.

	global main									; the standard gcc entry point
		getSIEVES_MAX:
	
	pushad									; set up stack frame
	mov		ebp,esp
	
	pushad 
	push dword output_getSIEVES_MAX
	call printf
	add esp, 4
	popad
	
	
	pushad
	push dword SIEVES_MAX
	push dword input1
	call scanf
	add esp, 8
	popad
	
	
	
	mov		esp, ebp						; takedown stack frame
	popad    								; same as "leave" op

	mov		eax,0							; normal, no error, return value
	ret	
	
	getARRAY_SIZE:
	
	pushad									; set up stack frame
	mov		ebp,esp
	
	pushad 
	push dword output_getARRAY_SIZE
	call printf
	add esp, 4
	popad
	
	
	pushad
	push dword ARRAY_SIZE
	push dword input1
	call scanf
	add esp, 8
	popad
	
	
	
	mov		esp, ebp						; takedown stack frame
	popad    								; same as "leave" op

	mov		eax,0							; normal, no error, return value
	ret	
	
	createArray:
	
	
		pushad									; set up stack frame
		mov		ebp,esp
		
		
		mov ecx, dword[ARRAY_SIZE]
		mov esi, array
		.loop:
		push ecx
		
		mov ebx, dword[ARRAY_SIZE]
		sub ebx, ecx
		
		pushad
		push dword var1
		push dword input1
		call scanf
		add esp ,8
		popad
		
		mov eax, [var1]
		mov [array + 4 * ebx],eax
		
		
		
		pop ecx
		loop createArray.loop
		
		mov ebx, 0
	
	
		mov		esp, ebp						; takedown stack frame
		popad    								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret										; return
		
	printArray:
	
		pushad									; set up stack frame
		mov		ebp,esp
		
		mov ecx, dword[ARRAY_SIZE]
		mov ebx, 0
		mov eax, 0
		
	.loop:
	
		mov eax,dword[array+4*ebx]
		
		push    ebx
		push    ecx
		push    eax
		
		push    array_output1
		call    printf
		add esp,8 
		
		pop ecx
		pop ebx
		
		inc ebx
		dec ecx
		
		cmp ecx,0       ;
		jg printArray.loop
	
		push dword endl
		call printf
		add esp,4
		
		
		
		mov		esp, ebp						; takedown stack frame
		popad    								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret			
	
	reverseArray:
	
		push	ebp								; set up stack frame
		mov		ebp,esp
	
		
		mov ebx, 0								;start of the loop counter
		
		.loop:									;reverse loop runs for length of the array (ARRAY_SIZE - 1)
		mov eax, 0	
		
		mov eax, dword[ARRAY_SIZE]	
		mov esi, 1								; (ARRAY_SIZE -1 ) is the last element in the array
		sub eax, esi						
		sub eax, ebx
		
		
		mov ecx, dword[array + ebx*4]			; store elements from left hand side into ecx
		mov edx, dword[array + eax*4]			; store elements from right hand side into edx
												
		mov dword[array + eax*4], ecx			; in place array swap
		mov dword[array + ebx*4], edx
		
		

		
		inc ebx
		cmp ebx, eax							; loop for half array size
		jl reverseArray.loop
		
		
	
	
		mov		esp, ebp						; takedown stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret										; return
	
	Problem1:
	
		push	ebp								; set up stack frame
		mov		ebp,esp
	
		
		call getARRAY_SIZE
		
		pushad
		push dword [ARRAY_SIZE]
		push dword p1_msg
		call printf
		add esp, 8
		popad
		
		
		call createArray
		
		call reverseArray
	
		call printArray
	
		mov		esp, ebp						; takedown stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret	
		
	Problem2:	
		
		push	ebp								; set up stack frame
		mov		ebp,esp
		
		call getARRAY_SIZE
		 
		pushad
		push dword [ARRAY_SIZE]
		push dword p1_msg
		call printf
		add esp, 8
		popad
		
		call createArray
		
		
		
												; get shift ( either left or right )
		pushad										
		push dword output_shift	
		call printf
		add esp, 4
		popad
		
		pushad		
		push dword shift
		push dword input1
		call scanf
		add esp, 8
		popad
												;get shift_factor  ( num elements to shift)
			
		mov edi, dword[ARRAY_SIZE]
		dec edi
		mov dword[var1], edi
		
		
		
		pushad										
		push dword [var1]
		push dword output_shift_factor
		call printf
		add esp, 8
		popad
		
		
		
		
		
		pushad
		push dword shift_factor
		push dword input1
		call scanf
		add esp,8
		popad
		
		call rotateArray
		
		call printArray
		
		
		mov		esp, ebp						; takedown stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret	
		
	rotateArray:
	
		push	ebp								; set up stack frame
		mov		ebp,esp
	
		
	
												;rotate left 1 spot
		
												;store first element into register
		
		mov esi, [shift]
		mov eax, 2								;check if shift is left
		cmp esi,eax							
		jne rotateArray.right
		
		.left:									;always works any number above 0
		
		mov esi, [shift_factor]
		jmp rotateArray.loop1
		
		.right:									; take array size and subtract left shift factor to get effective right shift factor
		mov esi, dword[ARRAY_SIZE]					; only works if left shift factor input is less than array size
		mov ebx, [shift_factor]
		sub esi, ebx
		
		
		
		
		
		.loop1:
		mov ecx, dword[ARRAY_SIZE]
		dec ecx
		mov ebx,dword[array]					;store 1st element to shift in ebx
		mov edx, dword[array +4*ecx]			;store last element to edx
		mov dword[array +4*ecx], ebx			;wrap around first element to last
		
		.loop2:
		push ecx
		mov eax, 0
		mov eax, ecx
		dec eax									; eax = max array - 1
		
	
		
		mov ebx, dword[array + 4*eax]			;store element before last
		mov dword[array + 4*eax], edx			;overwrite element
		mov edx, ebx							;copy ebx into edx to use in the loop
		
		
		pop ecx
		loop rotateArray.loop2
	
		dec esi
		mov eax, 0
		cmp esi, eax
		jne rotateArray.loop1
		
	
		mov		esp, ebp						; take down stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret

	createTable:
	
		push	ebp								; set up stack frame
		mov		ebp,esp
		
		
		mov ecx, TABLE_SIZE						;initialize table to contain all zeros for character frequency
		.loop:
		push ecx
		
		mov eax, 0
		mov dword[table + ecx*4], eax
		
		
		
		mov eax, 0
		
		
		
		pop ecx
		loop createTable.loop
	
		mov		esp, ebp						; take down stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret	
		
	printTable:
	
		push	ebp								; set up stack frame
		mov		ebp,esp
		
		
		mov ecx, TABLE_SIZE
		
		.loop1:
		push ecx
		
		mov eax, 0
		mov eax, dword[table + 4*ecx]
		
		mov dword[var2],ecx
		
		mov esi, 0
		cmp eax, esi
		je printTable.zero
		
		.nonzero:
		
		
		pushad
		push dword[table+ 4*ecx]
		push dword table_out
		call printf
		add esp, 8
		popad
		
		pushad
		push dword var2
		push dword string_out
		call printf
		add esp, 8
		popad
		
		
		.zero:
		
		
		pop ecx
		mov ebx, 0
		dec ecx
		cmp ecx, ebx
		jge printTable.loop1
		
		
		
		
		
		
		mov		esp, ebp					; take down stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
	freqTable:
	
	
		push	ebp							; set up stack frame
		mov		ebp,esp
		
		
											
											
		push dword string					; get the string in question
		push dword input2
		call scanf
		add esp, 8
		
		mov eax,0 							;clear registers after c function call
		mov ebx, 0
		mov ecx, 0
		
		
		mov ecx, STRING_MAX
		
		.loop1:								; this loop adds 1 to the element in the table which letter appears
		push ecx
		mov eax, 0
		
		mov al, byte[string+ecx]			; take a character from the string and store ascii value in al
		
		mov esi, 0
		mov esi, dword[table + 4*eax]		; add 1 to ascii value in table
		inc esi
		mov dword[table + 4 * eax], esi
		
		pop ecx
		mov ebx, 0
		dec ecx
		cmp ecx, ebx
		jge freqTable.loop1
		
		
		
		
		
		mov		esp, ebp					; take down stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
		

		
	Problem3:
		
		push	ebp							; set up stack frame
		mov		ebp,esp
		
		pushad								; message to user about string
		push dword string_output								
		call printf
		add esp, 4
		popad
		
		
		call createTable					; initialize ascii frequency table to zeros
		
		
		call freqTable
		
	
		call printTable
		
	
		
		
		
		mov		esp, ebp					; take down stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
	
	createSieves:
		
		push	ebp							; set up stack frame
		mov		ebp,esp
	
		xor ecx, ecx						; Zero out counter
		mov ecx, 0
		mov eax, 1
		.loop1:					
	   	
											; The sieve starts at 1, therefore add 1 to the loop counter
	   	mov dword [sieves+4*ecx], eax 		; Insert value into array
	   	
		add eax, 1
		inc ecx
		mov esi, dword[SIEVES_MAX]
		cmp ecx, esi
		jl createSieves.loop1
		
	   	
		
	
	
		mov		esp, ebp					; takedown stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
		
		
		
		
		
		
		
	createMarked:
	
		push	ebp							; set up stack frame
		mov		ebp,esp
		
		
		mov ecx, 0							;initialize table to contain all zeros for character frequency
		.loop:
		push ecx
		
		mov eax, 0
		mov dword[mark_array + ecx*4], eax
		
		pop ecx
		inc ecx
		mov esi, dword[SIEVES_MAX]
		cmp ecx, esi
		jl createMarked.loop
	
		mov		esp, ebp						; take down stack frame
		pop		ebp								; same as "leave" op

		mov		eax,0							; normal, no error, return value
		ret	
	printSieves:
		
		push	ebp								; set up stack frame
		mov		ebp,esp
	
		mov ecx, 0
		.loop1:
		push ecx
		
		
		push dword[sieves+4*ecx]
		push dword array_output1
		call printf
		add esp, 8
		
		
		pop ecx
		inc ecx
		mov esi, dword[SIEVES_MAX]
		cmp ecx, esi
		jl printSieves.loop1
		
		
		
		
		mov		esp, ebp					; takedown stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
	markSieves:
	
		push	ebp							; set up stack frame
		mov		ebp,esp
		
		;first thing to do is to mark the number 1 as special
		
		;1 will be the marker for special
		;2 will be the marker for composites 
		
		mov eax, 1
		mov dword[mark_array], eax 			;first element is special
		
		
		
		
		
		mov ecx, 1							;start loop counter at 1 since the first element has been taken care of already
		.loop1:
		
		mov eax, 0
		mov eax, dword[sieves + ecx * 4]	;move sieves number in eax temp
		mov dword[k], eax 					;current value k
											;check if value has been marked
		
		
		
		
		
		
		mov eax, dword[mark_array + ecx * 4]
		mov esi, 2							;check if composite
		cmp eax, esi 
		jne markSieves.prime
		
		.composite:
		
		jmp markSieves.next
		
		
		.prime:
		
			mov esi, 2							; move 2 into esi
			
			.loop2:
			 mov eax, dword[k]					;set eax to be k
			 
			 mul esi							; eax = k * esi
			 inc esi							;increment esi by 1						
			
			
			
			
			
			mov ebx, dword[SIEVES_MAX]
			cmp eax, ebx
			jg markSieves.next					;jump out of the loop to increment the ecx counter
			
			
												;now mark the new number in eax ad composite
												;repeat until the number gets above 100
			
			mov dword[m], eax
			
			
			
			mov ebx, 2
			dec eax									; address is not the exact number of the composite so we need to dec eax by 1
			mov dword[mark_array +eax*4],ebx
		
			
			
			jmp markSieves.loop2
		
		
		
		.next:
		
		
		inc ecx
		mov esi, dword[SIEVES_MAX]
		cmp ecx, esi
		jne markSieves.loop1



		
	
	
	
	
		mov		esp, ebp					; takedown stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret
	
	
	printPrimes:
		push	ebp							; set up stack frame
		mov		ebp,esp
	
		mov ecx, 0
		.loop1:
		
		mov eax,[mark_array + ecx*4]
		mov esi, 0
		cmp eax,esi
		je printPrimes.prime
		
		.composite:
		jmp printPrimes.next
		
		
		.prime:
		
		
		pushad
		push dword[sieves+ecx*4]
		push dword array_output1
		call printf
		add esp, 8
		popad
		
		mov eax, 0
		mov eax, [counter]
		inc eax
		mov [counter],eax
		mov esi, 10
		cmp eax, esi
		jl printPrimes.next
		
		.newline:
		
		pushad
		push dword endl
		call printf
		add esp, 4
		popad
		
		mov ebx, 0
		mov [counter],ebx
		
		
		
		
		
		
		.next:
		
		inc ecx
		mov esi, dword[SIEVES_MAX]
		cmp ecx, esi
		jl printPrimes.loop1
	
	
		pushad
		push dword endl						;end line at very end
		call printf
		add esp, 4
		popad
		
	
		mov		esp, ebp					; takedown stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
	Problem4:
		
		push	ebp							; set up stack frame
		mov		ebp,esp
	
		call getSIEVES_MAX
		call createSieves
		
		call createMarked
	
		call markSieves
		
		call printPrimes
	
	
	
	
	
	
	
	
		mov		esp, ebp					; takedown stack frame
		pop		ebp							; same as "leave" op

		mov		eax,0						; normal, no error, return value
		ret	
	
	
	
	main:									; the program label for the entry point
		pushad								; set up stack frame
		mov		ebp,esp
	
		push dword output_menu				; print out menu to display
		call printf
		add esp, 4
		
		
		push dword menu						;get input of menu from user
		push dword input1
		call scanf
		add esp, 8
		
		mov eax ,[menu]						;  if menu == 1  ->  run program 1
		mov ebx, 1
		cmp eax, ebx
		je main.One
		mov ebx, 2							; if menu == 2 -> run program 2
		cmp eax, ebx
		je main.Two
		mov ebx, 3 
		cmp eax, ebx						; if menu == 3 -> run program 3
		je main.Three
		mov ebx, 4
		cmp eax,ebx
		je main.Four
		jmp main.end						; if menu == 4 -> run program 4
		
		
		.One:
		call Problem1
		jmp main.end
		
		.Two:
		call Problem2
		jmp main.end
		
		.Three:	
		
		call Problem3
		jmp main.end
		
		.Four:
		call Problem4
		jmp main.end
		
		.end:									;jump point when selected function call has ended
		
		
	
	
		mov		esp, ebp					; take down stack frame
		popad		

		mov		eax,0						; normal, no error, return value
		ret									; return