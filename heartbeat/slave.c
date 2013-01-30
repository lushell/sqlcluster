#include "slave.h"
#include "global.h"

int slave(s_hbt *hbt)
{
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(fd < 0)
  {
    perror("socket()");
    return HBT_ERR;
  }
  int ret = 0;
  int opt = 1;
  ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, 
		sizeof(opt));
  if(ret < 0)
  {
    perror("setsockopt()");
    return HBT_ERR;
  }
  
  struct sockaddr_in ipaddr;
  ipaddr.sin_family = AF_INET;
  ipaddr.sin_port = htons(BROADCAST_PORT);
  ipaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

  ret = bind(fd, (struct sockaddr *)&ipaddr, 
		sizeof(struct sockaddr));
  if(ret < 0)
  {
    perror("bind()");
    return HBT_ERR;
  }

  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);

  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 9;
/* receive packet  */
  ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
  if(ret == -1)
  {
    perror("select()");
    return HBT_ERR;
  }
  if(ret == 0)
  {
    return HBT_NO_DATA;
  }
  if(ret > 0)
  {
    char buffer[255];
    int sock_len = sizeof(struct sockaddr_in);
    memset(buffer, 0, 256);
    int len = recvfrom(fd, buffer, sizeof(buffer), 0, 
			(struct sockaddr *)&ipaddr,
			&sock_len);
    s_hbt *data = (s_hbt *)buffer; 
    printf("slave state, receive from %s packet size is %d, ifname is %s,"
		 	"len is %d, ip is %s, state is %d\n", 
			inet_ntoa(ipaddr.sin_addr),sizeof(*data), data->ifname, 
			len, ipint_to_char(data->ip), data->state);
  }
  return HBT_OK;
}
