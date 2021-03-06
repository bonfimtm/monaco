//
//  powertrain.hpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#ifndef powertrain_hpp
#define powertrain_hpp

#include "service_client.hpp"

enum class DrivingDirection
{
  FORWARD = 1,
  REVERSE = -1,
};

class Powertrain
{
private:
  unsigned int pwmPin;
  unsigned int dirPinA;
  unsigned int dirPinB;
  ServiceClient *serviceClient;
  float motorPower;
  unsigned int motorPowerRaw;
  DrivingDirection direction;
  constexpr static float MOTOR_POWER_MIN = 0.0f;
  constexpr static float MOTOR_POWER_MAX = 100.0f;
  const static unsigned int MOTOR_POWER_RAW_MIN = 0;
  const static unsigned int MOTOR_POWER_RAW_MAX = 255;

public:
  Powertrain(
      unsigned int __pwmPin,
      unsigned int __dirPinA,
      unsigned int __dirPinB,
      ServiceClient *__serviceClient);
  void setup(void);
  void loop(void);
};

#endif /* powertrain_hpp */
