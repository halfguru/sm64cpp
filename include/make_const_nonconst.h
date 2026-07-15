#ifndef MAKE_CONST_NONCONST_H
#define MAKE_CONST_NONCONST_H

#ifdef TARGET_N64
// IDO sometimes puts const variables in .rodata and sometimes in .data, which breaks ordering.
// This makes sure all variables are put into the same section (.data). We need to do this for
// both IDO and gcc for TARGET_N64.
#define const
#elif defined(__cplusplus)
// For C++, const variables have internal linkage by default. Redefining const to empty
// here makes them non-const, which gives them external linkage so they can be linked globally.
// This is safe because make_const_nonconst.h is included after system/std headers but before asset arrays.
#define const
#endif

#endif // MAKE_CONST_NONCONST_H
