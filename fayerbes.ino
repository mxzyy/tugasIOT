#include <HCSR04.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "akusaja"
#define WIFI_PASS "123456789"

#define API_KEY "AIzaSyBbLU7PoWox4mR9cFWxvdmP4w-Q-8QUK8o"
#define DATABASE_URL "https://ultrasonic-fc2c3-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

const int trigPin = 12; // d6
const int echoPin = 14; // d5

#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting To Wifi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
    }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("OK");
    signupOK = true;
    }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }
  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.ready() == signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
      sendDataPrevMillis = millis();

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distanceCm = duration * SOUND_VELOCITY/2;
      distanceInch = distanceCm * CM_TO_INCH;

      Serial.print("Distance (cm): ");
      Serial.println(distanceCm);
      Serial.print("Distance (inch): ");
      Serial.println(distanceInch);

      if (Firebase.RTDB.setFloat(&fbdo, "test/distanceCm", distanceCm)){
        Serial.println("PASSED");
        Serial.println("PATH : " + fbdo.dataPath());
        Serial.println("TYPE : " + fbdo.dataType());
        }
      else{
        Serial.print("FAILED");
        Serial.print("REASON : " + fbdo.errorReason());
        }
      count++;
      if (Firebase.RTDB.setFloat(&fbdo, "test/distanceInch", distanceInch)){
        Serial.println("PASSED");
        Serial.println("PATH : " + fbdo.dataPath());
        Serial.println("TYPE : " + fbdo.dataType());
        }
      else{
        Serial.print("FAILED");
        Serial.print("REASON : " + fbdo.errorReason());
        } 
    }
}
