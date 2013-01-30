#include "hbt_thread.h"

void *create_master_thread(void *agc)
{
  int tid = *(int *)agc;
  handler_master();
  pthread_exit(NULL);
}

void *master_thread(void *agc)
{
  int tid = *(int *)agc;
  handler_slave();
  pthread_exit(NULL);
}

int do_create_thread()
{
  pthread_t pt_master;
  pthread_t pt_slave;
  pthread_mutex_init(&mutex, NULL);
  int res;
  res = pthread_create(&pt_master, NULL, create_master_thread, NULL);
  if(res)
  {
    perror("pthread_create()");
    return HBT_ERR;
  }
  res = pthread_create(&pt_slave, NULL, create_slave_thread, NULL);
  if(res)
  {
    perror("pthread_create()");
    return HBT_ERR;
  }
  return HBT_OK;
}
