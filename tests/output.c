int function1(int arg1, int arg2)
{
	int var1 = arg1;
	int var2 = arg2;
	int var3 = var1;
	int var4 = var2;
	var4 = var4 + var3;
}

int main()
{
	function1(0x5, 0x2);
	return 0;
}

