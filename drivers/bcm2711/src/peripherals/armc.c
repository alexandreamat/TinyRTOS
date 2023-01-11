#include "peripherals/armc.h"

#include "peripherals/videocore.h"

void armc_handle_irq(void) { videocore_handle_irq(); }