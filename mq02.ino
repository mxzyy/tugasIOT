#include <BlynkSimpleESP8266.h>

#define BLYNK_TEMPLATE_ID "TMPL6pEv8sw_9"
#define BLYNK_TEMPLATE_NAME "GAS"
#define BLYNK_AUTH_TOKEN "9Pmm7oUXC8FnMXGhuWUW4W_6O8DOm8zM"

char auth[] = BLYNK_AUTH_TOKEN
char ssid[] = "andaikan"
char pass[] = "123456789"

#define MQ02DPin 0 //D3
#define MQ02APin A0
#define BuzzerPin 4 //D2
int maxValue = 500; //Value jika terjadi kebocoran gas

void setup() {
  // put your setup code here, to run once:
  pinMode(MQ02DPin, INPUT);
  pinMode(MQ02APin, INPUT);
  pinMode(BuzzerPin, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogMQ02 = analogRead(MQ02APin);
  Serial.print("MQ02 Analog : ");
  Serial.println(analogMQ02);
  Blynk.virtualWrite(V0, analogMQ02);
  if (analogMQ02 >= maxValue){
    Blynk.virtualWrite(V1, "Terjadi kebocoran Gas!");
    digitalWrite(BuzzerPin, HIGH);
  }else{
    Blynk.virtualWrite(V1, "Gas dalam keadaan aman");
    digitalWrite(BuzzerPin, LOW);
  }
  Blynk.run();
}
