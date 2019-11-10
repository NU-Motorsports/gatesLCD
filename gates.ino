//NOTE: REQUIRES ADAFRUIT LIBRARY FOR RGBLCDSHEILD
//Link: https://learn.adafruit.com/rgb-lcd-shield/using-the-rgb-lcd-shield

int start_pin = 2;
int finish_pin = 3;
unsigned long start_time = 0;
float run_time;

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>

#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

//#include <EEPROM.h>

//declare lcd object
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

int addr = 0;
int tNum = 1;

void setup()
{
  //initialize lcd size
  lcd.begin(16, 2);

  //set up input pins for gates
  pinMode(start_pin, INPUT_PULLUP);
  pinMode(finish_pin, INPUT_PULLUP);

  //when pin state changes call respective function
  attachInterrupt(digitalPinToInterrupt(start_pin), start, FALLING);
  attachInterrupt(digitalPinToInterrupt(finish_pin), finish, FALLING);

  Serial.begin(9600);
}

//start gate
void start()
{
    if (start_time == 0)
    {
        //start timer
        start_time = millis();
        
        //notify start
        Serial.println("start triggered");
        lcd.setCursor(0, 0);
        lcd.print("start triggered");
    }
}

//finish gate
void finish()
{
    if (start_time > 0)
    {
        //take time difference
        start_time = millis() - start_time;
        //convert to seconds
        run_time = (float)(start_time) / 1000;
        //output result
        Serial.println(run_time,3);
        lcd.setCursor(0, 1);
        lcd.print(run_time);
//        EEPROM.write(addr, run_time);
        //reset start time
        start_time = 0;
        addr = addr + 1;
//        if (addr == EEPROM.length()) {
//          addr = 0;
//        }
    }
}

void loop()
{
}
