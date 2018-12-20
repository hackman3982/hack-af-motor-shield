/*
 **************************************************************************************************
 * Sketch : Controls a 4 wheel drive vehicle over a bluetooth link
 * Board  : HACK-AF-MOTOR-SHIELD
 * Wiring : Refer Adafruit Motor Shield circuit schematic
 * Author : Written by Rushikesh Deshmukh for http://www.hack-man.io
 * License: Berkeley Software Distribution (BSD)
 **************************************************************************************************            
 */
  
/*
 * ------------------------------------------------------------------------------------------------
 * Library files
 * ------------------------------------------------------------------------------------------------
 */
 #include <AFMotor.h>         // adafruit motor shield library
                              // https://github.com/adafruit/Adafruit-Motor-Shield-library.git
 #include<SoftwareSerial.h>   // to replicate the functionality of serial port
/*
 * ------------------------------------------------------------------------------------------------
 * Macros
 * ------------------------------------------------------------------------------------------------
 */ 
 
/*
 * ------------------------------------------------------------------------------------------------
 * Global declarations
 * ------------------------------------------------------------------------------------------------
 */
 /* Obejcts of motor shield */
 AF_DCMotor m1(1, MOTOR12_1KHZ); 
 AF_DCMotor m2(2, MOTOR12_1KHZ); 
 AF_DCMotor m3(3, MOTOR12_1KHZ); 
 AF_DCMotor m4(4, MOTOR12_1KHZ); 

 /* Object of software serial for bluetooth */
 SoftwareSerial btSerial(A1, A0); 

 char command = 'S';  // commands from mobile app (initialized to STOP)
 
/*
 * ------------------------------------------------------------------------------------------------
 * Functions, ISRs
 * ------------------------------------------------------------------------------------------------
 */
 void cruise() {
  m1.run(FORWARD); 
  m2.run(FORWARD); 
  m3.run(FORWARD); 
  m4.run(FORWARD); 
 }

 void left() {
  m1.run(FORWARD); 
  m2.run(FORWARD); 
  m3.run(BACKWARD); 
  m4.run(BACKWARD); 
 }

 void right() {
  m1.run(BACKWARD); 
  m2.run(BACKWARD); 
  m3.run(FORWARD); 
  m4.run(FORWARD); 
 }
 
 void back() {
  m1.run(BACKWARD); 
  m2.run(BACKWARD); 
  m3.run(BACKWARD); 
  m4.run(BACKWARD); 
 }

 void halt() {
  m1.run(RELEASE); 
  m2.run(RELEASE); 
  m3.run(RELEASE); 
  m4.run(RELEASE); 
 }

/*
 * ------------------------------------------------------------------------------------------------
 * put your setup code here, to run once:
 * ------------------------------------------------------------------------------------------------
 */
 void setup() {
  Serial.begin(9600);     // set serial com at 9600bps                                 
  btSerial.begin(9600);   // set myserial com at 9600bps
  
  m1.setSpeed(150);       // set the speed for motor (0-255)
  m2.setSpeed(150);       // set the speed for motor (0-255)
  m3.setSpeed(150);       // set the speed for motor (0-255)
  m4.setSpeed(150);       // set the speed for motor (0-255)
 }
  
/*
 * ------------------------------------------------------------------------------------------------
 * put your main code here, to run repeatedly:
 * ------------------------------------------------------------------------------------------------
 */
 void loop() {
  
  if(btSerial.available() > 0){ 
    delay(50);        // delay for stability
    command = btSerial.read(); 
  
  //  configure these commands in bluetooth app 
    switch(command){
    case 'C':         // command for cruise           
      cruise();
      break;
    case 'L':         // command for left turn 
       left();
      break;
    case 'R':         // command for right turn 
      right();
      break;
    case 'B':         // command for reverse
      back();
      break;
    case 'H':         // command for halt
      halt();
      break; 
    default:          // default is halt
      halt();
      break;
    }
  }
 }
