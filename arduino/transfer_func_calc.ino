/*

using tone to calculate the resulted signal

*/

int kilo = 1000;
int F = 17*kilo;          // carrier wave

// int Fs[] = {kilo, 5*kilo, 7.5*kilo, 10*kilo, 11*kilo, 
//             12*kilo, 12.2*kilo, 12.4*kilo, 12.6*kilo, 12.8*kilo, 
//             13*kilo, 13.2*kilo, 13.4*kilo, 13.6*kilo, 13.8*kilo, 
//             14*kilo, 14.2*kilo, 14.4*kilo, 14.6*kilo, 14.8*kilo, 
//             15*kilo, 15.2*kilo, 15.4*kilo, 15.6*kilo, 15.8*kilo,
//             16*kilo, 17*kilo, 18*kilo, 19*kilo, 20*kilo, 
//             25*kilo, 30*kilo, 40*kilo, 50*kilo, 100*kilo};
int Fs[] = {F, F, F, F, F, F, F, F, F, F, F, F};
// int Fs[] = {13*kilo, 13.2*kilo, 13.4*kilo, 13.6*kilo, 13.8*kilo, 
//             14*kilo, 14.2*kilo, 14.4*kilo, 14.6*kilo, 14.8*kilo, 
//             15*kilo, 15.2*kilo, 15.4*kilo, 15.6*kilo, 15.8*kilo,
//             16*kilo, 17*kilo, 18*kilo, 19*kilo, 20*kilo, 
//             25*kilo, 30*kilo, 40*kilo, 50*kilo, 100*kilo};

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
  int bits[] = {1,1,0,1,1,0,1,0}; // bits to transmit

  for (int j = 0; j < sizeof(Fs); j++) {

    int F = Fs[j];
    Serial.println(F);

    for (int k = 0; k < kilo; k++) {

      for (int i = 0; i < 8; i++) {
        int bit = bits[i];

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

    delay(200);

    }
  }
}