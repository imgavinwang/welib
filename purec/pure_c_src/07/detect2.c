#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <strings.h>
#include <unistd.h> 
#include <signal.h>

#include <netinet/ip_icmp.h>
#include <net/if_arp.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <netinet/ip.h> 
#include <netdb.h> 
#include <netinet/tcp.h> 
#include <netinet/udp.h>
#include <signal.h> 
#include <net/if.h> 
#include <sys/ioctl.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <linux/igmp.h>
#include <netinet/tcp.h>

/* 全局变量结构的结构体原型 - 包含要记录的任何全局信息 */
struct global_info {
    unsigned int bytes;             /* 网卡接收的总字节数     */
    unsigned int packet_num;        /* 网卡接受的帧的总数量   */
     
    unsigned int packet_arp;        /* 接收到的arp包的数量    */
    unsigned int packet_rarp;       /* 接收到的rarp包的数量   */
 
    unsigned int packet_ip;         /* 接收到的ip包的数量     */
    unsigned int packet_icmp;       /* 接收到的icmp包的数量   */
    unsigned int packet_igmp;       /* 接收到的igmp包的数量   */
 
    unsigned int packet_tcp;        /* 接收到的tcp包的数量    */
    unsigned int packet_udp;        /* 接收到的udp包的数量    */
     
    int print_flag_frame;           /* 是否打印帧头信息标志, 1表示打印, 0表示不打印 */
    int print_flag_arp;             /* 是否打印arp头信息标志  */
    int print_flag_ip;              /* 是否打印ip头信息标志   */
    int print_flag_rarp;            /* 是否打印rarp头信息标志 */
    int print_flag_tcp;             /* 是否打印tcp头信息标志  */
    int print_flag_udp;             /* 是否打印udp头信息标志  */
    int print_flag_icmp;            /* 是否打印icmp头信息标志 */
    int print_flag_igmp;            /* 是否打印igmp头信息标志 */
};
 
/* 定义一个全局变量，用于存储全局信息 */
struct global_info global;
 
/* 一个用于打印全局信息的函数  */
void print_global( struct global_info var )
{
    printf("\n\n********** GLOBAL INFO *****************\n\n");
    printf("RECV BYTES: %d kbytes.\n", var.bytes / 1024 );
    printf("RECV PACKET NUM: %d\n\n", var.packet_num );
     
    if( var.packet_arp ) printf("ARP: %d\n", var.packet_arp );
    if( var.packet_rarp) printf("RARP: %d\n", var.packet_rarp );
    if( var.packet_ip )  printf("IP: %d\n", var.packet_ip );
    if( var.packet_icmp) printf("ICMP: %d\n", var.packet_icmp );
    if( var.packet_igmp) printf("IGMP: %d\n", var.packet_igmp );
    if( var.packet_tcp ) printf("TCP: %d\n", var.packet_tcp );
    if( var.packet_udp ) printf("UDP: %d\n", var.packet_udp );
     
    printf("\n");
}

/* 用于处理当下按ctrl-c时的处理函数 */
void sig_int( int sig )
{
    print_global( global );
    exit( 0 );
}

