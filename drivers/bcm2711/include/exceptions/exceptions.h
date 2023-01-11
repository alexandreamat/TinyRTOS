#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#define EXCEPTIONS_SYNC_EL1T (0)
#define EXCEPTIONS_IRQ_EL1T (1)
#define EXCEPTIONS_FIQ_EL1T (2)
#define EXCEPTIONS_ERROR_EL1T (3)

#define EXCEPTIONS_SYNC_EL1H (4)
#define EXCEPTIONS_IRQ_EL1H (5)
#define EXCEPTIONS_FIQ_EL1H (6)
#define EXCEPTIONS_ERROR_EL1H (7)

#define EXCEPTIONS_SYNC_EL0_64 (8)
#define EXCEPTIONS_IRQ_EL0_64 (9)
#define EXCEPTIONS_FIQ_EL0_64 (10)
#define EXCEPTIONS_ERROR_EL0_64 (11)

#define EXCEPTIONS_SYNC_EL0_32 (12)
#define EXCEPTIONS_IRQ_EL0_32 (13)
#define EXCEPTIONS_FIQ_EL0_32 (14)
#define EXCEPTIONS_ERROR_EL0_32 (15)

extern void exceptions_init_vector_table();
extern void exceptions_clear_irq_mask_bits();
extern void exceptions_set_irq_mask_bits();

void exceptions_handle_irq(void);

#endif  // __EXCEPTIONS_H__