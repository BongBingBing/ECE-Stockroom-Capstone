#include "HX711-multi.h"


#define TARE_TIMEOUT_SECONDS 4

byte DOUTS[3] = {DOUT1, DOUT2, DOUT3};

#define CHANNEL_COUNT sizeof(DOUTS)/sizeof(byte)

long int results[CHANNEL_COUNT]

HX711MULTI scales(CHANNEL_COUNT, DOUTS, CLK);

void tare() {
  bool tareSuccessful = false;

  unsigned long tareStartTime = millis();
  while (!tareSuccessful && millis()<(tareStartTime + TARE_TIMEOUT_SECONDS * 1000)) {
    tareSuccessful = scales.tare(20,10000);  //reject 'tare' if still ringing
  }
}

void setup()
{
    Serial.begin(9600);
    Serial.flush();

    Serial.println("Starting test case");
    Serial.println("Remove weight (5s)");
    
    delay(5000);

    tare();
}

void loop()
{
  
  if (!runthrough){
    Serial.println("Add quarter to weight (5s)");

    scales.read()

  }

}

