//#include <TinyGPS.h>

#include<TinyGPS++.h>
#include<SoftwareSerial.h>

float lati=28.5458;
float lon=100.1703;
unsigned long Distance_To_Home;  
int GPS_Course; 
SoftwareSerial gpsSerial(3,4);
TinyGPSPlus gps;
#define leftmot1 8 
#define leftmot2 9 
#define rightmot1 7
#define rightmot2 11
void forward();
void halt();
void SlowLeftTurn();
void SlowRightTurn();
void setup(){
  Serial.begin(9600);
  Serial.println("The GPS received signal:");
  gpsSerial.begin(9600);
  
}
void loop(){
  //while(gpsSerial.available()){
    
   //long Home_LAT = gps.location.lat();                      
   //long Home_LON = gps.location.lng();                    
//    Serial.println(gps.satellites.value);
Serial.println(gps.location.lat());
Serial.println(gps.location.lng());
Serial.println("available");
//Serial.println("LAT:");
//Serial.println(Home_LAT);
//Serial.println("LON:");
//Serial.println(Home_LON);
    gps.encode(gpsSerial.read());
    //if(gps.encode(gpsSerial.read()!=NULL))
    //{
      Serial.print("LAT=");
      Serial.println(gps.location.lat(),6);
      Serial.print("LONG=");
      Serial.println(gps.location.lng(),6);
      Serial.print("ALT=");
      Serial.println(gps.altitude.meters());
      printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
    Distance_To_Home = (unsigned long)TinyGPSPlus::distanceBetween(lati,lon, gps.location.lat(), gps.location.lng());      //Query Tiny GPS for Distance to Destination
  GPS_Course = TinyGPSPlus::courseTo(lati,lon,gps.location.lat(),gps.location.lng());                               //Query Tiny GPS for Course to Destination 
  
    if (Distance_To_Home == 0)                                   // If the Vehicle has reached it's Destination, then Stop
        {
        halt();                                              // Stop the robot after each waypoint is reached
        Serial.println("You have arrived!");                    // Print to Bluetooth device - "You have arrived"          
       // ac++;                                                    // increment counter for next waypoint
        //break;              
        }
                                                                 // go to next waypoint
    else if (abs(GPS_Course) <= 15)                               // If GPS Course and the Compass Heading are within x degrees of each other then go Forward                                                                  
                                                                  // otherwise find the shortest turn radius and turn left or right  
       forward();                                               
       
    else 
         {                                                       
            int x = (GPS_Course - 360);                           // x = the GPS desired heading - 360
           // int y = (compass_heading - (x));                      // y = the Compass heading - x
            int z = (x- 360);                                    // z = y - 360
            
            if ((z <= 180) && (z >= 0))                           // if z is less than 180 and not a negative value then turn left otherwise turn right
                  { SlowLeftTurn();  }
             else { SlowRightTurn(); }
         }
    }
  //}

 void halt()
  {
                   digitalWrite(leftmot1, LOW);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,LOW);
                  digitalWrite(rightmot2,LOW); 
  }                    

  void forward()
 {
                  //digitalWrite(12,HIGH);
                  digitalWrite(leftmot1, HIGH);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,HIGH);
                  digitalWrite(rightmot2,LOW);
 }

  void SlowRightTurn()
 {
                 analogWrite(leftmot1, 125);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,LOW);
                  digitalWrite(rightmot2,LOW);
                 // delay(3000);
 }

 void SlowLeftTurn()
  {
                 digitalWrite(leftmot1, LOW);
                  digitalWrite(leftmot2, LOW);
                  digitalWrite(rightmot1,HIGH);
                  digitalWrite(rightmot2,LOW);
                 // delay(3000);
  }
  static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (gpsSerial.available())
      gps.encode(gpsSerial.read());
  } while (millis() - start < ms);
}
