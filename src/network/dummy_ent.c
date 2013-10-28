#include "libc.h"

void sethostent(int x)
{
}

void *getnetent()
{
        return 0;
}

void endnetent(void)
{
}

weak_alias(sethostent, setnetent);

weak_alias(sethostent, setservent);
weak_alias(getnetent, getservent);
weak_alias(endnetent, endservent);

weak_alias(sethostent, setprotoent);
weak_alias(getnetent, getprotoent);
weak_alias(endnetent, endprotoent);

