// SparkFun Serial LCD example 1
// Clear the display and say "Hello World!"

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the Software Serial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

// Attach the serial enabld LCD's RX line to digital pin 11
SoftwareSerial LCD(10, 11); // Arduino SS_RX = pin 10 (unused), Arduino SS_TX = pin 11 

void setup() {

  Serial.begin(57600);
  Serial.println("Arrancando esto......");

  LCD.begin(9600); // set up serial port for 9600 baud
  LCD.print("--------------------------------------------------------------------------------");
  delay(500); // wait for display to boot up

  //************************************************************
  //this block of code is used to reset a bricked LCD screen, uncomment to use
  /*
  pinMode(13, OUTPUT);//used to indicate when using resetDefault():
  digitalWrite(13, HIGH);// turn the LED ON
  resetDefault(); //reset screen
  digitalWrite(13, LOW);// turn the LED OFF
  */
  //************************************************************
  
  //Uncomment any of these to configure the character LCD's
  //number of characters wide and lines
  //set_16x2(); //set as 16x2
  //set_20x4(); //set as 20x4
  
  //Uncomment this line to enters function to change baud
  //changeBaud();

}

/* Bucle inicial
void loop()
{
  // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  // clear display by sending spaces
  LCD.write("                "); 
  LCD.write("                ");

 // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  LCD.write("Hola mundo!");


  // move cursor to beginning of second line
  LCD.write(254);
  LCD.write(192);

  LCD.write("Funcionado!^_^");

  while(1); // wait forever
}
*/

//-------------------------------------------------------------------------------------------
// Pruebas
void loop(){
  //set_test();  //uncomment to test LCD after changing # of characters wide and lines
  Serial.println("Arrancando scrollingMarquee.....");
  scrollingMarquee();//example of scrolling text across the LCD
  Serial.println("Arrancando tempAndHumidity......");
  tempAndHumidity();//example of displaying values
  Serial.println("Arrancando counter......");
  counter(); //display counter
  Serial.println("Arrancando backlight......");
  backlight(); //test backlight
  Serial.println("Arrancando cursors......");
  cursors(); //test cursors
}


//-------------------------------------------------------------------------------------------

void resetDefault() {
  for(int i=0; i<20; i++){ //repeats 20x so that the LCD will catch the reset
    LCD.write(0x7C);// special command byte => 0d124 or 0x7C
    LCD.write(0x12);//command to reset the LCD back to 9600
    /*      HOW TO UNBRICK YOUR LCD
    1.)remove power from the LCD so that it goes back to the splash screen
    2.)run the code so that the Arduino runs the resetDefault code
    3.)the LCD will indicate that it has been reset "Reset to 9600"
    4.)power cycle LCD to finish reseting the LCD
    
    Note: There might be some settings that have the backlight
     turned down or you need to change the contrast. If this happens
     just let the code cycle through to turn the brightness back on or
     adjust the potentiometer
     
    If this does not work, the last resort is to try using a Pickit 3 Programmer with
    the steps listed in the SparkFun "Tech Support Tips/Troubleshooting/Common Issues"
    [ https://www.sparkfun.com/tutorials/246#comment-563918fb757b7f100d8b4567 ]
    */
  }
}

//-------------------------------------------------------------------------------------------

void set_16x2(){//set character LCD as 16x2
  LCD.write(0x7C); //command flag
  LCD.write(0x04);     //16 char wide
  LCD.write(0x7C); //command flag
  LCD.write(0x06);     //2 lines
  /*NOTE: Make sure to power cycle the serial enabled LCD 
  after re-configuring the # char and lines.*/
}

//-------------------------------------------------------------------------------------------

void set_20x4(){//set character LCD as 20x4
  LCD.write(0x7C); //command flag
  LCD.write(0x03);     //20 char wide
  LCD.write(0x7C); //command flag
  LCD.write(0x05);     //4 lines
  /*NOTE: Make sure to power cycle the serial enabled LCD 
  after re-configuring the # char and lines.*/
}

//-------------------------------------------------------------------------------------------

void set_test(){//used to test the character LCD after reconfiguring # of char and lines
  selectLineOne();//start from first line
  LCD.print("testTESTtestTESTENDH");
  delay(500);
  LCD.print("TESTtestTESTtestendH");
  delay(500);
  LCD.print("testTESTtestTESTENDH");
  delay(500);
  LCD.print("TESTtestTESTtestendH");
  delay(500);
}
//-------------------------------------------------------------------------------------------

void changeBaud(){
  LCD.write(0x7C);// special command byte => 0d124 or 0x7C
  LCD.write(0x0B); //change current baud to 2400 baud

  /*ASCII Value to hex
  2400 baud, "<control>k" => 0x0B
  4800 baud, "<control>l" => 0x0C
  9600 baud, "<control>m" => 0x0D
  14400 baud, "<control>n" => 0x0E
  19200 baud, "<control>o" => 0x0F
  38400 baud, "<control>p" => 0x10
  reset to default baud while LCD is the splash screen is still active, "<control>r" => 0x12*/
}

//-------------------------------------------------------------------------------------------

void clearScreen(){
  //clears the screen, you will use this a lot!
  LCD.write(0xFE);
  LCD.write(0x01);
}

