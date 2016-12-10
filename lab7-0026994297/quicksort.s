.global quicksort
@modify here
quicksort:

  PUSH {r4,r5,r6,r9,r10, fp, lr}
  //mov fp, sp

  //cmp r1, #2	//MAY NEED TO CHANGE BASED ON RECURSION
  //blt end

  mov r12, #4		//used to offset pointers

  cmp r1, #1		//checks n>1
  ble done
    mov r6, r1		//puts n into r6
    mov r4, r0		//pointer to array in r4

    bl partition

    //mov r5, r0	//puts result (p) into r5
    mov r5, r0
    mov r1, r5		//puts p into r1 for next function call
    mov r0, r4		//puts arguments for call

    bl quicksort

    mov r9, r6		//r9 = n
    sub r9, r9, r5	//r9 = n-p
    sub r9, r9, #1	//r9 = n-p-1

    mov r12, #4
    add r10, r5, #1	//gets p+1 for assignmenr
    mul r10, r10, r12
    add r10, r10, r4
    mov r0, r10		//puts pointer of a[p+1] to r0
    mov r1, r9		//moves n-p-1 into r1

    bl quicksort
    //b done

  done:
    POP {r4,r5,r6,r9,r10, fp, pc}
    //bx lr

partition:

  PUSH {r2,r3,r4,r5,r6,r7,r8,r9,r10, fp, lr}
  mov r12, #4
  sub r7, r1, #1	//r7 is n-1
  mul r8, r7, r12
  //ldr r8, [r4, r7] 	//r8 contains pivot
  ldr r8, [r4,r8]
  mov r2, #0		//r2 is i

  mov r3, r2 		//r3 is j
  //b loop

  loop:
    mov r7, r1
    sub r7, r7, #1
    cmp r3, r7		//check to break out of loop
    bge loop_end 	//if loop finishes, branch to the end

    mul r11, r3, r12
    ldr r10, [r4, r11]	//gets a[j]

    cmp r10, r8		//compare with pivot
    blt swap
    add r3, r3, #1	//increase j
    b loop

  swap:
    mul r11, r2, r12 	//gets i
    mul r5, r3, r12	//gets j
    add r11, r11,r4	//offset
    add r5, r5, r4
    ldr r9, [r11]	//conatains a[i]
    ldr r10, [r5]	//contains a[j]
    str r9, [r5]	//swaps
    str r10, [r11]
    add r2, r2, #1	//increase i and j
    add r3, r3, #1
    //mov r5, r2	//r5 is i for return value
    b loop

  loop_end:
    //mov r7, r1
    //sub r7, r7, #1	//r7 = n-1
    mov r12, #4
    mul r11, r7, r12
    mul r5, r2, r12
    ldr r9, [r4,r11]	//puts a[n-1] in r9
    ldr r10, [r4,r5]	//puts a[i] in r10
    str r9, [r4,r5]	//swaps values
    str r10, [r4,r11]
    mov r0, r2		//returns i
    POP {r2,r3,r4,r5,r6,r7,r8,r9,r10,fp,pc}
