//
//  service_client.hpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#ifndef service_client_hpp
#define service_client_hpp

#include <SPI.h>
#include <WiFiNINA.h>

// WiFiNINA library
// https://www.arduino.cc/en/Reference/WiFiNINA

class ServiceClient
{
private:
  float powertrainLevel;
  float steeringAngle;
  
  const char *ssid;
  const char *pass;
  const char *server;
  const char *endpoint;
  unsigned int port;

  WiFiClient client;           // Wi-Fi client
  int status = WL_IDLE_STATUS; // Wi-Fi connectoin status

  const static unsigned int BODY_SIZE = 8;    // HTTP response body size in bytes
  const static unsigned int HEADER_LINES = 8; // Number of lines in HTTP header
  byte responseBody[ServiceClient::BODY_SIZE];

public:
  ServiceClient(
      const char *__ssid,
      const char *__pass,
      const char *__server,
      const char *__endpoint,
      unsigned int __port);
  void setup(void);
  void loop(void);
  void printWiFiStatus(void);
  float getPowertrainLevel(void) const;
  float getSteeringAngle(void) const;
};

#endif /* service_client_hpp */
