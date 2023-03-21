#include <stdio.h>

int main(){
  printf("P1 hello. P1=%d\n", getpid());
  int p2 = fork();
  if(p2 == 0){
    printf("P2 hello. P2=%d\n", getpid());
    int p3 = fork();
    if(p3 == 0){  
      printf("P3 hello. P3=%d\n", getpid());
    }
  } else{
    int p4 = fork();
    if(p4 == 0){
      printf("P4 hello. P4=%d\n", getpid());
      int p5 = fork();
      if(p5 == 0){
        printf("P5 hello. P5=%d\n", getpid());
      }
    }
  }
  // int status1 = waitpid(p5, 0, 0);
  return 0;
}
/*
processes will not terminate until all the child processes returns
Processes creation sequence is 1->2->4->5->3, like pre-order tree traverse
Processes termination sequence is 4->5->2->3->1, like post-order tree traverse
    1
   / \
  2   3
 / \ 
4   5

*/