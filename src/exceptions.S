#include "exceptions_registers.h"

// Macros

.macro exceptions_store_registers
    sub     sp,     sp,     #256
    stp     x0,     x1,     [sp, #16 * 0]
    stp     x2,     x3,     [sp, #16 * 1]
    stp     x4,     x5,     [sp, #16 * 2]
    stp     x6,     x7,     [sp, #16 * 3]
    stp     x8,     x9,     [sp, #16 * 4]
    stp     x10,    x11,    [sp, #16 * 5]
    stp     x12,    x13,    [sp, #16 * 6]
    stp     x14,    x15,    [sp, #16 * 7]
    stp     x16,    x17,    [sp, #16 * 8]
    stp     x18,    x19,    [sp, #16 * 9]
    stp     x20,    x21,    [sp, #16 * 10]
    stp     x22,    x23,    [sp, #16 * 11]
    stp     x24,    x25,    [sp, #16 * 12]
    stp     x26,    x27,    [sp, #16 * 13]
    stp     x28,    x29,    [sp, #16 * 14]
    stp     x30,    xzr,    [sp, #16 * 15]
.endm

.macro exceptions_load_registers
    ldp     x30,    xzr,    [sp, #16 * 15]
    ldp     x28,    x29,    [sp, #16 * 14]
    ldp     x26,    x27,    [sp, #16 * 13]
    ldp     x24,    x25,    [sp, #16 * 12]
    ldp     x22,    x23,    [sp, #16 * 11]
    ldp     x20,    x21,    [sp, #16 * 10]
    ldp     x18,    x19,    [sp, #16 * 9]
    ldp     x16,    x17,    [sp, #16 * 8]
    ldp     x14,    x15,    [sp, #16 * 7]
    ldp     x12,    x13,    [sp, #16 * 6]
    ldp     x10,    x11,    [sp, #16 * 5]
    ldp     x8,     x9,     [sp, #16 * 4]
    ldp     x6,     x7,     [sp, #16 * 3]
    ldp     x4,     x5,     [sp, #16 * 2]
    ldp     x2,     x3,     [sp, #16 * 1]
    ldp     x0,     x1,     [sp, #16 * 0]
    add     sp,     sp,     #256
.endm

.macro unexpected_exception vector
    exceptions_store_registers
	mov	    x0, #\vector
	mrs	    x1, esr_el1
	mrs	    x2, elr_el1
	bl	    exceptions_handle_unexpected_exception
	b	    .
.endm

// Functions 
.global exceptions_init
exceptions_init:
	adr	    x0, exception_vector_table_el1  // load VBAR_EL1 with virtual
	msr	    vbar_el1, x0		            // vector table address
	ret

.global exceptions_unmask_irq
exceptions_unmask_irq:
	msr     daifclr, #2 
	ret

.global exceptions_mask_irq
exceptions_mask_irq:
	msr     daifset, #2
	ret

.global exceptions_call_supervisor
exceptions_call_supervisor:
    svc     0

.balign 2048
exception_vector_table_el1:
// Current EL with SP0
.balign 0x80 // 0x000 Synchronous
    b       exceptions_sync_el1t_vector
.balign 0x80 // 0x080 IRQ/vIRQ
    b       exceptions_irq_el1t_vector
.balign 0x80 // 0x100 FIQ/vFRQ
    b       exceptions_fiq_el1t_vector
.balign 0x80 // 0x180 SError/vSError
    b       exceptions_error_el1t_vector

// Current EL with SPx
.balign 0x80 // 0x200 Synchronous
    b       exceptions_sync_el1h_vector
.balign 0x80 // 0x280 IRQ/vIRQ
    b       exceptions_irq_el1h_vector
.balign 0x80 // 0x300 FIQ/vFRQ
    b       exceptions_fiq_el1h_vector
.balign 0x80 // 0x380 SError/vSError
    b       exceptions_error_el1h_vector

// Lower EL using AArch64
.balign 0x80 // 0x400 Synchronous
    b       exceptions_sync_el0_64_vector
.balign 0x80 // 0x480 IRQ/vIRQ
    b       exceptions_irq_el0_64_vector
.balign 0x80 // 0x500 FIQ/vFRQ
    b       exceptions_fiq_el0_64_vector
.balign 0x80 // 0x580 SError/vSError
    b       exceptions_error_el0_64_vector

// Lower EL using AArch32
.balign 0x80 // 0x600 Synchronous
    b       exceptions_sync_el0_32_vector
.balign 0x80 // 0x680 IRQ/vIRQ
    b       exceptions_irq_el0_32_vector
.balign 0x80 // 0x700 FIQ/vFRQ
    b       exceptions_fiq_el0_32_vector
.balign 0x80 // 0x780 SError/vSError
    b       exceptions_error_el0_32_vector


exceptions_sync_el1t_vector:
    unexpected_exception    EXCEPTIONS_SYNC_EL1T

exceptions_irq_el1t_vector:
    unexpected_exception    EXCEPTIONS_IRQ_EL1T

//    exceptions_store_registers
//    bl exceptions_handle_irq
//    exceptions_load_registers
//    eret

exceptions_fiq_el1t_vector:
    unexpected_exception    EXCEPTIONS_FIQ_EL1T

exceptions_error_el1t_vector:
    unexpected_exception    EXCEPTIONS_ERROR_EL1T

exceptions_sync_el1h_vector:
    unexpected_exception    EXCEPTIONS_SYNC_EL1H

exceptions_irq_el1h_vector:
    unexpected_exception    EXCEPTIONS_IRQ_EL1H

//    exceptions_store_registers
//    bl exceptions_handle_irq
//    exceptions_load_registers
//    eret

exceptions_fiq_el1h_vector:
    unexpected_exception    EXCEPTIONS_FIQ_EL1H

exceptions_error_el1h_vector:
    unexpected_exception    EXCEPTIONS_ERROR_EL1H

exceptions_sync_el0_64_vector:
    unexpected_exception    EXCEPTIONS_SYNC_EL0_64

exceptions_irq_el0_64_vector:
    unexpected_exception    EXCEPTIONS_IRQ_EL0_64

//    exceptions_store_registers
//    bl exceptions_handle_irq
//    exceptions_load_registers
//    eret

exceptions_fiq_el0_64_vector:
    unexpected_exception    EXCEPTIONS_FIQ_EL0_64

exceptions_error_el0_64_vector:
    unexpected_exception    EXCEPTIONS_ERROR_EL0_64

exceptions_sync_el0_32_vector:
    unexpected_exception    EXCEPTIONS_SYNC_EL0_32

exceptions_irq_el0_32_vector:
    unexpected_exception    EXCEPTIONS_IRQ_EL0_32

//    exceptions_store_registers
//    bl exceptions_handle_irq
//    exceptions_load_registers
//    eret

exceptions_fiq_el0_32_vector:
    unexpected_exception    EXCEPTIONS_FIQ_EL0_32

exceptions_error_el0_32_vector:
    unexpected_exception    EXCEPTIONS_ERROR_EL0_32
