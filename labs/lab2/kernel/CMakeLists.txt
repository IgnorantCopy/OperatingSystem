add_executable(lab2_kernel_main main.c)
add_executable(lab2_kernel_disk kernel/disk.c)
add_executable(lab2_kernel_i8259 kernel/i8259.c)
add_executable(lab2_kernel_idt kernel/idt.c)
add_executable(lab2_kernel_irqHandle kernel/irqHandle.c)
add_executable(lab2_kernel_keyboard kernel/keyboard.c)
add_executable(lab2_kernel_kvm kernel/kvm.c)
add_executable(lab2_kernel_serial kernel/serial.c)
add_executable(lab2_kernel_vga kernel/vga.c)
add_executable(lab2_kernel_lib_abort lib/abort.c)

include_directories(include)