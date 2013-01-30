/*
  author: tangchao@360buy.com
  date: 2013/1/6
  upgrade 20120109
  for mysql heartbeat
*/
#include "global.h"
#include "master.h"
#include "slave.h"

static void init_hbt(s_hbt *hbt)
{
  memset(hbt, 0, sizeof(*hbt));
  hbt->state = VIPOFF;
  hbt->sql_role = ALONE;
}

int main(int argc, char *argv[])
{
  s_hbt *hbt;
  init_hbt(hbt);
  int ret = 0;
  char ifname[] = "eth0";
  memcpy(hbt->ifname, ifname, sizeof(ifname));
  while( TRUE )
  {
    switch( hbt->state )
    {
      case VIPON: master(hbt); break;
      case VIPOFF:
	if(slave(hbt) == HBT_NO_DATA) 
	{ 
	  hbt->state = VIPON; 
	  printf("change to master state\n");
	} 
	break;
      default: break;
    }
  }
  printf("Exit:\n"
	 "     heartbeat state is %d\n", hbt->state);
  return HBT_OK;
}
