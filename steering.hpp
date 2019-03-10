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
  int angle;
  unsigned int angleRaw;

  const static int ANGLE_LEFT_MAX = -90;
  const static int ANGLE_CENTER = 0;
  const static int ANGLE_RIGHT_MAX = 90;

  const static int ANGLE_LEFT_MECH_MAX = -60;
  const static int ANGLE_RIGHT_MECH_MAX = 60;

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
  void setAngle(int angle);
};

#endif /* steering_hpp */
