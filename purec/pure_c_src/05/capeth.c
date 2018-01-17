#include <sys/socket.h>
#include <sys/ioctl.h>             /*ioctl function*/
#include <linux/if_ether.h>        /*ethhdr struct*/
#include <string.h>                
#include <unistd.h>                
/*#include <signal.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <net/if.h>                /*ifreq  struct*/
#include <netinet/in.h>            /*in_addr struct*/
#include <linux/ip.h>              /*iphdr  struct*/
#include <linux/udp.h>             /*udphdr struct*/
#include <linux/tcp.h>             /*tcphdr struct*/

int fd;

int init(char *ethname)
{
    int i;
    struct ifreq  ifr;
    
    fd = socket(AF_INET, SOCK_PACKET, htons(0x0003));
    if ( fd < 0 )
    {    
         perror("socket");
         return -3;
    }
    strcpy(ifr.ifr_name, ethname);
    i = ioctl(fd, SIOCGIFFLAGS, &ifr);
    if ( i < 0 )
    {    
         close(fd);
         perror("cant't get flags \n");
         printf("%s\n", ethname);
         return -1;
    }
/*    ifr.ifr_flags |= IFF_PROMISC; */
    i = ioctl(fd, SIOCSIFFLAGS, &ifr); 
    if ( i < 0 )
    {
         perror("promiscuous set error\n");
         return -2;
    }
    return 0;
}

int main(int argc, char *argv[])
{
	int n, i, j;
        char ethname[255];
        char ef[ETH_FRAME_LEN];
        struct ethhdr  *p_ethhdr;
	
        if (argc < 2) 
            strcpy(ethname, "eth0");
        else
            strcpy(ethname, argv[1]);
        
        i = init(ethname);
        
        if (i < 0)  {
            printf("Error: %d     ", errno);
            exit(1); 
            }
        p_ethhdr = (struct ethhdr *)ef;

for (j=0; j<9; j++) {
        n = read(fd, ef, ETH_FRAME_LEN);
        
	if (n < 0)
                perror("Err code: ");
             printf("\n");
 
        printf("Line %d: Dest MAC: ", i);
        for (i=0; i<ETH_ALEN-1; i++)
             printf("%02x-", p_ethhdr->h_dest[i]);
        printf("%02x ", p_ethhdr->h_dest[ETH_ALEN-1]);
        printf("Source MAC: ");
        for (i=0; i<ETH_ALEN-1; i++)
             printf("%02x-", p_ethhdr->h_source[i]);
        printf("%02x ", p_ethhdr->h_source[ETH_ALEN-1]);
        printf("protocol: 0x%04x \n", ntohs(p_ethhdr->h_proto));
/*	sleep(1); */
}

        close(fd);
        return 0;	
}
