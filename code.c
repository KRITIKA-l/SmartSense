#include <ESP8266WiFi.h>       // Library for ESP8266 WiFi connection
#include <ESP8266HTTPClient.h> // Library for HTTP requests

// WiFi credentials
const char* ssid = "name"; 
const char* password = "password";

// ThingSpeak API details
const char* apiKey = "api_key";
const char* thingspeakServer = "http://api.thingspeak.com/update";

// Initialize WiFi client
WiFiClient wifiClient;

// Sensor and LED pin assignments
int sensor1 = D5, led1 = D2;
int sensor2 = D6, led2 = D3;
int sensor3 = D7, led3 = D4;

// Counters for feedback collection
int count1 = 0, count2 = 0, count3 = 0;

//Sends collected data to ThingSpeak
void sendToThingSpeak(int count, int field) 
{
  if (WiFi.status() == WL_CONNECTED) // Check if WiFi is connected
  {
    HTTPClient http;
    
    // Construct ThingSpeak API URL
    String url = String(thingspeakServer) + "?api_key=" + apiKey + "&field" + String(field) + "=" + String(count);
    
    http.begin(wifiClient, url); // Start HTTP request
    http.GET();                  // Send GET request
    http.end();                   // Close connection
    
    delay(2000); // Delay to prevent frequent requests
  }
}

void setup() 
{
  Serial.begin(9600); // Initialize serial communication for debugging
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("."); // Print progress dots while connecting
  }
  Serial.println("\nWiFi connected");

  // Set sensor pins as input
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  
  // Set LED pins as output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() 
{
  // Check if sensor1 is triggered
  if (digitalRead(sensor1) == LOW) 
  {
    count1++;                 // Increment counter for sensor1
    digitalWrite(led1, HIGH); // Turn on LED1
    sendToThingSpeak(count1, 1); // Send data to ThingSpeak
    delay(200);               // Short delay
    digitalWrite(led1, LOW);  // Turn off LED1
  }

  // Check if sensor2 is triggered
  if (digitalRead(sensor2) == LOW) 
  {
    count2++;                 // Increment counter for sensor2
    digitalWrite(led2, HIGH); // Turn on LED2
    sendToThingSpeak(count2, 2); // Send data to ThingSpeak
    delay(200);               // Short delay
    digitalWrite(led2, LOW);  // Turn off LED2
  }

  // Check if sensor3 is triggered
  if (digitalRead(sensor3) == LOW) 
  {
    count3++;                 // Increment counter for sensor3
    digitalWrite(led3, HIGH); // Turn on LED3
    sendToThingSpeak(count3, 3); // Send data to ThingSpeak
    delay(200);               // Short delay
    digitalWrite(led3, LOW);  // Turn off LED3
  }
}