//-------------------------------------------------------------------------------------------

void selectLineOne(){
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(128); //position
}

//-------------------------------------------------------------------------------------------

void selectLineTwo(){
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(192); //position
}

//-------------------------------------------------------------------------------------------

void moveCursorRightOne(){
  //moves the cursor right one space
  LCD.write(0xFE); //command flag
  LCD.write(20); // 0x14
}

//-------------------------------------------------------------------------------------------

void moveCursorLeftOne(){
  //moves the cursor left one space
  LCD.write(0xFE); //command flag
  LCD.write(16); // 0x10
}

//-------------------------------------------------------------------------------------------

void scrollRight(){
  //same as moveCursorRightOne
  LCD.write(0xFE); //command flag
  LCD.write(20); // 0x14
}

//-------------------------------------------------------------------------------------------

void scrollLeft()
{
  //same as moveCursorLeftOne
  LCD.write(0xFE); //command flag
  LCD.write(24); // 0x18
}
//-------------------------------------------------------------------------------------------
void turnDisplayOff(){
  //this tunrs the display off, but leaves the backlight on.
  LCD.write(0xFE); //command flag
  LCD.write(8); // 0x08
}

//-------------------------------------------------------------------------------------------

void turnDisplayOn(){
  //this turns the dispaly back ON
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}

//-------------------------------------------------------------------------------------------

void underlineCursorOn(){
  //turns the underline cursor on
  LCD.write(0xFE); //command flag
  LCD.write(14); // 0x0E
}

//-------------------------------------------------------------------------------------------

void underlineCursorOff()
{
  //turns the underline cursor off
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}

//-------------------------------------------------------------------------------------------

void boxCursorOn(){
  //this turns the box cursor on
  LCD.write(0xFE); //command flag
  LCD.write(13); // 0x0D
}

//-------------------------------------------------------------------------------------------

void boxCursorOff(){
  //this turns the box cursor off
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}

//-------------------------------------------------------------------------------------------

void toggleSplash(){
  //this toggles the spalsh screenif off send this to turn onif on send this to turn off
  LCD.write(0x7C); //command flag = 124 dec
  LCD.write(9); // 0x09
}

//-------------------------------------------------------------------------------------------

int backlight(int brightness){// 128 = OFF, 157 = Fully ON, everything inbetween = varied brightnbess
  //this function takes an int between 128-157 and turns the backlight on accordingly
  LCD.write(0x7C); //NOTE THE DIFFERENT COMMAND FLAG = 124 dec
  LCD.write(brightness); // any value between 128 and 157 or 0x80 and 0x9D
}

//-------------------------------------------------------------------------------------------

void scrollingMarquee(){
  //This function scroll text across the screen on both lines
  clearScreen(); // it's always good to clear the screen before movonh onto a new print
  for (int j = 0; j < 17; j++)
  {
    selectLineOne();
    for (int i = 0; i < j; i++)
      moveCursorRightOne();
    LCD.print("SPARK");
    selectLineTwo();
    for (int i = 0; i < j; i++)
      moveCursorRightOne();
    LCD.print(" FUN");
    delay(500); // you must have a delay, otherwise the screen will print and clear before you can see the text
    clearScreen();
  }
}

//-------------------------------------------------------------------------------------------

void counter(){
  //this function prints a simple counter that counts to 10
  clearScreen();
  for (int i = 0; i <= 10; i++)
  {
    LCD.print("Counter = ");
    LCD.print(i, DEC);
    delay(500);
    clearScreen();
  }
}

//-------------------------------------------------------------------------------------------

void tempAndHumidity()
{
  //this function shows how you could read the data from a temerature and humidity
  //sensro and then print that data to the SerLCD.

  //these could be varaibles instead of static numbers
  float tempF = 77.0;
  float tempC = 25.0;
  float humidity = 67.0;

  clearScreen();
  selectLineOne();
  LCD.print(" Temp = ");
  LCD.print((long)tempF, DEC);
  LCD.print("F ");
  LCD.print((long)tempC, DEC);
  LCD.print("C");
  selectLineTwo();
  LCD.print(" Humidity = ");
  LCD.print((long)humidity, DEC);
  LCD.print("%");
  delay(2500);
}

//-------------------------------------------------------------------------------------------

void backlight(){
  //this function shows the different brightnesses to which the backlight can be set
  clearScreen();
  for (int i = 128; i < 158; i += 2) // 128-157 are the levels from off to full brightness
  {
    backlight(i);
    delay(100);
    LCD.print("Backlight = ");
    LCD.print(i, DEC);
    delay(500);
    clearScreen();
  }
}

//-------------------------------------------------------------------------------------------

void cursors(){
  //this function shows the different cursors avaiable on the SerLCD
  clearScreen();

  boxCursorOn();
  LCD.print("Box On");
  delay(1500);
  clearScreen();

  boxCursorOff();
  LCD.print("Box Off");
  delay(1000);
  clearScreen();

  underlineCursorOn();
  LCD.print("Underline On");
  delay(1500);
  clearScreen();

  underlineCursorOff();
  LCD.print("Underline Off");
  delay(1000);
  clearScreen();
}

