#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiClient client;

unsigned long channelID = YOUR_CHANNEL_ID;
const char* apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

void setup() {

  // UART communication with Arduino
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  // Start ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {

  if (Serial.available()) {

    // Receive four LDR values from Arduino
    int ldr1 = Serial.parseInt();
    int ldr2 = Serial.parseInt();
    int ldr3 = Serial.parseInt();
    int ldr4 = Serial.parseInt();

    // Display received values
    Serial.print("LDR1: ");
    Serial.println(ldr1);

    Serial.print("LDR2: ");
    Serial.println(ldr2);

    Serial.print("LDR3: ");
    Serial.println(ldr3);

    Serial.print("LDR4: ");
    Serial.println(ldr4);

    // Send values to ThingSpeak
    ThingSpeak.setField(1, ldr1);
    ThingSpeak.setField(2, ldr2);
    ThingSpeak.setField(3, ldr3);
    ThingSpeak.setField(4, ldr4);

    int response = ThingSpeak.writeFields(channelID, apiKey);

    if (response == 200) {
      Serial.println("Data uploaded successfully!");
    }
    else {
      Serial.print("ThingSpeak error: ");
      Serial.println(response);
    }

    // ThingSpeak requires at least 15 seconds between updates
    delay(15000);
  }
}
