int puts();

int function1()	// 2 parameters
{
	asm("mov DWORD PTR [rbp-0x4], edi");
	asm("mov eax, esi");
	asm("mov BYTE PTR [rbp-0x8], al");
	asm("movsx eax, BYTE PTR [rbp-0x8]");
	asm("mov edx, DWORD PTR [rbp-0x4]");
	asm("sub edx, eax");
	asm("mov eax, edx");
}

int main()	// 0 parameters
{
	asm("mov esi, 0x5");
	asm("mov edi, 0x2");
	function1();
	asm("lea rax, [rip+0xe98]");
	asm("mov rdi, rax");
	puts();
	return 0;
}

