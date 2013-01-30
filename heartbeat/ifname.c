#include "global.h"

/* find out ifname's ip */
uint32_t ifname_to_ip( char *ifname )
{
  struct ifreq    ifr; 
  int             fd      = socket(AF_INET, SOCK_DGRAM, 0);
  uint32_t        addr    = 0; 

  if (fd < 0)     
    return (-1);
  strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
  if (ioctl(fd, SIOCGIFADDR, (char *)&ifr) == 0) 
  { 
    struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
    addr = ntohl(sin->sin_addr.s_addr);
  } 
  close(fd);
  return addr;
}

/* conversion numeric ip to character */
char * ipint_to_char( uint32_t int_addr )
{
  char 	*	ip_addr 	= NULL;
  struct 	in_addr 	debug_addr;

  debug_addr.s_addr = int_addr;
  ip_addr = inet_ntoa(debug_addr); 
  return ip_addr;
}
