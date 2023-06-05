#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Blynk.h"

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

#define BLYNK_TEMPLATE_ID "TMPL3i1dpmBtQ"
#define BLYNK_TEMPLATE_NAME "Oldage Healthcare System"
#define BLYNK_AUTH_TOKEN "YIsi4aVeszR9LdLhxoCxbTY4tTpXtJS4"

//String BLYNK_TEMPLATE_ID = "TMPL3iyJ6LzI2";
//String BLYNK_TEMPLATE_NAME = "PETROLPUMP";
//String BLYNK_AUTH_TOKEN = "WrByiymasmLeI_DAWfRtRjXXbclDz6U7";

//char ssid[] = "Oldage";
//char pass[] = "12345678";
char ssid[] = "Redmi 9i";
char pass[] = "ding ding";
char auth[] = "YIsi4aVeszR9LdLhxoCxbTY4tTpXtJS4";

WidgetTerminal DiabeticPatientDiet(V5);
WidgetTerminal ArtheitisPatientDiet(V6);
WidgetTerminal HeartPatientDiet(V7);

WidgetTerminal DiabeticPatientMed(V8);
WidgetTerminal ArtheitisPatientMed(V9);
WidgetTerminal HeartPatientMed(V10);

MAX30105 particleSensor;

unsigned long prevDibDiet1,prevDibDiet2,prevDibDiet3,prevDibDiet4,prevDibDiet5;
unsigned long  prevArthDiet1,prevArthDiet2,prevArthDiet3,prevArthDiet4,prevArthDiet5,prevArthDiet6;
unsigned long prevHerDiet1,prevHerDiet2,prevHerDiet3,prevHerDiet4,prevHerDiet5,prevHerDiet6,prevHerDiet7;
bool flagArthDiet1,flagArthDiet2,flagArthDiet3,flagArthDiet4,flagArthDiet5,flagArthDiet6;
bool flagDibDiet1,flagDibDiet2,flagDibDiet3,flagDibDiet4,flagDibDiet5,flagDibDiet6;
bool flagHerDiet1,flagHerDiet2,flagHerDiet3,flagHerDiet4,flagHerDiet5,flagHerDiet6,flagHerDiet7;

unsigned long prevDibMed1,prevDibMed2,prevDibMed3,prevDibMed4,prevDibMed5,prevDibMed6,prevDibMed7,prevDibMed8,prevDibMed9,prevDibMed10,prevDibMed11,prevDibMed12;
unsigned long  prevArthMed1,prevArthMed2,prevArthMed3,prevArthMed4,prevArthMed5,prevArthMed6,prevArthMed7,prevArthMed8,prevArthMed9,prevArthMed10,prevArthMed11,prevArthMed12;
unsigned long prevHerMed1,prevHerMed2,prevHerMed3,prevHerMed4,prevHerMed5,prevHerMed6,prevHerMed7,prevHerMed8,prevHerMed9,prevHerMed10,prevHerMed11,prevHerMed12;
int flagArthMed1=2,flagArthMed2=2,flagArthMed3=2,flagArthMed4=2,flagArthMed5=2,flagArthMed6=2,flagArthMed7=2,flagArthMed8=2,flagArthMed9=2,flagArthMed10=2,flagArthMed11=2,flagArthMed12=2;
int flagDibMed1=2,flagDibMed2=2,flagDibMed3=2,flagDibMed4=2,flagDibMed5=2,flagDibMed6=2,flagDibMed7=2,flagDibMed8=2,flagDibMed9=2,flagDibMed10=2,flagDibMed11=2,flagDibMed12=2;
int flagHerMed1=2,flagHerMed2=2,flagHerMed3=2,flagHerMed4=2,flagHerMed5=2,flagHerMed6=2,flagHerMed7=2,flagHerMed8=2,flagHerMed9=2,flagHerMed10=2,flagHerMed11=2,flagHerMed12=2;

int flagDib1=0,flagDib2=0,flagDib3=0,flagDib4=0;
int flagArth1=0,flagArth2=0,flagArth3=0,flagArth4=0;
int flagHer1=0,flagHer2=0,flagHer3=0,flagHer4=0;

