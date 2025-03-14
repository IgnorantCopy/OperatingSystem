#include "x86.h"
#include "device.h"

extern int displayRow;
extern int displayCol;

extern uint32_t keyBuffer[MAX_KEYBUFFER_SIZE];
extern int bufferHead;
extern int bufferTail;


void GProtectFaultHandle(struct TrapFrame *tf);

void KeyboardHandle(struct TrapFrame *tf);

void syscallHandle(struct TrapFrame *tf);
void syscallWrite(struct TrapFrame *tf);
void syscallPrint(struct TrapFrame *tf);
void syscallRead(struct TrapFrame *tf);
void syscallGetChar(struct TrapFrame *tf);
void syscallGetStr(struct TrapFrame *tf);

void updateNewLine() {
    displayRow++;
    displayCol = 0;
    if (displayRow == 25) {
        displayRow--;
        scrollScreen();
    }
}

void updateNewCharacter() {
    displayCol++;
    if (displayCol == 80) {
        updateNewLine();
    }
}

void irqHandle(struct TrapFrame *tf) { // pointer tf = esp
	/*
	 * 中断处理程序
	 */
	/* Reassign segment register */
	asm volatile("movw %%ax, %%ds"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%es"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%fs"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%gs"::"a"(KSEL(SEG_KDATA)));
	switch(tf->irq) {
		// TODO: 填好中断处理程序的调用
        case 0xd:
            GProtectFaultHandle(tf);
            break;
        case 0x21:
            KeyboardHandle(tf);
            break;
        case 0x80:
            syscallHandle(tf);
            break;
        case -1:
            break;
		default:assert(0);
	}
}

void GProtectFaultHandle(struct TrapFrame *tf){
	assert(0);
	return;
}

void KeyboardHandle(struct TrapFrame *tf){
	uint32_t code = getKeyCode();
	if(code == 0xe){ // 退格符
		// TODO: 要求只能退格用户键盘输入的字符串，且最多退到当行行首
        if (displayCol > 0) {
            displayCol--;
            int offset = 0;
            for (; displayCol + offset < 80; offset++) {
                int pos = (bufferHead + offset) % MAX_KEYBUFFER_SIZE;
                if (pos == bufferTail) {
                    break;
                }
                uint32_t c = keyBuffer[(pos + 1) % MAX_KEYBUFFER_SIZE];
                if (c == 0x1c) {
                    break;
                }
                keyBuffer[pos] = c;
            }
            keyBuffer[(bufferHead + offset) % MAX_KEYBUFFER_SIZE] = 0;
        }
	}else if(code == 0x1c){ // 回车符
		// TODO: 处理回车情况
        updateNewLine();
        keyBuffer[bufferHead] = 0x1c;
        if (bufferHead == bufferTail) {
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
        }
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
	}else if(code < 0x81){ // 正常字符
		// TODO: 注意输入的大小写的实现、不可打印字符的处理
        if (getChar(code) == 0) {
            return;
        }
        updateNewCharacter();
        keyBuffer[bufferHead] = code;
        if (bufferHead == bufferTail) {
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
        }
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
	}
	updateCursor(displayRow, displayCol);
}

void syscallHandle(struct TrapFrame *tf) {
	switch(tf->eax) { // syscall number
		case 0:
			syscallWrite(tf);
			break; // for SYS_WRITE
		case 1:
			syscallRead(tf);
			break; // for SYS_READ
		default:break;
	}
}

void syscallWrite(struct TrapFrame *tf) {
	switch(tf->ecx) { // file descriptor
		case 0:
			syscallPrint(tf);
			break; // for STD_OUT
		default:break;
	}
}

void syscallPrint(struct TrapFrame *tf) {
	int sel = USEL(SEG_UDATA);  //TODO: segment selector for user data, need further modification
	char *str = (char*)tf->edx;
	int size = tf->ebx;
	int i = 0;
	int pos = 0;
	char character = 0;
	uint16_t data = 0;
	asm volatile("movw %0, %%es"::"m"(sel));
	for (i = 0; i < size; i++) {
		asm volatile("movb %%es:(%1), %0":"=r"(character):"r"(str+i));
		// TODO: 完成光标的维护和打印到显存
        if (character == '\n') {
            updateNewLine();
        } else {
            data = character | (0x0c << 8);
            pos = (displayRow * 80 + displayCol) * 2;
            asm volatile("movw %0, (%1)"::"r"(data), "r"(0xb8000 + pos));
            updateNewCharacter();
        }
	}
	
	updateCursor(displayRow, displayCol);
}

void syscallRead(struct TrapFrame *tf){
	switch(tf->ecx){ //file descriptor
		case 0:
			syscallGetChar(tf);
			break; // for STD_IN
		case 1:
			syscallGetStr(tf);
			break; // for STD_STR
		default:break;
	}
}

void syscallGetChar(struct TrapFrame *tf){
	// TODO: 自由实现
    if (bufferHead == bufferTail) {
        tf->eax = -1;
    } else {
        tf->eax = keyBuffer[bufferHead];
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
    }
}

void syscallGetStr(struct TrapFrame *tf){
	// TODO: 自由实现
    int sel = USEL(SEG_UDATA);
    char *str = (char*)tf->edx;
    int size = tf->ebx;
    int i = 0;
    char character = 0;
    asm volatile("movw %0, %%es"::"m"(sel));
    for (; i < size - 1; i++) {
        if (bufferHead == bufferTail) {
            break;
        }
        character = keyBuffer[bufferHead];
        if (character == 0x1c) {
            break;
        }
        str[i] = character;
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
    }
    str[i] = 0;
}