void print_icmp( struct icmphdr * picmp )
{
    printf("ICMP-|");
     
    printf("TYPE:%d ", picmp->type );
    switch( picmp->type ){
        case ICMP_ECHOREPLY:
            printf("ICMP_ECHOREPLY ");
            break;
        case ICMP_DEST_UNREACH:
                printf("ICMP_DEST_UNREACH ");
            break;
        case ICMP_SOURCE_QUENCH:
            printf("ICMP_SOURCE_QUENCH ");
            break;
        case ICMP_REDIRECT:
            printf("ICMP_REDIRECT "); 
            break;
        case ICMP_ECHO:
            printf("ICMP_ECHO ");   
            break;
        case ICMP_TIME_EXCEEDED:
            printf("ICMP_TIME_EXCEEDED ");
            break;
        case ICMP_PARAMETERPROB:
            printf("ICMP_PARAMETERPROB ");
            break;
        case ICMP_TIMESTAMP:
            printf("ICMP_TIMESTAMP ");  
            break;
        case ICMP_TIMESTAMPREPLY:
            printf("ICMP_TIMESTAMPREPLY ");  
            break;
        case ICMP_INFO_REQUEST:
            printf("ICMP_INFO_REQUEST "); 
            break;
        case ICMP_INFO_REPLY:
            printf("ICMP_INFO_REPLY ");
            break;
        case ICMP_ADDRESS:
            printf("ICMP_ADDRESS ");
            break;
        case ICMP_ADDRESSREPLY:
            printf("ICMP_ADDRESSREPLY ");
            break;
        default:
            printf("UNKNOW_TYPE ");
            break;
    }

    printf("SUBTYPE:%d ", picmp->code );
    switch( picmp->type ){
        case ICMP_ECHOREPLY:
            printf("ICMP_ECHOREPLY ");
            break;
        case ICMP_DEST_UNREACH:
            switch( picmp->type ){
                case ICMP_NET_UNREACH:
                    printf("ICMP_NET_UNREACH ");
                    break;
                case ICMP_HOST_UNREACH:
                    printf("ICMP_HOST_UNREACH "); 
                    break;
                case  ICMP_PROT_UNREACH:
                    printf("ICMP_PROT_UNREACH ");
                    break; 
                case  ICMP_PORT_UNREACH:
                    printf("ICMP_PORT_UNREACH ");
                    break;
                case  ICMP_FRAG_NEEDED:
                    printf("ICMP_FRAG_NEEDED ");
                    break;
                case  ICMP_SR_FAILED:
                    printf("ICMP_SR_FAILED ");
                    break;
                case  ICMP_NET_UNKNOWN:
                    printf("ICMP_NET_UNKNOWN ");
                    break;
                case  ICMP_HOST_UNKNOWN:
                    printf("ICMP_HOST_UNKNOWN ");
                    break;
                case  ICMP_HOST_ISOLATED:
                    printf("ICMP_HOST_ISOLATED ");
                    break;
                case  ICMP_NET_ANO:
                    printf("ICMP_NET_ANO ");
                    break;
                case  ICMP_HOST_ANO:
                    printf("ICMP_HOST_ANO ");
                    break;
                case  ICMP_NET_UNR_TOS:
                    printf("ICMP_NET_UNR_TOS ");
                    break;
                case  ICMP_HOST_UNR_TOS:
                    printf("ICMP_HOST_UNR_TOS ");
                    break;
                case  ICMP_PKT_FILTERED:
                    printf("ICMP_PKT_FILTERED ");
                    break;
                case  ICMP_PREC_VIOLATION:
                    printf("ICMP_PREC_VIOLATION ");
                    break;
                case  ICMP_PREC_CUTOFF:
                    printf("ICMP_PREC_CUTOFF ");
                    break;
                default:
                    printf("UNKNOW_TYPE\n");
                    break;
 
            }
            break;
        case ICMP_SOURCE_QUENCH:
            printf("ICMP_SOURCE_QUENCH ");
            break;
        case ICMP_REDIRECT:
            switch( picmp->type ){
                case ICMP_REDIR_NET:
                    printf("ICMP_REDIR_NET ");
                    break;
                case ICMP_REDIR_HOST:
                    printf("ICMP_REDIR_HOST ");  
                    break;
                case ICMP_REDIR_NETTOS:
                    printf("ICMP_REDIR_NETTOS "); 
                    break;
                case ICMP_REDIR_HOSTTOS:
                    printf("ICMP_REDIR_HOSTTOS ");
                    break;
                defalut:
                    printf("UNKNOW_TYPE ");
                    break;
            }
            break;
        case ICMP_ECHO:
            printf("ICMP_ECHO ");   
            break;
        case ICMP_TIME_EXCEEDED:
            switch( picmp->type ){
                case ICMP_EXC_TTL:
                    printf("ICMP_EXC_TTL ");
                    break;
                case ICMP_EXC_FRAGTIME:
                    printf("ICMP_EXC_FRAGTIME ");
                    break;
                default:
                    printf("UNKNOW_TYPE ");
                    break;
            }
            break;
        case ICMP_PARAMETERPROB:
            switch( picmp->type ){
                case 0:
                    printf("IP HEAD ERROR ");
                    break;
                case 1:
                    printf("LESS MUST OPTION ");
                    break;
                default:
                    printf("UNKNOW_TYPE ");
                    break;
            }
            break;
        case ICMP_TIMESTAMP:
            printf("ICMP_TIMESTAMP ");  
            break;
        case ICMP_TIMESTAMPREPLY:
            printf("ICMP_TIMESTAMPREPLY ");  
            break;
        case ICMP_INFO_REQUEST:
            printf("ICMP_INFO_REQUEST "); 
            break;
        case ICMP_INFO_REPLY:
            printf("ICMP_INFO_REPLY ");
            break;
        case ICMP_ADDRESS:
            printf("ICMP_ADDRESS ");
            break;
        case ICMP_ADDRESSREPLY:
            printf("ICMP_ADDRESSREPLY ");
            break;
        default:
            printf("UNKNOW_TYPE ");
            break;
    }
 
    printf("CRC: %d|", ntohs(picmp->checksum) );
}

