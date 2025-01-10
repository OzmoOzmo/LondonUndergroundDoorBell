/*
 London Underground Doorbell
 
 Waits for Door Button press - 
 Activates Wireless Doorbell
 Then does an animation
 
 Ambrose Clarke /08/2022
 
 8 Led Lights are on Pins 2,3,4,5,A3,A2,A1,A0
 Doorbell Button listens on pin A5
 
 The Wireless doorbell transmitter Press is also connected to A5 - so it triggers too.
 The Wireless doorbell is powered from the 3v output of the Arduino Nano
 
 */

int brightness1 = 0;    // how bright the LED is
int brightness2 = 0;    // how bright the LED is
int fadeAmount1 = 1;    // how many points to fade the LED by
int fadeAmount2 = 2;    // how many points to fade the LED by

#define s0 2
#define s1 3
#define s2 4
#define s3 5

#define s4 A3
#define s5 A2
#define s6 A1
#define s7 A0

#define b0 A5

const int normalBright = 100;

const int speed = 12; //10 is slow 20 is fast animation


void setAll(int value){
  digitalWrite(s0, value);
  digitalWrite(s1, value);
  digitalWrite(s2, value);
  digitalWrite(s3, value);
  digitalWrite(s4, value);
  digitalWrite(s5, value);
  digitalWrite(s6, value);
  digitalWrite(s7, value);
}

// the setup routine runs once when you press reset:
void setup()  { 
  Serial.begin(115200);
  
  pinMode(s0, OUTPUT);     
  pinMode(s1, OUTPUT);     
  pinMode(s2, OUTPUT);     
  pinMode(s3, OUTPUT);     
  pinMode(s4, OUTPUT);     
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
  pinMode(s7, OUTPUT);
  pinMode(b0, INPUT_PULLUP);

  setAll(HIGH);
} 

void fadeToOff()
{
  for (int duty=0; duty<100; duty++)
  {
    for (int y=0;y<speed;y++)
    {
      setAll(HIGH);
      delayMicroseconds(1000 - duty*10);
      setAll(LOW);
      delayMicroseconds(duty*10); // Approximately 10% duty cycle @ 1KHz
    }
  }
}

void fadeToOn()
{
  for (int duty=0; duty<100; duty++)
  {
    for (int y=0;y<speed;y++)
    {
      setAll(LOW);
      delayMicroseconds(1000 - duty*10); //100%..90%.. % duty cycle @ 1KHz
      setAll(HIGH);
      delayMicroseconds(duty*10); // 
    }
  }
}

void loopAnimation(int nTimes)
{
    for (int n=0;n<nTimes;n++){
      bool bNotLast = !(n==2);
      digitalWrite(s0, HIGH);
      delayEx(10); 
      if (bNotLast) digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      delayEx(10); 
      if (bNotLast) digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
      delayEx(10); 
      if (bNotLast) digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      delayEx(10);
      if (bNotLast)  digitalWrite(s3, LOW);
      digitalWrite(s4, HIGH);
      delayEx(10);
      if (bNotLast)  digitalWrite(s4, LOW);
      digitalWrite(s5, HIGH);
      delayEx(10);
      if (bNotLast)  digitalWrite(s5, LOW);
      digitalWrite(s6, HIGH);
      delayEx(10);
      if (bNotLast)  digitalWrite(s6, LOW);
      digitalWrite(s7, HIGH);
      delayEx(10);
      if (bNotLast)  digitalWrite(s7, LOW);
  }
}

void brightness()
{
  if(normalBright == 100)
    return; //want full brightness
    
  setAll(HIGH); //on for (brightness)% of time... 
  delayMicroseconds(normalBright*10); // Approximately 10% duty cycle @ 1KHz
  setAll(LOW); //off for (100-brightness)% of time... 
  //delayMicroseconds(1000 - normalBright*10);

}

// the loop routine runs over and over again forever:
void loop()
{ 
  brightness();
  
  int btn = digitalRead(b0);
  if (btn == HIGH){
    delayEx(1); 
    return;
  }
 
  loopAnimation(3);

  fadeToOff();
  fadeToOn();
}

void delayEx(int d)
{
  for(int n=0;n<d;n++)
  {
    // wait for 30 milliseconds to see the dimming effect    
    delay(7);
  }    
}
