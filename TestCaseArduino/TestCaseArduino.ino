#include <DFRobot_HX711.h>

//This follows the pattern of MyScale({Data Pin}, {Clock Pin})
DFRobot_HX711 MyScale(A2, A3);


struct MuxCombo {
  unsigned char A;
  unsigned char B;
  unsigned char C;
};

const MuxCombo MuxCombos[] = {
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0}
};

volatile bool runthrough = false;

int pinA = 30;
int pinB = 32;
int pinC = 34;



void setup()
{
    Serial.begin(9600);
    Serial.flush();

    Serial.println("Starting test case");
    Serial.println("Remove weight (5s)");
    
    delay(5000);

    digitalWrite(pinA, MuxCombos[0].A);
    digitalWrite(pinB, MuxCombos[0].B);
    digitalWrite(pinC, MuxCombos[0].C);



}

void loop()
{
  
  if (!runthrough){
    Serial.println("Add quarter to weight (5s)");

    delay(5000);

    Serial.println("Reading....");

    long raw_reading = MyScale.readWeight();

    Serial.print("Raw value read: ");
    Serial.println(raw_reading);

    long cal_factor = raw_reading / 5.67;

    Serial.print("Calculated calibration factor: ");
    Serial.println(cal_factor);

    Serial.println("Remove weight (5s)");
    delay(5000);

    MyScale.setCalibration(cal_factor);

    Serial.println("Add another coin to the scale (5s)");
    delay(5000);

    Serial.println("Read weight: " + String(MyScale.readWeight()));


  }

}

