#include <sys/socket.h>
#include <netinet/in.h>

class UDPServer 
{
  public:
    UDPServer();
    int Recv(char *msg);
    void Send(char *msg);
    int m_sockfd;
    struct sockaddr_in m_incomingaddr;
};
