//
//  steering.cpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#include "steering.hpp"

Steering::Steering(
    unsigned int __pwmPin,
    unsigned int __dirPinA,
    unsigned int __dirPinB,
    ServiceClient *__serviceClient)
{
    this->pwmPin = __pwmPin;
    this->dirPinA = __dirPinA;
    this->dirPinB = __dirPinB;
    this->serviceClient = __serviceClient;
    this->angle = Steering::ANGLE_CENTER;
    this->angleRaw = Steering::ANGLE_RAW_MIN;
}

void Steering::setup(void)
{
    pinMode(this->dirPinA, OUTPUT);
    pinMode(this->dirPinB, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);

    digitalWrite(this->dirPinA, LOW);
    digitalWrite(this->dirPinB, HIGH);

    analogWrite(this->pwmPin, this->angleRaw);
}

void Steering::loop(void)
{
    this->angle = this->serviceClient->getSteeringAngle();

    Serial.println();
    Serial.print("Steering angle: ");
    Serial.print(this->angle);
    Serial.print(" deg");

    if (this->angle < Steering::ANGLE_LEFT_MECH_MAX || this->angle > Steering::ANGLE_RIGHT_MECH_MAX)
    {
        return;
    }

    this->angleRaw = (int)(abs(this->angle) / (float)Steering::ANGLE_RIGHT_MAX * Steering::ANGLE_RAW_MAX);
    
    Serial.print(" (");
    Serial.print(this->angleRaw);
    Serial.println(")");

    if (this->angle > Steering::ANGLE_CENTER)
    {
        // Right
        digitalWrite(this->dirPinA, HIGH);
        digitalWrite(this->dirPinB, LOW);
    }
    else
    {
        // Left
        digitalWrite(this->dirPinA, LOW);
        digitalWrite(this->dirPinB, HIGH);
    }

    analogWrite(this->pwmPin, this->angleRaw);
}
