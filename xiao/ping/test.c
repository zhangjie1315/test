#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>
//飞秋

int main()
{
   // int sfd= socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
    int sfd= socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
    if(sfd == -1)perror("socket"),exit(1);

    int op =1;
    setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,&op,sizeof op);
    char buf[1500] ={};
    while(1){
        memset(buf,0x00,sizeof buf);
        int r=read(sfd,buf,1500);
        if(r<=0) break;
        struct ip *pip=(struct ip*)(buf);
        printf("%s<------->",inet_ntoa(pip->ip_dst));
        printf("%s\n",inet_ntoa(pip->ip_src));
        struct tcphdr *ptcp=(struct tcphdr*)(buf+(pip->ip_hl<<2));
        printf("%hd : %hd\n",ntohs(ptcp->dest),ntohs(ptcp->source));
    }
}
