#include <semaphore.h>

#define MAX 100

int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
  buffer[fill] = value;
  fill = (fill+1) % MAX;
}
int get(){
  int tmp = buffer[use];
  use = (use+1) % MAX;
  return tmp;
}

sem_t empty;
sem_t full;
sem_t mutex;
int loops = 1000;

void *producer(void *arg){
  for(int i=0; i<loops; i++){
    sem_wait(&empty); // producer consumes a empty slot in buffer
    sem_wait(&mutex);
    put(i); // critical section
    sem_wait(&mutex);
    sem_post(&full); // producer fills up a slot
  }
}
void *consumer(void *arg){
  for(int i=0; i<loops; i++){
    sem_wait(&full);
    sem_wait(&mutex);
    int tmp = get();
    sem_wait(&mutex);
    sem_post(&empty);
    printf("%d\n", tmp);
  }
}

int main(int argc, char *argv[]){
  sem_init(&empty, 0, MAX); // All slots are empty when program starts
  sem_init(&full, 0, 0); // no slots are filled up
}