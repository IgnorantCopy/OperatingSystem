# void switch(struct context **old, struct context *new);
#
# Save current register context in old
# and then load register context from new.
.global switch
switch:
    # Save old registers
    movl 4(%esp), %eax  # put old ptr into eax
    pop 0(%eax)         # save the old IP
    movl %esp, 4(%eax)  # save the old SP
    movl %ebx, 8(%eax)  # save other registers
    movl %ecx, 12(%eax)
    movl %edx, 16(%eax)
    movl %esi, 20(%eax)
    movl %edi, 24(%eax)
    movl %ebp, 28(%eax)

    # Load new registers
    movl 4(%esp), %eax  # put new ptr into eax
    movl 28(%eax), %ebp # restore other registers
    movl 24(%eax), %edi
    movl 20(%eax), %esi
    movl 16(%eax), %edx
    movl 12(%eax), %ecx
    movl 8(%eax), %ebx
    movl 4(%eax), %esp  # stack is switched
    pushl 0(%eax)       # return address put in place
    ret                 # return to new context