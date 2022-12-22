#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

extern void exceptions_init();
extern void exceptions_call_supervisor();
extern void exceptions_unmask_irq();
extern void exceptions_mask_irq();

// void exceptions_handle_irq(void);
void exceptions_handle_unexpected_exception(int type, unsigned long esr,
                                            unsigned long address);

#endif  // __EXCEPTIONS_H__