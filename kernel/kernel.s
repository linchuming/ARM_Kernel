	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.arm
	.syntax divided
	.file	"kernel.c"
	.text
	.align	2
	.global	uart_enable
	.type	uart_enable, %function
uart_enable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #4096
	mov	r2, #20
	movt	r3, 57344
	str	r2, [r3]
	bx	lr
	.size	uart_enable, .-uart_enable
	.align	2
	.global	uart_disable
	.type	uart_disable, %function
uart_disable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #4096
	mov	r2, #40
	movt	r3, 57344
	str	r2, [r3]
	bx	lr
	.size	uart_disable, .-uart_disable
	.align	2
	.global	uart_init
	.type	uart_init, %function
uart_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r4, #4096
	movt	r4, 57344
	movw	r6, #8191
	ldr	r5, .L5
	str	r6, [r4, #12]
	bl	uart_disable(PLT)
	ldr	r3, .L5+4
.LPIC0:
	add	r5, pc, r5
	mov	r2, #32
	mov	r1, #3
	mov	lr, #62
	str	r1, [r4]
	mov	ip, #6
	str	r6, [r4, #20]
	mov	r1, #0
	str	r2, [r4, #4]
	mov	r0, #296
	str	r2, [r4, #32]
	str	r2, [r4, #68]
	str	r1, [r4, #28]
	str	lr, [r4, #24]
	str	ip, [r4, #52]
	str	r0, [r4]
	ldr	r3, [r5, r3]
	str	r1, [r3]
	ldmfd	sp!, {r4, r5, r6, pc}
.L6:
	.align	2
.L5:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC0+8)
	.word	puts_lock(GOT)
	.size	uart_init, .-uart_init
	.align	2
	.global	uart_spin_getbyte
	.type	uart_spin_getbyte, %function
uart_spin_getbyte:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r1, #4096
	movt	r1, 57344
.L8:
	ldr	r2, [r1, #44]
	mov	r3, #4096
	movt	r3, 57344
	tst	r2, #2
	bne	.L8
	ldr	r0, [r3, #48]
	uxtb	r0, r0
	bx	lr
	.size	uart_spin_getbyte, .-uart_spin_getbyte
	.align	2
	.global	uart_spin_putbyte
	.type	uart_spin_putbyte, %function
uart_spin_putbyte:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r1, #4096
	movt	r1, 57344
.L12:
	ldr	r2, [r1, #44]
	mov	r3, #4096
	movt	r3, 57344
	tst	r2, #16
	bne	.L12
	str	r0, [r3, #48]
	bx	lr
	.size	uart_spin_putbyte, .-uart_spin_putbyte
	.align	2
	.global	uart_spin_puts
	.type	uart_spin_puts, %function
uart_spin_puts:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L21
	mov	r1, #1
	ldr	r2, .L21+4
.LPIC9:
	add	r3, pc, r3
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	ldr	r5, [r3, r2]
	.syntax divided
@ 22 "device/../spinlock.h" 1
	1: ldrex r3,[r5]
	teq r3,#0
	strexeq r3, r1,[r5]
	teqeq r3 ,#0
	bne 1b
	
@ 0 "" 2
	.arm
	.syntax divided
	ldrb	r0, [r0]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L17
.L16:
	bl	uart_spin_putbyte(PLT)
	ldrb	r0, [r4, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L16
.L17:
	mov	r3, #0
	str	r3, [r5]
	ldmfd	sp!, {r4, r5, r6, pc}
.L22:
	.align	2
.L21:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC9+8)
	.word	puts_lock(GOT)
	.size	uart_spin_puts, .-uart_spin_puts
	.align	2
	.global	gtc_get_time
	.type	gtc_get_time, %function
gtc_get_time:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	movt	r3, 63728
.L24:
	ldr	r1, [r3, #516]
	ldr	r0, [r3, #512]
	ldr	r2, [r3, #516]
	cmp	r2, r1
	bne	.L24
	stmfd	sp!, {r4, r5}
	mov	r4, #0
	mov	r5, r2
	orr	r4, r4, r0
	mov	r0, r4
	mov	r1, r5
	ldmfd	sp!, {r4, r5}
	bx	lr
	.size	gtc_get_time, .-gtc_get_time
	.align	2
	.global	sleep
	.type	sleep, %function
sleep:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	bl	gtc_get_time(PLT)
	mov	r3, #33792
	movt	r3, 6103
	mul	r3, r3, r4
	adds	r4, r0, r3
	adc	r5, r1, r3, asr #31
.L28:
	bl	gtc_get_time(PLT)
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L28
	ldmfd	sp!, {r4, r5, r6, pc}
	.size	sleep, .-sleep
	.align	2
	.global	usleep
	.type	usleep, %function
usleep:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	bl	gtc_get_time(PLT)
	mov	r3, #400
	mul	r3, r3, r4
	adds	r4, r0, r3
	adc	r5, r1, r3, asr #31
.L32:
	bl	gtc_get_time(PLT)
	cmp	r5, r1
	cmpeq	r4, r0
	bhi	.L32
	ldmfd	sp!, {r4, r5, r6, pc}
	.size	usleep, .-usleep
	.align	2
	.global	sd_init
	.type	sd_init, %function
sd_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, #0
	mov	r2, #1
	movt	r3, 57360
	mov	r1, r3
	strb	r2, [r3, #47]
.L36:
	ldrb	r2, [r1, #47]	@ zero_extendqisi2
	mov	r3, #0
	movt	r3, 57360
	tst	r2, #1
	bne	.L36
	mov	r1, r3
	movw	r2, #16385
	strh	r2, [r3, #44]	@ movhi
.L37:
	ldrh	r2, [r1, #44]
	mov	r3, #0
	movt	r3, 57360
	tst	r2, #2
	beq	.L37
	ldrh	r1, [r3, #44]
	mov	r2, #0
	str	lr, [sp, #-4]!
	orr	r1, r1, #4
	mov	lr, #15
	strh	r1, [r3, #44]	@ movhi
	mvn	ip, #256
	strb	lr, [r3, #41]
	mvn	r0, #3072
	strb	r2, [r3, #40]
	mov	r1, #512
	strh	ip, [r3, #52]	@ movhi
	strh	r0, [r3, #54]	@ movhi
	strh	r2, [r3, #56]	@ movhi
	strh	r2, [r3, #58]	@ movhi
	strh	r1, [r3, #4]	@ movhi
	ldr	pc, [sp], #4
	.size	sd_init, .-sd_init
	.align	2
	.global	sd_frame_cmd
	.type	sd_frame_cmd, %function
sd_frame_cmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r0, #4352
	beq	.L44
	bhi	.L45
	cmp	r0, #1792
	beq	.L46
	bhi	.L47
	cmp	r0, #768
	beq	.L59
	bls	.L120
	cmp	r0, #1280
	beq	.L52
	cmp	r0, #1536
	bne	.L43
	movw	r0, #1594
	bx	lr
.L47:
	cmp	r0, #2560
	beq	.L46
	bhi	.L54
	cmp	r0, #2048
	bne	.L121
	movw	r0, #2074
	bx	lr
.L45:
	cmp	r0, #14080
	beq	.L46
	bls	.L122
	cmp	r0, #38656
	beq	.L44
	bls	.L123
	cmp	r0, #43520
	beq	.L46
	cmp	r0, #45824
	beq	.L44
	cmp	r0, #43264
	bne	.L43
.L50:
	ubfx	r0, r0, #0, #14
	orr	r0, r0, #2
	bx	lr
.L52:
	movw	r0, #1307
	bx	lr
.L122:
	cmp	r0, #6144
	beq	.L44
	bhi	.L57
	cmp	r0, #4608
	beq	.L44
	cmp	r0, #5888
	bne	.L43
.L44:
	ubfx	r0, r0, #0, #14
	orr	r0, r0, #58
	bx	lr
.L123:
	cmp	r0, #34304
	beq	.L46
	cmp	r0, #36096
	beq	.L46
.L43:
	ubfx	r0, r0, #0, #14
	bx	lr
.L120:
	cmp	r0, #256
	beq	.L50
	cmp	r0, #512
	bne	.L43
.L51:
	orr	r0, r0, #9
	bx	lr
.L59:
	movw	r0, #795
	bx	lr
.L57:
	cmp	r0, #6400
	beq	.L44
	cmp	r0, #13312
	bne	.L43
.L46:
	ubfx	r0, r0, #0, #14
	orr	r0, r0, #26
	bx	lr
.L121:
	cmp	r0, #2304
	beq	.L51
	b	.L43
.L54:
	cmp	r0, #3072
	beq	.L46
	cmp	r0, #4096
	bne	.L43
	b	.L46
	.size	sd_frame_cmd, .-sd_frame_cmd
	.align	2
	.global	sd_spin_send_cmd
	.type	sd_spin_send_cmd, %function
sd_spin_send_cmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r6, r1
	mov	r5, r2
	mov	r4, r3
	bl	sd_frame_cmd(PLT)
	mov	ip, #0
	movt	ip, 57360
	ldr	ip, [ip, #36]
	tst	ip, #1
	bne	.L131
	tst	ip, #2
	bne	.L141
.L126:
	cmp	r4, #1
	mov	ip, #0
	movt	ip, 57360
	mov	r3, #14
	strh	r6, [ip, #6]	@ movhi
	mvn	r2, #0
	strh	r3, [ip, #46]	@ movhi
	mvn	r3, #3072
	str	r5, [ip, #8]
	strh	r2, [ip, #48]	@ movhi
	moveq	r2, #55
	strh	r3, [ip, #50]	@ movhi
	beq	.L128
	cmp	r4, #2
	moveq	r2, #39
	movne	r2, #1
.L128:
	mov	r3, #0
	movt	r3, 57360
	strh	r2, [r3, #12]	@ movhi
	mov	r1, r3
	strh	r0, [r3, #14]	@ movhi
	b	.L130
.L143:
	tst	r3, #1
	bne	.L142
.L130:
	ldrh	r3, [r1, #48]
	mov	r2, #0
	movt	r2, 57360
	uxth	r3, r3
	tst	r3, #32768
	beq	.L143
	mvn	r0, #2
	ldmfd	sp!, {r4, r5, r6, pc}
.L141:
	tst	r0, #32
	beq	.L126
	mvn	r0, #1
	ldmfd	sp!, {r4, r5, r6, pc}
.L142:
	mov	r3, #1
	mov	r0, #0
	strh	r3, [r2, #48]	@ movhi
	ldmfd	sp!, {r4, r5, r6, pc}
.L131:
	mvn	r0, #0
	ldmfd	sp!, {r4, r5, r6, pc}
	.size	sd_spin_send_cmd, .-sd_spin_send_cmd
	.align	2
	.global	sd_spin_init_mem_card
	.type	sd_spin_init_mem_card, %function
sd_spin_init_mem_card:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r5, #0
	movt	r5, 57360
	ldr	r3, [r5, #36]
	tst	r3, #65536
	beq	.L150
	mov	r0, #2000
	bl	usleep(PLT)
	mov	r3, #0
	mov	r2, r3
	mov	r1, r3
	mov	r0, r3
	bl	sd_spin_send_cmd(PLT)
	subs	r3, r0, #0
	bne	.L151
	mov	r1, r3
	movw	r2, #426
	mov	r0, #2048
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L152
	ldr	r2, [r5, #16]
	movw	r3, #426
	cmp	r2, r3
	beq	.L159
	b	.L153
.L146:
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L147
	ldr	r4, [r5, #16]
	cmp	r4, #0
	blt	.L163
.L159:
	mov	r3, #0
	mov	r0, #14080
	mov	r2, r3
	mov	r1, r3
	bl	sd_spin_send_cmd(PLT)
	mov	r2, #0
	movt	r2, 16432
	subs	r3, r0, #0
	mov	r0, #43264
	mov	r1, r3
	beq	.L146
.L147:
	mvn	r0, #4
	ldmfd	sp!, {r4, r5, r6, pc}
.L163:
	mov	r3, r0
	mov	r2, r0
	mov	r1, r0
	mov	r0, #512
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L154
	mov	r6, #0
	movt	r6, 57360
	b	.L149
.L165:
	ldr	r5, [r6, #16]
	mov	r5, r5, lsr #16
	mov	r5, r5, asl #16
	cmp	r5, #0
	bne	.L164
.L149:
	mov	r3, #0
	mov	r0, #768
	mov	r2, r3
	mov	r1, r3
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	beq	.L165
	mvn	r0, #6
	ldmfd	sp!, {r4, r5, r6, pc}
.L164:
	mov	r3, r0
	mov	r1, r0
	mov	r2, r5
	mov	r0, #2304
	bl	sd_spin_send_cmd(PLT)
	subs	r3, r0, #0
	bne	.L156
	mov	r2, r5
	mov	r1, r3
	mov	r0, #1792
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L157
	ubfx	r0, r4, #30, #1
	ldmfd	sp!, {r4, r5, r6, pc}
.L150:
	mvn	r0, #0
	ldmfd	sp!, {r4, r5, r6, pc}
.L151:
	mvn	r0, #1
	ldmfd	sp!, {r4, r5, r6, pc}
.L153:
	mvn	r0, #3
	ldmfd	sp!, {r4, r5, r6, pc}
.L152:
	mvn	r0, #2
	ldmfd	sp!, {r4, r5, r6, pc}
.L156:
	mvn	r0, #7
	ldmfd	sp!, {r4, r5, r6, pc}
.L154:
	mvn	r0, #5
	ldmfd	sp!, {r4, r5, r6, pc}
.L157:
	mvn	r0, #8
	ldmfd	sp!, {r4, r5, r6, pc}
	.size	sd_spin_init_mem_card, .-sd_spin_init_mem_card
	.align	2
	.global	sd_dma_spin_read
	.type	sd_dma_spin_read, %function
sd_dma_spin_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, #0
	movt	r4, 57360
	ldr	r3, [r4, #36]
	tst	r3, #65536
	beq	.L170
	str	r0, [r4]
	mov	r3, #1
	mov	r0, #4608
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L171
	mov	r1, r4
	b	.L169
.L168:
	tst	r3, #2
	bne	.L175
.L169:
	ldrh	r3, [r1, #48]
	mov	r2, #0
	movt	r2, 57360
	uxth	r3, r3
	tst	r3, #32768
	beq	.L168
	mvn	r3, #3072
	mvn	r0, #2
	strh	r3, [r2, #50]	@ movhi
	ldmfd	sp!, {r4, pc}
.L175:
	mov	r3, #2
	mov	r0, #0
	strh	r3, [r2, #48]	@ movhi
	ldmfd	sp!, {r4, pc}
.L170:
	mvn	r0, #0
	ldmfd	sp!, {r4, pc}
.L171:
	mvn	r0, #1
	ldmfd	sp!, {r4, pc}
	.size	sd_dma_spin_read, .-sd_dma_spin_read
	.align	2
	.global	sd_dma_spin_write
	.type	sd_dma_spin_write, %function
sd_dma_spin_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, #0
	movt	r4, 57360
	ldr	r3, [r4, #36]
	tst	r3, #65536
	beq	.L180
	str	r0, [r4]
	mov	r3, #2
	mov	r0, #6400
	bl	sd_spin_send_cmd(PLT)
	cmp	r0, #0
	bne	.L181
	mov	r1, r4
	b	.L179
.L178:
	tst	r3, #2
	bne	.L185
.L179:
	ldrh	r3, [r1, #48]
	mov	r2, #0
	movt	r2, 57360
	uxth	r3, r3
	tst	r3, #32768
	beq	.L178
	mvn	r3, #3072
	mvn	r0, #2
	strh	r3, [r2, #50]	@ movhi
	ldmfd	sp!, {r4, pc}
.L185:
	mov	r3, #2
	mov	r0, #0
	strh	r3, [r2, #48]	@ movhi
	ldmfd	sp!, {r4, pc}
.L180:
	mvn	r0, #0
	ldmfd	sp!, {r4, pc}
.L181:
	mvn	r0, #1
	ldmfd	sp!, {r4, pc}
	.size	sd_dma_spin_write, .-sd_dma_spin_write
	.align	2
	.global	puts_uint
	.type	puts_uint, %function
puts_uint:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, lr}
	mov	lr, r0
	ldr	r6, .L190
	sub	sp, sp, #36
	ldr	r7, .L190+4
	add	r5, sp, #12
.LPIC10:
	add	r6, pc, r6
	mov	r4, sp
.LPIC11:
	add	r7, pc, r7
	mov	ip, #28
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	mov	r3, sp
	ldmia	r7, {r0, r1, r2}
	ldr	r6, [r6]
	stmia	r3!, {r0, r1}
	mov	r1, r2, lsr #16
	strh	r2, [r3], #2	@ movhi
	strb	r6, [r5]
	strb	r1, [r3]
.L187:
	mov	r3, lr, lsr ip
	add	r1, sp, #32
	and	r3, r3, #15
	rsb	r2, ip, #28
	add	r3, r1, r3
	sub	ip, ip, #4
	add	r2, r1, r2, asr #2
	cmn	ip, #4
	ldrb	r3, [r3, #-20]	@ zero_extendqisi2
	strb	r3, [r2, #-32]
	bne	.L187
	mov	r0, r4
	bl	uart_spin_puts(PLT)
	add	sp, sp, #36
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, pc}
.L191:
	.align	2
.L190:
	.word	.LC0-(.LPIC10+8)
	.word	.LC1-(.LPIC11+8)
	.size	puts_uint, .-puts_uint
	.align	2
	.global	ilog2
	.type	ilog2, %function
ilog2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, r0, lsr #2
	movw	r1, #21845
	orr	r0, r3, r0, lsr #1
	bfi	r1, r1, #16, #16
	str	lr, [sp, #-4]!
	orr	r0, r0, r0, lsr #2
	movw	lr, #21845
	bfi	lr, lr, #16, #16
	orr	r0, r0, r0, lsr #4
	movw	r2, #13107
	mov	ip, r2
	bfi	r2, r2, #16, #16
	orr	r0, r0, r0, lsr #8
	bfi	ip, ip, #16, #16
	movw	r3, #3855
	bfi	r3, r3, #16, #16
	orr	r0, r0, r0, lsr #16
	and	r1, r1, r0
	and	r0, lr, r0, lsr #1
	add	r1, r1, r0
	and	r2, r2, r1
	and	r1, ip, r1, lsr #2
	add	r2, r2, r1
	add	r2, r2, r2, lsr #4
	and	r3, r3, r2
	add	r3, r3, r3, lsr #8
	bic	r0, r3, #-16777216
	bic	r0, r0, #65280
	add	r0, r0, r0, lsr #16
	uxth	r0, r0
	ldr	pc, [sp], #4
	.size	ilog2, .-ilog2
	.align	2
	.global	write_page
	.type	write_page, %function
write_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r1, r1, lsr #20
	mov	r0, r0, lsr #20
	mov	r1, r1, asl #20
	orr	r1, r1, #1056
	orr	r1, r1, #6
	str	r1, [r2, r0, asl #2]
	bx	lr
	.size	write_page, .-write_page
	.align	2
	.global	remove_lower_address
	.type	remove_lower_address, %function
remove_lower_address:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.syntax divided
@ 53 "mmu.h" 1
	isb
@ 0 "" 2
	.arm
	.syntax divided
	mov	r2, #0
	mov	r1, r2
.L196:
	mov	r3, r2, lsr #20
	add	r2, r2, #1048576
	cmp	r2, #8388608
	mov	r3, r3, asl #2
	add	r3, r3, #-2147483648
	add	r3, r3, #1064960
	str	r1, [r3]
	bne	.L196
	.syntax divided
@ 58 "mmu.h" 1
	isb
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	bx	lr
	.size	remove_lower_address, .-remove_lower_address
	.align	2
	.global	create_first_page
	.type	create_first_page, %function
create_first_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, #0
.L199:
	mov	r1, r4, asl #20
	mov	r2, #1064960
	add	r4, r4, #1
	mov	r0, r1
	bl	write_page(PLT)
	cmp	r4, #4096
	bne	.L199
	mov	r4, #0
.L200:
	mov	r1, r4
	add	r0, r4, #-2147483648
	mov	r2, #1064960
	add	r4, r4, #1048576
	bl	write_page(PLT)
	cmp	r4, #536870912
	bne	.L200
	ldmfd	sp!, {r4, pc}
	.size	create_first_page, .-create_first_page
	.align	2
	.global	enable_mmu
	.type	enable_mmu, %function
enable_mmu:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	bl	create_first_page(PLT)
	mov	r3, #1064960
	.syntax divided
@ 78 "mmu.h" 1
	mov r0, r3
	mcr p15,0,r0,c2,c0,0
	
@ 0 "" 2
@ 84 "mmu.h" 1
	ldr r0, =0x7
	mcr p15,0,r0,c3,c0,0
	
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
@ 90 "mmu.h" 1
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0x1
	mcr p15,0,r0,c1,c0,0
	isb
	
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	mov	r2, #3
	movt	r3, 63728
	str	r2, [r3]
	ldmfd	sp!, {r4, pc}
	.size	enable_mmu, .-enable_mmu
	.align	2
	.global	enable_cache
	.type	enable_cache, %function
enable_cache:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.syntax divided
@ 112 "mmu.h" 1
	ldr r1, =0x1804
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,r1
	mcr p15,0,r0,c1,c0,0
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #8192
	mov	r2, #1
	movt	r3, 63728
	str	r2, [r3, #256]
	bx	lr
	.size	enable_cache, .-enable_cache
	.align	2
	.global	mem_init
	.type	mem_init, %function
mem_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L209
	mov	r2, #0
	ldr	r0, .L209+4
	movt	r2, 32896
.LPIC12:
	add	r3, pc, r3
	ldr	r1, .L209+8
	str	lr, [sp, #-4]!
	mov	ip, #0
	ldr	r0, [r3, r0]
	mov	lr, #511705088
	str	r2, [r0]
	str	lr, [r2]
	str	ip, [r2, #4]
	ldr	r3, [r3, r1]
	str	ip, [r3]
	ldr	pc, [sp], #4
.L210:
	.align	2
.L209:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC12+8)
	.word	free_head(GOT)
	.word	mem_lock(GOT)
	.size	mem_init, .-mem_init
	.align	2
	.global	kalloc
	.type	kalloc, %function
kalloc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	subs	r4, r0, #0
	ldr	r3, .L225
.LPIC13:
	add	r3, pc, r3
	beq	.L222
	ldr	r2, .L225+4
	mov	r1, #1
	ldr	lr, [r3, r2]
	.syntax divided
@ 22 "device/../spinlock.h" 1
	1: ldrex r2,[lr]
	teq r2,#0
	strexeq r2, r1,[lr]
	teqeq r2 ,#0
	bne 1b
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r2, .L225+8
	mov	r1, r4, asl #12
	ldr	r5, [r3, r2]
	ldr	ip, [r5]
	cmp	ip, #0
	moveq	r0, ip
	beq	.L214
	ldr	r3, [ip]
	cmp	r1, r3
	movls	r0, ip
	movls	r2, #0
	bls	.L216
	mov	r2, ip
	b	.L215
.L217:
	ldr	r3, [r0]
	cmp	r1, r3
	bls	.L216
	mov	r2, r0
.L215:
	ldr	r0, [r2, #4]
	cmp	r0, #0
	bne	.L217
.L214:
	mov	r3, #0
	str	r3, [lr]
	ldmfd	sp!, {r4, r5, r6, pc}
.L216:
	cmp	r1, r3
	bcs	.L218
	ldr	r6, [r0, #4]
	cmp	ip, r0
	add	ip, r1, r0
	rsb	r3, r1, r3
	str	r3, [r0, r4, asl #12]
	str	r6, [ip, #4]
	streq	ip, [r5]
	strne	ip, [r2, #4]
	b	.L214
.L218:
	ldr	r3, [r0, #4]
	cmp	r0, ip
	streq	r3, [r5]
	strne	r3, [r2, #4]
	b	.L214
.L222:
	mov	r0, r4
	ldmfd	sp!, {r4, r5, r6, pc}
.L226:
	.align	2
.L225:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC13+8)
	.word	mem_lock(GOT)
	.word	free_head(GOT)
	.size	kalloc, .-kalloc
	.align	2
	.global	kfree
	.type	kfree, %function
kfree:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #0
	ldr	r3, .L244
.LPIC14:
	add	r3, pc, r3
	beq	.L237
	ldr	r2, .L244+4
	mov	ip, #1
	stmfd	sp!, {r4, r5, lr}
	ldr	lr, [r3, r2]
	.syntax divided
@ 22 "device/../spinlock.h" 1
	1: ldrex r2,[lr]
	teq r2,#0
	strexeq r2, ip,[lr]
	teqeq r2 ,#0
	bne 1b
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r2, .L244+8
	mov	r1, r1, asl #12
	ldr	r3, [r3, r2]
	ldr	r2, [r3]
	str	r1, [r0]
	cmp	r0, r2
	mov	ip, r2
	bcc	.L229
	cmp	r2, #0
	cmpne	r0, r2
	movls	r4, #0
	movls	r3, r2
	movhi	r4, #1
	movls	r2, r4
	bhi	.L234
	b	.L231
.L238:
	mov	r2, r3
.L234:
	ldr	r3, [r2, #4]
	cmp	r3, #0
	cmpne	r0, r3
	mov	ip, r3
	bhi	.L238
	mov	r4, r2
.L231:
	cmp	r3, #0
	str	r3, [r0, #4]
	beq	.L235
	add	r1, r0, r1
	cmp	r1, ip
	ldmcsia	r3, {r1, r5}
	rsbcs	r3, r0, r1
	addcs	ip, r3, ip
	strcs	r5, [r0, #4]
	strcs	ip, [r0]
.L235:
	ldr	r1, [r2]
	add	r3, r1, r4
	cmp	r0, r3
	strhi	r0, [r2, #4]
	ldmlsia	r0, {r3, ip}
	addls	r1, r3, r1
	strls	r1, [r2]
	strls	ip, [r2, #4]
	b	.L233
.L229:
	add	r1, r1, r0
	str	r2, [r0, #4]
	cmp	r2, r1
	ldmlsia	r2, {r1, ip}
	addls	r2, r2, r1
	rsbls	r2, r0, r2
	stmlsia	r0, {r2, ip}
	str	r0, [r3]
.L233:
	mov	r0, #0
	str	r0, [lr]
	ldmfd	sp!, {r4, r5, pc}
.L237:
	mvn	r0, #0
	bx	lr
.L245:
	.align	2
.L244:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC14+8)
	.word	mem_lock(GOT)
	.word	free_head(GOT)
	.size	kfree, .-kfree
	.align	2
	.global	divmod
	.type	divmod, %function
divmod:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r0, lsr r1
	cmp	r0, r3, asl r1
	movne	r0, #1
	moveq	r0, #0
	bx	lr
	.size	divmod, .-divmod
	.align	2
	.global	kalloc_align
	.type	kalloc_align, %function
kalloc_align:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
	mov	r7, r0, asl #1
	sub	r7, r7, #1
	mov	r8, r0
	mov	r0, r7
	bl	kalloc(PLT)
	subs	r9, r0, #0
	beq	.L252
	mov	r6, r8, asl #12
	mov	r3, r9
	mov	r5, #0
	b	.L249
.L250:
	add	r5, r5, #1
.L249:
	mov	r0, r6
	mov	r4, r3
	bl	ilog2(PLT)
	mov	r1, r0
	mov	r0, r4
	bl	divmod(PLT)
	add	r3, r4, #4096
	cmp	r0, #0
	bne	.L250
	cmp	r5, #0
	bne	.L257
.L251:
	add	r0, r5, r8
	cmp	r7, r0
	bls	.L248
	rsb	r1, r8, r7
	add	r0, r9, r0, lsl #12
	rsb	r1, r5, r1
	bl	kfree(PLT)
.L248:
	mov	r0, r4
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
.L257:
	mov	r1, r5
	mov	r0, r9
	bl	kfree(PLT)
	b	.L251
.L252:
	mov	r4, r9
	mov	r0, r4
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
	.size	kalloc_align, .-kalloc_align
	.align	2
	.global	showFreememory
	.type	showFreememory, %function
showFreememory:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L264
	stmfd	sp!, {r4, lr}
.LPIC15:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldr	r3, .L264+4
	ldr	r2, .L264+8
.LPIC16:
	add	r3, pc, r3
	ldr	r3, [r3, r2]
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L261
.L260:
	mov	r0, r4
	bl	puts_uint(PLT)
	ldr	r0, [r4]
	bl	puts_uint(PLT)
	ldr	r4, [r4, #4]
	cmp	r4, #0
	bne	.L260
.L261:
	ldr	r0, .L264+12
	ldmfd	sp!, {r4, lr}
.LPIC17:
	add	r0, pc, r0
	b	uart_spin_puts(PLT)
.L265:
	.align	2
.L264:
	.word	.LC2-(.LPIC15+8)
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC16+8)
	.word	free_head(GOT)
	.word	.LC3-(.LPIC17+8)
	.size	showFreememory, .-showFreememory
	.align	2
	.global	memcpy
	.type	memcpy, %function
memcpy:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r2, #0
	bxeq	lr
	add	r2, r1, r2
.L268:
	ldrb	r3, [r1], #1	@ zero_extendqisi2
	cmp	r1, r2
	strb	r3, [r0], #1
	bne	.L268
	bx	lr
	.size	memcpy, .-memcpy
	.align	2
	.global	memset
	.type	memset, %function
memset:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r2, #0
	bxeq	lr
	add	r2, r0, r2
.L273:
	strb	r1, [r0], #1
	cmp	r0, r2
	bne	.L273
	bx	lr
	.size	memset, .-memset
	.align	2
	.global	slab_init
	.type	slab_init, %function
slab_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r0, #1
	bl	kalloc(PLT)
	ldr	r4, .L282
.LPIC26:
	add	r4, pc, r4
	cmp	r0, #0
	ldmeqfd	sp!, {r4, pc}
	ldr	ip, .L282+4
	add	r1, r0, #4096
	ldr	r3, .L282+8
	mov	r2, #0
	ldr	lr, [r4, ip]
	ldr	r3, [r4, r3]
	ldr	ip, [lr]
	b	.L279
.L278:
	ldr	r2, [r3]
.L279:
	str	r0, [r3]
	str	r2, [r0], #128
	cmp	r0, r1
	bne	.L278
	add	r3, ip, #32
	mov	r0, #1
	str	r3, [lr]
	ldmfd	sp!, {r4, pc}
.L283:
	.align	2
.L282:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC26+8)
	.word	slab_num(GOT)
	.word	slab_header(GOT)
	.size	slab_init, .-slab_init
	.align	2
	.global	new_slab
	.type	new_slab, %function
new_slab:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	ldr	r4, .L290
	ldr	r3, .L290+4
.LPIC27:
	add	r4, pc, r4
	ldr	r5, [r4, r3]
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L289
.L285:
	ldr	r2, .L290+8
	sub	r3, r3, #1
	ldr	r2, [r4, r2]
	ldr	r0, [r2]
	ldr	r1, [r0]
	str	r3, [r5]
	str	r1, [r2]
	ldmfd	sp!, {r4, r5, r6, pc}
.L289:
	bl	slab_init(PLT)
	cmp	r0, #0
	ldmeqfd	sp!, {r4, r5, r6, pc}
	ldr	r3, [r5]
	b	.L285
.L291:
	.align	2
.L290:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC27+8)
	.word	slab_num(GOT)
	.word	slab_header(GOT)
	.size	new_slab, .-new_slab
	.align	2
	.global	free_slab
	.type	free_slab, %function
free_slab:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L293
	ldr	r1, .L293+4
.LPIC28:
	add	r3, pc, r3
	ldr	r2, .L293+8
	ldr	r1, [r3, r1]
	ldr	ip, [r1]
	str	r0, [r1]
	str	ip, [r0]
	ldr	r2, [r3, r2]
	ldr	r3, [r2]
	add	r3, r3, #1
	str	r3, [r2]
	bx	lr
.L294:
	.align	2
.L293:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC28+8)
	.word	slab_header(GOT)
	.word	slab_num(GOT)
	.size	free_slab, .-free_slab
	.align	2
	.global	pkb_init
	.type	pkb_init, %function
pkb_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r0, #1
	bl	kalloc(PLT)
	ldr	r4, .L302
.LPIC29:
	add	r4, pc, r4
	cmp	r0, #0
	ldmeqfd	sp!, {r4, pc}
	ldr	ip, .L302+4
	add	r1, r0, #4096
	ldr	r3, .L302+8
	mov	r2, #0
	ldr	lr, [r4, ip]
	ldr	r3, [r4, r3]
	ldr	ip, [lr]
	str	r0, [r3]
	str	r2, [r0], #1024
	cmp	r0, r1
	beq	.L301
.L297:
	ldr	r2, [r3]
	str	r0, [r3]
	str	r2, [r0], #1024
	cmp	r0, r1
	bne	.L297
.L301:
	add	r3, ip, #4
	mov	r0, #1
	str	r3, [lr]
	ldmfd	sp!, {r4, pc}
.L303:
	.align	2
.L302:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC29+8)
	.word	pkb_num(GOT)
	.word	kb_header(GOT)
	.size	pkb_init, .-pkb_init
	.align	2
	.global	new_kb
	.type	new_kb, %function
new_kb:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	ldr	r4, .L310
	ldr	r3, .L310+4
.LPIC30:
	add	r4, pc, r4
	ldr	r5, [r4, r3]
	ldr	r3, [r5]
	cmp	r3, #0
	beq	.L309
.L305:
	ldr	r2, .L310+8
	sub	r3, r3, #1
	ldr	r2, [r4, r2]
	ldr	r0, [r2]
	ldr	r1, [r0]
	str	r3, [r5]
	str	r1, [r2]
	ldmfd	sp!, {r4, r5, r6, pc}
.L309:
	bl	pkb_init(PLT)
	cmp	r0, #0
	ldmeqfd	sp!, {r4, r5, r6, pc}
	ldr	r3, [r5]
	b	.L305
.L311:
	.align	2
.L310:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC30+8)
	.word	pkb_num(GOT)
	.word	kb_header(GOT)
	.size	new_kb, .-new_kb
	.align	2
	.global	free_kb
	.type	free_kb, %function
free_kb:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L313
	ldr	r1, .L313+4
.LPIC31:
	add	r3, pc, r3
	ldr	r2, .L313+8
	ldr	r1, [r3, r1]
	ldr	ip, [r1]
	str	r0, [r1]
	str	ip, [r0]
	ldr	r2, [r3, r2]
	ldr	r3, [r2]
	add	r3, r3, #1
	str	r3, [r2]
	bx	lr
.L314:
	.align	2
.L313:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC31+8)
	.word	kb_header(GOT)
	.word	pkb_num(GOT)
	.size	free_kb, .-free_kb
	.align	2
	.global	syscall_handler
	.type	syscall_handler, %function
syscall_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r4, r0
	ldr	r0, .L320
.LPIC32:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	mov	r0, r4
	bl	puts_uint(PLT)
	ldr	r3, [r4]
	cmp	r3, #16
	ldmnefd	sp!, {r4, pc}
	mov	r3, #0
	ldr	r0, [r3, #16]
	ldmfd	sp!, {r4, lr}
	b	uart_spin_puts(PLT)
.L321:
	.align	2
.L320:
	.word	.LC4-(.LPIC32+8)
	.size	syscall_handler, .-syscall_handler
	.align	2
	.global	pcb_init
	.type	pcb_init, %function
pcb_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L325
	mov	r3, #0
	ldr	r0, .L325+4
	mov	r1, r3
.LPIC33:
	add	r2, pc, r2
	ldr	r2, [r2, r0]
.L323:
	str	r3, [r2, #8]
	add	r3, r3, #1
	cmp	r3, #128
	str	r1, [r2]
	add	r2, r2, #76
	bne	.L323
	bx	lr
.L326:
	.align	2
.L325:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC33+8)
	.word	pcb(GOT)
	.size	pcb_init, .-pcb_init
	.align	2
	.global	copyproc
	.type	copyproc, %function
copyproc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, lr}
	add	ip, r0, #8
	ldr	r4, [r1, #8]
	add	r3, r1, #8
	ldr	r7, [r1, #4]
	add	lr, r1, #56
	ldr	r6, [r1, #60]
	ldr	r5, [r1, #64]
	str	r2, [r0]
	str	r4, [r0, #8]
	ldr	r2, [r1, #68]
	ldr	r4, [r1, #72]
	str	r7, [r0, #4]
	str	r6, [r0, #60]
	str	r5, [r0, #64]
	str	r4, [r0, #72]
	str	r2, [r0, #68]
.L328:
	ldr	r2, [r3, #4]!
	cmp	r3, lr
	str	r2, [ip, #4]!
	bne	.L328
	ldmfd	sp!, {r4, r5, r6, r7, pc}
	.size	copyproc, .-copyproc
	.align	2
	.global	getCPUId
	.type	getCPUId, %function
getCPUId:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	movt	r3, 63728
	ldr	r0, [r3, #260]
	subs	r0, r0, #240
	movne	r0, #1
	bx	lr
	.size	getCPUId, .-getCPUId
	.align	2
	.global	proc_init
	.type	proc_init, %function
proc_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	bl	getCPUId(PLT)
	mov	r2, #76
	ldr	r3, .L334
	mov	ip, #0
	ldr	r1, .L334+4
.LPIC34:
	add	r3, pc, r3
	ldr	r3, [r3, r1]
	mul	r0, r2, r0
	str	ip, [r3, r0]
	ldmfd	sp!, {r4, pc}
.L335:
	.align	2
.L334:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC34+8)
	.word	proc(GOT)
	.size	proc_init, .-proc_init
	.align	2
	.global	schedule_init
	.type	schedule_init, %function
schedule_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r5, #0
	ldr	r4, .L338
	ldr	r3, .L338+4
.LPIC35:
	add	r4, pc, r4
	ldr	r3, [r4, r3]
	str	r5, [r3]
	bl	pcb_init(PLT)
	ldr	r3, .L338+8
	ldr	r3, [r4, r3]
	str	r5, [r3]
	ldmfd	sp!, {r4, r5, r6, pc}
.L339:
	.align	2
.L338:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC35+8)
	.word	schedule_lock(GOT)
	.word	pcb_counter(GOT)
	.size	schedule_init, .-schedule_init
	.align	2
	.global	schedule
	.type	schedule, %function
schedule:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L356
	mov	r0, #76
	ldr	ip, .L356+4
.LPIC36:
	add	r3, pc, r3
	ldr	r1, .L356+8
	stmfd	sp!, {r4, r5, lr}
	mov	r4, #1
	ldr	lr, [r3, ip]
	ldr	r2, .L356+12
	ldr	r5, [r3, r1]
	ldr	ip, [r3, r2]
	ldr	r3, [lr]
.L347:
	.syntax divided
@ 22 "device/../spinlock.h" 1
	1: ldrex r2,[r5]
	teq r2,#0
	strexeq r2, r4,[r5]
	teqeq r2 ,#0
	bne 1b
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r2, #128
	b	.L346
.L341:
	add	r3, r3, #1
	cmp	r3, #128
	movcs	r3, #0
	subs	r2, r2, #1
	beq	.L355
.L346:
	mul	r1, r0, r3
	ldr	r1, [ip, r1]
	cmp	r1, #1
	bne	.L341
	mov	r2, #76
	add	r1, r3, #1
	mul	r3, r2, r3
	cmp	r1, #127
	mov	r2, #2
	strls	r1, [lr]
	add	r0, ip, r3
	str	r2, [ip, r3]
	movhi	r3, #0
	strhi	r3, [lr]
	mov	r3, #0
	str	r3, [r5]
	ldmfd	sp!, {r4, r5, pc}
.L355:
	str	r2, [r5]
	b	.L347
.L357:
	.align	2
.L356:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC36+8)
	.word	pcb_counter(GOT)
	.word	schedule_lock(GOT)
	.word	pcb(GOT)
	.size	schedule, .-schedule
	.align	2
	.global	timer_schedule
	.type	timer_schedule, %function
timer_schedule:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	bl	getCPUId(PLT)
	ldr	r4, .L360
.LPIC37:
	add	r4, pc, r4
	mov	r2, r4
	mov	r3, r0
	.syntax divided
@ 75 "mode.h" 1
	mov r0, #0xF
	mrs r1, cpsr
	orr r1, r1, r0
	msr cpsr, r1
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r0, #76
	ldr	r1, .L360+4
	mul	r3, r0, r3
	ldr	r0, [r4, r1]
	add	r2, r0, r3
	add	r2, r2, #68
	.syntax divided
@ 47 "schedule.h" 1
	str r12,[r2]
	
@ 0 "" 2
	.arm
	.syntax divided
	add	r3, r3, #56
	add	r0, r3, r0
	add	r3, r0, #8
	.syntax divided
@ 51 "schedule.h" 1
	str lr,[r3]
	
@ 0 "" 2
	.arm
	.syntax divided
	add	r0, r0, #4
	.syntax divided
@ 55 "schedule.h" 1
	str sp,[r0]
	
@ 0 "" 2
	.arm
	.syntax divided
	ldmfd	sp!, {r4, pc}
.L361:
	.align	2
.L360:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC37+8)
	.word	proc(GOT)
	.size	timer_schedule, .-timer_schedule
	.align	2
	.global	ICD_init
	.type	ICD_init, %function
ICD_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, #5120
	movw	r1, #5216
	movt	r2, 63728
	movt	r1, 63728
.L363:
	movw	r3, #41120
	bfi	r3, r3, #16, #16
	str	r3, [r2], #4
	cmp	r2, r1
	bne	.L363
	mov	r2, #6144
	movw	r1, #6240
	movt	r2, 63728
	movt	r1, 63728
.L364:
	movw	r3, #771
	bfi	r3, r3, #16, #16
	str	r3, [r2], #4
	cmp	r2, r1
	bne	.L364
	mov	r3, #4096
	mvn	r2, #0
	movt	r3, 63728
	mov	r1, #1
	str	r2, [r3, #256]
	str	r2, [r3, #260]
	str	r2, [r3, #264]
	str	r1, [r3]
	bx	lr
	.size	ICD_init, .-ICD_init
	.align	2
	.global	ICC_init
	.type	ICC_init, %function
ICC_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	mov	r2, #1
	movt	r3, 63728
	str	r0, [r3, #260]
	str	r2, [r3, #256]
	bx	lr
	.size	ICC_init, .-ICC_init
	.align	2
	.global	read_cpsr
	.type	read_cpsr, %function
read_cpsr:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L370
	stmfd	sp!, {r4, lr}
.LPIC38:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldr	r3, .L370+4
	ldr	r2, .L370+8
.LPIC39:
	add	r3, pc, r3
	ldr	r3, [r3, r2]
	.syntax divided
@ 68 "handler.h" 1
	str r0,[r3]
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r0, [r3]
	ldmfd	sp!, {r4, lr}
	b	puts_uint(PLT)
.L371:
	.align	2
.L370:
	.word	.LC5-(.LPIC38+8)
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC39+8)
	.word	cpsr(GOT)
	.size	read_cpsr, .-read_cpsr
	.align	2
	.global	interrupt_init
	.type	interrupt_init, %function
interrupt_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.syntax divided
@ 27 "mode.h" 1
	ldr r1, =0xFFFFFFF0
	mrs r0, cpsr
	and r0, r0, r1
	orr r0, r0, #3
	msr cpsr, r0
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	movt	r3, 40944
	.syntax divided
@ 79 "handler.h" 1
	mov sp, r3
	
@ 0 "" 2
@ 63 "mode.h" 1
	ldr r1, =0xFFFFFFF0
	mrs r0, cpsr
	and r0, r0, r1
	orr r0, r0, #2
	msr cpsr, r0
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	movt	r3, 40928
	.syntax divided
@ 84 "handler.h" 1
	mov sp, r3
	
@ 0 "" 2
@ 39 "mode.h" 1
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr, r0
	isb
	
@ 0 "" 2
@ 75 "mode.h" 1
	mov r0, #0xF
	mrs r1, cpsr
	orr r1, r1, r0
	msr cpsr, r1
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #-2147483648
	.syntax divided
@ 91 "handler.h" 1
	ldr r0, =vector_table
	movs r1, r3
	add r0, r0, r1
	mcr p15, 0, r0, c12, c0, 0
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	bx	lr
	.size	interrupt_init, .-interrupt_init
	.align	2
	.global	SWI_interrupt
	.type	SWI_interrupt, %function
SWI_interrupt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r4, r0
	ldr	r0, .L380
	mov	r5, r1
.LPIC40:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	cmp	r4, #2
	beq	.L375
	cmp	r4, #256
	beq	.L376
	cmp	r4, #1
	ldmnefd	sp!, {r4, r5, r6, pc}
	mov	r0, r5
	bl	puts_uint(PLT)
	ldmfd	sp!, {r4, r5, r6, lr}
	b	read_cpsr(PLT)
.L376:
	mov	r0, r5
	ldmfd	sp!, {r4, r5, r6, lr}
	b	syscall_handler(PLT)
.L375:
	.syntax divided
@ 111 "handler.h" 1
	mrs r0,spsr
	ldr r1, =0xFFFFFFF0
	and r0, r0, r1
	orr r0, r0, #2
	msr spsr, r0
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r0, .L380+4
	ldmfd	sp!, {r4, r5, r6, lr}
.LPIC41:
	add	r0, pc, r0
	b	uart_spin_puts(PLT)
.L381:
	.align	2
.L380:
	.word	.LC6-(.LPIC40+8)
	.word	.LC7-(.LPIC41+8)
	.size	SWI_interrupt, .-SWI_interrupt
	.align	2
	.global	IRQ_interrupt
	.type	IRQ_interrupt, %function
IRQ_interrupt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, #0
	movt	r3, 63728
	stmfd	sp!, {r4, r5, r6, lr}
	ldr	r4, [r3, #268]
	ldr	r5, .L389
	ubfx	r4, r4, #0, #10
	cmp	r4, #29
.LPIC42:
	add	r5, pc, r5
	beq	.L387
.L383:
	mov	r2, #0
	movt	r2, 63728
	ldr	r3, [r2, #272]
	bic	r3, r3, #1020
	bic	r3, r3, #3
	orr	r4, r3, r4
	str	r4, [r2, #272]
	ldmfd	sp!, {r4, r5, r6, pc}
.L387:
	mov	r6, r0
	bl	getCPUId(PLT)
	mov	r3, #76
	ldr	r2, .L389+4
	ldr	r2, [r5, r2]
	mul	r0, r3, r0
	ldr	r3, [r2, r0]
	cmp	r3, #2
	beq	.L388
.L385:
	mov	r2, #0
	mov	r3, #4096
	movt	r2, 63728
	movt	r3, 63728
	mov	r0, #1
	mov	r1, #536870912
	str	r0, [r2, #1548]
	str	r1, [r3, #640]
	b	.L383
.L388:
	mov	r0, r6
	bl	timer_schedule(PLT)
	b	.L385
.L390:
	.align	2
.L389:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC42+8)
	.word	proc(GOT)
	.size	IRQ_interrupt, .-IRQ_interrupt
	.align	2
	.global	PrefetchAbort_interrupt
	.type	PrefetchAbort_interrupt, %function
PrefetchAbort_interrupt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L393
	stmfd	sp!, {r4, lr}
.LPIC43:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldmfd	sp!, {r4, lr}
	b	uart_spin_getbyte(PLT)
.L394:
	.align	2
.L393:
	.word	.LC8-(.LPIC43+8)
	.size	PrefetchAbort_interrupt, .-PrefetchAbort_interrupt
	.align	2
	.global	DataAbortHandler_interrupt
	.type	DataAbortHandler_interrupt, %function
DataAbortHandler_interrupt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L397
	stmfd	sp!, {r4, lr}
.LPIC44:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldmfd	sp!, {r4, lr}
	b	uart_spin_getbyte(PLT)
.L398:
	.align	2
.L397:
	.word	.LC9-(.LPIC44+8)
	.size	DataAbortHandler_interrupt, .-DataAbortHandler_interrupt
	.align	2
	.global	new_ttb
	.type	new_ttb, %function
new_ttb:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r0, #4
	bl	kalloc_align(PLT)
	mov	r2, #16384
	mov	r1, #0
	mov	r4, r0
	bl	memset(PLT)
	mov	r1, #24576
	add	r0, r4, #8192
	movt	r1, 32784
	mov	r2, #8192
	bl	memcpy(PLT)
	mov	r0, r4
	ldmfd	sp!, {r4, pc}
	.size	new_ttb, .-new_ttb
	.align	2
	.global	write_process_page
	.type	write_process_page, %function
write_process_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r2]
	cmp	r3, #0
	beq	.L413
	stmfd	sp!, {r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	mov	r4, r1
	add	r5, r2, #16
	b	.L405
.L404:
	ldr	r3, [r6, r7, asl #2]
	ubfx	r1, r4, #12, #8
	ldr	r0, [r5, #-16]
	add	r4, r4, #4096
	ldr	r2, [r5], #16
	bic	r3, r3, #1020
	bic	r3, r3, #3
	orr	r0, r0, #6
	cmp	r2, #0
	str	r0, [r3, r1, asl #2]
	beq	.L414
.L405:
	mov	r7, r4, lsr #20
	ldr	r8, [r6, r7, asl #2]
	cmp	r8, #0
	bne	.L404
	bl	new_kb(PLT)
	mov	r1, r8
	mov	r2, #1024
	subs	r8, r0, #0
	beq	.L407
	add	r8, r8, #-2147483648
	bl	memset(PLT)
	orr	r8, r8, #1
	str	r8, [r6, r7, asl #2]
	b	.L404
.L414:
	mov	r0, #1
	ldmfd	sp!, {r4, r5, r6, r7, r8, pc}
.L407:
	mov	r0, r8
	ldmfd	sp!, {r4, r5, r6, r7, r8, pc}
.L413:
	mov	r0, #1
	bx	lr
	.size	write_process_page, .-write_process_page
	.align	2
	.global	free_process_memory
	.type	free_process_memory, %function
free_process_memory:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #12
	ldr	r3, .L431
	add	r9, r0, #8192
	ldr	r6, .L431+4
	mov	r7, r0
	ldr	r5, .L431+8
.LPIC45:
	add	r3, pc, r3
	str	r0, [sp, #4]
.LPIC46:
	add	r6, pc, r6
	str	r3, [sp]
.LPIC47:
	add	r5, pc, r5
	b	.L419
.L416:
	add	r7, r7, #4
	cmp	r9, r7
	beq	.L429
.L419:
	ldr	r3, [r7]
	cmp	r3, #0
	beq	.L416
	ldr	r8, [r7]
	ldr	r0, [sp]
	bic	r8, r8, #1020
	bl	uart_spin_puts(PLT)
	bic	r8, r8, #3
	add	r8, r8, #-2147483648
	add	fp, r8, #1024
	mov	r0, r8
	mov	r4, r8
	bl	puts_uint(PLT)
	b	.L418
.L417:
	add	r4, r4, #4
	cmp	fp, r4
	beq	.L430
.L418:
	ldr	r2, [r4]
	cmp	r2, #0
	beq	.L417
	ldr	r0, [r4]
	add	r4, r4, #4
	bic	r0, r0, #4080
	bic	r0, r0, #15
	add	r10, r0, #-2147483648
	mov	r0, r10
	bl	puts_uint(PLT)
	mov	r1, #1
	mov	r0, r10
	bl	kfree(PLT)
	mov	r0, r6
	bl	uart_spin_puts(PLT)
	bl	showFreememory(PLT)
	mov	r0, r5
	bl	uart_spin_puts(PLT)
	cmp	fp, r4
	bne	.L418
.L430:
	mov	r0, r8
	add	r7, r7, #4
	bl	free_kb(PLT)
	cmp	r9, r7
	bne	.L419
.L429:
	ldr	r4, [sp, #4]
	mov	r0, r4
	bl	puts_uint(PLT)
	mov	r0, r4
	mov	r1, #4
	add	sp, sp, #12
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}
	b	kfree(PLT)
.L432:
	.align	2
.L431:
	.word	.LC10-(.LPIC45+8)
	.word	.LC11-(.LPIC46+8)
	.word	.LC3-(.LPIC47+8)
	.size	free_process_memory, .-free_process_memory
	.align	2
	.global	timer_init
	.type	timer_init, %function
timer_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movw	r3, #5320
	mov	r2, #0
	movt	r3, 5
	movt	r2, 63728
	mul	r0, r3, r0
	sub	r0, r0, #1
	str	r0, [r2, #1536]
	str	r0, [r2, #1540]
	.syntax divided
@ 22 "timer.h" 1
	isb
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #2
	str	r3, [r2, #1544]
	bx	lr
	.size	timer_init, .-timer_init
	.align	2
	.global	timer_start
	.type	timer_start, %function
timer_start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	mov	r2, #7
	movt	r3, 63728
	str	r2, [r3, #1544]
	bx	lr
	.size	timer_start, .-timer_start
	.align	2
	.global	timer_close
	.type	timer_close, %function
timer_close:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #0
	mov	r2, #2
	movt	r3, 63728
	str	r2, [r3, #1544]
	bx	lr
	.size	timer_close, .-timer_close
	.align	2
	.global	cpu1_start
	.type	cpu1_start, %function
cpu1_start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L437
	mvn	r1, #0
	ldr	r2, .L437+4
.LPIC48:
	add	r3, pc, r3
	ldr	r3, [r3, r2]
	str	r3, [r1, #-15]
	.syntax divided
@ 23 "cpu1.h" 1
	isb
	sev
	
@ 0 "" 2
	.arm
	.syntax divided
	bx	lr
.L438:
	.align	2
.L437:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC48+8)
	.word	cpu1_init(GOT)
	.size	cpu1_start, .-cpu1_start
	.align	2
	.global	enable_cpu1_mmu
	.type	enable_cpu1_mmu, %function
enable_cpu1_mmu:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, #1081344
	.syntax divided
@ 32 "cpu1.h" 1
	mov r0, r3
	mcr p15,0,r0,c2,c0,0
	
@ 0 "" 2
@ 38 "cpu1.h" 1
	ldr r0, =0x7
	mcr p15,0,r0,c3,c0,0
	
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
@ 44 "cpu1.h" 1
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0x1
	mcr p15,0,r0,c1,c0,0
	isb
	
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	mov	r2, #3
	movt	r3, 63728
	str	r2, [r3]
	bx	lr
	.size	enable_cpu1_mmu, .-enable_cpu1_mmu
	.align	2
	.global	cpu1_init
	.type	cpu1_init, %function
cpu1_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	.syntax divided
@ 27 "mode.h" 1
	ldr r1, =0xFFFFFFF0
	mrs r0, cpsr
	and r0, r0, r1
	orr r0, r0, #3
	msr cpsr, r0
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	movt	r3, 40896
	.syntax divided
@ 61 "cpu1.h" 1
	mov sp,r3
	
@ 0 "" 2
@ 63 "mode.h" 1
	ldr r1, =0xFFFFFFF0
	mrs r0, cpsr
	and r0, r0, r1
	orr r0, r0, #2
	msr cpsr, r0
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	movt	r3, 40880
	.syntax divided
@ 66 "cpu1.h" 1
	mov sp,r3
	
@ 0 "" 2
@ 75 "mode.h" 1
	mov r0, #0xF
	mrs r1, cpsr
	orr r1, r1, r0
	msr cpsr, r1
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r3, #0
	movt	r3, 8144
	.syntax divided
@ 71 "cpu1.h" 1
	mov sp,r3
	
@ 0 "" 2
	.arm
	.syntax divided
	mov	r2, #16384
	mov	r1, #1064960
	mov	r0, #1081344
	bl	memcpy(PLT)
	bl	enable_cpu1_mmu(PLT)
	bl	enable_cache(PLT)
	mov	r3, #-2147483648
	.syntax divided
@ 39 "asm.h" 1
	mov r0, r3
	add sp, sp, r0
	isb
	
@ 0 "" 2
@ 28 "asm.h" 1
	mov r0, r3
	add pc, pc, r0
	isb
	
@ 0 "" 2
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
@ 85 "cpu1.h" 1
	ldr r0, =vector_table
	movs r1, r3
	add r0, r0, r1
	mcr p15, 0, r0, c12, c0, 0
	isb
	
@ 0 "" 2
@ 39 "mode.h" 1
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr, r0
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r0, .L443
.LPIC49:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	mov	r0, #224
	bl	ICC_init(PLT)
	bl	ICD_init(PLT)
	mov	r0, #1000
	bl	timer_init(PLT)
	bl	timer_start(PLT)
.L441:
	mov	r0, #1
	bl	sleep(PLT)
	b	.L441
.L444:
	.align	2
.L443:
	.word	.LC12-(.LPIC49+8)
	.size	cpu1_init, .-cpu1_init
	.align	2
	.global	test_mem
	.type	test_mem, %function
test_mem:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	mov	r0, #1
	bl	kalloc(PLT)
	mov	r5, r0
	bl	puts_uint(PLT)
	mov	r0, #1
	bl	kalloc(PLT)
	mov	r6, r0
	bl	puts_uint(PLT)
	mov	r0, #4
	bl	kalloc_align(PLT)
	mov	r4, r0
	bl	puts_uint(PLT)
	bl	showFreememory(PLT)
	bl	uart_spin_getbyte(PLT)
	mov	r0, r6
	mov	r1, #1
	bl	kfree(PLT)
	mov	r0, r5
	mov	r1, #1
	bl	kfree(PLT)
	mov	r0, r4
	mov	r1, #4
	bl	kfree(PLT)
	bl	showFreememory(PLT)
	ldmfd	sp!, {r4, r5, r6, lr}
	b	uart_spin_getbyte(PLT)
	.size	test_mem, .-test_mem
	.align	2
	.global	debug
	.type	debug, %function
debug:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L449
	stmfd	sp!, {r4, r5, r6, lr}
.LPIC50:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldr	r3, .L449+4
	ldr	r2, .L449+8
	mov	r6, #0
.LPIC51:
	add	r3, pc, r3
	ldr	r3, [r3, r2]
	str	r6, [r3]
	bl	new_ttb(PLT)
	mov	r5, r0
	mov	r0, #1
	bl	kalloc(PLT)
	mov	r4, r0
	mov	r0, #1
	bl	kalloc(PLT)
	add	r0, r0, #-2147483648
	str	r0, [r4]
	bl	puts_uint(PLT)
	mov	r0, #1
	bl	kalloc(PLT)
	add	r0, r0, #-2147483648
	str	r0, [r4, #16]
	bl	puts_uint(PLT)
	mov	r2, r4
	mov	r1, #4194304
	str	r6, [r4, #32]
	mov	r0, r5
	bl	write_process_page(PLT)
	mov	r0, r5
	bl	free_process_memory(PLT)
	ldr	r0, .L449+12
.LPIC52:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	mov	r0, r4
	mov	r1, #1
	bl	kfree(PLT)
	bl	showFreememory(PLT)
	ldmfd	sp!, {r4, r5, r6, lr}
	b	uart_spin_getbyte(PLT)
.L450:
	.align	2
.L449:
	.word	.LC13-(.LPIC50+8)
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC51+8)
	.word	pkb_num(GOT)
	.word	.LC14-(.LPIC52+8)
	.size	debug, .-debug
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	mov	r0, #1
	bl	sleep(PLT)
	mov	r4, #-2147483648
	bl	uart_init(PLT)
	bl	uart_enable(PLT)
	ldr	r0, .L454
.LPIC53:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	ldr	r0, .L454+4
.LPIC54:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	bl	enable_mmu(PLT)
	ldr	r0, .L454+8
.LPIC55:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	.syntax divided
@ 28 "asm.h" 1
	mov r0, r4
	add pc, pc, r0
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r0, .L454+12
.LPIC56:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	.syntax divided
@ 39 "asm.h" 1
	mov r0, r4
	add sp, sp, r0
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	ldr	r0, .L454+16
.LPIC57:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	.syntax divided
@ 14 "asm.h" 1
	mov r0, #0
	mcr p15,0,r0,c8,c5,0
	mcr p15,0,r0,c8,c6,0
	mcr p15,0,r0,c8,c7,0
	mcr p15, 0, r0, c7, c5, 6
	mcr p15, 0, r0, c7, c10, 4
	dsb
	isb
	
@ 0 "" 2
	.arm
	.syntax divided
	bl	enable_cache(PLT)
	bl	interrupt_init(PLT)
	ldr	r0, .L454+20
.LPIC58:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	bl	mem_init(PLT)
	ldr	r0, .L454+24
.LPIC59:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
	bl	cpu1_start(PLT)
	mov	r0, #240
	bl	ICC_init(PLT)
	bl	ICD_init(PLT)
	mov	r0, #1000
	bl	timer_init(PLT)
	bl	timer_start(PLT)
	ldr	r0, .L454+28
.LPIC60:
	add	r0, pc, r0
	bl	uart_spin_puts(PLT)
.L452:
	mov	r0, #1
	bl	sleep(PLT)
	b	.L452
.L455:
	.align	2
.L454:
	.word	.LC15-(.LPIC53+8)
	.word	.LC16-(.LPIC54+8)
	.word	.LC17-(.LPIC55+8)
	.word	.LC18-(.LPIC56+8)
	.word	.LC19-(.LPIC57+8)
	.word	.LC20-(.LPIC58+8)
	.word	.LC21-(.LPIC59+8)
	.word	.LC22-(.LPIC60+8)
	.size	main, .-main
	.global	cpsr
	.comm	pcb_counter,4,4
	.comm	schedule_lock,4,4
	.comm	pcb,9728,4
	.comm	proc,152,4
	.comm	slab_header,4,4
	.comm	kb_header,4,4
	.global	slab_num
	.global	pkb_num
	.comm	mem_lock,4,4
	.global	free_head
	.comm	puts_lock,4,4
	.global	l2cache_base
	.global	mpcore_base
	.global	gpv_qos301_iou_base
	.global	gpv_qos301_dmac_base
	.global	gpv_qos301_cpu_base
	.global	gpv_trustzone_base
	.global	debug_cpu_ptm1_base
	.global	debug_cpu_ptm0_base
	.global	debug_cpu_cti1_base
	.global	debug_cpu_cti0_base
	.global	debug_cpu_pmu1_base
	.global	debug_cpu_pmu0_base
	.global	debug_ftm_base
	.global	debug_cti_ftm_base
	.global	debug_itm_base
	.global	debug_funnel_base
	.global	debug_tpiu_base
	.global	debug_cti_etb_tpiu_base
	.global	debug_etb_base
	.global	debug_dap_rom_base
	.global	ocmc_base
	.global	axi_hp3_base
	.global	axi_hp2_base
	.global	axi_hp1_base
	.global	axi_hp0_base
	.global	devcfg_base
	.global	ddrc_base
	.global	swdt_base
	.global	dmac0_ns_base
	.global	dmac0_s_base
	.global	ttc1_base
	.global	ttc0_base
	.global	slcr_base
	.global	smc_sram1_base
	.global	smc_sram0_base
	.global	smc_nand_base
	.global	sd1_base
	.global	sd0_base
	.global	smcc_base
	.global	qspi_base
	.global	gem1_base
	.global	gem0_base
	.global	gpio_base
	.global	can1_base
	.global	can0_base
	.global	spi1_base
	.global	spi0_base
	.global	i2c1_base
	.global	i2c0_base
	.global	usb1_base
	.global	usb0_base
	.global	uart1_base
	.global	uart0_base
	.global	ddr_end
	.global	qspi_linear_base
	.global	axi_gp1_base
	.global	axi_gp0_base
	.global	ddr_base
	.global	ocm_base
	.data
	.align	2
	.type	l2cache_base, %object
	.size	l2cache_base, 4
l2cache_base:
	.word	-118480896
	.type	mpcore_base, %object
	.size	mpcore_base, 4
mpcore_base:
	.word	-118489088
	.type	gpv_qos301_iou_base, %object
	.size	gpv_qos301_iou_base, 4
gpv_qos301_iou_base:
	.word	-124485632
	.type	gpv_qos301_dmac_base, %object
	.size	gpv_qos301_dmac_base, 4
gpv_qos301_dmac_base:
	.word	-124489728
	.type	gpv_qos301_cpu_base, %object
	.size	gpv_qos301_cpu_base, 4
gpv_qos301_cpu_base:
	.word	-124493824
	.type	gpv_trustzone_base, %object
	.size	gpv_trustzone_base, 4
gpv_trustzone_base:
	.word	-124780544
	.type	debug_cpu_ptm1_base, %object
	.size	debug_cpu_ptm1_base, 4
debug_cpu_ptm1_base:
	.word	-125186048
	.type	debug_cpu_ptm0_base, %object
	.size	debug_cpu_ptm0_base, 4
debug_cpu_ptm0_base:
	.word	-125190144
	.type	debug_cpu_cti1_base, %object
	.size	debug_cpu_cti1_base, 4
debug_cpu_cti1_base:
	.word	-125202432
	.type	debug_cpu_cti0_base, %object
	.size	debug_cpu_cti0_base, 4
debug_cpu_cti0_base:
	.word	-125206528
	.type	debug_cpu_pmu1_base, %object
	.size	debug_cpu_pmu1_base, 4
debug_cpu_pmu1_base:
	.word	-125227008
	.type	debug_cpu_pmu0_base, %object
	.size	debug_cpu_pmu0_base, 4
debug_cpu_pmu0_base:
	.word	-125235200
	.type	debug_ftm_base, %object
	.size	debug_ftm_base, 4
debug_ftm_base:
	.word	-125784064
	.type	debug_cti_ftm_base, %object
	.size	debug_cti_ftm_base, 4
debug_cti_ftm_base:
	.word	-125792256
	.type	debug_itm_base, %object
	.size	debug_itm_base, 4
debug_itm_base:
	.word	-125808640
	.type	debug_funnel_base, %object
	.size	debug_funnel_base, 4
debug_funnel_base:
	.word	-125812736
	.type	debug_tpiu_base, %object
	.size	debug_tpiu_base, 4
debug_tpiu_base:
	.word	-125816832
	.type	debug_cti_etb_tpiu_base, %object
	.size	debug_cti_etb_tpiu_base, 4
debug_cti_etb_tpiu_base:
	.word	-125820928
	.type	debug_etb_base, %object
	.size	debug_etb_base, 4
debug_etb_base:
	.word	-125825024
	.type	debug_dap_rom_base, %object
	.size	debug_dap_rom_base, 4
debug_dap_rom_base:
	.word	-125829120
	.type	ocmc_base, %object
	.size	ocmc_base, 4
ocmc_base:
	.word	-134168576
	.type	axi_hp3_base, %object
	.size	axi_hp3_base, 4
axi_hp3_base:
	.word	-134172672
	.type	axi_hp2_base, %object
	.size	axi_hp2_base, 4
axi_hp2_base:
	.word	-134176768
	.type	axi_hp1_base, %object
	.size	axi_hp1_base, 4
axi_hp1_base:
	.word	-134180864
	.type	axi_hp0_base, %object
	.size	axi_hp0_base, 4
axi_hp0_base:
	.word	-134184960
	.type	devcfg_base, %object
	.size	devcfg_base, 4
devcfg_base:
	.word	-134189056
	.type	ddrc_base, %object
	.size	ddrc_base, 4
ddrc_base:
	.word	-134193152
	.type	swdt_base, %object
	.size	swdt_base, 4
swdt_base:
	.word	-134197248
	.type	dmac0_ns_base, %object
	.size	dmac0_ns_base, 4
dmac0_ns_base:
	.word	-134201344
	.type	dmac0_s_base, %object
	.size	dmac0_s_base, 4
dmac0_s_base:
	.word	-134205440
	.type	ttc1_base, %object
	.size	ttc1_base, 4
ttc1_base:
	.word	-134209536
	.type	ttc0_base, %object
	.size	ttc0_base, 4
ttc0_base:
	.word	-134213632
	.type	slcr_base, %object
	.size	slcr_base, 4
slcr_base:
	.word	-134217728
	.type	smc_sram1_base, %object
	.size	smc_sram1_base, 4
smc_sram1_base:
	.word	-469762048
	.type	smc_sram0_base, %object
	.size	smc_sram0_base, 4
smc_sram0_base:
	.word	-503316480
	.type	smc_nand_base, %object
	.size	smc_nand_base, 4
smc_nand_base:
	.word	-520093696
	.type	sd1_base, %object
	.size	sd1_base, 4
sd1_base:
	.word	-535818240
	.type	sd0_base, %object
	.size	sd0_base, 4
sd0_base:
	.word	-535822336
	.type	smcc_base, %object
	.size	smcc_base, 4
smcc_base:
	.word	-536813568
	.type	qspi_base, %object
	.size	qspi_base, 4
qspi_base:
	.word	-536817664
	.type	gem1_base, %object
	.size	gem1_base, 4
gem1_base:
	.word	-536821760
	.type	gem0_base, %object
	.size	gem0_base, 4
gem0_base:
	.word	-536825856
	.type	gpio_base, %object
	.size	gpio_base, 4
gpio_base:
	.word	-536829952
	.type	can1_base, %object
	.size	can1_base, 4
can1_base:
	.word	-536834048
	.type	can0_base, %object
	.size	can0_base, 4
can0_base:
	.word	-536838144
	.type	spi1_base, %object
	.size	spi1_base, 4
spi1_base:
	.word	-536842240
	.type	spi0_base, %object
	.size	spi0_base, 4
spi0_base:
	.word	-536846336
	.type	i2c1_base, %object
	.size	i2c1_base, 4
i2c1_base:
	.word	-536850432
	.type	i2c0_base, %object
	.size	i2c0_base, 4
i2c0_base:
	.word	-536854528
	.type	usb1_base, %object
	.size	usb1_base, 4
usb1_base:
	.word	-536858624
	.type	usb0_base, %object
	.size	usb0_base, 4
usb0_base:
	.word	-536862720
	.type	uart1_base, %object
	.size	uart1_base, 4
uart1_base:
	.word	-536866816
	.type	uart0_base, %object
	.size	uart0_base, 4
uart0_base:
	.word	-536870912
	.type	ddr_end, %object
	.size	ddr_end, 4
ddr_end:
	.word	536870912
	.type	qspi_linear_base, %object
	.size	qspi_linear_base, 4
qspi_linear_base:
	.word	-67108864
	.type	axi_gp1_base, %object
	.size	axi_gp1_base, 4
axi_gp1_base:
	.word	-2147483648
	.type	axi_gp0_base, %object
	.size	axi_gp0_base, 4
axi_gp0_base:
	.word	1073741824
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"0123456789ABCDEF\000"
	.space	3
.LC1:
	.ascii	"00000000\015\012\000"
	.space	1
.LC2:
	.ascii	"show the free memory:\015\012\000"
.LC3:
	.ascii	"show end.\015\012\000"
.LC4:
	.ascii	"You are in the system call.\015\012\000"
	.space	2
.LC5:
	.ascii	"The cpsr is \000"
	.space	3
.LC6:
	.ascii	"You are in the SWI handler.\015\012\000"
	.space	2
.LC7:
	.ascii	"Change the spsr.\015\012\000"
	.space	1
.LC8:
	.ascii	"You are in the PrefetchAbort handler.\015\012\000"
.LC9:
	.ascii	"You are in the DataAbort handler.\015\012\000"
.LC10:
	.ascii	"l2 addr:\000"
	.space	3
.LC11:
	.ascii	"free ok.\015\012\000"
	.space	1
.LC12:
	.ascii	"CPU1 start!\015\012\000"
	.space	2
.LC13:
	.ascii	"debug\015\012\000"
.LC14:
	.ascii	"free memory\015\012\000"
	.space	2
.LC15:
	.ascii	"Welcome to the kernel on ARM cmlin!\015\012\000"
	.space	2
.LC16:
	.ascii	"ready to enable mmu.\015\012\000"
	.space	1
.LC17:
	.ascii	"enable mmu success.\015\012\000"
	.space	2
.LC18:
	.ascii	"update the pc value.\015\012\000"
	.space	1
.LC19:
	.ascii	"update the sp value.\015\012\000"
	.space	1
.LC20:
	.ascii	"Initialize Interrupt success.\015\012\000"
.LC21:
	.ascii	"Initialize memory allocation.\015\012\000"
.LC22:
	.ascii	"Kernel is running.\015\012\000"
	.bss
	.align	2
	.type	cpsr, %object
	.size	cpsr, 4
cpsr:
	.space	4
	.type	slab_num, %object
	.size	slab_num, 4
slab_num:
	.space	4
	.type	pkb_num, %object
	.size	pkb_num, 4
pkb_num:
	.space	4
	.type	free_head, %object
	.size	free_head, 4
free_head:
	.space	4
	.type	ddr_base, %object
	.size	ddr_base, 4
ddr_base:
	.space	4
	.type	ocm_base, %object
	.size	ocm_base, 4
ocm_base:
	.space	4
	.ident	"GCC: (GNU) 5.2.0"
