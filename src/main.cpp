#include <Arduino.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define CE_PIN 9
#define CSN_PIN 10
#define xAxis A0
#define yAxis A1

const uint64_t pipe = 0xE8E8F0F0E1LL;
const int PIN_BUTTON_A = 2;
const int PIN_BUTTON_B = 3;
const int PIN_BUTTON_C = 4;
const int PIN_BUTTON_D = 5;
const int PIN_BUTTON_E = 6;
const int PIN_BUTTON_F = 7;
const int PIN_BUTTON_G = 8;

RF24 radio(CE_PIN, CSN_PIN);

int joystick[9];

void setup()
{

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();

  pinMode(PIN_BUTTON_A, INPUT_PULLUP);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  pinMode(PIN_BUTTON_C, INPUT_PULLUP);
  pinMode(PIN_BUTTON_D, INPUT_PULLUP);
  pinMode(PIN_BUTTON_E, INPUT_PULLUP);
  pinMode(PIN_BUTTON_F, INPUT_PULLUP);
  pinMode(PIN_BUTTON_G, INPUT_PULLUP);

  digitalWrite(PIN_BUTTON_A, LOW);
  digitalWrite(PIN_BUTTON_B, LOW);
  digitalWrite(PIN_BUTTON_C, LOW);
  digitalWrite(PIN_BUTTON_D, LOW);
  digitalWrite(PIN_BUTTON_E, LOW);
  digitalWrite(PIN_BUTTON_F, LOW);
  digitalWrite(PIN_BUTTON_G, LOW);
}

void loop()
{
  joystick[0] = analogRead(xAxis);
  joystick[1] = analogRead(yAxis);
  joystick[2] = digitalRead(PIN_BUTTON_A);
  joystick[3] = digitalRead(PIN_BUTTON_B);
  joystick[4] = digitalRead(PIN_BUTTON_C);
  joystick[5] = digitalRead(PIN_BUTTON_D);
  joystick[6] = digitalRead(PIN_BUTTON_E);
  joystick[7] = digitalRead(PIN_BUTTON_F);
  joystick[8] = digitalRead(PIN_BUTTON_G);

  radio.write(joystick, sizeof(joystick));
  delay(100);

  Serial.print("X = ");
  Serial.print(analogRead(xAxis));
  Serial.print(" Y = ");
  Serial.print(analogRead(yAxis));
  Serial.print(" Up = ");
  Serial.print(digitalRead(PIN_BUTTON_A));
  Serial.print(" Right = ");
  Serial.print(digitalRead(PIN_BUTTON_B));
  Serial.print(" Down = ");
  Serial.print(digitalRead(PIN_BUTTON_C));
  Serial.print(" Left = ");
  Serial.print(digitalRead(PIN_BUTTON_D));
  Serial.print(" E = ");
  Serial.print(digitalRead(PIN_BUTTON_E));
  Serial.print(" F = ");
  Serial.print(digitalRead(PIN_BUTTON_F));
  Serial.print(" G = ");
  Serial.println(digitalRead(PIN_BUTTON_G));
}
