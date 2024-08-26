int function1()
{
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("mov DWORD PTR [rbp-0x4], edi");
	asm("mov DWORD PTR [rbp-0x8], esi");
	asm("mov edx, DWORD PTR [rbp-0x4]");
	asm("mov eax, DWORD PTR [rbp-0x8]");
	asm("add eax, edx");
	asm("pop rbp");
	asm("ret");
}

int main()
{
	asm("push rbp");
	asm("mov rbp, rsp");
	asm("mov esi, 0x2");
	asm("mov edi, 0x5");
	asm("call 0x1119");
	asm("mov eax, 0x0");
	asm("pop rbp");
	asm("ret");
}

