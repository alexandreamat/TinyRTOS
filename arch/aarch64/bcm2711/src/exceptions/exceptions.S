//D13.2.137
.globl exceptions_init_vector_table
exceptions_init_vector_table:
    adr x0, vectors
    msr vbar_el1, x0
    ret

//C5.2.2
.globl exceptions_clear_irq_mask_bits
exceptions_clear_irq_mask_bits:
    msr daifclr, #2
    ret

.globl exceptions_set_irq_mask_bits
exceptions_set_irq_mask_bits:
    msr daifset, #2
    ret
