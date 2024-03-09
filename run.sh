MODULE_NAME=hello_world

make clean && make 
sudo insmod $MODULE_NAME.ko
sleep 5
sudo rmmod $MODULE_NAME
sudo dmesg | tail -n 20 > output.txt
make clean