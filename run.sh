echo "Compiling disassembler"
g++ -g src/main.cpp src/FileManager.cpp src/Generator.cpp src/Parser.cpp src/Utils.cpp -o bin/rewind.elf || exit -1
echo "Disassembler compiled"

cd tests

gcc -O0 testcode-simple-fun.c || exit -1
objdump -M intel -d a.out > a.asm

echo "Disassembling file"
../bin/rewind.elf a.asm
echo "Compiling disassembled file"
gcc -masm=intel -g -O0 output.c -o output.elf || exit -1
echo "Launching recompiled file"
./output.elf
echo "Decompiling recompiled file"
objdump -M intel -d output.elf > output.asm

cd ..
