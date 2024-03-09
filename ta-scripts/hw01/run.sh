STUDENT_ID=312581029

rm -rf runtime
mkdir -p runtime
cp students_zip/HW01_$STUDENT_ID.zip runtime/HW01_$STUDENT_ID.zip
cd runtime
unzip HW01_$STUDENT_ID.zip

# run hello_world
cd hello_world

MODULE_NAME=hello_world

make clean && make 
sudo insmod $MODULE_NAME.ko
sleep 1
sudo rmmod $MODULE_NAME
sudo dmesg | tail -n 20 > output.txt
make clean
cd ..

# run file io
cd file_io

function is_reversed() {
  # Read the contents of both files
  original_text=$(< $1)
  reversed_text=$(< $2)

  # Reverse the original text using a loop
  reversed_original_text=""
  for (( i=${#original_text}-1; i>=0; i-- )); do
    reversed_original_text+="${original_text:$i:1}"
  done

  # Compare the reversed original text with the content of reversed_text.txt
  if [[ $reversed_original_text == $reversed_text ]]; then
    echo "Students: $STUDENT_ID pass file io part"
  else
    echo "Students: $STUDENT_ID didn't pass file io part -> The files are not reversed versions of each other."
  fi
}

function check_hello_world() {
    cat $1
}

MODULE_NAME=fileIO
make clean && make 
sudo insmod $MODULE_NAME.ko
sleep 1
sudo rmmod $MODULE_NAME
make clean
cd ..


check_hello_world hello_world/output.txt
is_reversed file_io/input.txt file_io/output.txt