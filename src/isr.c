#include "isr.h"
#include "monitor.h"


void isr_handler( registers_t regs )
{
	displayString("recieved interrupt: ");
	//monitor_write_dec(regs.int_no);
	displayString("\n");
}

