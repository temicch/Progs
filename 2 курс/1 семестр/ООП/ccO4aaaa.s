	.file	"dev-cpp-rus.cpp"
	.text
	.align 2
	.def	__ZSt17__verify_groupingPKcjRKSs;	.scl	3;	.type	32;	.endef
__ZSt17__verify_groupingPKcjRKSs:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSs4sizeEv
	decl	%eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	decl	%eax
	movl	%eax, -12(%ebp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt3minIjERKT_S2_S2_
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movb	$1, -17(%ebp)
	movl	$0, -24(%ebp)
L2:
	movl	-24(%ebp), %eax
	cmpl	-8(%ebp), %eax
	jae	L5
	cmpb	$0, -17(%ebp)
	je	L5
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	-24(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	sete	%al
	movb	%al, -17(%ebp)
	leal	-16(%ebp), %eax
	decl	(%eax)
	leal	-24(%ebp), %eax
	incl	(%eax)
	jmp	L2
L5:
	cmpl	$0, -16(%ebp)
	je	L6
	cmpb	$0, -17(%ebp)
	je	L6
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	-8(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	sete	%al
	movb	%al, -17(%ebp)
	leal	-16(%ebp), %eax
	decl	(%eax)
	jmp	L5
L6:
	movl	$0, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNKSsixEj
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	-8(%ebp), %edx
	addl	%eax, %edx
	movzbl	(%ecx), %eax
	cmpb	(%edx), %al
	jg	L8
	movzbl	-17(%ebp), %eax
	andl	$1, %eax
	movb	%al, -25(%ebp)
	jmp	L9
L8:
	movb	$0, -25(%ebp)
L9:
	movzbl	-25(%ebp), %eax
	movb	%al, -17(%ebp)
	movzbl	-17(%ebp), %eax
	leave
	ret
.lcomm __ZSt8__ioinit,16
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "\220_\220+\221<\221\330\220_\221<\220\374 \221_\220\365\220\361\221_\220_\220\363:\0"
LC1:
	.ascii "\220\366\221'\220\347\220\363:\0"
LC2:
	.ascii "\220_\221\330\220\347\221_\220\347\220_\221_:\0"
	.text
	.align 2
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$152, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -124(%ebp)
	movl	-124(%ebp), %eax
	call	__alloca
	call	___main
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tStackC1Ev
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC1Ev
	leal	-88(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tQueueC1Ev
	movl	$0, -92(%ebp)
L11:
	cmpl	$5, -92(%ebp)
	jg	L12
	movl	-92(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tStack4pushEi
	movl	-92(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-88(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tQueue4pushEi
	movl	-92(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-56(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tList4pushEi
	leal	-92(%ebp), %eax
	incl	(%eax)
	jmp	L11
L12:
	movl	$LC0, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	__ZNSolsEPFRSoS_E
	leal	-56(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC1ERKS_
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__Z4showI5tListEvT_
	movl	$LC1, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	__ZNSolsEPFRSoS_E
	leal	-40(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tStackC1ERKS_
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__Z4showI6tStackEvT_
	movl	$LC2, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	%eax, (%esp)
	call	__ZNSolsEPFRSoS_E
	leal	-88(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN6tQueueC1ERKS_
	leal	-120(%ebp), %eax
	movl	%eax, (%esp)
	call	__Z4showI6tQueueEvT_
	movl	$0, %eax
	leave
	ret
	.section	.text$_ZN6tQueueC1ERKS_,"x"
	.linkonce discard
	.align 2
.globl __ZN6tQueueC1ERKS_
	.def	__ZN6tQueueC1ERKS_;	.scl	2;	.type	32;	.endef
__ZN6tQueueC1ERKS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC2ERKS_
	movl	8(%ebp), %eax
	movl	$__ZTV6tQueue+8, (%eax)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, 12(%edx)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, 16(%edx)
	leave
	ret
L15:
L14:
	.section	.text$_ZN5tListC2ERKS_,"x"
	.linkonce discard
	.align 2
.globl __ZN5tListC2ERKS_
	.def	__ZN5tListC2ERKS_;	.scl	2;	.type	32;	.endef
__ZN5tListC2ERKS_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$__ZTV5tList+8, (%eax)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%edx)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 8(%edx)
	popl	%ebp
	ret
L18:
L17:
	.section	.text$_ZN6tStackC1ERKS_,"x"
	.linkonce discard
	.align 2
.globl __ZN6tStackC1ERKS_
	.def	__ZN6tStackC1ERKS_;	.scl	2;	.type	32;	.endef
__ZN6tStackC1ERKS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC2ERKS_
	movl	8(%ebp), %eax
	movl	$__ZTV6tStack+8, (%eax)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, 12(%edx)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, 16(%edx)
	leave
	ret
L21:
L20:
	.section	.text$_ZN5tListC1ERKS_,"x"
	.linkonce discard
	.align 2
.globl __ZN5tListC1ERKS_
	.def	__ZN5tListC1ERKS_;	.scl	2;	.type	32;	.endef
__ZN5tListC1ERKS_:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$__ZTV5tList+8, (%eax)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 4(%edx)
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 8(%edx)
	popl	%ebp
	ret
L24:
L23:
	.section	.text$_ZN5tList4pushEi,"x"
	.linkonce discard
	.align 2
.globl __ZN5tList4pushEi
	.def	__ZN5tList4pushEi;	.scl	2;	.type	32;	.endef
__ZN5tList4pushEi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
L27:
	movl	-8(%ebp), %eax
	cmpl	$0, 4(%eax)
	je	L28
	movl	-8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -8(%ebp)
	jmp	L27
L28:
	movl	$12, (%esp)
	call	__Znwj
	movl	%eax, %ebx
	movl	%ebx, (%esp)
	call	__ZN5tListC1Ev
L29:
	movl	%ebx, -12(%ebp)
	movl	-8(%ebp), %edx
	movl	-12(%ebp), %eax
	movl	%eax, 4(%edx)
	movl	-12(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
L26:
	.section	.text$_ZN6tQueue4pushEi,"x"
	.linkonce discard
	.align 2
.globl __ZN6tQueue4pushEi
	.def	__ZN6tQueue4pushEi;	.scl	2;	.type	32;	.endef
__ZN6tQueue4pushEi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	$20, (%esp)
	call	__Znwj
	movl	%eax, %ebx
	movl	%ebx, (%esp)
	call	__ZN6tQueueC1Ev
L32:
	movl	%ebx, -8(%ebp)
	movl	-8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	-8(%ebp), %eax
	movl	$0, 12(%eax)
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%eax, 12(%edx)
	movl	8(%ebp), %edx
	movl	-8(%ebp), %eax
	movl	%eax, 16(%edx)
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
L31:
	.section	.text$_ZN6tStack4pushEi,"x"
	.linkonce discard
	.align 2
.globl __ZN6tStack4pushEi
	.def	__ZN6tStack4pushEi;	.scl	2;	.type	32;	.endef
__ZN6tStack4pushEi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	movl	$20, (%esp)
	call	__Znwj
	movl	%eax, %ebx
	movl	%ebx, (%esp)
	call	__ZN6tStackC1Ev
L35:
	movl	%ebx, -8(%ebp)
	movl	-8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, 8(%edx)
	movl	8(%ebp), %edx
	movl	-8(%ebp), %eax
	movl	%eax, 16(%edx)
	movl	-8(%ebp), %edx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, 12(%edx)
	movl	8(%ebp), %edx
	movl	-8(%ebp), %eax
	movl	%eax, 12(%edx)
	addl	$20, %esp
	popl	%ebx
	popl	%ebp
	ret
L34:
	.section	.text$_ZN6tQueueC1Ev,"x"
	.linkonce discard
	.align 2
.globl __ZN6tQueueC1Ev
	.def	__ZN6tQueueC1Ev;	.scl	2;	.type	32;	.endef
__ZN6tQueueC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC2Ev
	movl	8(%ebp), %eax
	movl	$__ZTV6tQueue+8, (%eax)
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	movl	8(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%eax, 16(%edx)
	leave
	ret
	.section	.text$_ZN5tListC2Ev,"x"
	.linkonce discard
	.align 2
.globl __ZN5tListC2Ev
	.def	__ZN5tListC2Ev;	.scl	2;	.type	32;	.endef
__ZN5tListC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$__ZTV5tList+8, (%eax)
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	movl	8(%ebp), %eax
	movl	$0, 8(%eax)
	popl	%ebp
	ret
	.section	.text$_ZN5tListC1Ev,"x"
	.linkonce discard
	.align 2
.globl __ZN5tListC1Ev
	.def	__ZN5tListC1Ev;	.scl	2;	.type	32;	.endef
__ZN5tListC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$__ZTV5tList+8, (%eax)
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	movl	8(%ebp), %eax
	movl	$0, 8(%eax)
	popl	%ebp
	ret
	.section	.text$_ZN6tStackC1Ev,"x"
	.linkonce discard
	.align 2
.globl __ZN6tStackC1Ev
	.def	__ZN6tStackC1Ev;	.scl	2;	.type	32;	.endef
__ZN6tStackC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN5tListC2Ev
	movl	8(%ebp), %eax
	movl	$__ZTV6tStack+8, (%eax)
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	movl	8(%ebp), %eax
	movl	$0, 16(%eax)
	leave
	ret
	.section	.text$_ZSt3minIjERKT_S2_S2_,"x"
	.linkonce discard
	.align 2
.globl __ZSt3minIjERKT_S2_S2_
	.def	__ZSt3minIjERKT_S2_S2_;	.scl	2;	.type	32;	.endef
__ZSt3minIjERKT_S2_S2_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%eax), %eax
	cmpl	(%edx), %eax
	jae	L42
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	L41
L42:
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L41:
	movl	-4(%ebp), %eax
	leave
	ret
	.section .rdata,"dr"
LC3:
	.ascii "\11\0"
	.section	.text$_Z4showI5tListEvT_,"x"
	.linkonce discard
	.align 2
.globl __Z4showI5tListEvT_
	.def	__Z4showI5tListEvT_;	.scl	2;	.type	32;	.endef
__Z4showI5tListEvT_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
L44:
	cmpl	$0, -4(%ebp)
	je	L45
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEi
	movl	$LC3, 4(%esp)
	movl	%eax, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	L44
L45:
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEPFRSoS_E
	leave
	ret
	.section	.text$_Z4showI6tStackEvT_,"x"
	.linkonce discard
	.align 2
.globl __Z4showI6tStackEvT_
	.def	__Z4showI6tStackEvT_;	.scl	2;	.type	32;	.endef
__Z4showI6tStackEvT_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
L47:
	cmpl	$0, -4(%ebp)
	je	L48
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEi
	movl	$LC3, 4(%esp)
	movl	%eax, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	L47
L48:
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEPFRSoS_E
	leave
	ret
	.section	.text$_Z4showI6tQueueEvT_,"x"
	.linkonce discard
	.align 2
.globl __Z4showI6tQueueEvT_
	.def	__Z4showI6tQueueEvT_;	.scl	2;	.type	32;	.endef
__Z4showI6tQueueEvT_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
L50:
	cmpl	$0, -4(%ebp)
	je	L51
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEi
	movl	$LC3, 4(%esp)
	movl	%eax, (%esp)
	call	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	L50
L51:
	movl	$__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, 4(%esp)
	movl	$__ZSt4cout, (%esp)
	call	__ZNSolsEPFRSoS_E
	leave
	ret
.globl __ZTV6tQueue
	.section	.rdata$_ZTV6tQueue,"dr"
	.linkonce same_size
	.align 8
__ZTV6tQueue:
	.long	0
	.long	__ZTI6tQueue
	.long	__ZN6tQueue4pushEi
	.long	__ZN6tQueue3popEv
.globl __ZTV6tStack
	.section	.rdata$_ZTV6tStack,"dr"
	.linkonce same_size
	.align 8
__ZTV6tStack:
	.long	0
	.long	__ZTI6tStack
	.long	__ZN6tStack4pushEi
	.long	__ZN6tStack3popEv
.globl __ZTV5tList
	.section	.rdata$_ZTV5tList,"dr"
	.linkonce same_size
	.align 8
__ZTV5tList:
	.long	0
	.long	__ZTI5tList
	.long	__ZN5tList4pushEi
	.long	__ZN5tList3popEv
	.text
	.align 2
	.def	__Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
__Z41__static_initialization_and_destruction_0ii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$65535, 12(%ebp)
	jne	L53
	cmpl	$1, 8(%ebp)
	jne	L53
	movl	$__ZSt8__ioinit, (%esp)
	call	__ZNSt8ios_base4InitC1Ev
L53:
	cmpl	$65535, 12(%ebp)
	jne	L52
	cmpl	$0, 8(%ebp)
	jne	L52
	movl	$__ZSt8__ioinit, (%esp)
	call	__ZNSt8ios_base4InitD1Ev
L52:
	leave
	ret
	.section	.text$_ZN5tList3popEv,"x"
	.linkonce discard
	.align 2
.globl __ZN5tList3popEv
	.def	__ZN5tList3popEv;	.scl	2;	.type	32;	.endef
__ZN5tList3popEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L56:
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	$0, 4(%eax)
	je	L57
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	L56
L57:
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	-4(%ebp), %eax
	movl	$0, 4(%eax)
	leave
	ret
	.section	.text$_ZN6tStack3popEv,"x"
	.linkonce discard
	.align 2
.globl __ZN6tStack3popEv
	.def	__ZN6tStack3popEv;	.scl	2;	.type	32;	.endef
__ZN6tStack3popEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	cmpl	$0, 16(%eax)
	je	L58
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 12(%edx)
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 16(%edx)
L58:
	leave
	ret
	.section	.text$_ZN6tQueue3popEv,"x"
	.linkonce discard
	.align 2
.globl __ZN6tQueue3popEv
	.def	__ZN6tQueue3popEv;	.scl	2;	.type	32;	.endef
__ZN6tQueue3popEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	cmpl	$0, 12(%eax)
	jne	L61
	jmp	L60
L61:
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	8(%ebp), %edx
	movl	-4(%ebp), %eax
	movl	%eax, 12(%edx)
L60:
	leave
	ret
.globl __ZTI5tList
	.section	.rdata$_ZTI5tList,"dr"
	.linkonce same_size
	.align 4
__ZTI5tList:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTS5tList
.globl __ZTI6tStack
	.section	.rdata$_ZTI6tStack,"dr"
	.linkonce same_size
	.align 4
__ZTI6tStack:
	.long	__ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	__ZTS6tStack
	.long	__ZTI5tList
.globl __ZTI6tQueue
	.section	.rdata$_ZTI6tQueue,"dr"
	.linkonce same_size
	.align 4
__ZTI6tQueue:
	.long	__ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	__ZTS6tQueue
	.long	__ZTI5tList
.globl __ZTS5tList
	.section	.rdata$_ZTS5tList,"dr"
	.linkonce same_size
__ZTS5tList:
	.ascii "5tList\0"
.globl __ZTS6tStack
	.section	.rdata$_ZTS6tStack,"dr"
	.linkonce same_size
__ZTS6tStack:
	.ascii "6tStack\0"
.globl __ZTS6tQueue
	.section	.rdata$_ZTS6tQueue,"dr"
	.linkonce same_size
__ZTS6tQueue:
	.ascii "6tQueue\0"
	.text
	.align 2
	.def	__GLOBAL__I_main;	.scl	3;	.type	32;	.endef
__GLOBAL__I_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$65535, 4(%esp)
	movl	$1, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.section	.ctors,"w"
	.align 4
	.long	__GLOBAL__I_main
	.text
	.align 2
	.def	__GLOBAL__D_main;	.scl	3;	.type	32;	.endef
__GLOBAL__D_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$65535, 4(%esp)
	movl	$0, (%esp)
	call	__Z41__static_initialization_and_destruction_0ii
	leave
	ret
	.section	.dtors,"w"
	.align 4
	.long	__GLOBAL__D_main
	.def	__ZNSt8ios_base4InitD1Ev;	.scl	3;	.type	32;	.endef
	.def	__ZNSolsEi;	.scl	3;	.type	32;	.endef
	.def	__Z4showI6tQueueEvT_;	.scl	3;	.type	32;	.endef
	.def	__ZN6tQueueC1ERKS_;	.scl	3;	.type	32;	.endef
	.def	__Z4showI6tStackEvT_;	.scl	3;	.type	32;	.endef
	.def	__ZN6tStackC1ERKS_;	.scl	3;	.type	32;	.endef
	.def	__Z4showI5tListEvT_;	.scl	3;	.type	32;	.endef
	.def	__ZN5tListC1ERKS_;	.scl	3;	.type	32;	.endef
	.def	__ZNSolsEPFRSoS_E;	.scl	3;	.type	32;	.endef
	.def	__ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_;	.scl	3;	.type	32;	.endef
	.def	__ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc;	.scl	3;	.type	32;	.endef
	.def	__Znwj;	.scl	3;	.type	32;	.endef
	.def	__ZNSt8ios_base4InitC1Ev;	.scl	3;	.type	32;	.endef
	.def	__ZNKSsixEj;	.scl	3;	.type	32;	.endef
	.def	__ZNKSs4sizeEv;	.scl	3;	.type	32;	.endef
	.def	__ZdlPv;	.scl	3;	.type	32;	.endef
	.def	__ZSt3minIjERKT_S2_S2_;	.scl	3;	.type	32;	.endef
