g++ src/main.cpp src/FileManager.cpp src/Generator.cpp -o bin/rewind.elf || exit -1
cd tests
./gen.sh
../bin/rewind.elf a.asm
cd ..
