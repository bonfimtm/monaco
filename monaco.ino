//
//  monaco.ino
//  monaco
//
//  Circuit:
//    - Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#include "service_client.hpp"
#include "powertrain.hpp"
#include "steering.hpp"

// Enter your sensitive data to secrets.h
//   - SECRET_SSID: Your network SSID (name)
//   - SECRET_PASS: Your network password (use for WPA, or use as key for WEP)
//   - SECRET_SERVER_URL: Server's name address or IP address
//   - SECRET_ENDPOINT_PATH: Endpoint path
#include "secrets.h"

#define HTTP_PORT 80

#define SERIAL_BAUD_RATE 9600

#define POWERTRAIN_PWM_PIN 2
#define POWERTRAIN_DIR_PIN_A 0
#define POWERTRAIN_DIR_PIN_B 1

#define STEERING_PWM_PIN 5
#define STEERING_DIR_PIN_A 3
#define STEERING_DIR_PIN_B 4

ServiceClient serviceClient(SECRET_SSID, SECRET_PASS, SECRET_SERVER_URL, SECRET_ENDPOINT_PATH, HTTP_PORT);
Powertrain powertrain(POWERTRAIN_PWM_PIN, POWERTRAIN_DIR_PIN_A, POWERTRAIN_DIR_PIN_B, &serviceClient);
Steering steering(STEERING_PWM_PIN, STEERING_DIR_PIN_A, STEERING_DIR_PIN_B, &serviceClient);

// The setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  serviceClient.setup();
  powertrain.setup();
  steering.setup();
}

// The loop function runs over and over again forever
void loop()
{
  serviceClient.loop();
  powertrain.loop();
  steering.loop();
}
