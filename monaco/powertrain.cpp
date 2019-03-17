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

    Serial.println();
    Serial.print("Motor power: ");
    Serial.print(this->motorPower);
    Serial.print("\%");

    if (this->motorPower < -Powertrain::MOTOR_POWER_MAX || this->motorPower > Powertrain::MOTOR_POWER_MAX)
    {
        return;
    }

    this->motorPowerRaw = (int)(abs(this->motorPower) / (float)Powertrain::MOTOR_POWER_MAX * Powertrain::MOTOR_POWER_RAW_MAX);
    
    Serial.print(" (");
    Serial.print(this->motorPowerRaw);
    Serial.println(")");

    if (this->motorPower < 0.0f)
    {
        this->direction = DrivingDirection::REVERSE;
    }
    else
    {
        this->direction = DrivingDirection::FORWARD;
    }
    
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
