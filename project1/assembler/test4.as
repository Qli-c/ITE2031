	lw 0 1 num
	lw 0 2 zero
	lw 0 3 num2
	lw 0 4 to
	lw 0 7 num3
	noop
	jalr 4 5	jalr test
	halt
plus	add 3 2 3
	add 1 3 1
	add 3 7 3
	noop
	jalr 5 4
num .fill 2
zero .fill 0
to .fill plus
num2 .fill 3
num3 .fill 1
