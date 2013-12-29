#ifndef ADAFRUIT_CC3000_UDP_SERVER_H
#define ADAFRUIT_CC3000_UDP_SERVER_H

#include "Adafruit_CC3000_UDP_Server.h"
#include "Adafruit_CC3000_ClientRef.h"
#include "Server.h"
#include "utility/socket.h"

#define MAX_SERVER_CLIENTS 3

class Adafruit_CC3000_UDP_Server : public Server {
  public:
    Adafruit_CC3000_UDP_Server(uint16_t port);

    Adafruit_CC3000_ClientRef available();

    virtual void begin();

    virtual size_t write(const uint8_t *buffer, size_t size);

    virtual size_t write(uint8_t value);

    int16_t receiveFrom(char *msg);

    int16_t writeTo(char *msg);

    using Print::write;

  private:
    Adafruit_CC3000_Client _client;

    uint16_t _port;

    uint16_t _listenSocket;

    sockaddr_in _remoteAddress;

};

#endif
