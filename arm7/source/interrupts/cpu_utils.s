.align 4
.code 32
.arm

@Example: Assembler ARM7 opcodes use this format
@.global SWIVBLANKWAIT_ARM7
@.type	SWIVBLANKWAIT_ARM7 STT_FUNC
@SWIVBLANKWAIT_ARM7:
@	push {r0-r12,lr}
@   bl IRQVBlankWait
@	pop {r0-r12,lr}
@	bx lr

.end
