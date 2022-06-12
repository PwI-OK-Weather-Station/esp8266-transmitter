
#include "Arduino.h"
#include "ArduinoJson.h"
#include "Esp.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include "SoftwareSerial.h"

SoftwareSerial linkSerial(13, 15);
HTTPClient http;
WiFiClient client;

bool sendData(String data){
  if(WiFi.status()==WL_CONNECTED){
    http.addHeader("Content-Type", "application/json");
    int status = http.PUT(data);
    return (status==200)?true:false;
  }
  return false;
}

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(115200);
  Serial.setTimeout(30000);
  WiFi.begin("iot_project", "krkjkkkk"); 
 linkSerial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
  }

  if(WiFi.status()== WL_CONNECTED){
    Serial.println(WiFi.localIP());
    String server = "http://192.168.1.209:1880/weather";
    http.begin(client, server);
  }
}

void loop()
{
  
  if (linkSerial.available()) 
  {
    // Allocate the JSON document
    // This one must be bigger than for the sender because it must store the strings
    String x = linkSerial.readStringUntil('\n');
    sendData(x);
  }
}
