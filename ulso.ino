int trigPin1=13;
int echoPin1=12;
#define leftmot1 8 
#define leftmot2 9 
#define rightmot1 7
#define rightmot2 6
void setup() {
Serial.begin(9600);
pinMode(echoPin1, INPUT);
pinMode(trigPin1, OUTPUT);
pinMode(leftmot1,OUTPUT);
pinMode(leftmot2,OUTPUT);
pinMode(rightmot1,OUTPUT);
pinMode(rightmot2,OUTPUT); 
}

void loop() {
   long a,duration1;
   digitalWrite(trigPin1, HIGH);
   delayMicroseconds(1000);
   digitalWrite(trigPin1,LOW);
   duration1=pulseIn(echoPin1,HIGH);
   a=(duration1/2)/29.1;
   Serial.print(a);
   Serial.print("...");
   //delay(20);
   
   if(a<15 || a>2300  )
  {
    Serial.print("detected");
    halt();
    delay(300);
    reverse();
    delay(500);
    
    //delay(1000);
    right();
    
  }
  else
   {
            Serial.println("not detected");
              forward();
                  
   }

}
         
  


void forward()
{
  
                  digitalWrite(leftmot1, HIGH);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,HIGH);
                  digitalWrite(rightmot2,LOW);
}

void halt()
{
          digitalWrite(leftmot1, LOW);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,LOW);
                  digitalWrite(rightmot2,LOW);
}
  void right()
  {
                digitalWrite(leftmot1, HIGH);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,LOW);
                  digitalWrite(rightmot2,LOW);
                  delay(500);
  }

  void reverse()
  {

    digitalWrite(leftmot1, LOW);
                  digitalWrite(leftmot2, HIGH);
                  digitalWrite(rightmot1,LOW);
                  digitalWrite(rightmot2,HIGH);
    
  }
