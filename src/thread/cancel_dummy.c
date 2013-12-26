#include "pthread_impl.h"
#ifdef __ILP32__
#define __syscall_long long long
#else
#define __syscall_long long long
#endif

static __syscall_long sccp(__syscall_long nr, __syscall_long u,
                           __syscall_long v, __syscall_long w,
                           __syscall_long x, __syscall_long y, __syscall_long z)
{
	return (__syscall)(nr, u, v, w, x, y, z);
}

weak_alias(sccp, __syscall_cp);

static void dummy()
{
}

weak_alias(dummy, __testcancel);