int dib,hb,arth;
int x, y, a, b, i;
String str, temp;
int diet=0;
BLYNK_WRITE(V8)
{
dib = param.asInt(); 
}
BLYNK_WRITE(V10)
{
hb = param.asInt();   
}
BLYNK_WRITE(V9)
{
arth= param.asInt(); 
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
   Blynk.begin(auth, ssid, pass,"blynk.cloud",80);
 
int oxy,hb;
long irValue;
Serial.println("Initializing...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
 //     Blynk.virtualWrite(V10, "TEST");
}

void loop() {
  Blynk.run();
  ////////////////serial communication/////////////////////////////////////
     if (Serial.available())
  {
    str = Serial.readStringUntil('#');
   
    if (str[0] == 'D')
    {
     // Serial.print("x = ");
      i = 1;
      temp = "";
      while (str[i] != '\0')
      {
        temp = temp + str[i];
        i++;
      }
    //  Serial.println(temp);
      x = temp.toInt();
      //Serial.print("a= ");
      //Serial.println(x);
       if(x==1)
      {
        Blynk.virtualWrite(V4, "FALL DETECTED");
        Serial.println("fall detected");
      }
      if(x==0)
      {
         Blynk.virtualWrite(V4, "                      ");
      }
    }
  }
  //////////////////SENSOR DATA/////////////////////////////////////

long irValue = particleSensor.getIR();
  irValue = particleSensor.getRed();
 Serial.print("IR : ");
    Serial.print(irValue);
    Serial.print("   ");
int hb = map(irValue , 150,28000, 0, 100);
      Serial.print("IR : ");
   
    Serial.print("HB : ");
    Serial.print(hb);
    Serial.print("   ");
  Blynk.virtualWrite(V1,hb);
  
//     if(hb<60||hb>110)//normal range 60 to 100
//  {
//     
// 
//    Blynk.virtualWrite(V0,"abnormal hb");
//   // Blynk.virtualWrite(V1,hb);
//
//  }
//  else
//  {
//    Blynk.virtualWrite(V0,"normal hb         ");
//   // Blynk.virtualWrite(V1,hb);
//
//  }
   
    delay(1000);
 
 int oxy = map(irValue , 150, 28000, 0, 98);
    Serial.print("OXY : ");
    Serial.println(oxy);
    Serial.print("   ");
     Blynk.virtualWrite(V3,oxy);
    delay(1000);
   
//  if(oxy<75||oxy>100)//normal range 75 to 100
//  {
//   
//    Blynk.virtualWrite(V2,"abnormal oxygen");
//  //  Blynk.virtualWrite(V3,oxy);
//  }
//  else
//  {
//      Blynk.virtualWrite(V2,"normal oxygen    ");
// //   Blynk.virtualWrite(V3,oxy);
//
//  }

///////////////////////////DIET PLAN//////////////////////////////////////////
DiabeticPatientDietFn();
ArtheitisPatientDietFn();
HeartPatientDietFn();

////////////////////////////MED REM SYS///////////////////////////////////////
DiabeticPatientMedFn();
ArtheitisPatientMedFn();
HeartPatientMedFn();

}

void DiabeticPatientDietFn()
{
    
   if ((millis()-prevDibDiet1)>10000 && flagDibDiet1==false)///8 oclk
   {
       DiabeticPatientDiet.println(F("8.00 am : Breakfast Wheat tea or coffee without sugar"));
       prevDibDiet1=millis();
       flagDibDiet1=true;
      
   }
   
   else if ((millis()-prevDibDiet2)>40000 && flagDibDiet2 == false)///11 oclk
   {
       DiabeticPatientDiet.println(F("11.00 am : Salads roti"));
       prevDibDiet2=millis();
       flagDibDiet2=true;
      
   }
   else if ((millis()-prevDibDiet3)>70000 && flagDibDiet3==false)/// 2oclk
   {
       DiabeticPatientDiet.println(F("2.00 pm : Lunch"));
       prevDibDiet3=millis();
      flagDibDiet3=true;
      
   }
   else if ((millis()-prevDibDiet4)>90000 && flagDibDiet4==false)///4oclk
   {
       DiabeticPatientDiet.println(F("4.00 pm : Fruit"));
prevDibDiet4=millis();
flagDibDiet4=true;

   }
   else if ((millis()-prevDibDiet5)>130000 )///8 oclk
   {
       DiabeticPatientDiet.println(F("8.00 pm : Dinner"));
    prevDibDiet5=millis();
 
   }
}



void ArtheitisPatientDietFn()
{
   if ((millis()-prevArthDiet1)>20000 &&flagArthDiet1 == false)///9 oclk
   {
       ArtheitisPatientDiet.println(F("9.00 am : Milk egg + Breakfast"));
       flagArthDiet1=true;
       prevArthDiet1=millis();
   }
   
   else if ((millis()-prevArthDiet2)>40000 && flagArthDiet2== false)///11 oclk
   {
       ArtheitisPatientDiet.println(F("11.00 am : ONE Portion fruits"));
         flagArthDiet2=true;
       prevArthDiet2=millis();
   }
   else if ((millis()-prevArthDiet3)>60000 && flagArthDiet3== false)/// 1oclk
   {
       ArtheitisPatientDiet.println(F("1.00 pm :BrownRice/Roti/Salad"));
         flagArthDiet3=true;
       prevArthDiet3=millis();
   }
   else if ((millis()-prevArthDiet4)>95000 && flagArthDiet4== false)///4.30oclk
   {
         ArtheitisPatientDiet.println(F("4.30 pm : Fruit"));
         flagArthDiet4=true;
         prevArthDiet4=millis();
   }
   else if ((millis()-prevArthDiet5)>125000 && flagArthDiet5== false)///7.30 oclk
   {
         ArtheitisPatientDiet.println(F("7.30 pm : Wheat food items + veg/non-veg curry"));
         flagArthDiet5=true;
         prevArthDiet5=millis();
   }
   else if ((millis()-prevArthDiet6)>140000 && flagArthDiet6== false)///9.00 oclk
   {
         ArtheitisPatientDiet.println(F("9.00 pm : Fruit"));
         flagArthDiet6=true;
         prevArthDiet6=millis();
   }
}


void HeartPatientDietFn()
{
   if ((millis()-prevHerDiet1)>5000 &&  flagHerDiet1== false)///7 oclk
   {
       HeartPatientDiet.println(F("7.00 am : Veg+(oats/idly/dosa/roti)"));
       flagHerDiet1=true;
       prevHerDiet1=millis();
   }
   
   else if ((millis()-prevHerDiet2)>30000 && flagHerDiet2== false)///10 oclk
   {
       HeartPatientDiet.println(F("10.00 am : Fruits/Salads"));
         flagHerDiet2=true;
       prevHerDiet2=millis();
   }
   else if ((millis()-prevHerDiet3)>55000 && flagHerDiet3== false)/// 12.30oclk
   {
       HeartPatientDiet.println(F("12.30 pm : Brown Rice, veg or non-veg "));
         flagHerDiet3=true;
prevHerDiet3=millis();
   }
   else if ((millis()-prevHerDiet4)>80000 && flagHerDiet4== false)///2.00oclk
   {
       HeartPatientDiet.println(F("4.30 pm : Sprouded food + green tea , salads"));
         flagHerDiet4=true;
prevHerDiet4=millis();
   }
   else if ((millis()-prevHerDiet5)>105000 && flagHerDiet5== false)///4.30 oclk
   {
       HeartPatientDiet.println(F("8.30 pm : Wheat food"));
         flagHerDiet5=true;
prevHerDiet5=millis();
   }
//   else if ((millis()-prevHerDiet6)>145000 && flagHerDiet6== false)///8.30 oclk
//   {
//       HeartPatientDiet.println(F("Wheat food"));
//         flagHerDiet6=true;
//       prevHerDiet6=millis();
//   }
//   else if ((millis()-prevHerDiet7)>150000 && flagHerDiet7== false)///8.30 oclk
//   {
//       HeartPatientDiet.println(F("Wheat food"));
//         flagHerDiet7=true;
//       prevHerDiet7=millis();
//   }
}

void DiabeticPatientMedFn()
{
   if ((millis()-prevDibMed1)>12000 && flagDibMed1==2)///8.25 oclk
   {
       DiabeticPatientMed.println(F("8.25 AM : Medicine Alert"));
       prevDibMed1=millis();
       flagDibMed1=1;
   }
   else if ((millis()-prevDibMed2)>14000 && flagDibMed2== 2&& dib == 0)///8.30 oclk
   {
       DiabeticPatientMed.println(F("8.30 AM : Medicine Time"));
       prevDibMed2=millis();
       flagDibMed2=1;
   }

      else if ((millis()-prevDibMed3)>16000 && flagDibMed3== 2 && dib == 0)///8.35 oclk
   {
       DiabeticPatientMed.println(F("8.35 AM : Medicine Time"));
       prevDibMed3=millis();
       flagDibMed3=1;
   }

    else if ((millis()-prevDibMed4)>18000 && flagDibMed4== 2 && dib == 0)///8.40 oclk
   {
       DiabeticPatientMed.println(F("8.40 AM : Medicine Time"));
       prevDibMed4=millis();
    //   flagDibMed4=1;
       flagDib1=1;       
   }



     else if ((millis()-prevDibMed5)>72000 && flagDibMed5== 2)///2.25 oclk
   {
      DiabeticPatientMed.println(F("2.25 PM : Medicine Alert"));
       prevDibMed5=millis();
       flagDibMed5=1;
   }
   else if ((millis()-prevDibMed6)>74000 && flagDibMed6== 2)///8.30 oclk
   {
       DiabeticPatientMed.println(F("2.30 PM : Medicine Time"));
       prevDibMed6=millis();
       flagDibMed6=1;
   }

      else if ((millis()-prevDibMed7)>76000 && flagDibMed7== 2 && dib == 0)///8.35 oclk
   {
      DiabeticPatientMed.println(F("2.35 PM : Medicine Time"));
       prevDibMed7=millis();
       flagDibMed7=1;
   }

    else if ((millis()-prevDibMed8)>78000 && flagDibMed8== 2 && dib == 0)///8.40 oclk
   {
       DiabeticPatientMed.println(F("2.40 PM : Medicine Time"));
       prevDibMed8=millis();
   //flagDibMed2=1;
       flagDib2=1;       
   }


        else if ((millis()-prevDibMed9)>132000 && flagDibMed9== 2)///2.25 oclk
   {
     DiabeticPatientMed.println(F("8.25 PM : Medicine Alert"));
       prevDibMed9=millis();
       flagDibMed9=1;
   }
   else if ((millis()-prevDibMed10)>134000 && flagDibMed10== 2)///2.30 oclk
   {
       DiabeticPatientMed.println(F("8.30 PM : Medicine Time"));
       prevDibMed10=millis();
       flagDibMed10=1;
   }

      else if ((millis()-prevDibMed11)>136000 && flagDibMed11== 2 && dib == 0)///2.35 oclk
   {
      DiabeticPatientMed.println(F("8.35 PM : Medicine Time"));
       prevDibMed11=millis();
       flagDibMed11=1;
   }

    else if ((millis()-prevDibMed12)>138000 && flagDibMed12== 2 && dib == 0)///2.40 oclk
   {
       DiabeticPatientMed.println(F("8.40 PM : Medicine Time"));
       prevDibMed12=millis();
//       flagDibMed2=true;
       flagDib3=1;       
   }

   if((flagDib1==1)&&(dib==1))
   {
     flagDibMed1=1;
     prevDibMed1=0,prevDibMed2=0,prevDibMed3=0,prevDibMed4=0;
     flagDib1=0;
   }
   if((flagDib2==1)&&(dib==1))
   {
     flagDibMed2=1;
     flagDib2=0;
   }
   if((flagDib3==1)&&(dib==1))
   {
     flagDibMed3=1;
     flagDib3=0;
   }
   if((flagDib4==1)&&(dib==1))
   {
     flagDibMed4=1;
     flagDib4=0;
   }
}  
 
void ArtheitisPatientMedFn()
{
   if ((millis()-prevArthMed1)>22000 && flagArthMed1==2)///8.25 oclk
   {
       ArtheitisPatientMed.println(F("9.25 AM : Medicine Alert"));
       prevArthMed1=millis();
       flagArthMed1=1;
   }
   else if ((millis()-prevArthMed2)>24000 && flagArthMed2== 2&& arth== 0)///8.30 oclk
   {
       ArtheitisPatientMed.println(F("9.30 AM : Medicine Time"));
       prevArthMed2=millis();
       flagArthMed2=1;
   }

      else if ((millis()-prevArthMed3)>26000 && flagArthMed3== 2 && arth == 0)///8.35 oclk
   {
       ArtheitisPatientMed.println(F("9.35 AM : Medicine Time"));
       prevArthMed3=millis();
       flagArthMed3=1;
   }

    else if ((millis()-prevArthMed4)>28000 && flagArthMed4== 2 && arth == 0)///8.40 oclk
   {
       ArtheitisPatientMed.println(F("9.40 AM : Medicine Time"));
      prevArthMed4=millis();
    //   flagDibMed4=1;
       flagArth1=1;       
   }



     else if ((millis()-prevArthMed5)>62000 && flagArthMed5== 2)///2.25 oclk
   {
      ArtheitisPatientMed.println(F("1.25 PM : Medicine Alert"));
       prevArthMed5=millis();
       flagArthMed5=1;
   }
   else if ((millis()-prevArthMed6)>64000 && flagArthMed6== 2)///8.30 oclk
   {
       ArtheitisPatientMed.println(F("1.30 PM : Medicine Time"));
       prevArthMed6=millis();
      flagArthMed6=1;
   }

      else if ((millis()-prevArthMed7)>66000 && flagArthMed7== 2 && arth == 0)///8.35 oclk
   {
      ArtheitisPatientMed.println(F("1.35 PM : Medicine Time"));
       prevArthMed7=millis();
      flagArthMed7=1;
   }

    else if ((millis()-prevArthMed8)>68000 && flagArthMed8== 2 && arth == 0)///8.40 oclk
   {
       ArtheitisPatientMed.println(F("1.40 PM : Medicine Time"));
       prevArthMed8=millis();
   //flagDibMed2=1;
      flagArth2=1;       
   }


        else if ((millis()-prevArthMed9)>126000 && flagArthMed9== 2)///2.25 oclk
   {
      ArtheitisPatientMed.println(F("7.55 PM : Medicine Alert"));
       prevArthMed9=millis();
      flagArthMed9=1;
   }
   else if ((millis()-prevArthMed10)>127000 && flagArthMed10== 2)///2.30 oclk
   {
       ArtheitisPatientMed.println(F("8.00 PM : Medicine Time"));
      prevArthMed10=millis();
       flagArthMed10=1;
   }

      else if ((millis()-prevArthMed11)>128000 && flagArthMed11== 2 && arth == 0)///2.35 oclk
   {
      ArtheitisPatientMed.println(F("8.05 PM : Medicine Time"));
       prevArthMed11=millis();
      flagArthMed11=1;
   }

    else if ((millis()-prevArthMed12)>129000 && flagArthMed12== 2 && arth == 0)///2.40 oclk
   {
       ArtheitisPatientMed.println(F("8.10 PM : Medicine Time"));
       prevArthMed12=millis();
//       flagDibMed2=true;
     flagArth3=1;       
   }

   if((flagArth1==1)&&(arth==1))
   {
     flagArthMed1=1;
     prevArthMed1=0,prevArthMed2=0,prevArthMed3=0,prevArthMed4=0;
     flagArth1=0;
   }
   if((flagArth2==1)&&(arth==1))
   {
    flagArthMed2=1;
   flagArth2=0;
   }
   if((flagArth3==1)&&(arth==1))
   {
     flagArthMed3=1;
     flagArth3=0;
   }
   if((flagArth4==1)&&(arth==1))
   {
     flagArthMed4=1;
     flagArth4=0;
   }
}  

 
void HeartPatientMedFn()
{
  Serial.println("test");
   if ((millis()-prevHerMed1)>5500 && flagHerMed1==2)///8.25 oclk
   {
      Serial.println("test");
      HeartPatientMed.println(F("7.25 AM : Medicine Alert"));
    //  Blynk.virtualWrite(V10, "8.25 AM : Medicine Alert");
      prevHerMed1=millis();
      flagHerMed1=1;
   }
   else if ((millis()-prevHerMed2)>5700 && flagHerMed2== 2&& hb == 0)///8.30 oclk
   {
      Serial.println("test");
      HeartPatientMed.println(F("7.30 AM : Medicine Time"));
   //   Blynk.virtualWrite(V10, "8.30 AM : Medicine Time");
       prevHerMed2=millis();
      flagHerMed2=1;
   }

      else if ((millis()-prevHerMed3)>5900 && flagHerMed3== 2 && hb == 0)///8.35 oclk
   {
      Serial.println("test");
       HeartPatientMed.println(F("7.35 AM : Medicine Time"));
      //    Blynk.virtualWrite(V10, "8.35 AM : Medicine Time");
      prevHerMed3=millis();
       flagHerMed3=1;
   }

    else if ((millis()-prevHerMed4)>6000  && flagHerMed4== 2 && hb == 0)///8.40 oclk
   {
      Serial.println("test");
       HeartPatientMed.println(F("7.40 AM : Medicine Time"));
      //    Blynk.virtualWrite(V10, "8.40 AM : Medicine Time");
       prevHerMed4=millis();
    //   flagDibMed4=1;
      flagHer1=1;       
   }



     else if ((millis()-prevHerMed5)>56000 && flagHerMed5== 2)///2.25 oclk
   {
      Serial.println("test");
     HeartPatientMed.println(F("12.55 PM : Medicine Alert"));
    //    Blynk.virtualWrite(V10, "2.25 PM : Medicine Alert");
     prevHerMed5=millis();
       flagHerMed5=1;
   }
   else if ((millis()-prevHerMed6)>57000 && flagHerMed6== 2)///8.30 oclk
   {
      Serial.println("test");
       HeartPatientMed.println(F("1.00 PM : Medicine Time"));
       //   Blynk.virtualWrite(V10, "2.30 PM : Medicine Time");
       prevHerMed6=millis();
       flagHerMed6=1;
   }

      else if ((millis()-prevHerMed7)>58000 && flagHerMed7== 2 && hb == 0)///8.35 oclk
   {
      Serial.println("test");
        HeartPatientMed.println(F("1.05 PM : Medicine Time"));
        //   Blynk.virtualWrite(V10, "2.35 PM : Medicine Timee");
       prevHerMed7=millis();
       flagHerMed7=1;
   }

    else if ((millis()-prevHerMed8)>59000 && flagHerMed8== 2 && hb == 0)///8.40 oclk
   {
      Serial.println("test");
         HeartPatientMed.println(F("1.10 : Medicine Time"));
         //   Blynk.virtualWrite(V10, "2.40 PM : Medicine Time");
     prevHerMed8=millis();
   //flagDibMed2=1;
     flagHer2=1;       
   }


    else if ((millis()-prevHerMed9)>110000 && flagHerMed9== 2)///2.25 oclk
   {
      Serial.println("test");
     HeartPatientMed.println(F("8.55 PM : Medicine Alert"));
      //  Blynk.virtualWrite(V10, "8.25 PM : Medicine Alert");
     prevHerMed9=millis();
     flagHerMed9=1;
   }
   else if ((millis()-prevHerMed10)>112000 && flagHerMed10== 2)///2.30 oclk
   {
      Serial.println("test");
       HeartPatientMed.println(F("9.00 PM : Medicine Time"));
      //    Blynk.virtualWrite(V10, "8.30 PM : Medicine Time");
       prevHerMed10=millis();
       flagHerMed10=1;
   }

      else if ((millis()-prevHerMed11)>114000 && flagHerMed11== 2 && hb == 0)///2.35 oclk
   {
      Serial.println("test");
      HeartPatientMed.println(F("9.05 PM : Medicine Time"));
      //   Blynk.virtualWrite(V10, "8.35 PM : Medicine Time");
      prevHerMed11=millis();
      flagHerMed11=1;
   }

    else if ((millis()-prevHerMed12)>116000 && flagHerMed12== 2 && hb == 0)///2.40 oclk
   {
      Serial.println("test");
       HeartPatientMed.println(F("9.10 PM : Medicine Time"));
      //    Blynk.virtualWrite(V10, "8.40 PM : Medicine Time");
        prevHerMed12=millis();
//       flagDibMed2=true;
       flagHer3=1;       
   }

   if((flagHer1==1)&&(hb==1))
   {
     flagHer1=1;
     prevHerMed1=0,prevHerMed2=0,prevHerMed3=0,prevHerMed4=0;
     flagHer1=0;
   }
   if((flagHer2==1)&&(hb==1))
   {
     flagHerMed2=1;
     flagHer2=0;
   }
   if((flagHer3==1)&&(hb==1))
   {
     flagHerMed3=1;
     flagHer3=0;
   }
   if((flagHer4==1)&&(hb==1))
   {
     flagHerMed4=1;
     flagHer4=0;
   }
}
