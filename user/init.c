/*
    init.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#include "sys.h"

int main()
{
    puts("I am the init.\r\n");
    int pid = fork();
    if(pid>0) {
        puts("I am the father.\r\n");
    } else {
        puts("I am the fork kid.\r\n");
        exec("console");
    }
    while(1);
    return 0;
}
