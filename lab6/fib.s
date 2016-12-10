@ fib.s
.data

.section .data
.comm buffer, 48
msg: .ascii "The fib is: %d\n"
.word

format: .ascii "%d"
.word 0
.align 2
.comm a,4,4

addra: .word a
addrformata: .word format
addrmsg: .word msg

.global main

main:

ldr r0, addrformata
ldr r1, addra
bl scanf

ldr r5, addra		@puts scanned number into r6
ldr r6, [r5]

mov r8, r6		@checks for less than two
cmp r6, #2
blt end

mov r8, #1		@checks if is two
cmp r6, #2
beq end

mov r7, #2		@counter
mov r5, #1
mov r9, #1
loop:

  mov r4, r5		@r4 is temp register
  add r5, r5, r9	@adds itself and the previous
  mov r9, r4		@puts the temp equal to the previous, r5 has final output

  mov r8, r5
  add r7, #1		@check to exit loop
  cmp r7, r6
  beq end
  @bgt end

  b loop
end:

ldr r0, addrmsg
mov r1, r8
bl printf

mov r7, $1
svc $0
.end
