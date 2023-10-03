
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Stepper.h>
//#include <Wire.h>                            
//byte I2C_OnOff;                                 

const int buzzer = 3;

#define BUTTON_PIN 7
#define STEPS 32
Stepper stepper(STEPS, 8, 10, 9, 11);
int val = 0;
ThreeWire myWire(4,5,2); 
RtcDS1302<ThreeWire> Rtc(myWire);



String m;
String h;
int t;
void setup () 
{
    //Wire.begin(1);                                
    Serial.begin(9600);
    stepper.setSpeed(200);
    pinMode(buzzer, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    //Serial.println("");
    

    if (!now.IsValid())
    {
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(1000);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
  if(dt.Hour()<=12){t=(dt.Hour());}
  else{t=(dt.Hour()-12);}
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            t,
            dt.Minute(),
            dt.Second());
    Serial.println(datestring);
    m=dt.Minute();
    h=t;
    int value_Button=digitalRead(BUTTON_PIN);
    Serial.print("Button 0-true 1-false: ");
    Serial.println(value_Button);
    if (value_Button==0){
      tone(buzzer, 1000);
      delay(800);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(800);        // ...for 1sec
      stepper.step(-2100);
      delay(1000);//ave 1s/40ml
      stepper.step(2100);
      delay(1000);//change the postion from leaking then time/10mL 1000 delay, test until delay amount water and while delay, add clock 
      }

      //once a week watering (miltary time)
    //Wire.onReceive(BlinkLED);
    /*
    int waterSig=digitalRead(rec);
    Serial.print("Water read: ");
    Serial.println(rec);*/
    /*if(digitalRead(rec)==LOW){Serial.print("pass");}
    else{Serial.println("fail");}*/
    if(((dt.DayOfWeek()==1)||(dt.DayOfWeek()==2)||(dt.DayOfWeek()==3)||(dt.DayOfWeek()==4))&&((dt.Hour()==8)&&(dt.Minute()==40)&&(dt.Second()==0))){
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(3000);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(1000);        // ...for 1sec
  }
    if ((dt.DayOfWeek()==0)&&(dt.Hour()==6)&&(dt.Minute()==00)&&(dt.Second()==0)){Serial.println("Watering 6:00:0");//dt.DayOfWeek()== (0 sunday)(1 monday)(2 tuesday)(3 wensday) (4thursday)(5friday)(6 saterday)
      tone(buzzer, 1000);
      delay(800);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(800);        // ...for 1sec
      stepper.step(-2100);
      delay(1000);//ave 1s/40ml
      stepper.step(2100);
      delay(1000);}
    

}
/*void BlinkLED(int Press)
{
  I2C_OnOff = Wire.read();                      
  if (I2C_OnOff == 1)
  {
   Serial.println("on");                 
  }
  else if (I2C_OnOff == 0)
  {
   Serial.println("off");                 

  } 
}*/
