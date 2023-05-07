	lw 0 0 zero
	lw 0 1 result
	lw 0 2 mplier
	lw 0 3 mcand
	lw 0 4 temp
	lw 0 5 max
loop	nor 2 2 2
	nor 4 4 4
	nor 2 4 7
	nor 2 2 2
	nor 4 4 4
	beq 0 7 jump
	add 3 1 1
jump	add 3 3 3
	add 4 4 4
	beq 4 5 done
	beq 0 0 loop
done halt
zero .fill 0
result .fill 0
mplier .fill 12328
mcand .fill 32766
temp .fill 1
max .fill 32768
