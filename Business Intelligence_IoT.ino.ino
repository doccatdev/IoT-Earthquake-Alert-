#define BLYNK_TEMPLATE_ID "TMPL6BmMW5zaq"
#define BLYNK_TEMPLATE_NAME "Earthquake Alert Warning System"
#define BLYNK_AUTH_TOKEN "m-sG7ZFhNr02_rMWwQbelleoGI8ly92Y"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

// Blynk settings
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";
char pass[] = "";

// Vibration sensor settings
const int vibrationPin = A0; // Use the appropriate analog pin on your ESP8266
const int threshold = 500;  // Adjust this threshold based on your sensor and environment

// Buzzer settings
const int buzzerPin = D2; // Pin D2 on ESP8266

// Blynk Virtual Pins
#define VIRTUAL_PIN_VIBRATION V1

// Timer settings
BlynkTimer timer;

// Function prototypes
void checkVibration();

void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  // Set buzzerPin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Ensure buzzer is off at start

  timer.setInterval(1000, checkVibration);
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkVibration() {
  int vibrationValue = analogRead(vibrationPin);

  Blynk.virtualWrite(VIRTUAL_PIN_VIBRATION, vibrationValue);

  if (vibrationValue > threshold) {
    Serial.println("Vibration detected!");
    Blynk.logEvent("earthquake_alert", "Earthquake Alert! - Lindungi dan selamtkan diri Anda");

    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }
}
