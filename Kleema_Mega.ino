static int TEMP = A0;
static int PLUV = A1;
static int HUM = A3;
static int SOL = A5;

double temp = 0;//Grados centrigrados
double hum = 0;//Porcentaje de humedad
double pluv = 0;//Milimetros de lluvia
double sol = 0;//Horas de sol

void setup() {
  pinMode(TEMP, INPUT);
  pinMode(HUM, INPUT);
  pinMode(PLUV, INPUT);
  pinMode(SOL, INPUT);

  pinMode(52, OUTPUT);
  digitalWrite(52, HIGH);

  Serial.begin(9600);
}

void loop() {
  data();

  alert();

  sendData();
}

//Colectar la data
void data() {
  temp = (((analogRead(TEMP) * 5.0 / 1023.0 * 1000.0) - 100) / 10) + 5;
  delay(5);

  hum = 95 - analogRead(HUM) / 10.23;
  delay(5);

  pluv = digitalRead(PLUV);
  delay(5);

  sol = analogRead(SOL) / 10.23 / 5.0;
  delay(5);
}

//Buscar anomalias
void alert() {
  alert(temp, 15, 25, "TEMPERATURA");
  alert(sol, 3, 12, "LUZ");

  if(pluv)
    sendData("__[ESTA LLOVIENDO!]__");
  else
    alert(hum, 30, 60, "HUMEDAD");
}

void alert(int sensor, int bajo, int alto, String tipo) {
  if (sensor < bajo) {
    sendData("__[" + tipo + " BAJA!]__");
    Serial.println();
    delay(500);
  }
  else if (sensor > alto) {
    sendData("__[" + tipo + " ALTA!]__");
    Serial.println();
    delay(500);
  }

}

//Enviar la data
void sendData() {
  sendData("__[Datos_temp=" + String(temp) + "hum=" + String(hum) + "pluv=" + String(pluv) + "sol=" + String(sol) + "Fin]__");
  Serial.println();
  delay(500);
}

void sendData(String peticion) {
  char a[100];
  peticion.toCharArray(a, peticion.length());
  Serial.write(a);
}
