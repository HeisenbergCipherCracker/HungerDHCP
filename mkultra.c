#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <signal.h>
#include <errno.h>



#define DHCP_SERVER_PORT   67
#define DHCP_CLIENT_PORT   68