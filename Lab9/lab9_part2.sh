for file in file1.bin file2.bin file3.bin file4.bin
do
  echo "Part2 $file"
  time ./Part2Executable $file
  echo " "
done