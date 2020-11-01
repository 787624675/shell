#define KEY_MUTEX 100
#define KEY_APPLE 103
#define KEY_ORANGE 104
#define KEY_EMPTY 105
#define KEY_SHM	200
#define BUFFER_SIZE 10
typedef int semaphore;
union semun {
	// semaphore 带有的队列
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	/*struct seminfo *__buf;*/
};
struct shared_use_st {
	int buffer[BUFFER_SIZE];
	//int count;
	int apple_num;
	int orange_num;
};
extern int sem_p(semaphore sem_id);
extern int sem_v(semaphore sem_id);