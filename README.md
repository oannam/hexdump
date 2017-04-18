Implemented hexdump functionality in user-space and kernel-space.
Default usage is user-space functionality; "-k" parameter is required for kernel functionality.
The kernel module can be compiled using the Makefile inside the "kernel" folder; install.sh should be used to insert the module (with sudo)
Default line size is 8 bytes. Can be changed to 16 using -l parameter.

Usage:
	main -f input.bin -o output.txt
	main -f input.bin -o output.txt -l 16
	main -f input.bin -o output.txt -l 16 -k
	main -h
