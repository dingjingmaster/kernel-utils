/*************************************************************************
> FileName: kutils.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2025年03月08日 星期六 11时13分52秒
 ************************************************************************/
#include "kutils.h"

#include <linux/spinlock_types.h>


DEFINE_SPINLOCK(gKFlagsLocker);

void* k_get_syscall_table(void)
{
#ifdef __x86_64__
#define IA32_LAST 0xc0000082
    unsigned long syscallTableAddr = 0;
    void* origSyscallTableAddr = NULL;
    void* syscall = NULL;
    unsigned char* ptr = NULL;
    int i = 0, low = 0, high = 0;

    asm volatile("rdmsr" : "=a" (low), "=d" (high) : "c" (IA32_LAST));
    syscall = (void*) (((long) high << 32) | low);

    for (ptr = syscall, i = 0; i < 2500; i++) {
        if (ptr[0] == 0xff && ptr[1] == 0x14 && ptr[2] == 0xc5) {
            printk ("WARN: search_kallsyms return asm rdmsr #1\n");
            return (void*) (0xffffffff00000000 | *((unsigned int*) (ptr + 3)));
        }
        ptr++;
    }

    // for 4.4.0-116
    for (ptr = syscall, i = 0; i < 2500; i++) {
        if (ptr[0] == 0x8b && ptr[1] == 0x04 && ptr[2] == 0xc5) {
            printk ("WARN: search_kallsyms return asm rdmsr #2\n");
            return (void*) (0xffffffff00000000 | *((unsigned int*) (ptr + 3)));
        }
        ptr++;
    }

#else
#endif

    return NULL;
}