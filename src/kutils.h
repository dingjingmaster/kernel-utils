/*************************************************************************
> FileName: kutils.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2025年03月08日 星期六 11时13分39秒
 ************************************************************************/
#ifndef _K_UTILS_H
#define _K_UTILS_H
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/magic.h>
#include <linux/version.h>

#if 0
#define THREAD_INFO_GAP                     128
#define K_UTILS_DISABLE_PTR_CHECK_K2U       0x0400  
#define K_UTILS_DISABLE_PTR_CHECK_KFU       0x0800  
#define K_UTILS_FLAG_SAVE_POS               (THREAD_INFO_GAP - sizeof(KFlags) - sizeof(STACK_END_MAGIC))
#define K_UTILS_STACK_END_POS               (THREAD_INFO_GAP - sizeof(STACK_END_MAGIC))
#define K_UTILS_FAKE_SAVE_ADDR(task)        ((void*) task_stack_page(task) + THREAD_INFO_GAP)

typedef unsigned long KFlags;


extern spinlock_t gKFlagsLocker;

static inline void k_set_k2u_enable_ptr_check(void)
{
    spin_lock(&gKFlagsLocker);
    {
        unsigned char* p = ((unsigned char*) task_stack_page (current));
        KFlags* flags = ((KFlags*) (p + K_UTILS_FLAG_SAVE_POS));
        *flags &= ~K_UTILS_DISABLE_PTR_CHECK_K2U;
    }
    spin_unlock(&gKFlagsLocker);
}

static inline void k_set_k2u_disable_ptr_check(void)
{
    spin_lock(&gKFlagsLocker);
    {
        unsigned char* p = ((unsigned char*) task_stack_page (current));
        KFlags* flags = ((KFlags*) (p + K_UTILS_FLAG_SAVE_POS));
        *flags |= K_UTILS_DISABLE_PTR_CHECK_K2U;
    }
    spin_unlock(&gKFlagsLocker);
}

static inline void k_set_kfu_enable_ptr_check(void)
{
    spin_lock(&gKFlagsLocker);
    {
        unsigned char* p = ((unsigned char*) task_stack_page (current));
        KFlags* flags = ((KFlags*) (p + K_UTILS_FLAG_SAVE_POS));
        *flags &= ~K_UTILS_DISABLE_PTR_CHECK_KFU;
    }
    spin_unlock(&gKFlagsLocker);
}

static inline void k_set_kfu_disable_ptr_check(void)
{
    spin_lock(&gKFlagsLocker);
    {
        unsigned char* p = ((unsigned char*) task_stack_page (current));
        KFlags* flags = ((KFlags*) (p + K_UTILS_FLAG_SAVE_POS));
        *flags |= K_UTILS_DISABLE_PTR_CHECK_KFU;
    }
    spin_unlock(&gKFlagsLocker);
}
#endif

void* k_get_syscall_table(void);

#endif
