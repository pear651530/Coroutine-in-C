#include <errno.h>
#include <stdlib.h>
#include "coroutine_int.h"

//初始化
void rs_init(struct rs *rs) {
    rs->in = 0;
    rs->mask = BUFFER_SIZE - 1;
}

static inline unsigned int __buffer_unused(struct rs *rs) {
    //判斷是否滿
    if(rs->mask == rs->in) return 1;
    else return 0;
}

// enstack at in 放進去
int rs_enstack(struct rs *rs, struct task_struct *task) {
    if (__buffer_unused(rs))
        return -EAGAIN;

    rs->r[rs->in] = task;
    rs->in++;
    return 0;
}

// destack at out 拿出來
struct task_struct *rs_destack(struct rs *rs) {
    struct task_struct *rev;

    if (rs->in == 0) //判斷是否空
        return NULL;

    rs->in--;
    rev = rs->r[rs->in];

    return rev;
}