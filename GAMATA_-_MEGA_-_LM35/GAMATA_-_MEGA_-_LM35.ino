// Defines para los motores.
#define IN1  53   // Pines para M1-1
#define IN2  51   // Pines para M1-1
#define IN3  49   // Pines para M1-1
#define IN4  47   // Pines para M1-1

#define IN5 52    // Pines para M1-2
#define IN6 50    // Pines para M1-2
#define IN7 48    // Pines para M1-2
#define IN8 46    // Pines para M1-2

#define ON1 45     // Pines para M2-1
#define ON2 43     // Pines para M2-1
#define ON3 41     // Pines para M2-1
#define ON4 39     // Pines para M2-1

#define ON5 44     // Pines para M2-2
#define ON6 42     // Pines para M2-2
#define ON7 40     // Pines para M2-2
#define ON8 38     // Pines para M2-2

#define LM35_PIN 2 // Pines para LM 35.

// Defines para los DHT
#include "DHT.h"  // Cargamos la libreria DHT
#define DHTPIN_1 37  // Pin para el sensor DHT22 #1
// #define DHTPIN_2 35  // Pin para el sensor DHT22 #2
#define DHTTYPE DHT22 // SE selecciona el tipo de DHT (hay otros DHT)

// Defines para la fotoresistencia
#define ResLight 15  // Resistencia a la luz (10 lux) en Kilo Ohms
#define ResCalib 10  // Resistencia calibración en KiloOhms
#define ResOscu 1000 // Resistencia en oscuridad en KiloOhms

// Defines para el riego y para el fertilizante.
#define AguaPIN 33 // Pin para el riego del agua
#define FertPIN 31 // PIN para el riego del agua

String comando = "subir";
boolean stringComplete = false;

// Variables necesarias para el motor.
int steps_left = 4095;
boolean Direction = true;
boolean Direction2 = true;
int Steps = 0;
int Steps2 = 0;
int a = 0;
int Paso [ 8 ][ 4 ] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

// Variables necesarias para el DHT
DHT dht_1(DHTPIN_1, DHTTYPE); // Se inicia una variable que será usada por Arduino para comunicarse con el sensor
// DHT dht_2(DHTPIN_2, DHTTYPE); // Se inicia otra variable que será usada por Arduino para comunicarse con el sensor
float temp, hum; // Se crean variables para obtener los datos.
int c = 0, b = 0;

// Variables necesarias para la resistencia foto.
const int LDRPin = A1;
int V, ilum;

void setup() {
  // Setup necesario para los motores
  analogReference(INTERNAL1V1);
  Serial.begin(9600);
  comando.reserve(200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ON1, OUTPUT);
  pinMode(ON2, OUTPUT);
  pinMode(ON3, OUTPUT);
  pinMode(ON4, OUTPUT);

  // Setup necesario para los sensores DHT22
  dht_1.begin(); // Se inicia el sensor (1).
  // dht_2.begin(); // Se inicia el sensor (2).
  pinMode(DHTPIN_1, OUTPUT);
  // pinMode(DHTPIN_2, OUTPUT);

  // Setup necesario para el riego y la fertilizacion
  pinMode(AguaPIN, OUTPUT);
  pinMode(FertPIN, OUTPUT);

  //Establecer la temperatura máxima
  // setTempHum();
  temp = 30;
}

void loop() {
  // leerDHTs();
  if (comando.equals("subir")) {
    Direction = false;
    Direction2 = true;
    motores();
    comando = "";
  }

   else if (comando.equals("bajar")) {
    Direction = true;
    Direction2 = false;
    motores();
    comando = "";
  }

  else if (comando.equals("setear")) {
    setTempHum();
    comando = "";
  }

  else if (comando.equals("leerTempHum")) {
    // leerDHTs();
    leerLM();
    comando = "";
  }

  else if (comando.equals("getLums")){
    leerLums();
    comando = "";
  }

  else if (comando.equals("regar")){
    regar();
    comando = "";
  }

  else if (comando.equals("fertilizar")){
    fertilizar();
    comando = "";
  }

  else if (comando.equals("activalm")){
    leerLM();
    comando = "";
  }
}
/*
    Inicia el codigo para el motor
*/
void motores() {
  for (int a = 0; a < 4; a++) {
    while (steps_left > 0) {
      stepper();    // Avanza un paso
      stepper2();
      steps_left-- ;  // Un paso menos
      delay (1) ;
    }
    steps_left = 4095;
  }
  delay(2000);
}

