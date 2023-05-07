	lw 0 1 num
	lw 0 2 zero
	lw 0 3 num2
	lw 0 4 to
	noop
	jalr 4 5
	halt
plus	add 3 2 3
	add 1 3 1
	jalr 5 4
num .fill 2
zero .fill 0
to .fill 4
num2 .fill 3
