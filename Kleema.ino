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
  temp = analogRead(TEMP);
  delay(50);
  
  hum = analogRead(HUM);
  delay(50);
  
  pluv = analogRead(PLUV);
  delay(50);
  
  sol = analogRead(SOL);
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
  else if(temp > 12)
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
