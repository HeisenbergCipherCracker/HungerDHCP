#include <stdio.h>
#include <pcap.h>
#include <capture.h>

// Ethernet header structure
struct ethhdr {
    unsigned char h_dest[6];       // destination MAC address
    unsigned char h_source[6];     // source MAC address
    unsigned short h_proto;        // protocol type
};

void packet_handler(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    struct ethhdr *eth_header = (struct ethhdr *)packet;
    
    // Print source MAC address
    printf("[inf]Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth_header->h_source[0], eth_header->h_source[1], eth_header->h_source[2],
           eth_header->h_source[3], eth_header->h_source[4], eth_header->h_source[5]);
    
    // Print destination MAC address
    printf("[inf]Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth_header->h_dest[0], eth_header->h_dest[1], eth_header->h_dest[2],
           eth_header->h_dest[3], eth_header->h_dest[4], eth_header->h_dest[5]);
    
    // Print EtherType (in hex)
    printf("[inf]EtherType: %04x\n", ntohs(eth_header->h_proto));
    
    // Calculate and print payload length
    int payload_length = pkthdr->len - sizeof(struct ethhdr);
    printf("[inf]Payload length: %d bytes\n", payload_length);
    
    // Print out the raw packet data
    printf("Raw packet data:\n");
    for (int i = 0; i < pkthdr->len; i++) {
        printf("%02x ", packet[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n\n");
}

int capture(const char* interface) {
    char errbuf[PCAP_ERRBUF_SIZE];
    
    // Open the network interface for packet capture
    pcap_t *handle = pcap_open_live(interface, 65536, 1, 1000, errbuf); // Change "eth0" to your network interface
    
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s\n", errbuf);
        return 1;
    }
    
    // Start capturing packets
    pcap_loop(handle, -1, packet_handler, NULL);
    
    // Close the capture handle
    pcap_close(handle);
    
    return 0;
}
