#include "udpsrv.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#define BUFLEN 512

int main()
{
  UDPServer s = UDPServer();
  char buf[BUFLEN];
  while(1)
  {
    int rcvd = s.Recv(buf);
    if(rcvd==-1)
    {
      perror("recv()");
    }
    else
    {
      printf("Rcvd var:%d\n",rcvd);
      printf("Received from:%s:%d\n Data: %s\n", inet_ntoa(s.m_incomingaddr.sin_addr), ntohs(s.m_incomingaddr.sin_port), buf);
      s.Send(buf);
      memset(&buf[0], 0, BUFLEN); 
    }
  }

}
