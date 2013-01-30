#include "master.h"
#include "global.h"

int send_pkg(s_hbt *hbt)
{
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(fd < 0)
  {
    perror("socket()");
    return HBT_ERR;
  }
  int ret = 0;
  int so_broadcast = 1;
  ret = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, 
		sizeof(so_broadcast));
  if(ret < 0)
  {
    perror("setsockopt()");
    return HBT_ERR;
  }
  
  struct sockaddr_in ipaddr;
  ipaddr.sin_family = AF_INET;
  ipaddr.sin_port = htons(INADDR_ANY);
  ipaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

  ret = bind(fd, (struct sockaddr *)&ipaddr, 
		sizeof(struct sockaddr));
  if(ret < 0)
  {
    perror("bind()");
    return HBT_ERR;
  }

/* broadcast option */
  struct sockaddr_in broadcast_addr;
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_port = htons(BROADCAST_PORT);
  broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

/* send packet */
  sleep(1);
  ret = sendto(fd, (void *)hbt, sizeof(*hbt), 0, 
	 (struct sockaddr *)&broadcast_addr, 
	 sizeof(struct sockaddr)); 
  if(ret < 0)
  {
    perror("sendto()");
    return HBT_ERR;
  }

/* for debug */
  printf("packet size %d, ip is %s, role is master, ifname is %s, state is %d\n", 
				sizeof(*hbt), ipint_to_char(hbt->ip), 
				hbt->ifname, hbt->state); 

  return HBT_OK;
}

int master(s_hbt *hbt)
{
  hbt->sql_role = MASTER;
  hbt->priority = 100;
  hbt->ip = ifname_to_ip(hbt->ifname);

  send_pkg(hbt); 
  return HBT_OK;
}
