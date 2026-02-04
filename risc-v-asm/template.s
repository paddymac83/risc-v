# RISC-V Assembly Template
# Simple function that adds two numbers

.text
.globl add_numbers

add_numbers:
    # Arguments in a0 and a1
    # Return value in a0
    add a0, a0, a1
    ret

.globl _start
_start:
    # Load values
    li a0, 10
    li a1, 20
    
    # Call function
    call add_numbers
    
    # Exit
    li a7, 93      # exit syscall
    ecall
