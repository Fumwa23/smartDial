//Main code for SmartDial

//------------------------------Components---------------------------------
// AS5600: https://www.mouser.sg/datasheet/2/588/AS5600_DS000365_5_00-1877365.pdf
// ESP32:  https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
// 74HC595:https://www.instructables.com/Shift-Register-LED-Array-Arduino-5-Examples/
// 

//---------- Set constants ------------

// Angles of the circle LEDs (in degrees)
int ledPos1 = 0;
int ledPos2 = 45;
int ledPos3 = 90;
int ledPos4 = 135;
int ledPos5 = 180;
int ledPos6 = 135; //225 degrees but can be seen as 135 from the counter clock wise direction
int ledPos7 = 90; //same here
int ledPod8 = 45; //same here

//Radius of LED circle (in cm)
int radiusLed = 3;

class circleLed {
  public:
    circleLed(int red, int green, int blue, float angle) : 
    red(red), green(green), blue(blue), angle(angle) {}

    int getRed() const {return red;}
    int getGreen() const {return green;}
    int getBlue() const {return blue;}
    float getAngle() const {return angle;}

    void setRed(int r) {red = r;}
    void setGreen(int g) {green = g;}
    void setBlue(int b) {blue = b;}
    void setAngle(float a) {angle = a;}

  private:
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

void setup() {
  //Setting up LEDs
  circleLed circleLed1(0, 0, 0, ledPos1);
  circleLed circleLed2(0, 0, 0, ledPos2);
  circleLed circleLed3(0, 0, 0, ledPos3);
  circleLed circleLed4(0, 0, 0, ledPos4);
  circleLed circleLed5(0, 0, 0, ledPos5);
  circleLed circleLed6(0, 0, 0, ledPos6);
  circleLed circleLed7(0, 0, 0, ledPos7);
  circleLed circleLed8(0, 0, 0, ledPos8);
}

void loop() {
  // Main loop code goes here
}