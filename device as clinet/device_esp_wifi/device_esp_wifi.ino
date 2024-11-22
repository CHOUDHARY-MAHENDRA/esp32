#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your Wi-Fi credentials
const char* ssid = "...";
const char* password = "....";

// Replace with ESP32A's IP address
const char* esp32A_IP = "x.x.x.x";

const int buttonPin = 4;
bool lastButtonState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.print("ESP32B IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    toggleLED();
    delay(300); // Debounce delay
  }
  lastButtonState = buttonState;
}

void toggleLED() {
  static bool ledState = false;
  HTTPClient http;

  String url = String("http://") + esp32A_IP + (ledState ? "/led/off" : "/led/on");
  Serial.print("Sending request to: ");
  Serial.println(url);

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.println("Response: " + http.getString());
    ledState = !ledState;
  } else {
    Serial.print("Error: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
