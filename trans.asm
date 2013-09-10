[GLOBAL trans_begin]
[GLOBAL trans_end]
[EXTERN sched_yield]

align 16
trans_begin:
	jmp TB_LABEL

	call sched_yield
	TB_LABEL:
	xbegin -7
	ret

align 16
trans_end:
	xend
	ret

