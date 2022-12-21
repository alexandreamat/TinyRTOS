.section ".text.boot"  // Make sure the linker puts this at the start of the kernel image

.global _start  // Execution starts here

_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, master
    // We're not on the main core, so hang in an infinite wait loop

proc_hang: wfe
    b       proc_hang

master:  // We're on the main core!

    mov     x0, #0x33ff
    msr     cptr_el2, x0 	 // Disable coprocessor traps to EL3
    mov     x0, #3 << 20
    msr     cpacr_el1, x0	 // Enable FP/SIMD at EL1

#define SCTLR_EL1_RESERVED                  (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EL1_EE_LITTLE_ENDIAN          (0 << 25)
#define SCTLR_EL1_EOE_LITTLE_ENDIAN         (0 << 24)
#define SCTLR_EL1_I_CACHE_DISABLED          (0 << 12)
#define SCTLR_EL1_D_CACHE_DISABLED          (0 << 2)
#define SCTLR_EL1_MMU_DISABLED              (0 << 0)
#define SCTLR_EL1_VALUE	                    (SCTLR_EL1_RESERVED | SCTLR_EL1_EE_LITTLE_ENDIAN | SCTLR_EL1_I_CACHE_DISABLED | SCTLR_EL1_D_CACHE_DISABLED | SCTLR_EL1_MMU_DISABLED)
    
    ldr	x0, =SCTLR_EL1_VALUE
	msr	sctlr_el1, x0		

#define HCR_EL2_RW	    		            (1 << 31)
#define HCR_EL2_VALUE			            HCR_EL2_RW

	ldr	x0, =HCR_EL2_VALUE
	msr	hcr_el2, x0

#define SPSR_EL2_MASK_ALL 		            (7 << 6)
#define SPSR_EL2_EL1h			            (5 << 0)
#define SPSR_EL2_VALUE			            (SPSR_EL2_MASK_ALL | SPSR_EL2_EL1h)

	ldr	x0, =SPSR_EL2_VALUE
	msr	spsr_el2, x0

	adr	x0, el1_entry		
	msr	elr_el2, x0

	eret	

el1_entry:
    // Set stack to start below our code
    ldr     x1, =_start
    mov     sp, x1
    // Clean the BSS section
    ldr     x1, =__bss_start     // Start address
    ldr     w2, =__bss_size      // Size of the section
3:  cbz     w2, 4f               // Quit loop if zero
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b               // Loop if non-zero

    // Jump to our main() routine in C (make sure it doesn't return)
4:  bl      main
    // In case it does return, halt the master core too
    b       proc_hang


