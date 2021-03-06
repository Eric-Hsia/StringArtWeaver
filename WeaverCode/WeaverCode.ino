#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 4

#define DIR 8
#define STEP 9
#define SLEEP 13 // optional (just delete SLEEP from everywhere if not used)


#include "A4988.h"
#define MS1 10
#define MS2 11
#define MS3 15
#define microStepMode 8
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000
A4988 stepper(MOTOR_STEPS, DIR, STEP, SLEEP, MS1, MS2, MS3);
/*
   For Servo
  #define StringHeadPin 20
  #define StringHeadInitialPos 4
  #define StringHeadLastPos 75
  Servo StringHead;
*/
//Software parameters
int incomingByte = 0;
int flagRaised = 0;
int row = 0;

// Canvas Parameter
int nailNumber = 95;
int microStepPerNail = (MOTOR_STEPS*microStepMode) / nailNumber;
int numberOfSequence = 200;
int curNailID = 1;

// Weaving Sequence Data
int sequence[500][2] = {
{27,1},
{26,1},
{16,1},
{28,1},
{14,1},
{24,1},
{34,1},
{23,1},
{9,1},
{19,1},
{62,1},
{76,1},
{39,1},
{14,1},
{5,1},
{17,1},
{76,1},
{53,1},
{65,1},
{93,1},
{12,1},
{59,1},
{88,1},
{28,1},
{9,1},
{51,1},
{66,1},
{12,1},
{60,1},
{72,1},
{59,1},
{27,1},
{37,1},
{18,1},
{36,1},
{74,1},
{24,1},
{57,1},
{27,1},
{11,1},
{52,1},
{45,1},
{1,1},
{25,1},
{73,1},
{8,1},
{39,1},
{86,1},
{48,1},
{67,1},
{20,1},
{45,1},
{91,1},
{51,1},
{85,1},
{29,1},
{7,1},
{35,1},
{93,1},
{45,1},
{54,1},
{80,1},
{59,1},
{50,1},
{76,1},
{56,1},
{74,1},
{17,1},
{94,1},
{11,1},
{75,1},
{88,1},
{49,1},
{2,1},
{65,1},
{50,1},
{2,1},
{43,1},
{23,1},
{53,1},
{63,1},
{27,1},
{60,1},
{18,1},
{38,1},
{76,1},
{19,1},
{7,1},
{60,1},
{9,1},
{66,1},
{33,1},
{72,1},
{46,1},
{69,1},
{53,1},
{33,1},
{17,1},
{32,1},
{6,1},
{23,1},
{41,1},
{88,1},
{43,1},
{90,1},
{42,1},
{93,1},
{34,1},
{5,1},
{24,1},
{92,1},
{41,1},
{14,1},
{81,1},
{68,1},
{76,1},
{25,1},
{7,1},
{21,1},
{62,1},
{25,1},
{42,1},
{14,1},
{40,1},
{78,1},
{41,1},
{13,1},
{76,1},
{14,1},
{73,1},
{37,1},
{84,1},
{45,1},
{15,1},
{91,1},
{41,1},
{68,1},
{42,1},
{15,1},
{72,1},
{64,1},
{56,1},
{66,1},
{55,1},
{63,1},
{71,1},
{78,1},
{64,1},
{34,1},
{66,1},
{30,1},
{38,1},
{16,1},
{75,1},
{25,1},
{56,1},
{20,1},
{32,1},
{81,1},
{35,1},
{60,1},
{89,1},
{42,1},
{17,1},
{54,1},
{94,1},
{65,1},
{84,1},
{53,1},
{75,1},
{58,1},
{83,1},
{45,1},
{94,1},
{14,1},
{54,1},
{18,1},
{41,1},
{25,1},
{59,1},
{15,1},
{38,1},
{83,1},
{50,1},
{5,1},
{59,1},
{29,1},
{87,1},
{45,1},
{67,1},
{58,1},
{72,1},
{57,1},
{26,1},
{40,1},
{20,1},
{37,1},
{14,1},
{1,1},
{10,1},
{32,1},
{80,1},
{72,1},
{50,1},
{84,1},
{47,1},
{23,1},
{85,1},
{53,1},
{93,1},
{40,1},
{91,1},
{49,1},
{73,1},
{50,1},
{63,1},
{54,1},
{76,1},
{55,1},
{78,1},
{26,1},
{75,1},
{86,1},
{79,1},
{53,1},
{6,1},
{25,1},
{44,1},
{10,1},
{57,1},
{79,1},
{88,1},
{48,1},
{69,1},
{47,1},
{29,1},
{1,1},
{27,1},
{44,1},
{52,1},
{86,1},
{27,1},
{77,1},
{58,1},
{22,1},
{32,1},
{16,1},
{8,1},
{21,1},
{32,1},
{65,1},
{57,1},
{68,1},
{35,1},
{84,1},
{67,1},
{37,1},
{70,1},
{3,1},
{15,1},
{39,1},
{20,1},
{69,1},
{2,1},
{11,1},
{60,1},
{4,1},
{39,1},
{11,1},
{21,1},
{31,1},
{14,1},
{25,1},
{39,1},
{30,1},
{14,1},
{23,1},
{69,1},
{56,1},
{23,1},
{35,1},
{61,1},
{27,1},
{62,1},
{26,1},
{79,1},
{32,1},
{77,1},
{56,1},
{9,1},
{63,1},
{45,1},
{82,1},
{62,1},
{22,1},
{40,1},
{27,1},
{70,1},
{30,1},
{9,1},
{34,1},
{71,1},
{56,1},
{93,1},
{25,1},
{82,1},
{64,1},
{80,1},
{67,1},
{79,1},
{64,1},
{77,1},
{39,1},
{17,1},
{67,1},
{43,1},
{93,1},
{46,1},
{83,1},
{26,1},
{1,1},
{48,1},
{24,1},
{6,1},
{42,1},
{3,1},
{35,1},
{86,1},
{62,1},
{72,1},
{65,1},
{55,1},
{67,1},
{35,1},
{20,1},
{36,1},
{14,1},
{72,1},
{24,1},
{58,1},
{5,1},
{21,1},
{57,1},
{66,1},
{15,1},
{74,1},
{47,1},
{87,1},
{49,1},
{86,1},
{51,1},
{87,1},
{26,1},
{12,1},
{27,1},
{58,1},
{70,1},
{80,1},
{71,1},
{62,1},
{55,1},
{14,1},
{35,1},
{73,1},
{15,1},
{1,1},
{12,1},
{32,1},
{57,1},
{4,1},
{51,1},
{71,1},
{5,1},
{35,1},
{77,1},
{61,1},
{14,1},
{66,1},
{37,1},
{90,1},
{35,1},
{17,1},
{41,1},
{84,1},
{46,1},
{1,1},
{8,1},
{59,1},
{82,1},
{19,1},
{50,1},
{3,1},
{43,1},
{92,1},
{52,1},
{1,1},
{56,1},
{65,1},
{34,1},
{16,1},
{24,1},
{56,1},
{22,1},
{37,1},
{69,1},
{55,1},
{75,1},
{54,1},
{71,1},
{23,1},
{40,1},
{17,1},
{77,1},
{41,1},
{83,1},
{34,1},
{73,1},
{51,1},
{44,1},
{55,1},
{15,1},
{34,1},
{6,1},
{87,1},
{27,1},
{64,1},
{71,1},
{58,1},
{66,1},
{36,1},
{67,1},
{78,1},
{62,1},
{75,1},
{56,1},
{15,1},
{67,1},
{86,1},
{55,1},
{8,1},
{31,1},
{76,1},
{20,1},
{46,1},
{71,1},
{48,1},
{18,1},
{33,1},
{5,1},
{55,1},
{81,1},
{59,1},
{91,1},
{9,1},
{21,1},
{37,1},
{30,1},
{11,1},
{32,1},
{58,1},
{28,1},
{10,1},
{31,1},
{15,1},
{32,1},
{59,1},
{9,1},
{33,1},
{82,1},
{32,1},
{48,1},
{23,1},
{59,1},
{66,1},
{35,1},
{65,1},
{36,1},
{69,1},
{31,1},
{57,1},
{74,1},
{54,1},
{16,1},
{7,1},
{59,1},
{31,1},
{91,1},
{63,1},
{87,1},
{59,1},
{75,1},
{35,1},
{88,1},
{37,1},
{1,1},
{64,1},
{57,1},
{25,1},
{15,1},
{33,1}
}
;


