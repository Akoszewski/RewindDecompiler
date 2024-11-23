echo "Compiling decompiler"
g++ -g -fsanitize=address src/main.cpp src/FileManager.cpp src/Generator.cpp src/Parser.cpp \
    src/Utils.cpp src/Analyser.cpp  -o bin/rewind.elf || exit -1
echo "Decompiler compiled"

cd tests
rm a.asm output.asm output.c a.out output.elf rodata.txt

# gcc -O0 testcode-simple-variable.c -lm || exit -1
gcc -O0 testcode-library-fun.c -lm || exit -1
# gcc -O0 testcode-simple-fun.c -lm || exit -1
objdump -s -j .rodata a.out | awk '{gsub(/[ ]{2,}/, " | "); print}' > a.asm
objdump -M intel -d a.out >> a.asm


echo "Decompiling file"
../bin/rewind.elf a.asm
echo "Compiling decompiled file"
gcc -masm=intel -g -O0 output.c -o output.elf -lm || exit -1
echo "Launching recompiled file"
./output.elf
echo "The recompiled program returned: $?"
echo "Decompiling recompiled file"
objdump -M intel -d output.elf > output.asm

cd ..
