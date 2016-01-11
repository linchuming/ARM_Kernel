/*
    memory.h
    Author: cmlin
    Email: 13307130255@fudan.edu.cn
*/

#ifndef _MEMORY_H
#define _MEMORY_H
#include "kernel.h"

#define START_ADDR  (0x00800000 + KERN_BASE)
#define END_ADDR  (0x1F000000 + KERN_BASE)
#define _Ksize  4096 //4KB

struct run {
    uint size;
    struct run * next;
};

static struct run * free_head = NULL;
static spinlock_t mem_lock;
void mem_init()
{
    free_head = (struct run*)START_ADDR;
    free_head->size = END_ADDR - START_ADDR;
    free_head->next = NULL;
    spinlock_init(&mem_lock);
}

/*
    char * kalloc(uint)
    The memory calloc unit is 4KB
    The count means you want the number of 4KB
*/
char * kalloc(uint count)
{
    if(count == 0) {
        return NULL;
    }
    spin_lock(&mem_lock);
    uint size = count * _Ksize;
    char * res = NULL;
    struct run * r = free_head;
    struct run * pre = NULL;

    while(r) {
        if(r->size < size) {
            pre = r;
            r = r->next;
        } else if(r->size > size) {
            res = (char*)r;
            uint n_size = r->size - size;
            uint addr = (uint)r + size;
            struct run * n = (void*)addr;
            n->size = n_size;
            n->next = r->next;
            if((uint)r==(uint)free_head) {
                free_head = n;
            } else {
                pre->next = n;
            }
            break;
        } else {
            res = (char*)r;
            if((uint)r == (uint)free_head) {
                free_head = r->next;
            } else {
                pre->next = r->next;
            }
            break;
        }
    }
    release_lock(&mem_lock);
    return res;
}

/*
    int kfree(char*,uint)
    count is the number of 4KB
*/
int kfree(char * addr,uint count)
{
    if(count==0) return -1;
    spin_lock(&mem_lock);
    struct run * r = free_head;
    uint size = count * _Ksize;
    struct run * n =  (void*)addr;
    n->size = size;
    if((uint)n < (uint)free_head) {
        n->next = free_head;
        if((uint)n + n->size >= (uint)n->next) {
            n->size = n->next->size + (uint)n->next - (uint)n;
            n->next = n->next->next;

        }
        free_head = n;
    } else {
        struct run * pre = NULL;
        while((uint)r < (uint)n && r!=NULL) {
            pre = r;
            r = r->next;
        }
        n->next = r;
        if(r!=NULL && (uint)n+n->size >= (uint)r) {
            n->size = r->size + (uint)n->next - (uint)n;
            n->next = r->next;
        }
        if((uint)pre + pre->size >= (uint)n) {
            pre->next = n->next;
            pre->size += n->size;
        } else {
            pre->next = n;
        }
    }
    release_lock(&mem_lock);
    return 0;
}



/*
    char* kalloc_align(uint)
    count is the number
*/

int divmod(uint num,uint n)
{
    if(num - ( (num>>n)<<n) ) return 1; else return 0;
}

char * kalloc_align(uint count)
{
    uint n = (count<<1)-1;
    char * addr = kalloc(n);
    if(addr==NULL) return addr;
    uint i = 0;
    while(divmod((uint)(addr+i*_Ksize),ilog2(count*_Ksize)) ) i++;
    if(i) {
        kfree(addr,i);
    }
    if(i+count<n) {
        char * paddr =  addr + (i+count) * _Ksize;
        kfree(paddr,n-count-i);
    }

    return addr+i*_Ksize;
}

/*
    void showFreememory()
*/
void showFreememory()
{
    uart_spin_puts("show the free memory:\r\n");
    struct run * r = free_head;
    while(r) {
        puts_uint((uint)r);
        puts_uint(r->size);
        r = r->next;
    }
    uart_spin_puts("show end.\r\n");
}

/*
    void memcpy(void*,void*,uint)
*/

void memcpy(void* dest,void* src,uint _size)
{
    uint dt = (uint)dest;
    char* sc = src;
    for(uint i = 0;i < _size; i++) {
        *(volatile unsigned char*)(dt+i) = sc[i];
    }
}

void memset(void* dest,char p,uint _size)
{
    uint dt = (uint)dest;
    for(uint i = 0;i < _size; i++) {
        *(volatile unsigned char*)(dt+i) = p;
    }
}

/*
void memcpy(void* dest,void* src,uint _size)
{
    uint addr = (uint)dest;
    uint * data = src;
    _size = _size >> 2;
    for(uint i = 0;i<_size; i++ ) {
      puts_uint(i);
      puts_uint(addr);
      puts_uint(data[i]);
      uart_spin_getbyte();
      out32(addr+4*i,data[i]);
    }
}
*/
#endif // _MEMORY_H
