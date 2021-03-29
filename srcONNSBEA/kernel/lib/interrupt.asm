global disableInt
global enableInt
disableInt:
	cli
	ret

enableInt:
	sti
	ret