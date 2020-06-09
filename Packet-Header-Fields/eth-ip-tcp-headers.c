#include <features.h>
#include <sys/types.h>
#include <linux/if_ether.h>  /* Get definitions from kernel header file.  */
#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <unistd.h> 
#include <string.h>  
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include<netinet/if_ether.h>
#include<netinet/ip_icmp.h>




int main(int argc, char const *argv[])
{
    FILE* fp = fopen("packetlog.txt", "w");
    int sock_r;
    sock_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    //socket family --> AF_PACKET 
    //macro is ETH_P_ALL to recieve IP packets
    if(sock_r<0)
    {
        printf("\n Error in creating socket\n");
        return -1;
    }

    unsigned char *buffer = (unsigned char *)malloc(65536);
    memset(buffer, 0, 65536);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);

    //reci.. a network pack.. and copy in buffer

    int buflen = recvfrom(sock_r, buffer, 65536, 0, 
        &saddr, (socklen_t *)&saddr_len);

    if(buflen<0)
    {
        printf("\nError in reading from recvfrom\n");
        return -1;
    }


    struct ethhdr *eth = (struct ethhdr*)(buffer);

    fprintf(fp, "\nEthernet Header\n");
    fprintf(fp, "\t|-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
    fprintf(fp, "\t|-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
    fprintf(fp, "\t|-Protocol : %d\n",eth->h_proto);




    struct sockaddr_in source,dest;
    unsigned short iphdrlen;
    struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;
     

    fprintf(fp, "\n\n\n\n\n\n\n\nIP Header\n");
    fprintf(fp,  "\t|-Version : %d\n",(unsigned int)ip->version); 
    fprintf(fp , "\t|-Internet Header Length : %d DWORDS or %d Bytes\n",(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4); 
    fprintf(fp , "\t|-Type Of Service : %d\n",(unsigned int)ip->tos);
    fprintf(fp , "\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));
    fprintf(fp , "\t|-Identification : %d\n",ntohs(ip->id));
    fprintf(fp , "\t|-Time To Live : %d\n",(unsigned int)ip->ttl);
    fprintf(fp , "\t|-Protocol : %d\n",(unsigned int)ip->protocol);
    fprintf(fp , "\t|-Header Checksum : %d\n",ntohs(ip->check));
    fprintf(fp , "\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));
    fprintf(fp , "\t|-Destination IP : %s\n",inet_ntoa(dest.sin_addr));




    
    struct iphdr *iph = (struct iphdr *)buffer;
    iphdrlen = iph->ihl*4;
    
    struct tcphdr *tcph=(struct tcphdr*)(buffer + iphdrlen);
 
        
    fprintf(fp, "\n\n\n\n\n\n\n");
    fprintf(fp, "TCP Header\n");
    fprintf(fp, "\t|-Source Port      : %u\n",ntohs(tcph->source));
    fprintf(fp, "\t|-Destination Port : %u\n",ntohs(tcph->dest));
    fprintf(fp, "\t|-Sequence Number    : %u\n",ntohl(tcph->seq));
    fprintf(fp, "\t|-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
    fprintf(fp, "\t|-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    //fprintf(f p\t  |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
    //fprintf(f p\t  |-ECN Flag : %d\n",(unsigned int)tcph->ece);
    fprintf(fp, "\t|-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
    fprintf(fp, "\t|-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
    fprintf(fp, "\t|-Push Flag            : %d\n",(unsigned int)tcph->psh);
    fprintf(fp, "\t|-Reset Flag           : %d\n",(unsigned int)tcph->rst);
    fprintf(fp, "\t|-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
    fprintf(fp, "\t|-Finish Flag          : %d\n",(unsigned int)tcph->fin);
    fprintf(fp, "\t|-Window         : %d\n",ntohs(tcph->window));
    fprintf(fp, "\t|-Checksum       : %d\n",ntohs(tcph->check));
    fprintf(fp, "\t|-Urgent Pointer : %d\n",tcph->urg_ptr);
    fprintf(fp, "\n");


                        
    fprintf(fp,"\n###########################################################");
    


    fclose(fp);


    





    return 0;
}