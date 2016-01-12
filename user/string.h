/*
    string.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _STRING_H
#define _STRING_H

#include "sys.h"

unsigned int strlen(const char* _str)
{
    unsigned int len = 0;
    while(*_str!='\0') {
        //puts_uint(*_str);
        len++;
        _str++;
    }
    return len;
}

int strcmp(char* str1,char* str2)
{
    unsigned int len1,len2;
    len1 = strlen(str1);
    len2 = strlen(str2);
    if(len1>len2) return 1; else if(len1<len2) return -1;

    unsigned int i = 0;
    while(i<len1) {
        if(str1[i]>str2[i]) return 1;
        else if(str1[i]<str2[i]) return -1;
        else i++;
    }
    return 0;
}

#endif
