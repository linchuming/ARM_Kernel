/*
    console.c
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/
#include "../sys.h"
#include "../string.h"

char str[256];
int main()
{
    while(1) {
        puts("arm@cmlin:");
        str[0] = '\0';
        getline(str);
        if(strlen(str)==0) continue;
        /*
        puts(str);
        char * tmp = str;
        puts_uint(*(tmp-1));
        puts_uint(str[0]);
        puts_uint(*tmp);
        puts_uint(str[1]);
        puts_uint(*(tmp+1));
        puts_uint(str[2]);
        */
        int pid = fork();
        if(pid>0) {
            wait(pid);
        } else {
            exec(str);
            puts("unknown instruction.\r\n");
            break;
        }
    }
    return 0;
}
