#ifndef BOOT_H
#define BOOT_H

struct ELFHeader {
	unsigned int   magic;       // 0x7f454c46 (ELF)
	unsigned char  elf[12];     // describe other features of the file
	unsigned short type;        // 1=relocatable, 2=executable, 3=shared, 4=core
	unsigned short machine;     // 3=x86, 8=MIPS, 40=ARM, 62=x86-64
	unsigned int   version;     // 1=current
	unsigned int   entry;       // entry of the program
	unsigned int   phoff;       // offset of the program header table
	unsigned int   shoff;       // offset of the section header table
	unsigned int   flags;       // processor-specific flags, usually 0
	unsigned short ehsize;      // size of this header
	unsigned short phentsize;   // size of each program header
	unsigned short phnum;       // number of program headers
	unsigned short shentsize;   // size of each section header
	unsigned short shnum;       // number of section headers
	unsigned short shstrndx;    // index of the section header table that contains the section names
};

/* ELF32 Program header */
struct ProgramHeader {
	unsigned int type;
	unsigned int off;
	unsigned int vaddr;
	unsigned int paddr;
	unsigned int filesz;
	unsigned int memsz;
	unsigned int flags;
	unsigned int align;
};

void waitDisk(void);

void readSect(void *dst, int offset);

/* I/O functions */
static inline char inByte(short port) {
	char data;
	asm volatile("in %1,%0" : "=a" (data) : "d" (port));
	return data;
}

static inline int inLong(short port) {
	int data;
	asm volatile("in %1, %0" : "=a" (data) : "d" (port));
	return data;
}

static inline void outByte(short port, char data) {
	asm volatile("out %0,%1" : : "a" (data), "d" (port));
}

#endif
