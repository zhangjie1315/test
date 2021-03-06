#include <stdio.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/ip.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/ip_icmp.h>
//addr:需要计算检验和的数据起始地址
//len:数据大小，单位是字节
#define DATA_LEN 56
int sendnum = 0;      //发送数据包的编号
int recvnum = 0;      //接收数据包的编号
char sendbuf[1024];//发送数据包
char recvbuf[1024];//接收数据包
unsigned short chksum(unsigned short *addr,int len)
{
    unsigned int ret = 0;
    while(len>1)
    {
        ret += *addr;
            addr++;
        len -= 2;
    }
    if (len == 1){
        ret += *(unsigned char *)addr;
    }
    //校验和算法
    ret = (ret>>16)+(ret&0xffff);
    ret += (ret>>16);

    return (unsigned short)~ret;
}

//计算两个时间差的秒数
  float diftime(struct timeval *end,struct timeval *begin)
{
   float ret = (end->tv_sec - begin->tv_sec) * 1000.0+ 
    (end->tv_usec - begin->tv_usec) / 1000.0; 
       //*1000变成毫秒
return ret;
}
  //组包    num:ICMP报文的标识符字段
  int pack(int num,pid_t pid)
{       
    int len = DATA_LEN + 8;
   struct icmp *picmp = (struct icmp*)sendbuf;
   picmp->icmp_type = ICMP_ECHO;
   picmp->icmp_code = 0;
   picmp->icmp_cksum = 0;
   picmp->icmp_id = pid;
   picmp->icmp_seq = htons(num);
   gettimeofday((struct timeval*)(picmp->icmp_data),NULL);
   picmp->icmp_cksum = chksum((unsigned short*)sendbuf,len);
   return len;
}
     //发送数据包
     //sfd 套接字描述符
     //pid  组ICMP报文的标识符字段
     //addr 发送的目标机器
void send_packet(int sfd,pid_t pid,struct sockaddr_in addr){

    sendnum++;

    memset(sendbuf,0x00,sizeof recvbuf);
   int r = pack(sendnum,pid);
    sendto(sfd,sendbuf,r,0,(struct sockaddr*)&addr,sizeof(addr));
}
     
void unpack(int num,pid_t pid,struct sockaddr_in from){
    struct timeval end;
    gettimeofday(&end,NULL);
    struct ip *pip=(struct ip*)recvbuf;

    struct icmp *picmp = (struct icmp*)(recvbuf+(pip->ip_hl<<2));
    float d = diftime(&end,(struct timeval*)picmp->icmp_data);

    printf("%d bytes from %s:icmp_seq=%d tt1=%d time=%.4f ms\n",DATA_LEN+8,inet_ntoa(from.sin_addr),ntohs(picmp->icmp_seq),
           pip->ip_ttl,
           d);

}
void recv_packet(int sfd,pid_t pid){
    struct sockaddr_in from;
    socklen_t len = sizeof from;
    memset(recvbuf,0x00,sizeof recvbuf);
    recvnum++;
    recvfrom(sfd,recvbuf,1024,0,(struct sockaddr*)&from,&len);

    unpack(recvnum,pid,from);
}
  int main(int argc,char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"usage:./ping ip/域名\n");
        exit(1);
    }
    struct sockaddr_in addr = {};
    struct hostent *phost = NULL;
    addr.sin_addr.s_addr=inet_addr(argv[1]);
        if(addr.sin_addr.s_addr == INADDR_NONE){
            phost = gethostbyname(argv[1]);
            if(phost==NULL)
                perror("gethostbyname"),exit(1);
            memcpy((void*)&addr.sin_addr,(void*)phost->h_addr,phost->h_length);
        }
        printf("PING %s(%s) %d bytes of data.\n",
               argv[1],
               inet_ntoa(addr.sin_addr),
               DATA_LEN);
        addr.sin_family = AF_INET;
        int sfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
            if(sfd == -1) perror("socket"),exit(1);
               
    pid_t pid = getpid(); 
        while(1){
            send_packet(sfd,pid,addr);
            recv_packet(sfd,pid);
            sleep(1);
        }
}

