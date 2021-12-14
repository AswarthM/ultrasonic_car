///////////////////////////////////////
#include<Servo.h>
///////////////////////////////////////
Servo myservo;

///////////////////////////////////////
int trig = 8;
int echo = 9;
int mot1 = 13;
int mot2 = 12;
int mot3 = 11;
int mot4 = 10;
int distance = 0;
int distleft = 0;
int distright = 0;
int duration = 0;
///////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  myservo.attach(2);
  Serial.println("Starting");
}


void loop()
{
  if (measure()>20)
  {
    Serial.println(" going front");
    front();  
  }  

  else
  if(measure()<20)
  {
    staap();
    lookleft();
    if(distleft>20)
    {
      left();  
      delay (1000);
      staap();
      delay(1000);
    }
    else
    {
      lookright();
      if(distright>20)
      {
       right();
       delay (1000);
       staap();
       delay(1000);
      }
     else
     {
      back(); 
      delay(1000);
      staap();
      delay(1000);
     } 
    }
  }
}


int measure()
{
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
return(distance);
}


void front(){
    digitalWrite(mot1,HIGH);
    digitalWrite(mot2,LOW);
    digitalWrite(mot3,HIGH);
    digitalWrite(mot4,LOW);
    Serial.println("called front");
  }

void back(){
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,HIGH);
    digitalWrite(mot3,LOW);
    digitalWrite(mot4,HIGH);
    Serial.println("called back");
  }

void left(){
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,HIGH);
    digitalWrite(mot3,HIGH);
    digitalWrite(mot4,LOW);
    Serial.println("called left");
    delay(1000);
  }

void right(){
    digitalWrite(mot1,HIGH);
    digitalWrite(mot2,LOW);
    digitalWrite(mot3,LOW);
    digitalWrite(mot4,HIGH);
    Serial.println("called right");
    delay(1000);
  }

void staap(){
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,LOW);
    digitalWrite(mot3,LOW);
    digitalWrite(mot4,LOW);
    Serial.println("called staap");
  }  
        
void lookleft()
{
  myservo.write(180);
  delay(1000);
  distleft = measure();
  myservo.write(80);
  Serial.println("looking left");
  delay(1000);
}

void lookright()
{
  myservo.write(0);
  delay(1000);
  distright = measure();
  myservo.write(80);
  Serial.println("looking right");
  delay(1000);
}


