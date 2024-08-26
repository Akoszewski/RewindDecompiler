int function1()
{
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("mov DWORD PTR [rbp-0x4], edi");
	asm("mov DWORD PTR [rbp-0x8], esi");
	asm("mov edx, DWORD PTR [rbp-0x4]");
	asm("mov eax, DWORD PTR [rbp-0x8]");
	asm("add eax, edx");
	asm("pop rbp");
	asm("nop");
	asm("pop rbp");
}

int main()
{
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("mov esi, 0x2");
	asm("mov edi, 0x5");
	asm("call 45f");
	asm("mov eax, 0x0");
	asm("pop rbp");
	asm("mov eax, 0x0");
	asm("pop rbp");
}

