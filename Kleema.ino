static int TEMP = A0;
static int HUM = A1;
static int PLUV = A2;
static int SOL = A3;

double temp = 0;//Grados centrigrados 
double hum = 0;//Porcentaje de humedad
double pluv = 0;//Milimetros de lluvia
double sol = 0;//Horas de sol

void setup() {
  pinMode(TEMP, INPUT);
  pinMode(HUM, INPUT);
  pinMode(PLUV, INPUT);
  pinMode(SOL, INPUT);

  Serial.begin(9600);
}

void loop() {
  data();

  alert();

  sendData();
}

//Colectar la data
void data(){
  temp = (((analogRead(TEMP) * 5.0 / 1023.0 * 1000.0) - 100) / 10) - 40;
  delay(50);
  
  hum = analogRead(HUM) / 10.23;
  delay(50);
  
  pluv = analogRead(PLUV) / 10.23 / 2.0;
  delay(50);
  
  sol = analogRead(SOL) / 10.23 / 5.0;
  delay(50);
}

//Buscar anomalias
void alert(){
  if(temp < 18)
    Serial.println("ADVERTENCIA LA TEMPERATURA ESTA BAJA");
  else if(temp > 25)
    Serial.println("ADVERTENCIA LA TEMPERATURA ESTA ALTA");

  if(hum < 40)
    Serial.println("ADVERTENCIA LA HUMEDAD ESTA BAJA");
  else if(hum > 60)
    Serial.println("ADVERTENCIA LA HUMEDAD ESTA ALTA");

  if(pluv < 3)
    Serial.println("ADVERTENCIA NO HUBO LLUVIA");
  else if(pluv > 30)
    Serial.println("ADVERTENCIA LLUVIA ALTA");

  if(sol < 5)
    Serial.println("ADVERTENCIA SE PRESENTO POCAS HORAS DE SOL");
  else if(sol > 12)
    Serial.println("ADVERTENCIA SE PRESENTO MUCHAS HORAS DE SOL");
}

//Enviar la data
void sendData(){
  Serial.println(temp);
  Serial.println(hum);
  Serial.println(pluv);
  Serial.println(sol);
  Serial.println();
}
