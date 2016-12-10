@ product.s
.data

.section .data
.comm buffer, 48

msg: .ascii "***Enter the numbers here***\n"
.word 0

format: .ascii "%d"
.word 0
msgend: .ascii "***The product is:***\n%d\n"
.word 0

.section .data
.align 2
.comm a,4,4

addra: .word a
addrformat: .word format
addrmsg: .word msg
addrmsgend: .word msgend

.global main

main:

ldr r0, addrmsg		@print statment
bl printf

mov r5, #1		@puts initial value into r5
mov r6, #-1		@puts negative 1 in r6

loop:
  ldr r0, addrformat	@scans each number
  ldr r1, addra
  bl scanf

  ldr r9, addra		@puts the scanned number into r1 and r7
  ldr r1, [r9]
  mov r7, r1

  cmp r1, r6		@compares scanned with -1
  beq end
  mul r5, r5, r7	@multiplies
  b loop

end:

ldr r0, addrmsgend	@prints out
mov r1, r5
bl printf

mov r7, $1		@exits
svc $0
.end
