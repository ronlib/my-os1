#include "common.h"


void outb(u16int port,  u8int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
	u8int ret = 0;
	asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}


u16int inw(u16int port)
{
	u16int ret = 0;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}
