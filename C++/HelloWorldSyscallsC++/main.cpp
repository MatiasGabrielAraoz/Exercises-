extern "C" void _start() {
	const char msg[] = "Hello World\n";
	const long len = sizeof(msg) - 1;

	long bw;
	asm volatile (
		"syscall"
		:"=a" (bw)
		:"a" (1), "D" (1), "S" (msg), "d" (len)
		:"rcx", "r11", "memory"
		);
	asm volatile (
			"syscall"
			:
			: "a" (60), "D" (0)
			: "memory"
			);
}


