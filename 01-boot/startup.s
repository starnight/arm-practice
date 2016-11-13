// To keep this in the first portion of the binary.
.section ".text.boot"

.global _Reset
_Reset:
	LDR sp, =__stack_top
	BL main
	B .
