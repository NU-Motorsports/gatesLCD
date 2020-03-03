// NOTE: REQUIRES ADAFRUIT LIBRARY FOR RGBLCDSHEILD
// Link: https://learn.adafruit.com/rgb-lcd-shield/using-the-rgb-lcd-shield


#include <Wire.h>
//#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

int start_pin   = 2;
int finish_pin  = 3;

unsigned long start_time = 0;

double run_time     = 0;
double old_run_time = 1;

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
}

//start gate
void start()
{
    // start time will be zero if a run is not currently ongoing
    if (start_time == 0)
    {
        start_time = millis();
    }
}

//finish gate
void finish()
{
    // start time will be non-zero if a run is currently ongoing
    if (start_time != 0)
    {
        // take time difference and convert to seconds
        run_time = (float)(millis() - start_time) / 1000;
        
        // reset start time
        start_time = 0;
    }
}

void loop()
{
  if (run_time != old_run_time) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(run_time);
    old_run_time = run_time;
  }
  
  lcd.setCursor(0, 1);
  if (start_time != 0)
  {
    lcd.print((double)(millis() - start_time) / 1000);
    lcd.print(" ");
  }  
  else
  {
    lcd.print("READY");
  }
}
