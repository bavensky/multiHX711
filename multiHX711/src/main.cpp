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

const int numReadings = 10;
float readings1[numReadings];
float readings2[numReadings];
int readIndex = 0;
double average = 0;

uint32_t arrayScale[255];
// double arrayScale[];
int standCount = 0;
unsigned long readSpeed = 0;

boolean standState = false;

// (1 lbs = 0.453592 kg)
float get_units_kg1()
{
  return (scale1.get_units() * 0.453592);
}

float get_units_kg2()
{
  return (scale2.get_units() * 0.453592);
}

void get_average()
{
  readings1[readIndex] = get_units_kg1(); // * 1000;
  readings2[readIndex] = get_units_kg2(); // * 1000;

  readIndex++;
  if (readIndex >= numReadings)
  {
    readIndex = 0;
  }

  average = 0;
  for (int x = 0; x < numReadings; x++)
  {
    average += (readings1[x] + readings2[x]);
    // Serial.print(readings1[x]);
    // Serial.print("\t");
  }
  // Serial.print("\n");

  average = (average / numReadings) - 2.65;
  // standCount++;
  // Serial.print("average = ");
  // Serial.println(average);
  // delay(1000);
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
  // unsigned long startMillis = millis();
  // Serial.print("readSpeed = ");
  // Serial.print(startMillis - readSpeed);
  // Serial.print("\t");
  // readSpeed = startMillis;

  get_average();
  // Serial.print("stand = ");
  // Serial.println(standCount);
  // Serial.println(average);

  standCount = 0;
  while (average > 50.00)
  {
    get_average();
    arrayScale[standCount] = average;
    // Serial.print(arrayScale[standCount]);
    // Serial.print("  ");
    // Serial.print(" stand = ");
    // Serial.print(standCount);
    // Serial.print("  ");

    standCount += 1;
    standState = true;
    // delay(1000);
  }

  if (standState == true)
  {
    // Serial.print("\n");
    // Serial.print("\n");
    // Serial.print("standCount = ");
    // Serial.print(standCount);
    // delay(2000);

    // Serial.print("\nData = ");
    // for (int i = 0; i < standCount; i++)
    // {
    //   Serial.print(arrayScale[i]);
    //   Serial.print(" ");
    // }

    // Serial.print("\n");
    // Serial.print("\n");
    // Serial.print("lenght = ");
    // Serial.print(sizeof(arrayScale));
    // delay(3000);

    // Serial.print("\n");
    // Serial.print("\n");
    int32_t arraySize = standCount;
    arraySize = arraySize / 5;
    // Serial.print("arraySize = ");
    // Serial.print(arraySize);
    // delay(3000);

    // Serial.print("\n");
    // Serial.print("\n");
    // Serial.print("Inside array = ");
    double sumAVE = 0;
    for (int i = arraySize; i < (standCount - arraySize); i++)
    {
      sumAVE += arrayScale[i];
      // Serial.println(arrayScale[i]);
      // Serial.print(" ");
    }

    sumAVE = sumAVE / ((standCount - arraySize) - arraySize);
    // Serial.print("sumAVE = ");
    Serial.println(sumAVE);
    // delay(5000);

    standCount = 0;
    standState = false;
  }

  //   standCount = 0;
  //   standState = false;

  //   standCount = 0;
  //   for (int x = 0; x < standCount; x++)
  //   {
  //     Serial.print(arrayScale[standCount]);
  //     Serial.print("\t");
  //   }
  //   Serial.print("\n");
  //   delay(3000);
  // standState = false;
  // }

  // readings1[readIndex] = get_units_kg1(); // * 1000;
  // readings2[readIndex] = get_units_kg2(); // * 1000;

  // readIndex++;

  // if (readIndex >= numReadings)
  // {
  //   readIndex = 0;
  // }

  // average = 0;

  // for (int x = 0; x < numReadings; x++)
  // {
  //   average += (readings1[x] + readings2[x]);
  // Serial.print(readings1[x]);
  // Serial.print("\t");
  // }

  // average = (average / (numReadings * 2));

  // Serial.print("average = ");    // Serial.print(readings1[x]);
  // Serial.print("\t");1000 / 80
  // Serial.print(0);
  // Serial.print("\t");
  // Serial.print(100000);
  // Serial.print("\t");
  // Serial.println(average);

  // delay(15); // 1000 / 80 = 12.5

  // Serial.print("Reading: ");
  // String data1 = String(get_units_kg1() + offset, DEC_POINT);
  // String data2 = String(get_units_kg2() + offset, DEC_POINT);

  // Serial.println("function1 :");
  // for (int i = 0; i <= 10; i++)
  // {
  // scaleSum1 += get_units_kg1();
  // scaleSum2 += get_units_kg2();
  // }
  // scaleSum1 = scaleSum1 / 10;
  // scaleSum2 = scaleSum2 / 10;
  // scaleSum = (scaleSum1 + scaleSum2) - 3.5;

  // scaleSum1 = get_units_kg1();
  // scaleSum2 = get_units_kg2();
  // Serial.print(scaleSum1);
  // Serial.print("  ");
  // Serial.print(scaleSum2);
  // Serial.print("  ");
  // Serial.println(scaleSum);

  // // Serial.println("function2 :");
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
