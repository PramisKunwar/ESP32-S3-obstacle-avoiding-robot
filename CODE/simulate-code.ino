#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define SDA_PIN 21
#define SCL_PIN 20

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ENA 6
#define IN1 4
#define IN2 5

#define ENB 9
#define IN3 7
#define IN4 8

#define TRIG_PIN 12
#define ECHO_PIN 13

#define BUZZER 14
#define SAFE_DISTANCE 20

void setup()
{
  Serial.begin(115200);

  // I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  display.println("ROBOT");
  display.display();

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  // Enable motors
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  stopMotors();

  delay(1000);
}

void loop()
{
  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  displayDistance(distance);

  if (distance > 0 && distance < SAFE_DISTANCE)
  {
    obstacleRoutine();
  }
  else
  {
    forward();
  }

  delay(100);
}

void obstacleRoutine()
{
  stopMotors();

  digitalWrite(BUZZER, HIGH);
  delay(300);
  digitalWrite(BUZZER, LOW);

  backward();
  delay(1000);

  stopMotors();
  delay(300);
}

long getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    return 999;
  }

  long distance = duration * 0.0343 / 2;

  return distance;
}

void displayDistance(long distance)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Obstacle Bot");

  display.setTextSize(2);
  display.setCursor(0,20);
  display.print(distance);
  display.print(" cm");

  if(distance < SAFE_DISTANCE)
  {
    display.setTextSize(1);
    display.setCursor(0,50);
    display.print("Obstacle!");
  }
  else
  {
    display.setTextSize(1);
    display.setCursor(0,50);
    display.print("Moving Forward");
  }

  display.display();
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
