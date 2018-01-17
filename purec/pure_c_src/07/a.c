FR-1|O:00:00:00:00:00:00 D:00:00:00:00:00:00|IP-|OIP:127.0.0.1 DIP:127.0.0.1 TTL:64 PROTOCOL:6 |TCP-|OP:36895 DP:58574 ACK_SYN |
FR-6341|O:00:00:00:00:00:00 D:00:00:00:00:00:00|IP-|OIP:186.87.0.0 DIP:186.87.0.0 TTL:186 PROTOCOL:6 |TCP-|OP:47703 DP:36895 SYN |

SYN Flood Detection Warning:
SYN Number > ACK_SYN Number * 10 && ACK_SYN Number > 500
SYN Flood Analysis not done yet.
SYN Flood Defence Response:
Has send sms to sysadmin.


truct ether_header
{
  u_int8_t  ether_dhost[ETH_ALEN];      /* destination eth addr */
  u_int8_t  ether_shost[ETH_ALEN];      /* source ether addr    */
  u_int16_t ether_type;                 /* packet type ID field */
} __attribute__ ((__packed__));

struct iphdr
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ihl:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int ihl:4;
#else
# error "Please fix <bits/endian.h>"
#endif
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
    u_int16_t frag_off;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
    /*The options start here. */
  };

struct tcphdr
  {
    __extension__ union
    {
      struct
      {
        u_int16_t th_sport;             /* source port */
        u_int16_t th_dport;             /* destination port */
        tcp_seq th_seq;         /* sequence number */
        tcp_seq th_ack;         /* acknowledgement number */
# if __BYTE_ORDER == __LITTLE_ENDIAN
        u_int8_t th_x2:4;               /* (unused) */
        u_int8_t th_off:4;              /* data offset */
# endif
# if __BYTE_ORDER == __BIG_ENDIAN
        u_int8_t th_off:4;              /* data offset */
        u_int8_t th_x2:4;               /* (unused) */
# endif
        u_int8_t th_flags;
# define TH_FIN 0x01
# define TH_SYN 0x02
# define TH_RST 0x04
# define TH_PUSH        0x08
# define TH_ACK 0x10
# define TH_URG 0x20
        u_int16_t th_win;               /* window */
        u_int16_t th_sum;               /* checksum */
        u_int16_t th_urp;               /* urgent pointer */
      };
      struct
      {
        u_int16_t source;
        u_int16_t dest;
        u_int32_t seq;
        u_int32_t ack_seq;
# if __BYTE_ORDER == __LITTLE_ENDIAN
        u_int16_t res1:4;
        u_int16_t doff:4;
        u_int16_t fin:1;
        u_int16_t syn:1;
        u_int16_t rst:1;
        u_int16_t psh:1;
        u_int16_t ack:1;
        u_int16_t urg:1;
        u_int16_t res2:2;
# elif __BYTE_ORDER == __BIG_ENDIAN
        u_int16_t doff:4;
        u_int16_t res1:4;
        u_int16_t res2:2;
        u_int16_t urg:1;
        u_int16_t ack:1;
        u_int16_t psh:1;
        u_int16_t rst:1;
        u_int16_t syn:1;
        u_int16_t fin:1;
# else
#  error "Adjust your <bits/endian.h> defines"
# endif
        u_int16_t window;
        u_int16_t check;
        u_int16_t urg_ptr;
      };
    };
};

