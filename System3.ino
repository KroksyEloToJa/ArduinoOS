#include "DHT.h"

#define TONE_PIN 3
#define BUZZER_PIN 3  // Pin for the real buzzer
DHT dht(5, DHT22);    // Using DHT22 sensor

int buzzer_volume = 10;  // No longer used with the real buzzer
int buzzer_play_speed = 100;
bool isPolish = false;   // Language state flag (false = English, true = Polish)

void buzzerPlay(int pin, long frequency, int duration) {
  if (buzzer_play_speed < 30) buzzer_play_speed = 30;
  if (buzzer_play_speed > 255) buzzer_play_speed = 255;
  tone(pin, frequency);        // Start playing tone
  delay(duration * 100);       // Play tone for specified duration
  noTone(pin);                 // Stop tone
}

void printMenu() {
  if (isPolish) {
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
  } else {
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
}

void setup() {
  pinMode(2, INPUT_PULLUP);  // Button for language switch
  pinMode(4, INPUT_PULLUP);  // Button for temperature check
  pinMode(6, INPUT_PULLUP);  // Button for device test
  pinMode(7, OUTPUT);        // Pin for testing device signal
  Serial.begin(9600);
  pinMode(TONE_PIN, OUTPUT); // Pin for buzzer
  dht.begin();

  Serial.println("--------ArduinoOS--------");
  delay(2000);
  Serial.println("Initializing...");
  delay(3000);
  Serial.println("Checking files...");
  delay(1000);
  Serial.println("Welcome to ArduinoOS!");
  printMenu();  // Show the initial menu
}

void loop() {
  // Language switch button (connected to pin 2)
  if (digitalRead(2) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);  // Play a tone on button press
    isPolish = !isPolish;          // Toggle language flag
    delay(3000);                   // Debounce delay
    printMenu();                   // Reprint the menu in the new language
  }

  // Temperature check button (connected to pin 4)
  if (digitalRead(4) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);  // Play a tone on button press
    Serial.println(isPolish ? "Obecna temperatura jest:" : "Current temperature is:");
    float temp = dht.readTemperature(false); // Get temperature in Celsius
    Serial.println(temp);
  }

  // Device test button (connected to pin 6)
  if (digitalRead(6) == LOW) {
    buzzerPlay(TONE_PIN, 262, 1);  // Play a tone on button press
    if (isPolish) {
      Serial.println("Podłącz sygnał do D7 i prąd 5V Albo 3.3V Lub GND, aby przetestować urządzenie.");
    } else {
      Serial.println("Connect a signal to D7 and a current of 5V or 3.3V or GND to test the device.");
    }
    while (!(digitalRead(6) == LOW));  // Wait until button is released
    digitalWrite(7, HIGH);             // Simulate device test (turn pin 7 on)
    delay(5000);                       // Test duration (5 seconds)
    digitalWrite(7, LOW);              // Turn pin 7 off
    Serial.println(isPolish ? "Czy działa?" : "Is it working?");
  }
}
