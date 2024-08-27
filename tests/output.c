int puts();

int function1()
{
	asm("mov DWORD PTR [rbp-0x4], edi");
	asm("mov DWORD PTR [rbp-0x8], esi");
	asm("mov eax, DWORD PTR [rbp-0x4]");
	asm("sub eax, DWORD PTR [rbp-0x8]");
}

int main()
{
	asm("mov esi, 0x5");
	asm("mov edi, 0x2");
	function1();
	asm("lea rax, [rip+0xe9f]");
	asm("mov rdi, rax");
	puts();
	return 0;
}

