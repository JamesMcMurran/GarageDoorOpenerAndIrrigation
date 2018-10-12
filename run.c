#include <ESP8266WiFi.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";
char ssid[] = "";
char pass[] = "";

int garageStatus = 0; 

BlynkTimer timer;

void loop()
{
  timer.run(); // Initiates BlynkTimer
  Blynk.run();
  
}

void setup() {

  pinMode(5, OUTPUT);
  
  // Debug console
  Serial.begin(9600);
  Serial.print("Blynk Connecting");
  Blynk.begin(auth, ssid, pass);
  Serial.print("Blynk Connected");
  
  // Setup a function to be called every second
  timer.setInterval(500L, turnOffGarage);

}

BLYNK_CONNECTED() {
    #Blynk.syncAll();
    Blynk.syncVirtual(V1)
}

BLYNK_WRITE(V1){
  garageStatus = param.asInt();
}

void turnOffGarage( ){
  if( digitalRead(4)== LOW ){
    digitalWrite(4, HIGH);
    garageStatus =0 ;
    Blynk.virtualWrite(1, 0);
  }else if( garageStatus ==1){
    digitalWrite(4, LOW);
  }
  
}
