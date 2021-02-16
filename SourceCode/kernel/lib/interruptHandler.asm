global divideErrorHandler
global debugExceptionHandler
global nmiHandler
global breakPointerHandler
global overFlowHandler
global boundsCheckHandler
global undefinedHandler
global deviceUselessHandler
global doubleFaultHandler
global segmentOverHandler
global invalidTSSHandler
global segmentNotpresentHandler
global stackErrorHandler
global generalProtectionHandler
global pageFaultHandler
global floatMistakeHandler
global IRQ0Handler
global IRQ1Handler
global IRQ2Handler
global IRQ3Handler
global IRQ4Handler
global IRQ5Handler
global IRQ6Handler
global IRQ7Handler
global IRQ8Handler
global IRQ9Handler
global IRQ10Handler
global IRQ11Handler
global IRQ12Handler
global IRQ13Handler
global IRQ14Handler
global IRQ15Handler



extern generalExceptionHandler
;if the interrupt that happened has a error code, just push int vector
;otherwise,before push int vector ,push 0xffffffff
divideErrorHandler:		;0x08:0x30900
	push 0xffffffff
	push 0x00
	jmp exception
debugExceptionHandler:
	push 0xffffffff
	push 0x01
	jmp exception
nmiHandler:
	push 0xffffffff
	push 0x02
	jmp exception
breakPointerHandler:
	push 0xffffffff
	push 0x03
	jmp exception
overFlowHandler:
	push 0xffffffff
	push 0x04
	jmp exception
boundsCheckHandler:
	push 0xffffffff
	push 0x05
	jmp exception
undefinedHandler:
	push 0xffffffff
	push 0x06
	jmp exception
deviceUselessHandler:
	push 0xffffffff
	push 0x07
	jmp exception
doubleFaultHandler:
	push 0x08
	jmp exception
segmentOverHandler:
	push 0xffffffff
	push 0x09
	jmp exception
invalidTSSHandler:
	push 0x0a
	jmp exception
segmentNotpresentHandler:
	push 0x0b
	jmp exception
stackErrorHandler:
	push 0x0c
	jmp exception	
generalProtectionHandler:
	push 0x0d
	jmp exception	
pageFaultHandler:
	push 0x0e
	jmp exception	
floatMistakeHandler:
	push 0xffffffff
	push 0x10
	jmp	exception	

IRQ0Handler:
	push 0xffffffff
	push 0x20
	jmp exception

IRQ1Handler:
	push 0xffffffff
	push 0x21
	jmp exception
IRQ2Handler:
	push 0xffffffff
	push 0x22
	jmp exception
IRQ3Handler:
	push 0xffffffff
	push 0x23
	jmp exception
IRQ4Handler:
	push 0xffffffff
	push 0x24
	jmp exception
IRQ5Handler:
	push 0xffffffff
	push 0x25
	jmp exception
IRQ6Handler:
	push 0xffffffff
	push 0x26
	jmp exception
IRQ7Handler:
	push 0xffffffff
	push 0x27
	jmp exception
IRQ8Handler:
	push 0xffffffff
	push 0x28
	jmp exception
IRQ9Handler:
	push 0xffffffff
	push 0x29
	jmp exception
IRQ10Handler:
	push 0xffffffff
	push 0x2a
	jmp exception
IRQ11Handler:
	push 0xffffffff
	push 0x2b
	jmp exception
IRQ12Handler:
	push 0xffffffff
	push 0x2c
	jmp exception
IRQ13Handler:
	push 0xffffffff
	push 0x2d
	jmp exception
IRQ14Handler:
	push 0xffffffff
	push 0x2e
	jmp exception
IRQ15Handler:
	push 0xffffffff
	push 0x2f
	jmp exception

exception:	
	call generalExceptionHandler
	add esp,4*2
	hlt
