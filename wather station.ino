#include <Adafruit_GFX.h>  // Include core graphics library
#include <BoltIoT-Arduino-Helper.h>//Include boltiot library
#include "U8glib.h"

int lm35_sensor_value;
int intensity;
int cel ;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);//Specify the name of lcd which we have used 

String getAnalogData(String *data){
  String retval;
  retval=cel;
  return retval;
}
String getLightData(String *lightdata){
  String retval;
  retval=intensity;
  return retval;
}

///////////////////////////////Hex code of bitmap image used on oled display/////////////////////////////

/////////////////////////function for displaying temperature/////////
void setup() {
  Serial.begin(9600);
   boltiot.begin(6,7); //Initialize the Bolt interface over software serial uart.
       //In this example Tx pin of Bolt is connected to pin 6 of Arduino
       //and Rx pin of Bolt is connected to pin 7 of Arduino
   boltiot.setCommandString("GetAnalogData",getAnalogData);
   boltiot.setCommandString("GetAnalogData",getLightData);
   
  pinMode(0,INPUT); //Set pin 2 as input. We will send this pin's state as the data to the Bolt Cloud
  pinMode(A1,INPUT);
}

/////////////////////////function for displaying temperature/////////
void draw(void) 
{
u8g.drawBitmapP( 0, 0, 8, 64, cel);////////for drawing bitmap of size 64*64 and location is x=0,y=0
   
char s[2] = " ";
  u8g.setFont(u8g_font_fur35n);/// declaring font name 
u8g.setPrintPos(67, 50); ///position for printing temprature
    u8g.println(cel);//printing temp.
 u8g.setFont(u8g_font_osr18);
      s[0] = 176;///for displaying degree sign on oled disaplay
      u8g.drawStr(116, 28, s);
      }



void loop() {
  lm35_sensor_value = analogRead(A0);
   int mv = ( lm35_sensor_value/1024.0)*5000; 
    cel = mv/10;
 // float farh = (cel*9)/5 + 32;  
  intensity = analogRead(A1) ;
  
 Serial.print("TEMPRATURE = ");
 Serial.print(cel);
 Serial.print("*C");
 Serial.print(",");
 Serial.print("LIGHT INTENSITY = ");
Serial.print(intensity);
Serial.println( );

 delay(1000);
 

  ///////////////////////////////picture loop//////////////////
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  delay(1000);
 //boltiot.processPushDataCommand(cel);
  boltiot.CheckPoll(analogRead(0),analogRead(A1));
  boltiot.CheckPoll(analogRead(A1));//Send data to the Bolt Cloud, when the Bolt polls the Arduino for data.
                                   //This function needs to be called regularly. Calling the CheckPoll function once every seconds is required
}
