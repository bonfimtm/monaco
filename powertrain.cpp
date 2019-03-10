//
//  powertrain.cpp
//  monaco
//
//  Created by Thiago Bonfim on 2019-03-09.
//  Copyright © 2019. Thiago Bonfim. All rights reserved.
//

#include "powertrain.hpp"

Powertrain::Powertrain(
    unsigned int __pwmPin,
    unsigned int __dirPinA,
    unsigned int __dirPinB,
    ServiceClient *__serviceClient)
{
    this->pwmPin = __pwmPin;
    this->dirPinA = __dirPinA;
    this->dirPinB = __dirPinB;
    this->serviceClient = __serviceClient;
    this->motorPower = Powertrain::MOTOR_POWER_MIN;
    this->motorPowerRaw = Powertrain::MOTOR_POWER_RAW_MIN;
    this->direction = DrivingDirection::FORWARD;
}

void Powertrain::setup(void)
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(this->dirPinA, OUTPUT);
    pinMode(this->dirPinB, OUTPUT);
    pinMode(this->pwmPin, OUTPUT);

    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(this->dirPinA, HIGH);
    digitalWrite(this->dirPinB, LOW);

    analogWrite(this->pwmPin, this->motorPowerRaw);
}

void Powertrain::loop(void)
{
    this->motorPower = serviceClient->getPowertrainLevel();

    this->motorPowerRaw = abs(this->motorPower);

    if (this->motorPower < 0)
    {
        this->direction = DrivingDirection::REVERSE;
    }
    else
    {
        this->direction = DrivingDirection::FORWARD;
    }

    Serial.println();
    Serial.print("Motor power: ");
    Serial.println(this->motorPower);
    Serial.print("Direction: ");
    Serial.println((int) this->direction);

    if (DrivingDirection::FORWARD == this->direction)
    {
        digitalWrite(this->dirPinA, HIGH);
        digitalWrite(this->dirPinB, LOW);
        digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
        digitalWrite(this->dirPinA, LOW);
        digitalWrite(this->dirPinB, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
    }

    analogWrite(this->pwmPin, this->motorPowerRaw);
}
