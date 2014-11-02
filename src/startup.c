extern void startup();
void startup() {
	unsigned short *video = (unsigned short *)0xb8000;
	unsigned char *str = "hello\r\n";
	unsigned char c;
	while(c=*str++) {
		*video++ = (0x0e<<8)|c;
	} 
	while(1) {;}
}
