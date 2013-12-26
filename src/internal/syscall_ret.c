#include <errno.h>

long long __syscall_ret(unsigned long long r)
{
	if (r > -4096UL) {
		errno = -r;
		return -1;
	}
	return r;
}
