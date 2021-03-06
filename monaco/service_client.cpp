//
//  service_client.cpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#include "service_client.hpp"

ServiceClient::ServiceClient(
    const char *__ssid,
    const char *__pass,
    const char *__server,
    const char *__endpoint,
    unsigned int __port)
{
  this->ssid = __ssid;
  this->pass = __pass;
  this->server = __server;
  this->endpoint = __endpoint;
  this->port = __port;

  this->powertrainLevel = 0;
  this->steeringAngle = 0;
}

void ServiceClient::setup(void)
{

  // check for the Wi-Fi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with Wi-Fi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0")
  {
    Serial.println("Please upgrade the firmware");
  }

  // Try to connect to Wi-Fi network
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);

    // Waiting for connection:
    delay(5000);
  }
  Serial.println("Connected to Wi-Fi");

  printWiFiStatus();
}

void ServiceClient::loop(void)
{

  // Connecting to server
  if (!client.connect(server, port))
  {
    Serial.println("Error trying to connect to server");
    delay(1000);
  }

  if (client.connected())
  {
    // Connected to server
    // Make an HTTP request
    client.print("GET ");
    client.print(endpoint);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    // Check for available data
    while (!client.available())
    {
      // Waiting for server response
      delay(100);
    }

    // Find empty line
    if (client.find(ServiceClient::EMPTY_LINE) && ServiceClient::BODY_SIZE == client.available())
    {
      // Read response body
      client.readBytes(responseBody, ServiceClient::BODY_SIZE);

      memcpy(&this->steeringAngle, this->responseBody, sizeof(float));
      memcpy(&this->powertrainLevel, this->responseBody + sizeof(float), sizeof(float));

      Serial.println();
      Serial.print("Steering: ");
      Serial.println(this->steeringAngle);
      Serial.print("Powertrain: ");
      Serial.println(this->powertrainLevel);
    }
    else
    {
      Serial.print("Response body not found! Available bytes: ");
      Serial.println(client.available());
    }
  }

  // Check connection with server
  if (!client.connected())
  {
    // Stop client
    client.stop();
  }

  delay(10);
}

void ServiceClient::printWiFiStatus(void)
{
  // Print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("Device IP Address: ");
  Serial.println(ip);

  // Print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

float ServiceClient::getPowertrainLevel(void) const
{
  return this->powertrainLevel;
}

float ServiceClient::getSteeringAngle(void) const
{
  return this->steeringAngle;
}