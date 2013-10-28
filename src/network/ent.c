#include "__dns.h"
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

union sa {
        struct sockaddr_in sin;
        struct sockaddr_in6 sin6;
};

static struct {
	struct hostent he;
	char names[2][256];
	char *names_ptr[2];
	char *addrs[2];
	union ia {
		struct in_addr in;
		struct in6_addr in6;
	} ia;
} h;

static FILE* hosts_file;

struct hostent *gethostent(void)
{
	char line[1024], *p;
	if(!hosts_file && !(hosts_file = fopen("/etc/hosts", "r")))
		return 0;
get_line:
	if(!fgets(line, sizeof line, hosts_file))
		return 0;
	if ((p=strchr(line, '#'))) *p++='\n', *p=0;
	/* Isolate IP address to parse */
	for (p=line; *p && !isspace(*p); p++);
	*p++ = 0;
	for (; *p && isspace(*p); p++);
	if(!*p) goto get_line;
	union sa sa = {{0}};
	if (__ipparse(&sa, AF_UNSPEC, line) < 0) goto get_line;
	h.he.h_addrtype = sa.sin.sin_family;
	if(sa.sin.sin_family == AF_INET6) {
		h.he.h_length = sizeof(h.ia.in6.s6_addr);
		h.ia.in6 = sa.sin6.sin6_addr;
	} else if (sa.sin.sin_family == AF_INET) {
		h.he.h_length = sizeof(in_addr_t);
		h.ia.in = sa.sin.sin_addr;
	} else {
		goto get_line;
	}
	h.he.h_addr_list = h.addrs;
	h.addrs[0] = (char*)(void*) &h.ia;
	h.addrs[1] = 0;
	h.he.h_aliases = h.names_ptr;
	size_t alias = 0;
next_name:;
	char *e = p+1;
	for (; *e && !isspace(*e); e++);
	*e++ = 0;
	snprintf(h.names[alias], sizeof(h.names[0]), "%s", p);
	if(!alias) h.he.h_name = h.names[0];
	else h.names_ptr[alias - 1] = h.names[alias];
	if(*e && ++alias < sizeof h.names_ptr / sizeof h.names_ptr[0]) {
		p = e; goto next_name;
	}
	h.names_ptr[alias - 1] = 0;
	return &h.he;
}

void endhostent(void)
{
	if(hosts_file) fclose(hosts_file);
	hosts_file = 0;
}

