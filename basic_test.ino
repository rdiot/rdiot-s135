/* G1/2 Water Flow Sensor (SEN-HZ21WA) [S135] : http://rdiot.tistory.com/63 [RDIoT Demo] */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // LCD2004

volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;                               
int hallsensor = 2;    //The pin location of the sensor : D2
 
void rpm ()     //This is the function that the interupt calls 
{ 
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
} 

void setup()
{
  Serial.begin(9600); 

  pinMode(hallsensor, INPUT);
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
}

void loop()
{
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  sei();      //Enables interrupts
  delay (1000);   //Wait 1 second
  cli();      //Disable interrupts
  Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 

  Serial.print (Calc, DEC); //Prints the number calculated above
  Serial.println (" L/hour"); 
}