void do_icmp( char * data )
{
    global.packet_icmp ++;
 
    struct icmphdr * picmp = ( struct icmphdr * ) data;
     
    if( global.print_flag_icmp )
        print_icmp( picmp );
}

void print_ip( struct iphdr * iph )
{
    printf("IP-|OIP:%s DIP:%s TTL:%d PROTOCOL:%d", 
	       inet_ntoa( *(struct in_addr *)(&iph->saddr)),
	       inet_ntoa( *(struct in_addr *)(&iph->daddr)),
	       iph->ttl, iph->protocol);
}

void do_ip( char * data )
{
    global.packet_ip ++;
 
    struct iphdr *pip;        
    pip = ( struct iphdr * ) data;    /* pip = point to ip layer */
    if( global.print_flag_ip )
        print_ip( pip );
     
    ip_count( pip );
     
    char * pdata = data + pip->ihl * 4;
     
    switch( pip->protocol ){
        case IPPROTO_ICMP:
            do_icmp( pdata );
            break;
/*
        case IPPROTO_IGMP:
            do_igmp( pdata );
            break;
		case IPPROTO_UDP:
            do_udp( pdata );
            break;
*/
        case IPPROTO_TCP:
            do_tcp( pdata );
            break;

        default:
            //printf("IP: 未知其上层协议.\n");
            break;
    }
}

void print_frame( struct ether_header * peth )
{
    /* 定义一个数组，用于存储把mac地址转换成字符串后的字符串 */
    char buf[ 18 ];
 
    printf("FR-%d|", global.packet_num );
    char * shost = peth->ether_shost;
    mac_to_str( shost, buf );      
    printf("O:%s ", buf );
     
    char * dhost = peth->ether_dhost;
    mac_to_str( dhost, buf );
    printf("D:%s|", buf );
}

