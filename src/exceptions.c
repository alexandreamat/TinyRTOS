#include "exceptions.h"

#include "auxiliaries.h"
#include "exceptions_registers.h"
#include "morse.h"
#include "printf.h"

static const char *entry_error_messages[] = {
    "EXCEPTIONS_SYNC_EL1T",   "EXCEPTIONS_IRQ_EL1T",
    "EXCEPTIONS_FIQ_EL1T",    "EXCEPTIONS_ERROR_EL1T",

    "EXCEPTIONS_SYNC_EL1H",   "EXCEPTIONS_IRQ_EL1H",
    "EXCEPTIONS_FIQ_EL1H",    "EXCEPTIONS_ERROR_EL1H",

    "EXCEPTIONS_SYNC_EL0_64", "EXCEPTIONS_IRQ_EL0_64",
    "EXCEPTIONS_FIQ_EL0_64",  "EXCEPTIONS_ERROR_EL0_64",

    "EXCEPTIONS_SYNC_EL0_32", "EXCEPTIONS_IRQ_EL0_32",
    "EXCEPTIONS_FIQ_EL0_32",  "EXCEPTIONS_ERROR_EL0_32"};

// void exceptions_handle_irq(void) {
//   morse_send_text("E");
//   // morse_send_text("IRQ");
//   volatile unsigned int *base = (unsigned int *)IRQ0_PENDING0;
//   if (*base & VIDEOCORE_IRQ_AUX) auxiliaries_isr();
// }

void exceptions_handle_unexpected_exception(int type, unsigned long esr,
                                            unsigned long address) {
  morse_send_text("ERR");
  printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr,
         address);
}
