#ifndef __GIC400_H__
#define __GIC400_H__

#include "peripherals/base.h"

#define GICD_BASE   (GIC_400_BASE | 0x1000)  // Distributor
#define GICC_BASE   (GIC_400_BASE | 0x2000)  // CPU Interfaces
#define GICH_BASE   (GIC_400_BASE | 0x4000)  // Virtual interface control block
#define GICV_BASE   (GIC_400_BASE | 0x6000)  // Virtual CPU interface

#define GICD_CTLR           (GICD_BASE | 0x000) // Distributor Control Register
#define GICD_TYPER          (GICD_BASE | 0x004) // Interrupt Controller Type Register
#define GICD_IIDR           (GICD_BASE | 0x008) // Distributor Implementer Identification Register, GICD_IIDR on page 3-6
#define GICD_IGROUPRn       (GICD_BASE | 0x080) // Interrupt Group Registerse
#define GICD_ISENABLERn     (GICD_BASE | 0x100) // Interrupt Set-Enable Registers
#define GICD_ICENABLERn     (GICD_BASE | 0x180) // Interrupt Clear-Enable Registers
#define GICD_ISPENDRn       (GICD_BASE | 0x200) // Interrupt Set-Pending Registers
#define GICD_ICPENDRn       (GICD_BASE | 0x280) // Interrupt Clear-Pending Registers
#define GICD_ISACTIVERn     (GICD_BASE | 0x300) // Interrupt Set-Active Registers
#define GICD_ICACTIVERn     (GICD_BASE | 0x380) // Interrupt Clear-Active Registers
#define GICD_IPRIORITYRn    (GICD_BASE | 0x400) // Interrupt Priority Registers
#define GICD_ITARGETSRn     (GICD_BASE | 0x800) // Interrupt Processor Targets Registers
#define GICD_ICFGRn         (GICD_BASE | 0xC00) // Interrupt Configuration Registers, GICD_ICFGRn on page 3-6
#define GICD_PPISR          (GICD_BASE | 0xD00) // Private Peripheral Interrupt Status Register, GICD_PPISR on page 3-7
#define GICD_SPISRn         (GICD_BASE | 0xD04) // Shared Peripheral Interrupt Status Registers, GICD_SPISRn on page 3-7
#define GICD_SGIR           (GICD_BASE | 0xF00) // Software Generated Interrupt Register
#define GICD_CPENDSGIRn     (GICD_BASE | 0xF10) // SGI Clear-Pending Registers
#define GICD_SPENDSGIRn     (GICD_BASE | 0xF20) // SGI Set-Pending Registers
#define GICD_PIDR4          (GICD_BASE | 0xFD0) // Peripheral ID 4 Register
#define GICD_PIDR5          (GICD_BASE | 0xFD4) // Peripheral ID 5 Register
#define GICD_PIDR6          (GICD_BASE | 0xFD8) // Peripheral ID 6 Register
#define GICD_PIDR7          (GICD_BASE | 0xFDC) // Peripheral ID 7 Register
#define GICD_PIDR0          (GICD_BASE | 0xFE0) // Peripheral ID 0 Register
#define GICD_PIDR1          (GICD_BASE | 0xFE4) // Peripheral ID 1 Register
#define GICD_PIDR2          (GICD_BASE | 0xFE8) // Peripheral ID 2 Register
#define GICD_PIDR3          (GICD_BASE | 0xFEC) // Peripheral ID 3 Register
#define GICD_CIDR0          (GICD_BASE | 0xFF0) // Component ID 0 Register
#define GICD_CIDR1          (GICD_BASE | 0xFF4) // Component ID 1 Register
#define GICD_CIDR2          (GICD_BASE | 0xFF8) // Component ID 2 Register
#define GICD_CIDR3          (GICD_BASE | 0xFFC) // Component ID 3 Register

#define GICC_CTLR   (GICC_BASE | 0x0000) // CPU Interface Control Register
#define GICC_PMR    (GICC_BASE | 0x0004) // Interrupt Priority Mask Register
#define GICC_BPR    (GICC_BASE | 0x0008) // Binary Point Register. The minimum value of the Binary Point Register depends on which security-banked copy is considered: 0x2 Secure copy, 0x3 Non-secure copy
#define GICC_IAR    (GICC_BASE | 0x000C) // Interrupt Acknowledge Register
#define GICC_EOIR   (GICC_BASE | 0x0010) // End of Interrupt Register
#define GICC_RPR    (GICC_BASE | 0x0014) // Running Priority Register
#define GICC_HPPIR  (GICC_BASE | 0x0018) // Highest Priority Pending Interrupt Register
#define GICC_ABPR   (GICC_BASE | 0x001C) // Aliased Binary Point Registerd. The minimum value of the Aliased Binary Point Register is 0x3.
#define GICC_AIAR   (GICC_BASE | 0x0020) // Aliased Interrupt Acknowledge Registerd
#define GICC_AEOIR  (GICC_BASE | 0x0024) // Aliased End of Interrupt Registerd
#define GICC_AHPPIR (GICC_BASE | 0x0028) // Aliased Highest Priority Pending Interrupt Registercd
#define GICC_APR0   (GICC_BASE | 0x00D0) // Active Priority Register
#define GICC_NSAPR0 (GICC_BASE | 0x00E0) // Non-Secure Active Priority Registerd
#define GICC_IIDR   (GICC_BASE | 0x00FC) // CPU Interface Identification Register, GICC_IIDR on page 3-1
#define GICC_DIR    (GICC_BASE | 0x1000) // Deactivate Interrupt Register

void gic_400_install_irq(unsigned int intid, unsigned int cpu);

#endif  // __GIC400_H__