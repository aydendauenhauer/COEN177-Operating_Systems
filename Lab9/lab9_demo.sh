#!/bin/bash

make clean

echo "Part A:"
ls -l file?.bin
sleep 2

echo "Part B:"
make
sleep 2

echo "Part C:"
echo "C: Part 4"
time ./Part4Executable file3.bin 10000
ls -l file?.bin copy*.out
sleep 3
diff file3.bin copy*.out
rm -f copy*.out
sleep 2

echo "C: Part 5"
time ./Part5Executable file3.bin 10000 4
ls -l file?.bin copy*.out
sleep 3
diff file3.bin copy*.out
rm -f copy*.out
sleep 2

echo "Part D:"
bash lab9_part2.sh
sleep 2
bash lab9_part3.sh
sleep 2
bash lab9_part4.sh
sleep 2
bash lab9_part5.sh
sleep 2

echo "Part E:"
make clean

