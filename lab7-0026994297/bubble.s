.global bubble
@modify here
bubble:
  push {r4-r9, fp, lr}
  mov fp, sp
  sub sp, sp, #4
  //length of array r1
  //address of array in r0
  cmp r1, #1
  ble end
  mov r4, r1  //r4 conatains number of elements
  mov r6, #0 //r6 is the outer counter
  mov r7, #0 //r7 is the inner counter
  mov r5, #0 //inner loop limit
  mov r8, r0 //pointer to array

outerloop:
  //add r8, r8, #4
  mov r8, r0
  mov r7, #0 //inner loop counter to 0
  cmp r6, r4 // checks outer counter with number of elemets
  beq end
  //mov r8, r0 // moves array into r8
  add r6, r6, #1 // adds one to counter
  b innerloop

innerloop:
  sub r5, r4, #2
  ldr r2, [r8] // loads first value into r2
  ldr r3, [r8, #4] // loads second value into r3
  cmp r2, r3 // compres
  bgt swap

after:
  cmp r7, r5 // compares inner counter with n-1
  beq outerloop
  add r7, r7, #1 // adds one to inner counter
  add r8, r8, #4 //increments pointer
  b innerloop

swap:
  ldr r2, [r8]		//loads first value
  ldr r3, [r8, #4]	//loads next value
  str r2, [r8, #4]	//stores current into [r8 +4]
  str r3, [r8]		//stornes next into [r8]
  b after

end:
mov r0, r8
mov sp, fp
pop {r4-r9, fp, lr}
bx lr


