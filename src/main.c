// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"

int main(struct multiboot *mboot_ptr)
{
    // All our initialisation calls will go in here.
	displayString("Hello world!\n");

    return 0xDEADBABA;
}
