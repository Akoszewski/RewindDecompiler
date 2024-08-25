gcc -O0 main.c || exit -1
objdump -M intel -d a.out > a.asm
