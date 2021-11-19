#include <DHT.h>

#define PLUV    A0
#define SOL     A2
#define DHTPIN  A1       // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
float temp = 0;//Grados centrigrados
float hum = 0;//Porcentaje de humedad
bool pluv = 0;//Milimetros de lluvia
bool sol = 0;//Horas de sol

void setup() {
  pinMode(PLUV, INPUT);
  pinMode(SOL, INPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  data();
  Send();
}

//Colectar la data
void data() {
  temp = dht.readTemperature();
  delay(5);

  hum = dht.readHumidity();
  delay(5);

  pluv = digitalRead(PLUV);
  delay(5);

  sol = analogRead(SOL) < 500;
  delay(5);
}


//Enviar la data
void Send() {
  Serial.println(" [Datos_temp=" + String(temp) + "hum=" + String(hum) + "pluv=" + String(pluv) + "sol=" + String(sol) + "Fin] ");
  delay(500);
}

void sen(String peticion) {
  char a[100];
  peticion.toCharArray(a, peticion.length());
  Serial.write(a);
}
