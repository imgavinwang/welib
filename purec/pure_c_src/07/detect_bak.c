/*-------------------------------------------------------------*/
/* Exemplo Socket Raw - Captura pacotes recebidos na interface */
/*-------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos                */

#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP

#include <netinet/in_systm.h> //tipos de dados

#define BUFFSIZE 1518
#define TAMANHO_TIPO 2

// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.

  unsigned char buff1[BUFFSIZE]; // buffer de recepcao

  int sockd;
  int on;
  struct ifreq ifr;

  // GERAL
  int minSizePacket;
  int maxSizePacket;
  int averageSizePacket;

  // NIVEL DE ENLACE
  int totalArpRequest = 0;
  int percentArpRequest = 0;
  int totalArpReply = 0;
  int percentArpReply = 0;

  // NIVEL DE REDE
  int totalPacketChecksumError;
  int totalICMPPacket;

int main(int argc,char *argv[])
{
    /* Criacao do socket. Todos os pacotes devem ser construidos a partir do protocolo Ethernet. */
    /* De um "man" para ver os parametros.*/
    /* htons: converte um short (2-byte) integer para standard network byte order. */
    if((sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
    {
       printf("Erro na criacao do socket.\n");
       exit(1);
    }

  // O procedimento abaixo eh utilizado para "setar" a interface em modo promiscuo
  strcpy(ifr.ifr_name, "eth0");
  if(ioctl(sockd, SIOCGIFINDEX, &ifr) < 0)
    printf("erro no ioctl!");
  ioctl(sockd, SIOCGIFFLAGS, &ifr);
  ifr.ifr_flags |= IFF_PROMISC;
  ioctl(sockd, SIOCSIFFLAGS, &ifr);

  // recepcao de pacotes
  while (1)
  {
      recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
    // impressao do conteudo - exemplo Endereco Destino e Endereco Origem
    
    printf("FR-|%x:%x:%x:%x:%x:%x ", buff1[0],buff1[1],buff1[2],buff1[3],buff1[4],buff1[5]);
    printf("%x:%x:%x:%x:%x:%x|", buff1[6],buff1[7],buff1[8],buff1[9],buff1[10],buff1[11]);
    
    if(buff1[12] == 0x08)
    {
      if(buff1[13] == 0x00)
      {
        printf("IP-|");

        switch(buff1[23])
        { // PROTOCOL
          case 0x01:
          {
            printf("(001) ICMP.");
            totalICMPPacket++;
            printf("totalICMPPacket = %d|",totalICMPPacket);
            printf("ICMP Type: ");
            switch(buff1[34]) // ICMP type
            {
              case 0x00:
                printf("(00) Echo reply.|");
                break;
              case 0x03:
                printf("(03) Destination Unreachable.");
                printf("Code:");
                switch(buff1[35])
                {
                  case 0x00:
                    printf("(00) Net Unreachable.|");
                    break;
                  case 0x01:
                    printf("(01) Host Unreachable.|");
                    break;
                  case 0x02:
                    printf("(02) Protocol Unreachable.|");
                    break;
                  case 0x03:
                    printf("(03) Port Unreachable.|");
                    break;
                  case 0x04:
                    printf("(04) Fragmentation Needed & DF Set.|");
                    break;
                  case 0x05:
                    printf("(05) Source Route Failed.|");
                    break;
                  case 0x06:
                    printf("(06) Destination Network Unknown.|");
                    break;
                  case 0x07:
                    printf("(07) Destination Host Unknown.|");
                    break;
                  case 0x08:
                    printf("(08) Source Host Isolated.|");
                    break;
                  case 0x09:
                    printf("(09) Network Administratively Prohibited.|");
                    break;
                  case 0x0A: // 10
                    printf("(10) Host Administratively Prohibited.|");
                    break;
                  case 0x0B: // 11
                    printf("(11) Network Unreachable for TOS.|");
                    break;
                  case 0x0C: // 12
                    printf("(12) Host Unreachable for TOS.|");
                    break;
                  case 0x0D: // 13
                    printf("(13) Communication Administratively Prohibited.|");
                    break;
                } // fecha o code do -> (03) Destination Unreachable
                break;

              case 0x04:
                printf("(04) Source Quench.|");
                break;

              case 0x05:
                printf("(05) Redirect.");
                printf("Code:");
                switch(buff1[35])
                {
                  case 0x00:
                    printf("(00) Redirect Datagram for the Network.|"); 
                    break;
                  case 0x01:
                    printf("(01) Redirect Datagram for the Host.|");
                    break;
                  case 0x02:
                    printf("(02) Redirect Datagram for the TOS & Network.|");
                    break;
                  case 0x03:
                    printf("(03) Redirect Datagram for the TOS & Host.|");
                    break;
                } // fecha o code do -> (05) Redirect
                break;

              case 0x08:
                printf("(08) Echo.|");
                break;

              case 0x09:
                printf("09) Router Advertisement.|");
                break;

              case 0x0A: // 10
                printf("10) Router Selection.|");
                break;

              case 0x0B: // 11
                printf("(11) Time Exceeded.");
                printf("Code:");
                switch(buff1[35])
                {
                  case 0x00:
                    printf("(00) Time to Live exceeded in Transit.|");
                    break;
                  case 0x01:
                    printf("(01) Fragment Reassembly Time Exceeded.|");
                    break;
                } // fecha o code do -> (11) Time Exceeded
                break;

              case 0x0C: //12
                printf("(12) Parameter Problem.");
                printf("Code:");
                switch(buff1[35])
                {
                  case 0x00:
                    printf("(00) Pointer indicates the error.|");
                    break;
                  case 0x01:
                    printf("(01) Missing a Required Option.|");
                    break;
                  case 0x03:
                    printf("(02) Bad Length.|");
                    break;
                } // fecha o code do -> (12) Parameter Problem
                break;

              case 0x0D: //13
                printf("13) Timestamp.|");
                break;
              case 0x0E: //14
                printf("(14) Timestamp Reply.|");
                break;
              case 0x0F: //15
                printf("(15) Information Request.|");
                break;
              case 0x10: //16
                printf("(16) Information Reply.|");
                break;
              case 0x11: // 17
                printf("(17) Address Mark Request.|");
                break;
              case 0x12: // 18
                printf("(18) Address Mark Reply.|");
                break;
              case 0x1E: // 30
                printf("(30) Traceroute.|");
                break;
            } // fecha o ICMP type/code
            
            printf("ICMP Checksum: %x|", buff1[36]<<8|buff1[37]);
            //printf("Other msg-specific info: %x\n", buff1[38]<<8|buff1[39]);
          	//printf("==========    Pacote ICMP    ==========\n");
            break; // sai do ICMP
          }
          case 0x02:
            printf("(002) IGMP.|");
            break;
          case 0x06:
          {
            printf("(006) TCP.|");

            // printf("Source Port: %x\n", (buff1[34]<<8)|(buff1[35]));
            // printf("Destination Port: %x\n", (buff1[36]<<8)|(buff1[37]));

            // printf("Sequencial Number: %x\n", (buff1[37]<<24)|(buff1[38]<<16)|(buff1[39]<<8)|(buff1[40]));
            // printf("Acknoledgment Number: %x\n", (buff1[41]<<24)|(buff1[42]<<16)|(buff1[43]<<8)|(buff1[44]));

            // printf("Offset (Header Length): %x\n", buff1[45]>>4);
            // printf("Reserved: %x\n", buff1[45]&0x0F);
            
            // printf("Flags: %x\n", buff1[46]);
            // printf("Window: %x\n", (buff1[47]<<8)|(buff1[48]));
            
            // printf("Checksum: %x\n", (buff1[49]<<8)|(buff1[50]));
            // printf("Urgent Pointer: %x\n", (buff1[51]<<8)|(buff1[52]));

            break;
          } //fecha printf("(006) Protocolo TCP.\n");
          case 0x09:
            printf("(009) IGRP.|");
            break;
          case 0x11: // 17
            printf("(017) UDP.|");
            break;
          case 0x2F: // 47
            printf("(047) GRE.|");
            break;
          case 0x32: // 50
            printf("(050) ESP.|");
            break;
          case 0x33: // 51
            printf("(051) AH.|");
            break;
          case 0x39: // 57
            printf("(057) SKIP.|");
            break;
          case 0x58: // 88
            printf("(088) EIGRP.|");
            break;
          case 0x59: // 89
            printf("(089) OSPF.|");
            break;
          case 0x73: // 115
            printf("(115) L2TP.|");
            break;
        }
      } // fecha IP
      else if(buff1[13] == 0x06)
      {
        printf("(6) ARP.|");
      }
    }
    printf("\n");
  }
}
