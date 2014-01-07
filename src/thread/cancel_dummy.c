#include "pthread_impl.h"
#include "syscall.h"

static long sccp(__sca nr, __sca u, __sca v, __sca w, __sca x, __sca y, __sca z)
{
	return (__syscall)(nr, u, v, w, x, y, z);
}

weak_alias(sccp, __syscall_cp);

static void dummy()
{
}

weak_alias(dummy, __testcancel);
