#include <sys/socket.h>
#include <netinet/in.h>

class UDPServer 
{
  public:
    UDPServer();
    int RecvFrom(char *msg);
    int Recv(char *msg);
    void Send(char *msg);
    int Available();
    int m_sockfd;
    struct sockaddr_in m_incomingaddr;
};
