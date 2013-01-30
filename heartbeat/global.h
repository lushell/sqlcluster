#include <stdio.h>
#include <assert.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/errno.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define HBT_OK		0
#define HBT_ERR		-1
#define HBT_NO_DATA	100	/* heartbeat have no data */

#define TRUE		1
#define FALSE		0

#define MASTER		1	/* mysql master state */
#define SLAVE		2	/* mysql slave state */
#define ALONE		3	/* mysql alone state */
#define MS		4	/* mysql master and slave */
#define MASTER_INVALID	5	/* voting request for master */
#define SLAVE_INVALID	6	/* voting request for slave */

#define VIPON 	10
#define VIPOFF 	11

#define LFILE_LEN 	32
#define IFNAME_LEN 	15

#define MAXPRIORITY	oxffffffff



/* structure data packet */
typedef struct _s_hbt {
  uint32_t ip;			/* ipaddr */
  char ifname[IFNAME_LEN];	/* heartbeat ifname */
  int sql_role;			/* mysql role are master/slave/alone */
  int state;			/* vip flag, 10 vip on, 11 vip off */
  uint32_t priority;		/* priority in cluster */
  int preempt;			/* true if a higher prio preempt a lower one */
  unsigned long int lpos;	/* mysql binlog postion */
  char lfile[LFILE_LEN];	/* mysql binlog file name */
} s_hbt;


int master(s_hbt *hbt);
int slave(s_hbt *hbt);
uint32_t ifname_to_ip(char *ifname);
char * ipint_to_char(uint32_t int_addr);
