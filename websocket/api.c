//test.c

#include <pthread.h>
#include <stdio.h>

void *input_listener(void *condition)
{
  while(1)
    {
      printf("A key was pressed.\n");
      if (*(int*)condition)
	break;
      sleep(2);
    }
  pthread_exit(0);
}

int main()
{
  printf("Start\n");
  pthread_t thread;
  int val = 0;
  pthread_create(&thread, NULL, input_listener, &val);

  // Continue main
  int i = 10;
  while(i)
    {
      getchar();
      i--;
    }
  lock = 1;
  pthread_join(thread, NULL);
  return (0);
}