/* 用于从网卡接受一帧数据,同时根据以太网协议字段传递数据给相应的上层协议处理 */
void do_frame( int sock )
{
    /* 用于存储一帧数据         */
    char frame_buf[ 2000 ];
     
    /* 清空帧数据缓冲区     */
    bzero( frame_buf, sizeof(frame_buf) );
 
    int len = sizeof( frame_buf );
     
    /* 用于存储接受字节数       */
    int recv_num;
 
    /* 用于存储发送方的地址信息 */
    struct sockaddr_in addr;
 
    /* 从网卡接收一帧数据       */
        recv_num = recvfrom( sock, (char *)frame_buf, sizeof( frame_buf ), 0, ( struct sockaddr * )&addr, &len ); 
 
    /* 所接收的包的总数自加1    */
    global.packet_num ++;
 
    /* 从网卡接收的字节总数     */
    global.bytes += recv_num;
 
    /* 打印接收的包是第几个包   */
    //printf("此帧数据长度: %d\n", recv_num );
     
    /* 定义一个用于指向以太网帧的指针 (这里我们只考虑最常见的以太网帧的情况) */
    struct ether_header * peth;
 
    /* 让以太网头指针指向从网卡接受到的帧的数据的开头 */
        peth = (struct ether_header *)frame_buf;
 
    /* 传递以太网帧首地址给打印以太网帧信息的打印函数 */
    if( global.print_flag_frame )
        print_frame( peth );
 
    /* 定义一个数据指针,用于指向以太网帧的数据部分    */
    char * pdata;
 
    /* 让 pdata 指向以太网帧的数据部分                */
    pdata = frame_buf + sizeof( struct ether_header );
 
    /* 根据以太网帧的协议字段进行数据分用 － 也就是进行数据拆封，根据协议字段调用相应层的处理函数 */
    switch( ntohs( peth->ether_type ) ){
        case ETHERTYPE_PUP:
            break;
        breakcase ETHERTYPE_IP:
            do_ip( pdata );
            break;
/*
        case ETHERTYPE_ARP:
            do_arp( pdata );
            break;
        case ETHERTYPE_REVARP:
            do_rarp( pdata );
            break;
*/
        default:
            //printf("Unkonw ethernet type  %d %x.\n", ntohs(peth->ether_type), ntohs(peth->ether_type) );
            break;
    }
}

int main( int argc, char ** argv ) 
{ 
    /* 用于存储套接口文件描述符 */
    int sockfd;
 
    /* 初始化全局变量    */
    init_global( &global );
	memset(&global, 0x00, sizeof(global_info));
 
    if( argc == 1 ) {               /* 表示打印所有包头信息 */
        global.print_flag_frame = 1;
        global.print_flag_arp = 1;
        global.print_flag_ip = 1;
        global.print_flag_rarp = 1;
        global.print_flag_tcp = 1;
        global.print_flag_udp = 1;
        global.print_flag_icmp = 1;
        global.print_flag_igmp = 1;
    } else {               /* 帮助 或者 通过指定协议名称只打印某层些协议 */
        if( !strcasecmp( argv[1], "-h" ) ){
            help();
            exit( 0 );
        } else {
            int i;
            for( i=1; i < argc; i++ ){
                if( !strcasecmp( argv[i], "frame" ) )
                    global.print_flag_frame = 1;
                else if( !strcasecmp( argv[i], "arp" ) )
                    global.print_flag_arp = 1;
                else if( !strcasecmp( argv[i], "rarp" ) )
                    global.print_flag_rarp = 1;
                else if( !strcasecmp( argv[i], "ip" ) )
                    global.print_flag_ip = 1;
                else if( !strcasecmp( argv[i], "tcp" ) )
                    global.print_flag_tcp = 1;
                else if( !strcasecmp( argv[i], "udp" ) )
                    global.print_flag_udp = 1;
                else if( !strcasecmp( argv[i], "icmp" ) )
                    global.print_flag_icmp = 1;
                else if( !strcasecmp( argv[i], "igmp" ) )
                    global.print_flag_igmp = 1;
            }
        }
    }
     
    /* 通过协议族AF_PACKET类信SOCK_RAW, 类型SOCK_RAW创建一个用于可以接受网卡帧数据的套接口,同时返回套就口文件描述符 */
    if( (sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)) ) == -1 )
            error_and_exit( "socket", 1 );  /* 如果发生错误，返回错误值, 并退出 */
 
    /* 设定网卡eth0成混杂模式 */
    set_card_promisc( "eth0", sockfd );
 
    /* 设定信号处理函数, 下面是设置当我们按下ctrl-c时所调用的处理函数 */  
    signal( SIGINT, sig_int );
 
    /* 无限循环接收以太网卡数据帧, 并进行数据分用,直到你按下ctrl-c */
    while( 1 ){
        do_frame( sockfd );
    } 
 
    return 0;
}
