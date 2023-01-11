#include "interrupts.h"

#include "exceptions/exceptions.h"

void interrupts_init(void) {
  exceptions_init_vector_table();
  exceptions_clear_irq_mask_bits();
}