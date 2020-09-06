#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>// include the library code

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

#define DHTPIN 7
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht = DHT(DHTPIN, DHTTYPE);

// custom chars
byte Thermo[8] =
{
  0b01110,
  0b01110,
  0b01110,
  0b01010,
  0b01010,
  0b11011,
  0b10001,
  0b11111
};

byte Drop[8] =
{
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};


// ultrasonic sensor
const int trigPin = 9;
const int echoPin = 3;

// buzzer
int buzzerPin = 2;

// variable for take distance func output
int distCM;
bool beep;


void setup() {
  Serial.begin(9600);
  
  // Setup sensor:
  dht.begin();
  
  lcd.begin(16, 2);  // set LCD's number of columns and rows:

  // create new custom characters to display thermometer and a drop
  lcd.createChar(0, Thermo);
  lcd.createChar(1, Drop);

  // ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // buzzer pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  lcd.setCursor(0, 0); // set the cursor to column 0, row 0
  lcd.print("Display temp/hum");
  lcd.setCursor(1, 1); // set the cursor to column 1, row 1
  lcd.print("Come closer...");
  beep = true;

  distCM = take_distance(); // take the distance function

  while (distCM <= 35) {

    if (beep == true) {
      lcd.clear(); // delete whatever on the LCD at the moment
      double_beep();
      beep = false;
    }

    // start reading temp and humidity

    delay(250);
    
    // Read the humidity in %:
    float h = dht.readHumidity();
    // Read the temperature as Celsius:
    float t = dht.readTemperature();


    // display things on the LCD
    lcd.setCursor(0, 0); // set the cursor to col 0, row 0
    lcd.print("Temp:");  // Print a message to the LCD.
    lcd.setCursor(6, 0);
    lcd.print(t);
    lcd.setCursor(11, 0);
    lcd.print((char)223);
    // print the thermo custom icon
    lcd.setCursor(13, 0);
    lcd.write(byte(0));

    lcd.setCursor(0, 1); // set the cursor to column 0, row 1
    lcd.print(" Hum:");  // Print a message to the LCD.
    lcd.setCursor(6, 1);
    lcd.print(h);
    lcd.setCursor(11, 1);
    lcd.print("%");
    // print the drop custom icon
    lcd.setCursor(13, 1);
    lcd.write(byte(1));

    delay(5000); // wait 5 sec

    distCM = take_distance();

  }
}


// FUNCTIONS

int take_distance() {
  int distanceCM;
  long duration;

  // TAKE DISTANCE
  // clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // set trigPin on HIGH for 10 micro sec
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // reead echoPin and return the sound wave travel time in microsec
  duration = pulseIn(echoPin, HIGH);

  // calculate distance
  distanceCM = duration * 0.034 / 2; // s = t * v. the sound travels at 0.034 cm/µs (v). /2 because we want only one way trip

  return distanceCM;
}


void double_beep() {
  // make a double beep
  digitalWrite(buzzerPin, HIGH);   // turn the buzzer on (HIGH voltage level)
  delay(50);                       // wait for a second
  digitalWrite(buzzerPin, LOW);    // turn the buzzer off
  delay(50);
  digitalWrite(buzzerPin, HIGH);   // turn the buzzer on
  delay(50);                       // wait for a second
  digitalWrite(buzzerPin, LOW);    // turn the buzzer off
  delay(250);
}
