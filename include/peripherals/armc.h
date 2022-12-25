#ifndef __ARMC_H__
#define __ARMC_H__

#include "peripherals/base.h"

#define IRQ0_PENDING0 (ARMC_BASE + 0x200)  // ARM Core 0 IRQ Enabled Interrupt Pending bits [31:0]
#define IRQ0_PENDING1 (ARMC_BASE + 0x204)  // ARM Core 0 IRQ Enabled Interrupt pending bits [63:32]
#define IRQ0_PENDING2 (ARMC_BASE + 0x208)  // ARM Core 0 IRQ Enabled Interrupt pending bits [79:64]
#define IRQ0_SET_EN_0 (ARMC_BASE + 0x210)  // Write to Set ARM Core 0 IRQ enable bits [31:0]
#define IRQ0_SET_EN_1 (ARMC_BASE + 0x214)  // Write to Set ARM Core 0 IRQ enable bits [63:32]
#define IRQ0_SET_EN_2 (ARMC_BASE + 0x218)  // Write to Set ARM Core 0 IRQ enable bits[79:64]
#define IRQ0_CLR_EN_0 (ARMC_BASE + 0x220)  // Write to Clear ARM Core 0 IRQ enable bits [31:0]
#define IRQ0_CLR_EN_1 (ARMC_BASE + 0x224)  // Write to Clear ARM Core 0 IRQ enable bits [63:32]
#define IRQ0_CLR_EN_2 (ARMC_BASE + 0x228)  // Write to Clear ARM Core 0 IRQ enable bits [79:64]

#define IRQ_STATUS0 (ARMC_BASE + 0x230)    // Interrupt Line bits [31:0]
#define IRQ_STATUS1 (ARMC_BASE + 0x234)    // Interrupt Line bits [63:32]
#define IRQ_STATUS2 (ARMC_BASE + 0x238)    // Interrupt Line bits [79:64]

#define IRQ1_PENDING0 (ARMC_BASE + 0x240)  // ARM Core 1 IRQ Enabled Interrupt pending bits [31:0]
#define IRQ1_PENDING1 (ARMC_BASE + 0x244)  // ARM Core 1 IRQ Enabled Interrupt pending bits [63:32]
#define IRQ1_PENDING2 (ARMC_BASE + 0x248)  // ARM Core 1 IRQ Enabled Interrupt pending bits [79:64]
#define IRQ1_SET_EN_0 (ARMC_BASE + 0x250)  // Write to Set ARM Core 1 IRQ enable bits [31:0]
#define IRQ1_SET_EN_1 (ARMC_BASE + 0x254)  // Write to Set ARM Core 1 IRQ enable bits [63:32]
#define IRQ1_SET_EN_2 (ARMC_BASE + 0x258)  // Write to Set ARM Core 1 IRQ enable bits[79:64]
#define IRQ1_CLR_EN_0 (ARMC_BASE + 0x260)  // Write to Clear ARM Core 1 IRQ enable bits [31:0]
#define IRQ1_CLR_EN_1 (ARMC_BASE + 0x264)  // Write to Clear ARM Core 1 IRQ enable bits [63:32]
#define IRQ1_CLR_EN_2 (ARMC_BASE + 0x268)  // Write to Clear ARM Core 1 IRQ enable bits [79:64]

#define IRQ2_PENDING0 (ARMC_BASE + 0x280)  // ARM Core 2 IRQ Enabled Interrupt pending bits [31:0]
#define IRQ2_PENDING1 (ARMC_BASE + 0x284)  // ARM Core 2 IRQ Enabled Interrupt pending bits [63:32]
#define IRQ2_PENDING2 (ARMC_BASE + 0x288)  // ARM Core 2 IRQ Enabled Interrupt pending bits [79:64]
#define IRQ2_SET_EN_0 (ARMC_BASE + 0x290)  // Write to Set ARM Core 2 IRQ enable bits [31:0]
#define IRQ2_SET_EN_1 (ARMC_BASE + 0x294)  // Write to Set ARM Core 2 IRQ enable bits [63:32]
#define IRQ2_SET_EN_2 (ARMC_BASE + 0x298)  // Write to Set ARM Core 2 IRQ enable bits[79:64]
#define IRQ2_CLR_EN_0 (ARMC_BASE + 0x2A0)  // Write to Clear ARM Core 2 IRQ enable bits [31:0]
#define IRQ2_CLR_EN_1 (ARMC_BASE + 0x2A4)  // Write to Clear ARM Core 2 IRQ enable bits [63:32]
#define IRQ2_CLR_EN_2 (ARMC_BASE + 0x2A8)  // Write to Clear ARM Core 2 IRQ enable bits [79:64]

#define IRQ3_PENDING0 (ARMC_BASE + 0x2C0)  // ARM Core 3 IRQ Enabled Interrupt pending bits [31:0]
#define IRQ3_PENDING1 (ARMC_BASE + 0x2C4)  // ARM Core 3 IRQ Enabled Interrupt pending bits [63:32]
#define IRQ3_PENDING2 (ARMC_BASE + 0x2C8)  // ARM Core 3 IRQ Enabled Interrupt pending bits [79:64]
#define IRQ3_SET_EN_0 (ARMC_BASE + 0x2D0)  // Write to Set ARM Core 3 IRQ enable bits [31:0]
#define IRQ3_SET_EN_1 (ARMC_BASE + 0x2D4)  // Write to Set ARM Core 3 IRQ enable bits [63:32]
#define FIQ3_SET_EN_2 (ARMC_BASE + 0x3D8)  // Write to Set ARM Core 3 FIQ enable bits[79:64]
#define FIQ3_CLR_EN_0 (ARMC_BASE + 0x3E0)  // Write to Clear ARM Core 3 FIQ enable bits [31:0]
#define FIQ3_CLR_EN_1 (ARMC_BASE + 0x3E4)  // Write to Clear ARM Core 3 FIQ enable bits [63:32]
#define FIQ3_CLR_EN_2 (ARMC_BASE + 0x3E8)  // Write to Clear ARM Core 3 FIQ enable bits [79:64]

#define SWIRQ_SET (ARMC_BASE + 0x3F0)      // Write to Set Software Interrupt sources
#define SWIRQ_CLEAR (ARMC_BASE + 0x3F4)    // Write to Clear Software Interrupt sources

void armc_handle_irq(void);

#endif  // __ARMC_H__