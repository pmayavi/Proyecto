#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "kleema-549fd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "PvxAFk39PlQFvKaEgljemAa4g1ObufcN7sEG5rTj"
#define WIFI_SSID "MAYA"
#define WIFI_PASScomD "71666348"

String com;
int chk;
float Temp = 0;
float Hum = 0;
bool Pluv = false;
bool Sol = false;

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASScomD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  readSerial();
  interpretar();
  Send();
  delay(5);
}

void interpretar() {
  Serial.println(com);
  if (com.indexOf("Datos") != -1) {
    if (com.indexOf("temp=") != -1)
      Temp = com.substring(com.indexOf("temp=") + 5, com.indexOf("hum=")).toFloat();
    if (com.indexOf("hum=") != -1)
      Hum = com.substring(com.indexOf("hum=") + 4, com.indexOf("pluv=")).toFloat();
    if (com.indexOf("pluv=") != -1)
      Pluv = com.substring(com.indexOf("pluv=") + 5, com.indexOf("sol=")).toInt() == 1;
    if (com.indexOf("sol=") != -1)
      Sol = com.substring(com.indexOf("sol=") + 4, com.indexOf("Fin")).toInt() == 1;
  }
}

void readSerial() {
  if (Serial.available()) {
    if(Serial.read() == '['){
      com = Serial.readStringUntil(']');
    }
  }
}

void Send() {
  Firebase.setFloat("Temp", Temp);
  Firebase.setFloat("Hum", Hum);
  Firebase.setBool("Pluv", Pluv);
  Firebase.setBool("Sol", Sol);
}
