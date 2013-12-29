#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "udpsrv.h"
#define BUFLEN 512
#define PORT 9930

UDPServer::UDPServer()
{
  struct sockaddr_in my_addr, cli_addr;
  m_incomingaddr = cli_addr;
  int sockfd, i;
  socklen_t slen=sizeof(cli_addr);
  char buf[BUFLEN];

  if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
  {
    perror("socket");
  }
  else
  {
    m_sockfd = sockfd;
    printf("Server: Socket() successful\n");
  }

  bzero(&my_addr, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(PORT);
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(m_sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr)) ==-1)
  {
    perror("bind");
  }
  else
  {
    printf("Server: bind() successful\n");
  }

//  while(1)
//  {
//    if(recvfrom(m_sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen) ==-1)
//    {
//      perror("recvfrom()");
//    }
//    else
//    {
//      printf("Receved packet from %s:%d\n Data: %s\n\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);
//      sendto(m_sockfd, buf, strlen(buf), 0, (struct sockaddr*)&cli_addr, slen);
//    }
//  }
}

int UDPServer::Recv(char *msg)
{
  socklen_t slen=sizeof(m_incomingaddr);
  int ret = recvfrom(m_sockfd, msg, BUFLEN, 0, (struct sockaddr *)&m_incomingaddr, &slen); 
  return ret;
};

void UDPServer::Send(char *msg)
{
  socklen_t slen=sizeof(m_incomingaddr);
  sendto(m_sockfd, msg, strlen(msg), 0, (struct sockaddr*)&m_incomingaddr, slen);
};
