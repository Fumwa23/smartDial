//Main code for SmartDial

//------------------------------Components---------------------------------
// AS5600: https://www.mouser.sg/datasheet/2/588/AS5600_DS000365_5_00-1877365.pdf - magnetic enc
// ESP32:  https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf typical application: https://dl.espressif.com/dl/schematics/esp32_devkitc_v4-sch.pdf
// SN74HC595DR:https://datasheet.lcsc.com/lcsc/1809192316_Texas-Instruments-SN74HC595DR_C10092.pdf, https://www.instructables.com/Shift-Register-LED-Array-Arduino-5-Examples/ - shift register
// HX711: https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf - strain gauge sensor

// TMC6300-LA: https://datasheet.lcsc.com/lcsc/2211181800_TRINAMIC-Motion-Control-GmbH-TMC6300-LA-T_C5274455.pdf - BLDC motor controll
// VEML7700-TR: https://datasheet.lcsc.com/lcsc/2211160930_Vishay-Intertech-VEML7700-TR_C504893.pdf - Ambient light sensor
// SK6805 SIDE-G: http://www.normandled.com/upload/201912/SK6805SIDE-G%203512%20LED%20Datasheet.pdf - side firing LED
// Datasheet of similar board: https://docs.sparkfun.com/SparkFun_IoT_Brushless_Motor_Driver/assets/board_files/schematic.pdf?_gl=1*1t9ye71*_ga*MTUwMzc3MTM5Mi4xNzA3MzMxNDk4*_ga_T369JS7J9N*MTcwNzMzMTQ5OC4xLjEuMTcwNzMzMjEyOC40MC4wLjA
// Different LED (that I dont think i will use: http://www.normandled.com/upload/202106/SK6805SIDE-FRGBW-BW-P6%20LED%20Datasheet.pdf - Side firing LED
// DRV8311 motor driver: https://www.ti.com/cn/lit/ds/symlink/drv8311.pdf?ts=1707331097347&ref_url=https%253A%252F%252Fwww.lcsc.com%252F
//------------------------------Libraries----------------------------------
#include "ESP32.h"
#include "HX711.h"
#include "Simplefield" // add this library it is usefull
// 

//---------------------------- Set constants -------------------------------

// Angles of the circle LEDs (in degrees)
const int ledPos1 = 0;
const int ledPos2 = 45;
const int ledPos3 = 90;
const int ledPos4 = 135;
const int ledPos5 = 180;
const int ledPos6 = 135; // 225 degrees but can be seen as 135 from the counter-clockwise direction
const int ledPos7 = 90;  // same here
const int ledPos8 = 45;  // same here


//Radius of LED circle (in cm)
const int radiusLed = 3;

//--------------------------------Variables-----------------------------------
float knobAngle = 0;
//-------------------------------ESP32 pins-----------------------------------
//LEDs
const int LED1 = 1;
const int LED2 = 2;
const int LED3 = 3;
const int LED4 = 4;
const int LED5 = 5;
const int LED6 = 6;
const int LED7 = 7;
const int LED8 = 8;

//Strain sensors
HX711 strainSensor;
const int HX711_DOUT_PIN = 2;
const int HX711_SCK_PIN = 3;
const long threshold = 10000;

class circleLed {
  public:
    circleLed(int assignedPin, int red, int green, int blue, float angle) : 
    pin(assignedPin), red(red), green(green), blue(blue), angle(angle) {}

    int getPin() const {return pin;}
    int getRed() const {return red;}
    int getGreen() const {return green;}
    int getBlue() const {return blue;}
    float getAngle() const {return angle;}

    void setPin(int p) {pin = p;}
    void setRed(int r) {red = r;}
    void setGreen(int g) {green = g;}
    void setBlue(int b) {blue = b;}
    void setAngle(float a) {angle = a;}
    void softBlink(int time){
      // set the intensity to be equal to x for y seconds;
    }

  private:
    int pin;
    int red;
    int green;
    int blue;
    float angle;
};

void fadeLightFunction(int angleKnob) {
  /*
  Create smooth gradient effect as the nob is turned around. 
  This function uses linear difference in angle to determine the factor of red light intensity
  A doorknob aligned perfectly to an LED will cause it to be purple, as the blue RGB value is kept at 100%.

  Parameters:
    angleKnob (int): The angle of the input knob relative to 0.
  */
  circleLed1.setRed(((180 - (abs(circleLed1.getAngle()-angleKnob)))/180)*255);
  circleLed2.setRed(((180 - (abs(circleLed2.getAngle()-angleKnob)))/180)*255);
  circleLed3.setRed(((180 - (abs(circleLed3.getAngle()-angleKnob)))/180)*255);
  circleLed4.setRed(((180 - (abs(circleLed4.getAngle()-angleKnob)))/180)*255);
  circleLed5.setRed(((180 - (abs(circleLed5.getAngle()-angleKnob)))/180)*255);
  circleLed6.setRed(((180 - (abs(circleLed6.getAngle()-angleKnob)))/180)*255);
  circleLed7.setRed(((180 - (abs(circleLed7.getAngle()-angleKnob)))/180)*255);
  circleLed8.setRed(((180 - (abs(circleLed8.getAngle()-angleKnob)))/180)*255);
}

void onPress() {
  /*
  This function is seperate from the loop and is triggered when the strain sensors detech a press.
  The motor is triggered to imitate the feeling of clicking a mechanical button.
  */

}

void turnMotor(float changeAngle=0, int desiredAngle=knobAngle){
  /*
  This function calls on the motor driver to turn the stepper motor in the desired position.
  */
 knobAngle = desiredAngle;
 
}

void vibrateDial(int mode=0){
  /*
  This function causes a vibration in the dial, with different types based on the selected mode.
  Possible modes:
  - 'click': simulates a button press
  - 'error': simulates a no press
  */
 if (mode=0){ // Simulate Click
  turnMotor(2);
  delay(100);
  turnMotor(-2);
  Serial.print('Click simulated')
 } else if(mode=1){
  turnMotor(2);
  delay(100);
  turnMotor(-2);
  delay(100)
  turnMotor(2);
  delay(100);
  turnMotor(-2);
  delay(100)
  Serial.print('Error click simulated')
 }

}

void setup() {
  // Setting up LEDs
  circleLed circleLed1(0, 0, 0, ledPos1);
  circleLed circleLed2(0, 0, 0, ledPos2);
  circleLed circleLed3(0, 0, 0, ledPos3);
  circleLed circleLed4(0, 0, 0, ledPos4);
  circleLed circleLed5(0, 0, 0, ledPos5);
  circleLed circleLed6(0, 0, 0, ledPos6);
  circleLed circleLed7(0, 0, 0, ledPos7);
  circleLed circleLed8(0, 0, 0, ledPos8);

  // Interupt for On/Off button
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), onPress, CHANGE);

  //Setup of strain sensors
  strainSensor.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
  strainSensor.set_scale();
  strainSensor.tare();
}

void loop() {
  // Checking for dial button presses
  if (scale.is_ready()) {
    long weight = scale.get_units(10);
    if (weight > threshold) {
      onPress();
    }
  }
}