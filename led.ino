#include <BlynkSimpleESP8266.h>

#define BLYNK_TEMPLATE_ID "TMPL6BJLsLngG"
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN "c-G8B_Kx-EjJ1cg8vK8SAzpGGWMtwoh4"

char auth[] = BLYNK_AUTH_TOKEN
char ssid[] = "andaikan"
char pass[] = "123456789"

#define LedPin 0 

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  if (pinValue == 1){
    digitalWrite(LedPin, HIGH);
    Serial.print("Lampu : ");
    Serial.println("High");
  }else{
    digitalWrite(LedPin, LOW);
    Serial.print("Lampu : ");
    Serial.println("Low");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run()
}
