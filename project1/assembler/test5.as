	lw 0 1 num10
	lw 0 2 num2
	lw 0 3 addall
	lw 0 4 temp
	noop
loop	beq 1 4 done
	add 4 2 4
	add 3 4 3
	beq 1 1 loop	loop test
done	sw 0 3 13	sw test
	halt
num10 .fill 10
num2 .fill 2
addall .fill 0
temp .fill 0
