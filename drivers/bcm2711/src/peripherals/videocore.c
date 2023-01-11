#include "peripherals/videocore.h"

#include "misc.h"
#include "peripherals/armc.h"
#include "peripherals/auxiliaries/auxiliaries.h"
#include "peripherals/gic_400.h"

void videocore_enable_irq(videocore_irq_t irq) {
  gic_400_install_irq(VC_PERIPHERAL_IRQS_BASE_ID + irq, 0);
  mmio_write(IRQ0_SET_EN_0 + (irq / 32) * 4, 1 << (irq % 32));
}

void videocore_handle_irq(void) {
  volatile unsigned int irq0 = mmio_read(IRQ0_PENDING0);
  if (irq0 & (1 << VC_AUX_IRQ)) auxiliaries_isr();
}