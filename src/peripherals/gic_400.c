#include "peripherals/gic_400.h"

#include "misc.h"

#define GICD_ISENABLER(n) (GICD_ISENABLERn + 4 * (n))
#define SET_ENABLE_BIT(intid) ((intid) % 32)

#define GICD_ITARGETSR(n) \
  ((volatile unsigned char *const)(GICD_ITARGETSRn + 4 * (n)))
#define CPU_TARGETS_OFFSET_BYTE(intid) ((intid) % 4)

void gic_400_install_irq(unsigned int intid, unsigned int cpu) {
  volatile unsigned char *target_reg = GICD_ITARGETSR(intid / 4);
  target_reg[CPU_TARGETS_OFFSET_BYTE(intid)] |= 1 << cpu;
  mmio_write(GICD_ISENABLER(intid / 32), 1 << SET_ENABLE_BIT(intid));
}