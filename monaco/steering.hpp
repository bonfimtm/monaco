//
//  steering.hpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#ifndef steering_hpp
#define steering_hpp

#include "service_client.hpp"

class Steering
{
private:
  unsigned int pwmPin;
  unsigned int dirPinA;
  unsigned int dirPinB;
  ServiceClient *serviceClient;
  float angle;
  unsigned int angleRaw;

  constexpr static float ANGLE_LEFT_MAX = -90.0f;
  constexpr static float ANGLE_CENTER = 0.0f;
  constexpr static float ANGLE_RIGHT_MAX = 90.0f;

  constexpr static float ANGLE_LEFT_MECH_MAX = -70.0f;
  constexpr static float ANGLE_RIGHT_MECH_MAX = 70.0f;

  const static unsigned int ANGLE_RAW_MIN = 0;
  const static unsigned int ANGLE_RAW_MAX = 255;

public:
  Steering(
      unsigned int __pwmPin,
      unsigned int __dirPinA,
      unsigned int __dirPinB,
      ServiceClient *__serviceClient);
  void setup(void);
  void loop(void);
};

#endif /* steering_hpp */
