@ length.s
.data

.section .data
.comm buffer, 48

msg: .ascii "The length is: %d\n"
.word 0

formata: .ascii "%s"
.word 0

.section .data
.align 2
.comm a,4,4

addra: .word a
addrformata: .word formata
addrmsg: .word msg

.globl main

main:

ldr r0, addrformata      @Scan string
ldr r1, addra
bl scanf

ldr r0, addra           @load scanned string into r0

mov r5, #0              @Load counter to 0

loop:                  @Loop to count number of characters
  ldr r3, [r0]         @Load first character to r3
  cmp r3, #0           @Tests to make sure it is not null
  beq last             @If null, breaks from loop
  add r0, r0, #1       @increments pointer
  add r5, r5, #1       @increments counter
  b loop               @repeats loop

last:
ldr r0, addrmsg        @loads message to r0
mov r1, r5             @loads length to r1
bl printf              @prints response

mov r7, $1
svc $0
.end
