/* Real Mode Hello World */
#.code16
#
#.global start
#start:
#	movw %cs, %ax
#	movw %ax, %ds
#	movw %ax, %es
#	movw %ax, %ss
#	movw $0x7d00, %ax
#	movw %ax, %sp # setting stack pointer to 0x7d00

#loop:
#	jmp loop


/* Protected Mode Hello World */
#.code16
#
#.global start
#start:
#	movw %cs, %ax
#	movw %ax, %ds
#	movw %ax, %es
#	movw %ax, %ss
#
#.code32
#start32:
#	movw $0x10, %ax # setting data segment selector
#	movw %ax, %ds
#	movw %ax, %es
#	movw %ax, %fs
#	movw %ax, %ss
#loop32:
#	jmp loop32
#
#
#.p2align 2


/* Protected Mode Loading Hello World APP */
.code16

.global start
start:
    movw %cs, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    #TODO: Protected Mode Here
    cli

    inb $0x92, %al
    orb $0x02, %al
    outb %al, $0x92

    data32 addr32 lgdt gdtDesc

    movl %cr0, %eax
    orl $0x1, %eax
    movl %eax, %cr0

    data32 ljmp $0x08, $start32

.code32
start32:
    movw $0x10, %ax # setting data segment selector
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %ss
    movw $0x18, %ax # setting graphics data segment selector
    movw %ax, %gs

    movl $0x8000, %eax # setting esp
    movl %eax, %esp
    jmp bootMain # jump to bootMain in boot.c

.p2align 2
gdt:
    #gdt definition here
    .word 0x0000, 0x0000
    .byte 0x00, 0x00, 0x00, 0x00

    .word 0xffff, 0x0000
    .byte 0x00, 0x9a, 0xcf, 0x00

    .word 0xffff, 0x0000
    .byte 0x00, 0x92, 0xcf, 0x00

    .word 0xffff, 0x8000
    .byte 0x0b, 0x92, 0xcf, 0x00

gdtDesc: 
    #gdtDesc definition here
    .word (gdtDesc - gdt - 1)
    .long gdt
