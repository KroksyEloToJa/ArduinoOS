#include <TimerFreeTone.h>
#include "DHT.h"

#define TONE_PIN 3
DHT dht(5, DHT11);

int buzzer_volume = 10;
int buzzer_play_speed = 100;

void buzzerPlay(int pin, long frequency, int duration) {
  if (buzzer_play_speed < 30) buzzer_play_speed = 30;
  if (buzzer_play_speed > 255) buzzer_play_speed = 255;
  int playTime = 100000 / buzzer_play_speed / duration;
  TimerFreeTone(pin, frequency, playTime, buzzer_volume);
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  pinMode(TONE_PIN, OUTPUT);
  dht.begin();
  Serial.println("--------ArduinoOS--------");
  delay(2000);
  Serial.println("Initializing...");
  delay(3000);
  Serial.println("Checking files...");
  delay(1000);
  Serial.println("Welcome to ArduinoOS!");
  Serial.println("Options:");
  Serial.println("1: Switch Language");
  Serial.println("2: Check Temperature");
  Serial.println("3: Test Device");
}

void loop() {
  float temperature = dht.readTemperature(false);

  // Check if temperature exceeds 25C
  if (temperature > 25) {
    Serial.println("Jest Za gorąco żeby mógł działać/It's too hot to make ArduinoOS working.");
    while(true);  // Halt the system
  }

  if (digitalRead(2) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);
    Serial.println("Switching to Polski");
    delay(3000);
    Serial.println("--------ArduinoOS--------");
    delay(2000);
    Serial.println("Inicjowanie...");
    delay(3000);
    Serial.println("Sprawdzanie plików...");
    delay(1000);
    Serial.println("Witamy w ArduinoOS!");
    Serial.println("Opcje:");
    Serial.println("1: Zmień Język");
    Serial.println("2: Sprawdź Temperaturę");
    Serial.println("3: Przytestuj Urządzenie");
    while(!(digitalRead(2) == LOW));
    buzzerPlay(TONE_PIN, 262, 1);
    Serial.println("Zmienianie języku na English");
    delay(3000);
    Serial.println("--------ArduinoOS--------");
    delay(2000);
    Serial.println("Initializing...");
    delay(3000);
    Serial.println("Checking files...");
    delay(1000);
    Serial.println("Welcome to ArduinoOS!");
    Serial.println("Options:");
    Serial.println("1: Switch Language");
    Serial.println("2: Check Temperature");
    Serial.println("3: Test Device");
  }
  if (digitalRead(4) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);
    Serial.println("Current temperature is/Obecna temperatura jest:");
    Serial.println(temperature);
  }
  if (digitalRead(6) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);
    Serial.println("Aby przytestować urządzenie podłącz sygnał do D7 i prąd 5V Albo 3.3V Lub GND/To test the device, connect a signal to D7 and a current of 5V or 3.3V or GND");
    while(!(digitalRead(6) == LOW));
    digitalWrite(7, HIGH);
    delay(5 * 1000);
    digitalWrite(7, LOW);
    Serial.println("Czy działa/Is it working?");
  }
}

