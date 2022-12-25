#include "sysregs.h"
#include "mm.h"


.section ".text.boot"  

.global _start  

_start:
    mrs     x1, mpidr_el1
    and     x1, x1, #0xFF
    cbz     x1, master
    b       proc_hang

master:  
    mov     x0, #0x33ff
    msr     cptr_el2, x0 	 
    mov     x0, #3 << 20
    msr     cpacr_el1, x0	 
    
    ldr	    x0, =SCTLR_EL1_VALUE
	msr	    sctlr_el1, x0		

	ldr 	x0, =HCR_EL2_VALUE
	msr	    hcr_el2, x0

	ldr	    x0, =SPSR_EL2_VALUE
	msr	    spsr_el2, x0

	adr	    x0, el1_entry		
	msr	    elr_el2, x0

	eret	

el1_entry:
    
    adr     x0, __bss_start
    adr     x1, __bss_end
    sub     x1, x1, x0
    bl      memzero

    mov     sp, #LOW_MEMORY
    bl      main
    b       proc_hang


proc_hang:
    wfe
    b       proc_hang