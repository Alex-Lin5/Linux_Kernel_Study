// lock
typedef struct __lock_t { int flag; int guard; queue_t *q; } lock_t;

void lock_init(lock_t *m){
  m->flag = 0;
  m->guard  = 0;
  queue_init(m->q);
}

int TestAndSet(int *ptr, int new){
  int old = *ptr;
  *ptr = new;
  return old;
}

void lock(lock_t *m){
  while (TestAndSet(&m->guard, 1) == 1)
    yield(); // acquire guard lock by giving up CPU
  if (m->flag == 0) {
    m->flag = 1; // acquire lock m
    m->guard = 0; // release lock guard 
  } else {
    queue_add(m->q, gettid());
    // if another thread calls unpark() before this thread calls park() because of interruption
    // the subsequent park() will return immediately rather than sleep
    setpark(); // Solaris solution that indicates the thread is about to park
    // setpark() should call before releasing guard lock so other thread cannot acquire it and call unpark()
    m->guard = 0;
    park();
  }
}

void unlock(lock_t *m){
  while (TestAndSet(&m->guard, 1) == 1)
    ; // acquire guard lock by spinning
  if (queue_empty(m->q))
    m->flag = 0; // release the lock since no threads waits it
  else
    unpark(queue_remove(m->q)); // wake up a thread in queue, hold lock for it
  m->guard = 0;
}

int waitingRace(){
  pthread_t* A;
  pthread_t* B;
  lock_t *m; lock_init(m);
  A->lock(m); // 1 Thread A holds the lock
  B->lock(m); // 2 before B acquire lock, context switch happened
  A->Execute();
  A->unlock(m); // 3 Thread A release the lock but no thread wakes up
  B->Execute(); // 4 Thread B gets CPU again but goes to sleep
  B->unlock(m);
  return 0;
}

/*-----------------------------------------------------------*/
// conditional variables
void thr_exit(){
  Pthread_mutex_lock(&m);
  done = 1;
  Pthread_cond_signal(&c);
  Pthread_mutex_unlock(&m);
}

void thr_join(){
  // guarding with mutex lock to prevent race condition that cause parent sleeps forever
  Pthread_mutex_lock(&m); 
  while (done == 0){
    // if parent is interrupted here before go to sleep
    // child will wake no threads when finished
    // resume from interruption parent will sleep forever
    Pthread_cond_wait(&c, &m); 
  }
  Pthread_mutex_unlock(&m);
}
void *child(void *arg){
  printf("child\n");
  thr_exit();
  return NULL;
}

int cond_var(){
  int done = 0; // captures and remember that child thread has returned
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t c = PTHREAD_COND_INITIALIZER;  
  printf("parent: begin\n");
  pthread_t p;
  pthread_create(&p, NULL, child, NULL); // child finished and wake parent
  thr_join(); // need to avoid child finished and wake nobody before parent is put in sleep
  printf("parent: end\n");
  return 0;
}

/*-----------------------------------------------------------*/
// Semaphore
void *child(void *arg){
  printf("child\n");
  sem_post(&s);
  return NULL;
}
int semaphore(){
  sem_t m;
  sem_init(&m, 0, X);
  printf("parent: begin\n");
  pthread_t c;
  pthread_create(c, NULL, child, NULL);
  sem_wait(&s);
  printf("parent: end\n");
  return 0;
}

