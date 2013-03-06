// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "common.h"
#include "monitor.h"


int main(struct multiboot *mboot_ptr)
{
	//asm volatile("int %0" : :"i"(3));
	displayString("Hello world!\n");
	
//	BREAKPOINT;
	
    // All our initialisation calls will go in here.
	
	
	init_descriptor_tables();
	
	BREAKPOINT;

    return 0xDEADBABA;
}
