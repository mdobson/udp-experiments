#include "Adafruit_CC3000_UDP_Server.h"
#include "Adafruit_CC3000_ClientRef.h"
#include "utility/socket.h"
#include <string.h>

#define CC3K_PRINTLN_F(text) { if(CC3KPrinter != NULL) { CC3KPrinter->println(F(text)); } }

#define HANDLE_NULL(client, value) { if(client == NULL) return value; }

#define RXBUFFERSIZE  64
/********************************************************************
 * Begin UDP Server Implementation
 */

//N2M: The colon after a constructor is an initialization list. Used to 
//set member variables before constructor code runs.
Adafruit_CC3000_UDP_Server::Adafruit_CC3000_UDP_Server(uint16_t port)
  : _port(port)
  , _listenSocket(-1)
{ }

Adafruit_CC3000_ClientRef Adafruit_CC3000_UDP_Server::available() 
{
  // if (_listenSocket > -1) 
  // {
  //   _client = Adafruit_CC3000_Client(_listenSocket);
  //   return Adafruit_CC3000_ClientRef(&_client);
  // }
  // else
  // {
  //   return Adafruit_CC3000_ClientRef(NULL);
  // }


}

void Adafruit_CC3000_UDP_Server::begin() 
{

  unsigned long aucDHCP = 14400;
  unsigned long aucARP = 3600;
  unsigned long aucKeepalive = 30;
  unsigned long aucInactivity = 0;

  cc3k_int_poll();
  if (netapp_timeout_values(&aucDHCP, &aucARP, &aucKeepalive, &aucInactivity) !=0 )
  {
    CC3K_PRINTLN_F("Error setting inactivity timeout!");
    return;
  }
  else
  {
    CC3K_PRINTLN_F("Set inactivity timeout!");
  }

  cc3k_int_poll();
  int16_t sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) 
  {
    CC3K_PRINTLN_F("Couldn't create listening socket!");
    return;
  }
  else
  {
    CC3K_PRINTLN_F("Created listening socket!");
  }

  cc3k_int_poll();
  char arg = SOCK_ON;
  if (setsockopt(sock, SOL_SOCKET, SOCKOPT_ACCEPT_NONBLOCK, &arg, sizeof(arg)) < 0 )
  {
    CC3K_PRINTLN_F("Couldn't set socket as non-blocking!");
    return;
  }
  else
  {
    CC3K_PRINTLN_F("Set socket as non-blocking!");
  }

  sockaddr_in home, remote;
  home.sin_family = AF_INET;
  home.sin_addr.s_addr = htonl(0);
  home.sin_port = htons(_port);

  cc3k_int_poll();
  if(bind(sock, (sockaddr*)&home, sizeof(home)) < 0) 
  {
    CC3K_PRINTLN_F("Error binding listen socket to address!");
    return;
  }
  else
  {
    CC3K_PRINTLN_F("Bound listen socket to address!");
  }

  // cc3k_int_poll();
  // if(listen(sock, 0) < 0)
  // {
  //   CC3K_PRINTLN_F("Error opening socket for listening!");
  //   return;
  // }
  // else
  // {
  //   CC3K_PRINTLN_F("Opened socket for listening!");
  // }
  if (sock > -1)
  {
    CC3K_PRINTLN_F("Opened socket for listening!");
  }
  _listenSocket = sock;
  _remoteAddress = remote;
}

size_t Adafruit_CC3000_UDP_Server::write(const uint8_t *buffer, size_t size) 
{
  return 0;
}

size_t Adafruit_CC3000_UDP_Server::write(uint8_t size) 
{
  return 0;
}

int16_t Adafruit_CC3000_UDP_Server::writeTo(char *msg)
{
  socklen_t slen = sizeof(_remoteAddress);
  int ret = sendto(_listenSocket, msg, strlen(msg), 0, (sockaddr*)&_remoteAddress, slen);
  return ret;
}

int16_t Adafruit_CC3000_UDP_Server::receiveFrom(char *msg)
{
  socklen_t slen = sizeof(_remoteAddress);
  int16_t ret = recvfrom(_listenSocket, msg, RXBUFFERSIZE, 0, (sockaddr*)&_remoteAddress, &slen);
  return ret;
}