void setup() {
  Serial.begin(115200);
  delay(500);
  stepper.begin(RPM);
  stepper.enable();
  stepper.setMicrostep(microStepMode);   // Set microstep mode to 1:8
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  curNailID = sequence[0][0];
  Serial.print("The sequence is starting from nail ID:\t");
  Serial.println(curNailID);
}

void loop() {
  //Checking for Serial input
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 'n') {
      if (row < numberOfSequence) {
        row = row + 1;
      } else {
        Serial.println("Sequence Exhausted");
      }
    }
    else if (incomingByte == 'p') {
      row = row - 1;
    }
    else {
      //Serial.print("I received: nothing yet!");
    }
    if (curNailID != sequence[row][0]) {
      flagRaised = 0;
      int desiredNailID = sequence[row][0];
      int nails = stepsToMove(curNailID, desiredNailID, nailNumber);
      Serial.print("Desired Node: \t");
      Serial.print(desiredNailID);
      Serial.print("\tSteps \t");
      Serial.println(nails);
      curNailID = desiredNailID;
      stepNode(-1*nails);
    }
  }
  //End of Checking for Serial input

  //Have the user been notified
  if (flagRaised == 0) {
    flagRaised = 1;
    Serial.print("Current Row : ");
    Serial.print(row);
    Serial.print("\tString Direction : \t");
    if (sequence[row][1] == 1)
    {
      Serial.print("Face [Up]");
    }
    else {
      Serial.print("Face [Down]");
    }
    Serial.println("\tPress 'n' or 'p'");

  }
}

void stepNode(int nails) {
  int numberOfSteps = nails * (MOTOR_STEPS * microStepMode) / nailNumber;
  stepper.move(numberOfSteps);
}

int stepsToMove( int startingNail, int  endingNail, int NailNumber) {
  int distance = 0;
  //distance = NailNumber * (distance / NailNumber) - (distance % NailNumber)
  if (endingNail < startingNail) {
    distance = startingNail - endingNail;
    
    if (abs(distance) < NailNumber / 2) {
      distance = -1 * distance;
    } else {
      distance = NailNumber - distance;
    }
  }
  else {
    distance = NailNumber - endingNail + startingNail;
    if (abs(distance) < NailNumber / 2) {
      distance = -1 * distance;
    } else {
      distance = NailNumber - distance;
    }
  }
  return distance;
}

//counterDistance = x < y ? (N - y + x) : (x - y); 
//direction = counterDistance < N / 2 ? "counter" : "clock";
