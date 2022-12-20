.globl get_CurrentEL
get_CurrentEL:
	mrs x0, CurrentEL
	lsr x0, x0, #2
	ret