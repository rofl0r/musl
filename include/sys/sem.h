#ifndef _SYS_SEM_H
#define _SYS_SEM_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_size_t
#define __NEED_pid_t
#define __NEED_time_t
#ifdef _GNU_SOURCE
#define __NEED_struct_timespec
#endif
#include <bits/alltypes.h>

#include <sys/ipc.h>

#define SEM_UNDO	0x1000
#define GETPID		11
#define GETVAL		12
#define GETALL		13
#define GETNCNT		14
#define GETZCNT		15
#define SETVAL		16
#define SETALL		17

#include <endian.h>

struct semid_ds {
	struct ipc_perm sem_perm;
	time_t sem_otime;
	time_t __unused1;
	time_t sem_ctime;
	time_t __unused2;
#if __BYTE_ORDER == __LITTLE_ENDIAN
	unsigned short sem_nsems;
	char __sem_nsems_pad[sizeof(time_t)-sizeof(short)];
#else
	char __sem_nsems_pad[sizeof(time_t)-sizeof(short)];
	unsigned short sem_nsems;
#endif
	time_t __unused3;
	time_t __unused4;
};

#define _SEM_SEMUN_UNDEFINED 1

#define SEM_STAT 18
#define SEM_INFO 19

struct  seminfo {
	int semmap;
	int semmni;
	int semmns;
	int semmnu;
	int semmsl;
	int semopm;
	int semume;
	int semusz;
	int semvmx;
	int semaem;
};

struct sembuf {
	unsigned short sem_num;
	short sem_op;
	short sem_flg;
};

int semctl(int, int, int, ...);
int semget(key_t, int, int);
int semop(int, struct sembuf *, size_t);

#ifdef _GNU_SOURCE
int semtimedop(int, struct sembuf *, size_t, const struct timespec *);
#endif

#ifdef __cplusplus
}
#endif
#endif
