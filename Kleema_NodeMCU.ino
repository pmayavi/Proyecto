// Agregar librerias básicas para configurar el node MCU
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

char cha;
String wor;
double Temp = 0;
double Hum = 0;
double Pluv = 0;
double Sol = 0;
char token[] = "GPbFO9dAP-pBMMEe0kpaUTDRdoECWa7W";
//BlynkTimer timer;
WidgetLCD lcd(V4);

void setup() {
  Serial.begin(9600);
  //timer.setInterval(2000L, sendInfo); //Cada 2 mil mili llamar la funcion sensor
  Blynk.begin(token, "Salomon", "marianuwu");
}

void loop() {
  readSerial();
  interpretar();
  sendInfo();
  alert();
  wor = "";
  delay(5);
}

void interpretar(){
  Serial.println(wor);
  if (wor.indexOf("Datos") != -1) {
    if(wor.indexOf("temp=") != -1)
      Temp = wor.substring(wor.indexOf("temp=") + 5, wor.indexOf("hum=")).toDouble();
    if(wor.indexOf("hum=") != -1)
      Hum = wor.substring(wor.indexOf("hum=") + 4, wor.indexOf("pluv=")).toDouble();
    if(wor.indexOf("pluv=") != -1)
      Pluv = wor.substring(wor.indexOf("pluv=") + 5, wor.indexOf("sol=")).toDouble();
    if(wor.indexOf("sol=") != -1)
      Sol = wor.substring(wor.indexOf("sol=") + 4, wor.indexOf("Fin")).toDouble();
  }
}

void readSerial() {
  if (Serial.available()) {
    cha = Serial.read();
    if (cha = '[') {
      while (Serial.available() && cha != ']') {
        wor += cha;
        cha = Serial.read();
      }
    }
  }
}

void sendInfo() {
  Blynk.virtualWrite(V0, Temp);
  Blynk.virtualWrite(V1, Hum);
  Blynk.virtualWrite(V2, Pluv);
  Blynk.virtualWrite(V3, Sol);
}

void alert(){
  if (wor.indexOf("!") != -1){
    wor.replace("[","");
    wor.replace("_","");
    lcd.print(0,0,wor);
  } else lcd.clear();
}
