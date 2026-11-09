#include <SD.h>
File myFile;
const int CSPin = 4;
const int In1 = 5;
const int In2 = 6;
const int In3 = 9;
const int In4 = 11;
const int EnA = 3;
const int EnB = 10;

#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4
#define OE A5

int green[] = {155, 145, 150};
bool greenFlag[] = {false, false, false};
int difference = 0;
int frequency = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //digitalWrite(OE, LOW);
  pinMode(CSPin, OUTPUT);

  if (!SD.begin(CSPin))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt");

  if (myFile)
  {
    Serial.println("test.txt:");

    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    myFile.close();

  }
  else
  {
    Serial.println("error opening test.txt");                                   
  }
}

void loop()
{
  int s1 = digitalRead(12);
  Serial.println(s1);
  delay(100);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[0];

  if(abs(difference)<10)
  {
    greenFlag[0] = true;
  }

  delay(100);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[1];

  if(abs(difference)<10)
  {
    greenFlag[1] = true;
  }  

  delay(100);
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency = pulseIn(sensorOut, LOW);
  difference = frequency - green[2];

  if(abs(difference)<10)
  {
    greenFlag[2] = true;
  }

  if (greenFlag[0] && greenFlag[1] && greenFlag[2])
  {
    Serial.println("It is green");
  }
  else
  {
    Serial.println("UNKOWN");
  }

  greenFlag[0] = false; greenFlag[1] = false; greenFlag[2] = false;
  delay(1000);
}

void goStraight()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA, 165);
  delay(2000);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  goStraight();
  delay(1000);
}
