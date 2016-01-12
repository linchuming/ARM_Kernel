/*
    init.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#include "sys.h"
//#include "string.h"


char * str = (char*)0x7FFFF000;
//char str[256];
int main()
{
    puts("I am the init.\r\n");
    while(1)
    {
        puts("arm@cmlin:");
        *str = '\0';
        getline(str);
        //puts_uint(*str);
        if(*str=='\0') {
            continue;
        }

        if(str[0]=='f'&&str[1]=='o'&&str[2]=='r'&&str[3]=='k'&&str[4]=='\0') {
            int pid = fork();
            if(pid>0) {
                puts("I am father.\r\n");
            } else {
                puts("I am the kid.\r\n");
                while(1);
            }
        } else {
            puts("unknown instruction.\r\n");
        }
    }
    return 0;
}
