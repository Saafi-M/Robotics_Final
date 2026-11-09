#include <SD.h>
File myFile;
const int CSPin = 4;
const int In1 = 5;
const int In2 = 6;
const int In3 = 9;
const int In4 = 11;
const int EnA = 3;
const int EnB = 10;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
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
}

void goStraight()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(EnA, 165);
  analogWrite(EnB, 165);
  delay(2000);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  goStraight();
  delay(1000);
}
