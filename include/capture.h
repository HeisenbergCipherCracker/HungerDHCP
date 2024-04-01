#ifndef CAPTURE_H
#define CAPTURE_H

#include <stdint.h>
#include <pcap.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet);
int capture(const char* interface);
#endif // CAPTURE_H