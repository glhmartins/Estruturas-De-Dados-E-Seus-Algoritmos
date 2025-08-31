#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int i, x = atoi(argv[1]);
  printf("%d\n", x);
  for(i = 0; i < argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);
    
  return 0;
}