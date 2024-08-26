gcc -O0 testcode-simple-fun.c || exit -1
objdump -M intel -d a.out > a.asm
