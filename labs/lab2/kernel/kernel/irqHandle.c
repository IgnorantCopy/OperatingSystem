#include "x86.h"
#include "device.h"

extern int displayRow;
extern int displayCol;

extern char keyBuffer[MAX_KEYBUFFER_SIZE];
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

void displayCharacter(char c, int row, int col) {
    int pos = (row * 80 + col) * 2;
    uint16_t data = c | (0x0c << 8);
    asm volatile("movw %0, (%1)"::"r"(data), "r"(0xb8000 + pos));
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
        if (displayCol > 0 && bufferHead != bufferTail) {
            keyBuffer[bufferHead] = 0;
            bufferHead = (bufferHead - 1 + MAX_KEYBUFFER_SIZE) % MAX_KEYBUFFER_SIZE;
            displayCol--;
            displayCharacter(0, displayRow, displayCol);
        } else if (displayCol == 0 && bufferHead != bufferTail) {
            keyBuffer[bufferHead] = 0;
            bufferHead = (bufferHead - 1 + MAX_KEYBUFFER_SIZE) % MAX_KEYBUFFER_SIZE;
            displayCharacter(0, displayRow, displayCol);
        }
	}else if(code == 0x1c){ // 回车符
		// TODO: 处理回车情况
        updateNewLine();
        keyBuffer[bufferHead] = '\n';
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
        if (bufferHead == bufferTail) {
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
        }
    }else if(code < 0x81){ // 正常字符
		// TODO: 注意输入的大小写的实现、不可打印字符的处理
        char c = getChar(code);
        if (c == 0) {
            return;
        }
        displayCharacter(c, displayRow, displayCol);
        updateNewCharacter();
        keyBuffer[bufferHead] = c;
        bufferHead = (bufferHead + 1) % MAX_KEYBUFFER_SIZE;
        if (bufferHead == bufferTail) {
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
        }
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
//	int pos = 0;
	char character = 0;
//	uint16_t data = 0;
	asm volatile("movw %0, %%es"::"m"(sel));
	for (i = 0; i < size; i++) {
        asm volatile("movb %%es:(%1), %0":"=r"(character):"r"(str + i));
        // TODO: 完成光标的维护和打印到显存
        if (character == '\n') {
            updateNewLine();
        } else {
            displayCharacter(character, displayRow, displayCol);
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
    int sel = USEL(SEG_UDATA);
    char *str = (char*)tf->edx;
    int i = 0;
    char character = 0;
    int isEnd = 0;
    asm volatile("movw %0, %%es"::"m"(sel));
    while (i < MAX_KEYBUFFER_SIZE) {
        if (bufferHead == bufferTail) {
            break;
        }
        character = keyBuffer[(bufferTail + i) % MAX_KEYBUFFER_SIZE];
        if (character == '\n') {
            if (i == 0) {
                asm volatile("movb %0, %%es:(%1)"::"r"(character), "r"(str + i));
            }
            keyBuffer[bufferTail] = 0;
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
            if (bufferTail == bufferHead - 1) {
                keyBuffer[bufferTail] = 0;
                bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
            }
            isEnd = 1;
            break;
        }
        if (character != 0) {
            if (i == 0) {
                asm volatile("movb %0, %%es:(%1)"::"r"(character), "r"(str + i));
            }
            i++;
        } else {
            break;
        }
    }
    tf->eax = isEnd ? i : -1;
}

void syscallGetStr(struct TrapFrame *tf){
	// TODO: 自由实现
    int sel = USEL(SEG_UDATA);
    char *str = (char*)tf->edx;
    int size = tf->ebx;
    int i = 0;
    char character = 0;
    int isEnd = 0;
    asm volatile("movw %0, %%es"::"m"(sel));
    while (i < size - 1) {
        if (bufferHead == bufferTail) {
            break;
        }
        character = keyBuffer[(bufferTail + i) % MAX_KEYBUFFER_SIZE];
        if (character == '\n') {
            while (bufferTail != bufferHead) {
                keyBuffer[bufferTail] = 0;
                bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
            }
            isEnd = 1;
            break;
        } else if (character != 0) {
            asm volatile("movb %0, %%es:(%1)"::"r"(character), "r"(str + i));
            i++;
        } else {
            break;
        }
    }
    if (i == size - 1) {
        while (bufferTail != bufferHead) {
            keyBuffer[bufferTail] = 0;
            bufferTail = (bufferTail + 1) % MAX_KEYBUFFER_SIZE;
        }
        isEnd = 1;
    }
    asm volatile("movb $0, %%es:(%0)"::"r"(str + i));
    tf->eax = isEnd ? i : -1;
}
