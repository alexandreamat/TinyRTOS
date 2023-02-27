#include "exceptions/exceptions.h"

#include <stdio.h>

#include "misc.h"
#include "peripherals/armc.h"
#include "peripherals/auxiliaries/auxiliaries.h"
#include "peripherals/auxiliaries/mini_uart.h"
#include "peripherals/gic_400.h"
#include "utils/morse.h"

static const char *entry_error_messages[] = {
    "EXCEPTIONS_SYNC_EL1T",   "EXCEPTIONS_IRQ_EL1T",
    "EXCEPTIONS_FIQ_EL1T",    "EXCEPTIONS_ERROR_EL1T",

    "EXCEPTIONS_SYNC_EL1H",   "EXCEPTIONS_IRQ_EL1H",
    "EXCEPTIONS_FIQ_EL1H",    "EXCEPTIONS_ERROR_EL1H",

    "EXCEPTIONS_SYNC_EL0_64", "EXCEPTIONS_IRQ_EL0_64",
    "EXCEPTIONS_FIQ_EL0_64",  "EXCEPTIONS_ERROR_EL0_64",

    "EXCEPTIONS_SYNC_EL0_32", "EXCEPTIONS_IRQ_EL0_32",
    "EXCEPTIONS_FIQ_EL0_32",  "EXCEPTIONS_ERROR_EL0_32"};

void exceptions_handle_irq(void) { armc_handle_irq(); }

void exceptions_handle_unexpected_exception(int type, unsigned long esr,
                                            unsigned long address) {
  printf("%s, ESR: %lx, address: %lx\r\n", entry_error_messages[type], esr,
         address);
}
