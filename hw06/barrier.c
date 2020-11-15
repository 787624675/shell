#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

// #define SOL

static int nthread = 1;
static int round = 0;

struct barrier {
  pthread_mutex_t barrier_mutex;
  pthread_cond_t barrier_cond;
  int nthread;      // Number of threads that have reached this round of the barrier
  int round;     // Barrier round
} bstate;

static void
barrier_init(void)
{
  assert(pthread_mutex_init(&bstate.barrier_mutex, NULL) == 0);
  assert(pthread_cond_init(&bstate.barrier_cond, NULL) == 0);
  bstate.nthread = 0;
}

static void 
barrier()
{
  pthread_mutex_lock(&bstate.barrier_mutex);                                      //对临界区进行加锁，barrier_mutex是开头定义的信号量
  bstate.nthread++;                                                                                //将到达当前barrier的线程的数量加一
  if (bstate.nthread == nthread) {                                                           //如果所有的线程都到达了当前barrier
    pthread_cond_broadcast(&bstate.barrier_cond);                             //针对barrier_cond这个环境变量广播，表示激活所有线程
    bstate.nthread = 0;
    bstate.round++;
  }
  else {
    pthread_cond_wait(&bstate.barrier_cond, &bstate.barrier_mutex);//当还有线程没有到达barrier时，释放互斥锁，然后休眠
  }
  pthread_mutex_unlock(&bstate.barrier_mutex);                                //释放互斥锁
}

static void *
thread(void *xa)
{
  long n = (long) xa;
  long delay;
  int i;

  for (i = 0; i < 20000; i++) {
    int t = bstate.round;
    assert (i == t);
    barrier();
    usleep(random() % 100);
  }
}

int
main(int argc, char *argv[])
{
  pthread_t *tha;
  void *value;
  long i;
  double t1, t0;

  if (argc < 2) {
    fprintf(stderr, "%s: %s nthread\n", argv[0], argv[0]);
    exit(-1);
  }
  nthread = atoi(argv[1]);
  tha = malloc(sizeof(pthread_t) * nthread);
  srandom(0);

  barrier_init();

  for(i = 0; i < nthread; i++) {
    assert(pthread_create(&tha[i], NULL, thread, (void *) i) == 0);
  }
  for(i = 0; i < nthread; i++) {
    assert(pthread_join(tha[i], &value) == 0);
  }
  printf("OK; passed\n");
}
