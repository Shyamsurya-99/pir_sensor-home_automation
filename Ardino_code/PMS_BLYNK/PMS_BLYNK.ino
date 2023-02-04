#define BLYNK_TEMPLATE_ID "TMPLnTkcjjCR"
#define BLYNK_DEVICE_NAME "motion detection01"
#define BLYNK_AUTH_TOKEN            "eZoKVB0BgOc8I4xKUHJXC3OF_Y90UQw0"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OnePlus8";
char pass[] = "haha@6996";
int pinValue = 0;

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  if(value==1){
    Serial.println("System is OFF");  
    digitalWrite(2, LOW);
  }
  else{
    Serial.println("System is ON");  
    digitalWrite(2, HIGH);
  }
}
void motionDetection()
{
  bool sensor = digitalRead(14);
  if(sensor==1){
    Blynk.logEvent("motion_detected");
    Serial.println("motion detected");
    digitalWrite(4, HIGH);
    while(sensor==1){
      digitalWrite(2, LOW);
      delay(500);
      digitalWrite(2,HIGH);
      delay(500);
     }
  }
 else{
  digitalWrite(2,HIGH);
 }
}

void setup()
{
  // Debug console
  Serial.begin(115200);  
  pinMode(14, INPUT);//PIR SENSOR
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, motionDetection);
}

void loop()
{
  Blynk.run();
  timer.run();
}
