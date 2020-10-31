#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "myipc.h"

int main(int argc, char *argv[])
{
    // i is the iterator to memset the buffer later at row 67
    int i,mother_pid,father_pid,son_pid, daughter_pid, shmid;
    
	semaphore mutex, apple, orange, empty;
    union semun sem_union;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;

	if ( (mutex=semget((key_t)KEY_MUTEX,1,0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create semaphore!"); 
		exit(EXIT_FAILURE);
	if ( (full = semget((key_t)KEY_APPLE,1,0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create semaphore!"); 
		exit(EXIT_FAILURE);
	}
    if ( (full = semget((key_t)KEY_ORANGE,1,0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create semaphore!"); 
		exit(EXIT_FAILURE);
	}
    if ( (full = semget((key_t)KEY_EMPTY,1,0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create semaphore!"); 
		exit(EXIT_FAILURE);
	}
	if ( (shmid = shmget((key_t)KEY_SHM,sizeof(struct shared_use_st),0666|IPC_CREAT)) == -1 ) {
		fprintf(stderr,"Failed to create shared memory!"); 
		exit(EXIT_FAILURE);
	}

    sem_union.val = 1;
    // bind semaphore to the variaties
    if (semctl(mutex, 0, SETVAL, sem_union) == -1) {
		fprintf(stderr,"Failed to set semaphore!"); 
		exit(EXIT_FAILURE);
	}

    sem_union.val = 0;
    if (semctl(apple, 0, SETVAL, sem_union) == -1) {
		fprintf(stderr,"Failed to set semaphore!"); 
		exit(EXIT_FAILURE);
	}
    sem_union.val = 0;
    if (semctl(orange, 0, SETVAL, sem_union) == -1) {
		fprintf(stderr,"Failed to set semaphore!"); 
		exit(EXIT_FAILURE);
	}
    // empty is 2
    sem_union.val = 2;
    if (semctl(empty, 0, SETVAL, sem_union) == -1) {
		fprintf(stderr,"Failed to set semaphore!"); 
		exit(EXIT_FAILURE);
	}

    sem_union.val = BUFFER_SIZE;
    

	if ( (shared_memory = shmat(shmid,(void *)0,0) ) == (void *)-1) {
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	shared_stuff = (struct shared_use_st *)shared_memory;

	for(i=0;i<BUFFER_SIZE;i++)
	{
		shared_stuff->buffer[i] = 0;
	}
	shared_stuff -> lo = 0;
	shared_stuff -> hi = 0;
	shared_stuff -> cur = 0;

  	exit(EXIT_SUCCESS);
}
