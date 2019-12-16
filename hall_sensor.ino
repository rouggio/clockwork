#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <TimerOne.h>
#include <CircularBuffer.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pins
const int HALL_SENSOR_PIN = 2;

// constants
const int SAMPLE_SIZE = 8;
const unsigned long RPM_FACTOR = 60L * 1000 * 1000;

// shared variables
volatile CircularBuffer<unsigned long, SAMPLE_SIZE> hallSensorReads;

volatile int rpms = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("setup started");
  
  // Crank sensor
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), hallSensorChange, FALLING);

  // RPM calulation
  Timer1.initialize(1000 * 1000);
  Timer1.attachInterrupt(refreshRPMs);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  for (int i = 0; i < SAMPLE_SIZE; i++) {
    hallSensorReads.push(0);
  }
  
  Serial.println("setup completed");
}

void loop() {
  refreshDisplay();
  delay(20);
}

void refreshDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(rpms);
  display.display();
}

void hallSensorChange() {
  hallSensorReads.push(micros());
}

int refreshRPMs() {
  unsigned long lastTransit = hallSensorReads[SAMPLE_SIZE - 1];
  unsigned long secondLastTransit = hallSensorReads[SAMPLE_SIZE - 2];
  unsigned long lastKnownDuration = lastTransit - secondLastTransit;
  unsigned long instantDuration = micros() - lastTransit;
  if (instantDuration > (1000L * 1000L * 3L)) {
    // too long wait, engine is not turning
    rpms = 0;
  } else {
    rpms = averageRPMs();
  }
}

int averageRPMs() {
  unsigned long averageDuration = 0;
  int components = 0;
  for (int i = 1; i < SAMPLE_SIZE; i++) {
    unsigned long pairDuration = computeDuration(i - 1, i);
    if (pairDuration > 0) {
      averageDuration += pairDuration;
      components++;
    }
  }

//  unsigned long lastRead = hallSensorReads.last();
//  unsigned long now = micros();
  //if we are past the due transit as per last revolution, factor in an instant read as well
//  if (now > 
//  averageDuration += micros() - hallSensorReads.last();
  
  averageDuration = averageDuration / components;
  Serial.println(components);
  return RPM_FACTOR / averageDuration;
}

int computeDuration(int prevSampleIndex, int nextSampleIndex) {
    unsigned long nextTransit = hallSensorReads[nextSampleIndex];
    unsigned long previousTransit = hallSensorReads[prevSampleIndex];
    if (nextTransit > 0 && previousTransit > 0) {
      return nextTransit - previousTransit;
    } else {
      return 0;
    }
}
