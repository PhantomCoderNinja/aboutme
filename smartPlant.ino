#include <LiquidCrystal_I2C.h>
#include <dht.h>
#define BUTTON_PIN 4
#define sensorPower 7
#define sensorPin A0
/*#include <Wire.h>                                                        
byte I2C_OnOff;*/
String op;
String str;
dht DHT;
int b;
int screen=0;
#define DHT11_PIN 8
float f;
int h;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
int val = 0;
const int buzzer = 9;

const int pResistor = A1; // Photoresistor at Arduino analog pin A0

//Variables
int value;
int p=0;
void setup()
{
  //Wire.begin();                                                             
  Serial.begin(9600);
  pinMode(pResistor, INPUT);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  int level = readSensor();
  int chk = DHT.read11(DHT11_PIN);
  f=((DHT.temperature)*1.8)+32;
  h=DHT.humidity;
  value = analogRead(pResistor); //light sensor
  b=digitalRead(BUTTON_PIN);
  Serial.print("Temp: ");
  Serial.print(f);
  Serial.print("*F");
  Serial.print(" Hum: ");
  Serial.println(h);
  Serial.print("Light sensor: ");
  Serial.print(value);
  Serial.print("% Water sensor:");
  Serial.print(level);
  Serial.println("%");
  /*if(level>200&&level<425){I2C_OnOff=1;}// here
  else{I2C_OnOff=0;}
  Wire.beginTransmission(1);                                                
  Wire.write(I2C_OnOff);                                                    
  Wire.endTransmission();*/
  if (value>40&&value<70){if (h>40&&h<80){if (level>200&&level<425){if (f>67){p=100;}}}}
  else{if (h>40&&h<80){if (level>200&&level<425){if (f>67){p=75;}}}
  else{if (level>200&&level<425){if (f>67){p=50;}}else{if (f>67){p=25;
  }else{p=0;}}}}
  str=p;
  if(p>60&&p<80){op=str+"% Mid";}
  if(p>80){op=str+"% Good";}
  if(p<60){op=str+"% Bad";}
  Serial.print("Plant health: ");
  Serial.println(op);
  if (b==0){screen=screen+1;
  tone(buzzer, 1000);
  delay(800);
  noTone(buzzer);     // Stop sound...
  delay(800);
  }
  if (screen==0){lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print(f);
  }
  if (screen==1){lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity");
  if (h<40){op="Dry";}
  if (h>40&&h<65){op="Mid";}
  if(h>65){op="High";}
  str=h;
  op=str+"  "+op;
  lcd.setCursor(0, 1);
  lcd.print(op);
  }
  if (screen==2){lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light sensor");
  if (value<40){op="Low";}
  if (value>40&&value<70){op="Mid";}
  if(value>70){op="Bright";}
  str=value;
  op=str+"  "+op;
  lcd.setCursor(0, 1);
  lcd.print(op);
  }
  if (screen==3){lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water level");
  if (level<200){op="Dry";}
  if (level>200&&level<425){op="Mid";}
  if(level>425){op="High";}
  str=level;
  op=str+"  "+op;
  lcd.setCursor(0, 1);
  lcd.print(op);
  }
  if(screen==4){
    if (value>40&&value<70){if (h>40&&h<80){if (level>200&&level<425){if (f>67){p=100;}}}}
  else{if (h>40&&h<80){if (level>200&&level<425){if (f>67){p=75;}}}
  else{if (level>200&&level<425){if (f>67){p=50;}}else{if (f>67){p=25;
  }else{p=0;}}}}
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Plant health");
    lcd.setCursor(0, 1);
    str=p;
    if(p>60&&p<80){op=str+"% Mid";}
    if(p>80){op=str+"% Good";}
    if(p<60){op=str+"% Bad";}
    lcd.print(op);
    
    }
    if (screen==5){screen=0;}
  delay(1000);
}
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}
