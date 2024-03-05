#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/slab.h> 
#include <linux/unistd.h> 
#include <linux/sched.h> 
#include <linux/fs.h> 
#include <linux/file.h> 
#include <linux/mm.h> 
#include <asm/uaccess.h> 
 
#define BUFFER_SIZE 300
MODULE_DESCRIPTION("read file in and write it out in inverse"); 
MODULE_AUTHOR("Yong-Cheng Liao<tomhot246@gmail.com>"); 
MODULE_ALIAS("read file & write file module");
MODULE_LICENSE("GPL"); 

void reverse(char *str){
    int i,j;
    char temp;
    j = strlen(str) - 1;
    str[j + 1] = '\n';
    for (i=0; i<j; i++){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        j--;
    }
}

static int fileIO_init(void) 
{ 
    struct file *io;
    char tmp_char[BUFFER_SIZE];
    void* buf;
    ssize_t rx;
    ssize_t tx;
    size_t count;
    size_t writeCount;
    loff_t pos = 0;
    memset(tmp_char, 0, sizeof(tmp_char));
    io = filp_open("input.txt", O_RDONLY, 0);
    if (IS_ERR(io)){
        printk("open file error/n");
        return -1;
    }
    count = sizeof(tmp_char);
    buf = (void*)tmp_char;
    rx = kernel_read(io, tmp_char, count, &pos);
    printk("read result= %s\n", tmp_char);
    reverse(tmp_char);
    printk("reverse result= %s\n", tmp_char);
    filp_close(io, NULL);
    pos = 0;
    io = filp_open("output.txt", O_CREAT | O_RDWR, 0664);
    if (IS_ERR(io)){
        printk("open file error/n");
        return -1;
    }
    buf = (void *)tmp_char;
    writeCount = strlen(tmp_char);
    tx = kernel_write(io, buf, writeCount, &pos);
    filp_close(io, NULL);
    return 0;
} 
 
static void fileIO_exit(void) 
{ 
    printk("remove successfully\n");
} 
module_init(fileIO_init); 
module_exit(fileIO_exit); 