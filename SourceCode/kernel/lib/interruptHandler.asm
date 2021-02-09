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

exception:	
	call generalExceptionHandler
	add esp,4*2
	hlt
