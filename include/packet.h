#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <arpa/inet.h>


typedef struct dhcp_packet_struct{
        u_int8_t  op;
        u_int8_t  htype;
        u_int8_t  hlen;
        u_int8_t  hops;
        u_int32_t xid;
        u_int16_t secs;
        u_int16_t flags;
        struct in_addr ciaddr;
        struct in_addr yiaddr;
        struct in_addr siaddr;
        struct in_addr giaddr;
        unsigned char chaddr [16];
        char sname [64];
        char file [128];
	      char options[312];
        }dhcp_packet;

#endif