#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_ether.h>
#include <string.h>
/*#include <signal.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>

#define PORT_SEND 7474

struct arppacket
{
    unsigned short  ar_hrd;             /* Hardware Type */
    unsigned short  ar_pro;             /* Protocol Type */
    unsigned char   ar_hln;             /* Hardware Address Length */
    unsigned char   ar_pln;             /* Prototol Address Length */
    unsigned short  ar_op;              /* ARP operation code */
    unsigned char   ar_sha[ETH_ALEN];   /* Source MAC Address */
    in_addr_t       ar_sip;          /* Source IP  Address */
    unsigned char   ar_tha[ETH_ALEN];   /* Destin MAC Address */
    in_addr_t       ar_tip;          /* Destin IP  Address */
};

int main(int argc, char *argv[])
{
        struct sockaddr to;
	char ef[ETH_FRAME_LEN];
        struct ethhdr  *p_ethhdr;
        char eth_dest[ETH_ALEN]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
        char eth_source[ETH_ALEN]={0x00,0xe0,0x00,0x00,0xb7,0x4a};

	int i, n, fd;
	struct ifreq  ifr;
/*	struct sockaddr_in  addr_send; */	
/*	if(argc !=2)
		printf("error argc\n");
		
	if((fd = my_open(argv[1], O_RDONLY))<0)
		printf("can't open %s\n",argv[1]); */
/*        printf("Size of in_addr_t is %d, Size of int is %d.\n", sizeof(in_addr_t), sizeof(int)); */
        fd = socket(AF_INET, SOCK_PACKET, htons(0x0003));
        if (fd == -1)  {
            printf("Error: %d     ", errno);
            perror("Err code: ");
            exit(1); 
            }
	strcpy(ifr.ifr_name, "eth0");
/*	i = ioctl(fd, SIOCSIFFLAGS, &ifr);
	if ( i < 0 )
    	{
         	perror("ioctl set error\n");
         	return -2;
    	}	*/

/*        memset(&addr_send, 0, sizeof(addr_send)); 
        addr_send.sin_family = AF_INET;
        addr_send.sin_addr.s_addr = htonl(INADDR_ANY);
        addr_send.sin_port = htons(PORT_SEND);   */

/*	bind(fd, (struct sockaddr*)&addr_send, sizeof(addr_send)); */

	p_ethhdr = (struct ethhdr *)ef;
        memcpy(p_ethhdr->h_dest, eth_dest, ETH_ALEN);
        memcpy(p_ethhdr->h_source, eth_source, ETH_ALEN);
        p_ethhdr->h_proto = htons(0x0806);

        struct arppacket *p_arp;
        p_arp = ( struct arppacket *)ef + ETH_HLEN;
        p_arp->ar_hrd = htons(0x1);   
        p_arp->ar_pro = htons(0x0800);
	p_arp->ar_op = htons(0x1);   
        p_arp->ar_hln = 6;   
        p_arp->ar_pln = 4; 
          

        memcpy(p_arp->ar_sha, eth_source, ETH_ALEN);
        p_arp->ar_sip = htonl(inet_addr("192.168.76.6")); 
        memcpy(p_arp->ar_tha, eth_dest, ETH_ALEN);
        p_arp->ar_tip = htonl(inet_addr("192.168.76.254")); 

        for (i=0; i<3; i++) {
	     printf("%6x%6x%6x%6x%6x  ", p_arp->ar_hrd, p_arp->ar_pro, p_arp->ar_op, p_arp->ar_hln, p_arp->ar_pln);
	     int j = 0;
	     for (j=0; j<ETH_ALEN; j++)
	     	printf("%2x", p_arp->ar_tha[j]);
             printf("\n");	
	     strcpy(to.sa_data, "eth0");
	     n = sendto(fd, ef, sizeof(struct arppacket)+14, 0, &to, sizeof(struct sockaddr));
	     /*n = sendto(fd, p_arp, sizeof(struct arppacket), 0, &to, sizeof(struct sockaddr)); */
             /* n = write(fd, ef, ETH_FRAME_LEN); */
	     if (n < 0)
            	perror("Err code: ");
             printf("\n");	
             sleep(1);
             /* n = read(fd, ef, ETH_FRAME_LEN);*/
        }

        close(fd);
        return 0;	
}

