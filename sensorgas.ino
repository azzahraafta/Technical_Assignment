#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TOKO MBAK KUM";
const char* password = "sekawan007";
const char* serverName = "http://192.168.1.3:5000/gassensor/data";

const int gasPin = 34;  // Pin sensor gas terhubung ke GPIO 34 pada ESP32

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(gasPin, INPUT);
}

void loop() {
  int gasValue = analogRead(gasPin);  // Baca nilai dari sensor gas

  // Kirim data setiap 10 detik
  postData(gasValue);
  delay(10000);  // Delay 10 detik
}

void postData(int gasValue) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "gas=" + String(gasValue);
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}
