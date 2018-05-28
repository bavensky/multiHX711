#include <Arduino.h>
#include "HX711.h"


float calibration_factor1 = 11636.00;
#define zero_factor1 8123913

float calibration_factor2 = 12120.00;
#define zero_factor2 7842768


#define DOUT1  7
#define CLK1   6
#define DOUT2  8
#define CLK2   9

#define DEC_POINT  2

float offset = 0;
float get_units_kg();

HX711 scale1(DOUT1, CLK1);
HX711 scale2(DOUT2, CLK2);


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
  Serial.println("Load Cell");
  scale1.set_scale(calibration_factor1);
  scale1.set_offset(zero_factor1);

  scale2.set_scale(calibration_factor2);
  scale2.set_offset(zero_factor2);

}


void loop()
{
  Serial.print("Reading: ");
  String data1 = String(get_units_kg1() + offset, DEC_POINT);
  String data2 = String(get_units_kg2() + offset, DEC_POINT);

  Serial.print("scale1 :");
  Serial.print(data1);
  Serial.print(" kg\t");

  Serial.print("scale2 :");
  Serial.print(data2);
  Serial.println(" kg");
}
