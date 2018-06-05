#include <Arduino.h>
#include "HX711.h"

float calibration_factor1 = 11636.00;
#define zero_factor1 8123913

float calibration_factor2 = 12120.00;
#define zero_factor2 7842768

#define DOUT1 7
#define CLK1 6
#define DOUT2 8
#define CLK2 9

#define DEC_POINT 2

float offset = 0;
float get_units_kg();

double scaleSum = 0.0;
double scaleSum1 = 0.0;
double scaleSum2 = 0.0;
unsigned int count = 0;
boolean status = false;

HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);

// (1 lbs = 0.453592 kg)

float get_units_kg1()
{
  return (scale1.get_units() * 0.453592);
}

float get_units_kg2()
{
  return (scale2.get_units() * 0.453592);
}

void setup()
{
  Serial.begin(115200);

  scale1.set_scale(calibration_factor1);
  scale1.set_offset(zero_factor1);

  scale2.set_scale(calibration_factor2);
  scale2.set_offset(zero_factor2);
}

void loop()
{
  // Serial.print("Reading: ");
  // String data1 = String(get_units_kg1() + offset, DEC_POINT);
  // String data2 = String(get_units_kg2() + offset, DEC_POINT);

  // Serial.print("scale1 :");
  for (int i = 0; i <= 10; i++)
  {
    scaleSum1 += get_units_kg1();
    scaleSum2 += get_units_kg2();
  }
  scaleSum1 = scaleSum1 / 10;
  scaleSum2 = scaleSum2 / 10;
  // scaleSum = (scaleSum1 + scaleSum2);
  scaleSum = (scaleSum1 + scaleSum2) - 3.5;

  // Serial.print(scaleSum1);
  // Serial.print("  ");
  // Serial.print(scaleSum2);
  // Serial.print("  ");
  Serial.println(scaleSum);

  // scaleSum1 = 0.0;
  // scaleSum2 = 0.0;
  // count = 0;

  // while (get_units_kg1() > 20.00 || get_units_kg2() > 20.00)
  // {
  //   scaleSum1 += get_units_kg1();
  //   scaleSum2 += get_units_kg2();
  //   count++;
  //   Serial.print(scaleSum1);
  //   Serial.print(" ");
  //   Serial.print(scaleSum2);
  //   Serial.print(" ");
  //   Serial.println(count);
  //   status = true;
  // }

  // if (status == true)
  // {
  //   scaleSum1 = scaleSum1 / count;
  //   scaleSum2 = scaleSum2 / count;
  //   scaleSum = (scaleSum1 + scaleSum2) - 3.65;
  //   Serial.print("Weight Scale = ");
  //   Serial.println(scaleSum);
  //   delay(3000);
  //   status = false;
  // }
}
