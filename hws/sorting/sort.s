	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 0
	.globl	_sort                           ; -- Begin function sort
	.p2align	2
_sort:                                  ; @sort
	.cfi_startproc
; %bb.0:
	cmp	w1, #2
	b.lt	LBB0_8
; %bb.1:
	mov	w8, #0                          ; =0x0
	sub	w9, w1, #1
	add	x10, x0, #4
	mov	x11, x9
	b	LBB0_3
LBB0_2:                                 ;   in Loop: Header=BB0_3 Depth=1
	add	w8, w8, #1
	sub	w11, w11, #1
	cmp	w8, w9
	b.eq	LBB0_8
LBB0_3:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_6 Depth 2
	mov	w11, w11
	sub	w12, w8, w1
	cmn	w12, #2
	b.gt	LBB0_2
; %bb.4:                                ;   in Loop: Header=BB0_3 Depth=1
	ldr	w12, [x0]
	mov	x13, x11
	mov	x14, x10
	b	LBB0_6
LBB0_5:                                 ;   in Loop: Header=BB0_6 Depth=2
	stp	w15, w12, [x14, #-4]
	add	x14, x14, #4
	subs	x13, x13, #1
	b.eq	LBB0_2
LBB0_6:                                 ;   Parent Loop BB0_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w15, [x14]
	cmp	w12, w15
	b.gt	LBB0_5
; %bb.7:                                ;   in Loop: Header=BB0_6 Depth=2
	mov	x12, x15
	add	x14, x14, #4
	subs	x13, x13, #1
	b.ne	LBB0_6
	b	LBB0_2
LBB0_8:
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
