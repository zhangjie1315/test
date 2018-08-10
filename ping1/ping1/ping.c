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
char sendbuf[1024];//装发送数据包
char recvbuf[1024];//装接收数据包
unsigned short chksum(unsigned short *addr,int len)
{
    unsigned int ret = 0;
    while(len>1)
    {
        ret += *addr;
            addr++;
        len -= 2;
    }
    //奇数个     按照一个字节加
    if (len == 1){
        ret += *(unsigned char *)addr;
    }
        //只要低16位  高位不要，右移16位再加上低十六位   溢出再次进行
    //校验和算法
    ret = (ret>>16)+(ret&0xffff);
    ret += (ret>>16);
       //取反
    return (unsigned short)~ret;
}



//(1)计算两个时间差的毫秒数   
//两个结构体 
  float diftime(struct timeval *end,struct timeval *begin)
{      //变成微妙   两次取到时间 秒*1000变成多少毫秒   微妙/1000变成微妙 
   float ret = (end->tv_sec - begin->tv_sec) * 1000.0+ 
    (end->tv_usec - begin->tv_usec) / 1000.0; 
       //*1000变成毫秒
return ret;
}
//(2)组包
  //组包    num:ICMP报文的标识符字段
  //结构体 !vim /usr/include/netinet/ip_icmp.h 
  //icmp的结构体：用union联合体   用define简单
  int pack(int num,pid_t pid)
{       
   //内容大小定义成56
   //数据大小  头部还有8个字节
   //len为总大小
    int len = DATA_LEN + 8;

   struct icmp *picmp = (struct icmp*)sendbuf;
   picmp->icmp_type = ICMP_ECHO;//装类型
   picmp->icmp_code = 0;
   picmp->icmp_cksum = 0;//校验和初始清零
   picmp->icmp_id = pid;//等于进程id
   picmp->icmp_seq = htons(num);//序号
   gettimeofday((struct timeval*)(picmp->icmp_data),NULL);//装数据（当前的时间）
   picmp->icmp_cksum = chksum((unsigned short*)sendbuf,len);//调用函数计算校验和(需要地址和长度)
   return len;
}
     //发送数据包
     //sfd 套接字描述符
     //pid  组ICMP报文的标识符字段
     //addr 发送的目标机器
//（1）发包
void send_packet(int sfd,pid_t pid,struct sockaddr_in addr){
    //发送包的编号
    sendnum++;
    //发数据包之前需要将数据清空
    memset(sendbuf,0x00,sizeof recvbuf);
   int r = pack(sendnum,pid);
   //r发送的大小 选项0  地址发到 大小
    sendto(sfd,sendbuf,r,0,(struct sockaddr*)&addr,sizeof(addr));
}
//（4）解包  读到的数据包 大小 进程id 进程id   
void unpack(int num,pid_t pid,struct sockaddr_in from){
    struct timeval end;
    gettimeofday(&end,NULL);
//ip的结构体     
    struct ip *pip=(struct ip*)recvbuf;
//icmp的头部
    struct icmp *picmp = (struct icmp*)(recvbuf+(pip->ip_hl<<2));
    //获取当前时间
    float d = diftime(&end,(struct timeval*)picmp->icmp_data);
//应该需要判断比较等于 pid   才进行下一步
    if(picmp->icmp_id==pid)
    {
        //    多少字节  来自哪 包序号  ttl（跳数）  时间    
    printf("%d bytes from %s:icmp_seq=%d tt1=%d time=%.4f ms\n",DATA_LEN+8,inet_ntoa(from.sin_addr),ntohs(picmp->icmp_seq),
           pip->ip_ttl,
           d);}
     //
}

//（3）接收包
void recv_packet(int sfd,pid_t pid){
    struct sockaddr_in from;//数据来自于哪  from为值结果参数
    socklen_t len = sizeof from;//len初始化为值结果
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
        //如果输入ip    转换成点分十进制
    addr.sin_addr.s_addr=inet_addr(argv[1]);
      //转换不成功则域名转换
        if(addr.sin_addr.s_addr == INADDR_NONE){
            //gethostbyname  dns解析   解析域名   （通过域名获取ip地址）
            phost = gethostbyname(argv[1]);
            if(phost==NULL)
                perror("gethostbyname"),exit(1);
            //拷贝到sin.addr
            memcpy((void*)&addr.sin_addr,(void*)phost->h_addr,phost->h_length);
        }
        //到此输入域名或者ip都可以
        
        //解包后输出时的第一句话
        printf("PING %s(%s) %d bytes of data.\n",
               argv[1],
               inet_ntoa(addr.sin_addr),
               DATA_LEN);
        addr.sin_family = AF_INET;
        //自己组包，原始套接字
        int sfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
            if(sfd == -1) perror("socket"),exit(1);
             //组包，需要pid    
    pid_t pid = getpid(); 
        while(1){
            //发包   pid  地址
            send_packet(sfd,pid,addr);
            //收包   进行比较
            recv_packet(sfd,pid);
            //停留一秒钟
            sleep(1);
        }
}

