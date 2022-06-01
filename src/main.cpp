#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
//const int LOADCELL_DOUT_PIN[10] = {5R, 4R, 3R, 2R, 1R, 5L, 4L, 3L, 2L, 1L};
//const int LOADCELL_DOUT_PIN[10] = {36, 39, 34, 35, 25, 18, 17, 15, 4, 13};
//const int LOADCELL_SCK_PIN[10] = {27, 26, 33, 32, 23, 19, 16, 14, 5, 12};
// for loadcell
const int LOADCELL_DOUT_PIN[10] = {13, 25, 4, 35, 15, 34, 17, 39, 18, 36};
const int LOADCELL_SCK_PIN[10] = {12, 23, 5, 32, 14, 33, 16, 26, 19, 27};

long olddata[10];
long datanew[10];

HX711 scale[10];

double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 10; i++)
  {
    scale[i].begin( LOADCELL_DOUT_PIN[i], LOADCELL_SCK_PIN[i]);
  }

  Serial.println(" set zero ");
  for (int i = 0; i < 10; i++)
  {
    if (scale[i].wait_ready_timeout(1000))
    {
      olddata[i] = scale[i].read_average(10);
      Serial.print(" " + String(i) + " : ");
      Serial.print(datanew[i]);
    }
    else
    {
      Serial.println("HX711 not found.");
    }
  }
  Serial.println(" finish ");
}

void loop()
{
  for(int i = 0; i<10;i++){
    if (scale[i].wait_ready_timeout(500))
    {
      datanew[i] = scale[i].read();
      Serial.print(" "+String(i+1)+" : ");
      Serial.print((datanew[i]- olddata[i]));
    }
    else
    {
      Serial.println("HX711 not found.");
    }
  }
  Serial.println(" ");
  delay(1000);
  /*
  int datavin = analogRead(34);
  int datalow = analogRead(32);
  float mapdata = mapfloat(datavin,2800.00,3200.00,0.00,400.00);
  float mapdatalow = mapfloat(datalow, 2800.00, 3200.00, 400, 0);
  Serial.print("data in : ");
  Serial.print(datavin);
  Serial.print(" map in : ");
  Serial.print(mapdata);
  Serial.print(" data LOW : ");
  Serial.print(datalow);
  Serial.print(" map LOW : ");
  Serial.print(mapdatalow);
  Serial.println(" ");
  delay(100);
  */
}

