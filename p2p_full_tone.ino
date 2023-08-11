/*

using tone to calculate the resulted signal

*/

int kilo = 1000;
int F = 15*kilo;
int datarate = kilo;

int boudrate = 9600;
int pinhigh = 6;
int pinlow = 7;

void setup() {
  Serial.begin(boudrate);
  while (!Serial);
  pinMode(pinlow, OUTPUT);  
  pinMode(pinhigh, OUTPUT);

  //initiate pins
  digitalWrite(pinhigh, LOW);
  digitalWrite(pinlow, LOW);
}

void loop() {
  if (Serial.available() > 0) 
  {
    int inByte = Serial.read();
    // Serial.println(inByte);

  // int bits[] = {1,1,1,1,1,1,1,1};
  // int bits[] = {1,0,1,0,1,0,1,0};
    Serial.println();
    for (int i = 0; i < 8; i++) {
      int bit = bitRead(inByte, i);
      Serial.print(bit);
      // int bit = bits[i];
      // to calculate the note duration, take one second divided by the note type.
      double delayTime = 1000000 / (F * 2);

      int repeats = F / datarate;
      if (bit == 1)
      {  
        for (int i = 0; i < repeats; i++) 
        {
          digitalWrite(pinlow, LOW);
          digitalWrite(pinhigh, HIGH);
          delayMicroseconds(delayTime);

          digitalWrite(pinhigh, LOW);
          digitalWrite(pinlow, HIGH);
          delayMicroseconds(delayTime); 
        }
        digitalWrite(pinhigh, LOW);
        digitalWrite(pinlow, LOW);
      }
      else
      {
        int timedelay = 2*delayTime*repeats;
        delayMicroseconds(timedelay);
        digitalWrite(pinhigh, LOW);
        digitalWrite(pinlow, LOW);
      }
    }
  }
}