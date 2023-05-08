	lw 0 0 num
	lw 0 1 num
	beq 0 1 32768	offsetFields that don't fit in 16 bits error
	halt
num .fill 1
