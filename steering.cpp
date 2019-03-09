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
    if (this->serviceClient->getSteeringAngle() > 0)
    {
        this->setAngle(Steering::ANGLE_RIGHT_MAX);
    }
    else if (this->serviceClient->getSteeringAngle() < 0)
    {
        this->setAngle(Steering::ANGLE_LEFT_MECH_MAX);
    }
    else
    {
        this->setAngle(Steering::ANGLE_CENTER);
    }

    analogWrite(this->pwmPin, this->angleRaw);
}

void Steering::setAngle(int angle)
{
    Serial.println();
    Serial.print("Setting steering angle to ");
    Serial.print(angle);
    Serial.print(" deg");

    if (angle < Steering::ANGLE_LEFT_MAX || angle > Steering::ANGLE_RIGHT_MAX)
    {
        return;
    }

    if (angle > Steering::ANGLE_CENTER)
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

    this->angleRaw = (int)(abs(angle) / (float)Steering::ANGLE_RIGHT_MAX * Steering::ANGLE_RAW_MAX);

    Serial.print(" (");
    Serial.print(this->angleRaw);
    Serial.println(")");
}