void stepper() {
  digitalWrite( IN1, Paso[Steps][ 0] );
  digitalWrite( IN2, Paso[Steps][ 1] );
  digitalWrite( IN3, Paso[Steps][ 2] );
  digitalWrite( IN4, Paso[Steps][ 3] );
  SetDirection();
}

void stepper2() {
  digitalWrite( ON1, Paso[Steps2][ 0] );
  digitalWrite( ON2, Paso[Steps2][ 1] );
  digitalWrite( ON3, Paso[Steps2][ 2] );
  digitalWrite( ON4, Paso[Steps2][ 3] );
  SetDirection2();
}

void SetDirection() {
  if (Direction)
    Steps++;
  else
    Steps--;
  Steps = ( Steps + 7 ) % 7 ;
}

void SetDirection2() {
  if (Direction2)
    Steps2++;
  else
    Steps2--;
  Steps2 = ( Steps2 + 7 ) % 7 ;
}
/*
   Terminan los codigos para los motores
*/

/*
   Comienzan los codigos para los DHT22
*/
void setTempHum() {
  Serial.println("Favor de introducir la temperatura estandar.");
  while (c == 0) {
    temp = Serial.parseFloat();
    delay(500);
    if (temp) {
      c = 1;
    }
  }
  Serial.println("Favor de introdicr la humedad estandar.");
  while (b == 0) {
    hum = Serial.parseFloat();
    delay(500);
    if (hum) {
      b = 1;
    }
  }
}

void leerDHTs() {
  float h1 = dht_1.readHumidity(); // Lee la humedad del primer sensor.
  // float h2 = dht_2.readHumidity(); // Lee la humedad del segundo sensor
  float t1 = dht_1.readTemperature(); // Lee la temperatura del primer sensor.
  // float t2 = dht_2.readTemperature(); // Lee la temperatura del segundo sensor.
  //float h = (h1 + h2) / 2;
  //float t = (t1 + t2) / 2;

  Serial.println(t1);
  Serial.println(h1);
  
  if (t1 >= temp) {
    Direction = true;
    Direction2 = false;
    motores();
  }
  if (t1 < temp) {
    Direction = false;
    Direction2 = true;
    motores();
  }
}
/*
 * Terminan los codigos de DHT22
 */
/*
 * Comienzan los codigos para luminocidad
 */
void leerLums(){
  //ilum = ((long)(1024-V)*ResOscu*10)/((long)ResLight*ResCalib*V); // Usar si LDR entre GND y A0
  //ilum = ((long)V*ResOscu*10)/((long)ResLight*ResCalib*(1024-V)); // Usar si LDR entre A0 y Vcc (como en el esquema anterior)
  ilum = analogRead(LDRPin);
  Serial.println(ilum);
  delay(1000);
}
/*
 * Terminan los codigos para luminocidad
 */

 /*
  * Comienzan los codigos para regar y fertilizar.
  */
void regar(){
  digitalWrite(AguaPIN, HIGH);
  delay(4000);
  digitalWrite(AguaPIN, LOW);
  delay(200);
}

void fertilizar(){
  digitalWrite(FertPIN, HIGH);
  delay(4000);
  digitalWrite(FertPIN, LOW);
  delay(200);
}
/*
 * Terminan los codigos de rogar y fertilizar.
 */


void serialEvent(){
  while(Serial.available()){
    char inChar = (char)Serial.read();
    if (inChar == '\r') continue;
    if(inChar == '\n'){
      stringComplete = true;
    } else {
      comando += inChar;
    }
  }
}

void leerLM(){
  int input = analogRead(LM35_PIN);    // Obtengo el valor sensado por el LM35
  float mv  = (1100 / 1024.0) * input; // Convierto el valor leido a mV (ahora el "tope" es de 1100mV)
  float cel = mv / 10;                 // Convierto los mV leidos a grados celsius
  Serial.println(cel);
  delay(1000); 
}

