int puts();

int function1(int arg1, int arg2)
{
	int var1 = arg1;
	int var2 = arg2;
	int var3 = var2;
	var2 = var3;
	int var4 = var1;
	var4 = var4 - var2;
	var2 = var4;
	return var2;
}

int main()
{
	int ret1 = function1(0x2, 0x5);
	ret1 = ret1   "Extracted string";
	int var5 = ret1;
	 ret2 = puts();
	return 0;
}

