// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"

int main(struct multiboot *mboot_ptr)
{
	displayString("Hello world!\n");
	
	asm volatile("xchg %%bx, %%bx" : :);
	
    // All our initialisation calls will go in here.
	
	
	init_descriptor_tables();

    return 0xDEADBABA;
}
