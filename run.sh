echo "Compiling decompiler"
g++ -g -fsanitize=address src/main.cpp src/FileManager.cpp src/Generator.cpp src/Parser.cpp \
    src/Utils.cpp src/Analyser.cpp  -o bin/rewind.elf || exit -1
echo "Decompiler compiled"

cd tests

# gcc -O0 testcode-simple-variable.c -lm || exit -1
gcc -O0 testcode-library-fun.c -lm || exit -1
# gcc -O0 testcode-simple-fun.c -lm || exit -1
objdump -M intel -d a.out > a.asm

echo "Decompiling file"
../bin/rewind.elf a.asm
echo "Compiling decompiled file"
gcc -masm=intel -g -O0 output.c -o output.elf -lm || exit -1
echo "Launching recompiled file"
./output.elf
echo "Decompiling recompiled file"
objdump -M intel -d output.elf > output.asm

cd ..
