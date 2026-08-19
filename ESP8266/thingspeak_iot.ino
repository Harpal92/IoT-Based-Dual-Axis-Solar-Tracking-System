#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiClient client;

unsigned long channelID = YOUR_CHANNEL_ID;
const char* apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

void setup() {

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  ThingSpeak.begin(client);
}

void loop() {

  if (Serial.available()) {

    int ldr1 = Serial.parseInt();
    int ldr2 = Serial.parseInt();

    Serial.print("LDR1: ");
    Serial.print(ldr1);

    Serial.print(" LDR2: ");
    Serial.println(ldr2);

    ThingSpeak.setField(1, ldr1);
    ThingSpeak.setField(2, ldr2);

    ThingSpeak.writeFields(channelID, apiKey);
  }

  delay(15000);
}