#include <IRremote.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
#define IR_RECEIVE_PIN 8
int num1=0;
int num2=90;
int num3=90;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  servo1.attach(6);
  servo2.attach(10);
  servo3.attach(9);
}
void loop() {
  // put your main code here, to run repeatedly:
    if (IrReceiver.decode()) {
    IrReceiver.resume();
    //servo1
    if(IrReceiver.decodedIRData.command==69){num1=num1+4;}//1-up
    if(IrReceiver.decodedIRData.command==68){num1=num1-4;}//4-down
    //servo2
    if(IrReceiver.decodedIRData.command==64){num2=num2+4;}//2-up
    if(IrReceiver.decodedIRData.command==70){num2=num2-4;}//5-down
    //servo3
    if(IrReceiver.decodedIRData.command==71){num3=num3+4;}//3-up
    if(IrReceiver.decodedIRData.command==67){num3=num3-4;}//6-down
    //ok button
    if(IrReceiver.decodedIRData.command==28){num1=0;num2=90;num3=90;Serial.println(" ~reset~ ");}
    //if((num1>=181)||(num2>=181)||(num3>=181)){num1=180;num2=180;num3=180;}
    //if((num1<=-1)||(num2<=-1)||(num3<=-1)){num1=0;num2=0;num3=0;}
    servo1.write(num1);
    servo2.write(num2);
    servo3.write(num3);
    Serial.print("Servo1: ");
    Serial.print(num1);
    Serial.print(" | ");
    Serial.print("Servo2: ");
    Serial.print(num2);
    Serial.print(" | ");
    Serial.print("Servo3: ");
    Serial.print(num3);
    Serial.print(" | IR: ");
    Serial.println(IrReceiver.decodedIRData.command);
    
  }
}
