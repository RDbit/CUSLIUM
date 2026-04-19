#include <Wire.h>
#include <U8g2lib.h> // mga library ni siya

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0); // Driver para sa Oled display


const int trigL = 5;
const int echoL = 4; // Ultrasonic left Pins
const int buzzerLeft = 3; // PWM for buzzer

// Right Sensor
const int trigR = 7;
const int echoR = 6; // Ultrasonic right Pins
const int buzzerRight = 9; // PWM for buzzer

long durationL, durationR;
int distanceL, distanceR;
int pwmL, pwmR;

void setup() {

  Serial.begin(9600);

  
  u8g2.begin();
  
  
  pinMode(trigL, OUTPUT); // Left sensor pins
  pinMode(echoL, INPUT);
  pinMode(buzzerLeft, OUTPUT);
  
  
  pinMode(trigR, OUTPUT); // Right sensor pins
  pinMode(echoR, INPUT);
  pinMode(buzzerRight, OUTPUT);
}

void loop() {
  
  digitalWrite(trigL, LOW); // Measure Left
  delayMicroseconds(2);
  digitalWrite(trigL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);
  durationL = pulseIn(echoL, HIGH);
  distanceL = durationL * 0.034 / 2;


  digitalWrite(trigR, LOW); // Measure Right
  delayMicroseconds(2);
  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigR, LOW);
  durationR = pulseIn(echoR, HIGH);
  distanceR = durationR * 0.034 / 2;

  
  if (distanceL >= 0 && distanceL <= 30) {   // Vibration Variable Left
    pwmL = 255;
  } else if (distanceL > 30 && distanceL <= 60) {
    pwmL = 110;
  } else if (distanceL > 60 && distanceL <= 100) {
    pwmL = 40;
  } else {
    pwmL = 0;
  }

  
  if (distanceR >= 0 && distanceR <= 30) {  // Vibration Variable Right
    pwmR = 255;
  } else if (distanceR > 30 && distanceR <= 60) {
    pwmR = 200;
  } else if (distanceR > 60 && distanceR <= 100) {
    pwmR = 170;
  } else {
    pwmR = 0;
  }

  
  analogWrite(buzzerLeft, pwmL); // Output PWM on the left
  analogWrite(buzzerRight, pwmR); // Output PWM on the right

  // Serial Monitor
  Serial.print("LEFT: ");
  Serial.print(distanceL);
  Serial.print(" cm | PWM: ");
  Serial.print(pwmL);
  Serial.print("     ||     RIGHT: ");
  Serial.print(distanceR);
  Serial.print(" cm | PWM: ");
  Serial.println(pwmR);

  
  u8g2.clearBuffer();               // Oled Code and Display
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.drawStr(0, 12, "LEFT:");
  u8g2.setCursor(50, 12);
  u8g2.print(distanceL);
  u8g2.print("cm");

  u8g2.drawStr(0, 30, "PWM L:");
  u8g2.setCursor(50, 30);
  u8g2.print(pwmL);

  u8g2.drawStr(0, 48, "RIGHT:");
  u8g2.setCursor(50, 48);
  u8g2.print(distanceR);
  u8g2.print("cm");

  u8g2.drawStr(0, 64, "PWM R:");
  u8g2.setCursor(50, 64);
  u8g2.print(pwmR);

  u8g2.sendBuffer();

  delay(100); //tguytuj thuyyhgjgjgjyyjf si ardee gwapo
