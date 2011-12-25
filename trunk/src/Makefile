# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o common.o monitor.o descriptor_tables.o interrupts.o tables_flush.o isr.o

CFLAGS=-nostdlib -nostdinc -fno-stack-protector -m32
LDFLAGS=-Tlink.ld -b32 --format elf32-i386 -m elf_i386
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
