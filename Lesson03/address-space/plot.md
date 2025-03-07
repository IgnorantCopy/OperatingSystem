# Registers

| Register | Hex Value | Decimal Value |
|----------|-----------|---------------|
| rax | 0x0000000000000000 | 0 |
| rbx | 0x0000000000000001 | 1 |
| rcx | 0x0000000000420f54 | 4329300 |
| rdx | 0x0000000000000000 | 0 |
| rsi | 0x00000000000c9268 | 823912 |
| rdi | 0x0000000000000003 | 3 |
| rbp | 0x00007fffffffdde0 | 140737488346592 |
| rsp | 0x00007fffffffdd50 | 140737488346448 |
| r8 | 0x0000000000000078 | 120 |
| r9 | 0x0000000000000001 | 1 |
| r10 | 0x0000000000000000 | 0 |
| r11 | 0x0000000000000202 | 514 |
| r12 | 0x00007fffffffde58 | 140737488346712 |
| r13 | 0x00007fffffffde68 | 140737488346728 |
| r14 | 0x00000000004ad868 | 4905064 |
| r15 | 0x0000000000000001 | 1 |
| rip | 0x0000000000402208 | 4203016 |
| eflags | 0x0000000000000246 | 582 |

# Memory Mappings

| Start Address | End Address | Size | Permissions | Name |
|---------------|-------------|------|--------------|------|
| 0x400000 | 0x401000 | 0x1000 | r--p | /mnt/d/codes/OperatingSystem/Lesson03/address-space/mmap-demo |
| 0x401000 | 0x486000 | 0x85000 | r-xp | /mnt/d/codes/OperatingSystem/Lesson03/address-space/mmap-demo |
| 0x486000 | 0x4ad000 | 0x27000 | r--p | /mnt/d/codes/OperatingSystem/Lesson03/address-space/mmap-demo |
| 0x4ad000 | 0x4b2000 | 0x5000 | r--p | /mnt/d/codes/OperatingSystem/Lesson03/address-space/mmap-demo |
| 0x4b2000 | 0x4b4000 | 0x2000 | rw-p | /mnt/d/codes/OperatingSystem/Lesson03/address-space/mmap-demo |
| 0x4b4000 | 0x4dc000 | 0x28000 | rw-p | [heap] |
| 0x7ffff7ff9000 | 0x7ffff7ffd000 | 0x4000 | r--p | [vvar] |
| 0x7ffff7ffd000 | 0x7ffff7fff000 | 0x2000 | r-xp | [vdso] |
| 0x7ffffffde000 | 0x7ffffffff000 | 0x21000 | rw-p | [stack] |
