int function1()
{
	asm("mov DWORD PTR [rbp-0x4], edi");
	asm("mov DWORD PTR [rbp-0x8], esi");
	asm("mov edx, DWORD PTR [rbp-0x4]");
	asm("mov eax, DWORD PTR [rbp-0x8]");
	asm("add eax, edx");
}

int main()
{
	asm("mov esi, 0x2");
	asm("mov edi, 0x5");
	asm("call 0x1119");
	asm("mov eax, 0x0");
}

