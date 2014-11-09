SECTIONS {
	. = 0x1000;
	_kernel_begin = .;
	.ipl 0x1000: {
		ipl.o;
		setup.o;
		startup.o
		video.o
	}
	.=ALIGN(32);
	_kernel_end = .;
	_kernel_end_sector = ((_kernel_end - _kernel_begin) + 511) / 512;
}
