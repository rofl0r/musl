#define SHMLBA 4096

struct shmid_ds
{
	struct ipc_perm shm_perm;
	size_t shm_segsz;
	time_t shm_atime;
	time_t shm_dtime;
	time_t shm_ctime;
	pid_t shm_cpid;
	pid_t shm_lpid;
	unsigned long long shm_nattch;
	unsigned long long __pad1;
	unsigned long long __pad2;
};

struct shminfo {
	unsigned long long shmmax, shmmin, shmmni, shmseg, shmall, __unused[4];
};

struct shm_info {
	int used_ids;
	unsigned long long shm_tot, shm_rss, shm_swp;
#ifdef _GNU_SOURCE
	unsigned long long swap_attempts, swap_successes;
#else
	unsigned long long __reserved[2];
#endif
};

typedef unsigned long long shmatt_t;

