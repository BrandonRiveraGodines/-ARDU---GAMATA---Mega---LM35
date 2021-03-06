// Realizado por y para GAMATA.
// Está tan completo que es solo comentar y descomentar lineas. Un saludo para la raza que la sigue cotorreando.

// Defines para los motores.
#define IN1  53   // Pines para M1-1        MOTOR CABLES VERDES 
#define IN2  51   // Pines para M1-1
#define IN3  49   // Pines para M1-1
#define IN4  47   // Pines para M1-1
#define IN5 52    // Pines para M1-2        MOTOR CABLES AMARILLO
#define IN6 50    // Pines para M1-2
#define IN7 48    // Pines para M1-2
#define IN8 46    // Pines para M1-2
#define ON1 45     // Pines para M2-1       MOTOR CABLES GRIS
#define ON2 43     // Pines para M2-1
#define ON3 41     // Pines para M2-1
#define ON4 39     // Pines para M2-1
#define ON5 44     // Pines para M2-2       MOTOR CABLES NARANJA
#define ON6 42     // Pines para M2-2
#define ON7 40     // Pines para M2-2
#define ON8 38     // Pines para M2-2
#define LM35_PIN 2 // Pines para LM 35.

// Defines para los DHT
#include "DHT.h"  // Cargamos la libreria DHT
#define DHTPIN_1 37  // Pin para el sensor DHT22 #1
#define DHTPIN_2 35  // Pin para el sensor DHT22 #2
// #define DHTPIN_3 33 //  Pin para el sensor DHT22 #3
#define DHTTYPE DHT22 // SE selecciona el tipo de DHT (hay otros DHT)

// Defines para la fotoresistencia
#define ResLight 15  // Resistencia a la luz (10 lux) en Kilo Ohms
#define ResCalib 10  // Resistencia calibración en KiloOhms
#define ResOscu 1000 // Resistencia en oscuridad en KiloOhms

// Defines para el riego y para el fertilizante.
#define AguaPIN 33 // Pin para el riego del agua
#define FertPIN 31 // PIN para el riego del agua

String comando;
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
int Paso2 [ 8 ][ 4 ] =
{ {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int Paso3 [ 8 ][ 4 ] =
{ {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int Paso4 [ 8 ][ 4 ] =
{ {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};


// Variables necesarias para el DHT
DHT dht_1(DHTPIN_1, DHTTYPE); // Se inicia una variable que será usada por Arduino para comunicarse con el sensor.
DHT dht_2(DHTPIN_2, DHTTYPE); // Se inicia otra variable que será usada por Arduino para comunicarse con el sensor.
// DHT dht_3(DHTPIN_3, DHTTYPE); // SE inicia otra variable que será usada por Arduino para comunicarse con el sensor.
float temp, hum; // Se crean variables para obtener los datos.
int c = 0, b = 0;

// Variables necesarias para la resistencia foto.
const int LDRPin = 0;
const int LDRPin2 = 1;
int V, ilum, ilum2;

void setup() {
  // Setup necesario para los motores
  analogReference(INTERNAL1V1);
  Serial.begin(9600);
  comando.reserve(200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  pinMode(ON1, OUTPUT);
  pinMode(ON2, OUTPUT);
  pinMode(ON3, OUTPUT);
  pinMode(ON4, OUTPUT);

  pinMode(ON5, OUTPUT);
  pinMode(ON6, OUTPUT);
  pinMode(ON7, OUTPUT);
  pinMode(ON8, OUTPUT);

  // Setup necesario para los sensores DHT22
  dht_1.begin(); // Se inicia el sensor (1).
  dht_2.begin(); // Se inicia el sensor (2).
  // dht_3.begin(); // Se inicia el sensor(3).
  pinMode(DHTPIN_1, OUTPUT);
  pinMode(DHTPIN_2, OUTPUT);
  // pinMode(DHTPIN_3, OUTPUT);

  // Setup necesario para el riego y la fertilizacion
  pinMode(AguaPIN, OUTPUT);
  pinMode(FertPIN, OUTPUT);

  comando.reserve(200);


  //Establecer la temperatura máxima
  // setTempHum();
  //temp = 30;
}

void loop() {
  // leerDHTs();
  // comandos();
  digitalWrite(AguaPIN, HIGH);
  digitalWrite(FertPIN, HIGH);
  if (!stringComplete) {
    if (comando.equals("subir")) {
      Direction = true;
      Direction2 = false;
      motores();
      comando = "";
      estado_cortinas = "1";
    }

    if (comando.equals("subirm")) {
      Direction = true;
      Direction2 = false;
      motores2();
      comando = "";
      estado_maya = "1";
    }

    else if (comando.equals("bajar")) {
      Direction = false;
      Direction2 = true;
      motores();
      comando = "";
      estado_cortinas = "0";
    }

    else if (comando.equals("bajarm")) {
      Direction = false;
      Direction2 = true;
      motores2();
      comando = "";
      estado_maya = "0";
    }

    else if (comando.equals("setear")) {
      setTempHum();
      comando = "";
    }

    else if (comando.equals("leerTempHum")) {
      leerDHTs();
      // leerLM();
      comando = "";
    }

    else if (comando.equals("getLums")) {
      leerLums();
      comando = "";
    }

    else if (comando.equals("regar")) {
      // regar();
      digitalWrite(AguaPIN, LOW);
      delay(4000);
      digitalWrite(AguaPIN, HIGH);
      delay(200);
      comando = "";
    }

    else if (comando.equals("fertilizar")) {
      fertilizar();
      comando = "";
    }

    else if (comando.equals("activalm")) {
      leerLM();
      comando = "";
    }
    //leerLM();
  }
}
/*
    Inicia el codigo para el motor
*/
void motores() {
  for (int a = 0; a < 3; a++) {
    while (steps_left > 0) {
      stepper();    // Avanza un paso   // VERDE
      stepper2();       // gris
      //stepper3();       // AMARILLO<
      //stepper4();     // NARANJA
      steps_left-- ;  // Un paso menos
      delay (1) ;
    }
    // steps_left = 4095;
    steps_left = 2500;
  }
  delay(4000);
}

void motores2() {
  for (int a = 0; a < 3; a++) {
    while (steps_left > 0) {
      stepper3();    // Avanza un paso   // VERDE
      stepper4();       // gris
      //stepper3();       // AMARILLO<
      //stepper4();     // NARANJA
      steps_left-- ;  // Un paso menos
      delay (1) ;
    }
    // steps_left = 4095;
    steps_left = 2500;
  }
  delay(4000);
}

void stepper() {
  //digitalWrite( IN5, Paso2[Steps][ 0] );
  //digitalWrite( IN6, Paso2[Steps][ 1] );
  //digitalWrite( IN7, Paso2[Steps][ 2] );
  //digitalWrite( IN8, Paso2[Steps][ 3] );
  digitalWrite( ON5, Paso4[Steps][ 0] );
  digitalWrite( ON6, Paso4[Steps][ 1] );
  digitalWrite( ON7, Paso4[Steps][ 2] );
  digitalWrite( ON8, Paso4[Steps][ 3] );
  SetDirection();
}

void stepper2() {
  //digitalWrite( ON1, Paso3[Steps][ 0] );
  //digitalWrite( ON2, Paso3[Steps][ 1] );
  //digitalWrite( ON3, Paso3[Steps][ 2] );
  //digitalWrite( ON4, Paso3[Steps][ 3] );
  digitalWrite( IN1, Paso[Steps2][ 0] );
  digitalWrite( IN2, Paso[Steps2][ 1] );
  digitalWrite( IN3, Paso[Steps2][ 2] );
  digitalWrite( IN4, Paso[Steps2][ 3] );
  SetDirection2();
}

void stepper3() {
  digitalWrite( IN5, Paso2[Steps][ 0] );
  digitalWrite( IN6, Paso2[Steps][ 1] );
  digitalWrite( IN7, Paso2[Steps][ 2] );
  digitalWrite( IN8, Paso2[Steps][ 3] );
  //digitalWrite( ON5, Paso4[Steps][ 0] );
  //digitalWrite( ON6, Paso4[Steps][ 1] );
  //digitalWrite( ON7, Paso4[Steps][ 2] );
  //digitalWrite( ON8, Paso4[Steps][ 3] );
  SetDirection();
}

void stepper4() {
  digitalWrite( ON1, Paso3[Steps][ 0] );
  digitalWrite( ON2, Paso3[Steps][ 1] );
  digitalWrite( ON3, Paso3[Steps][ 2] );
  digitalWrite( ON4, Paso3[Steps][ 3] );
  //digitalWrite( IN1, Paso[Steps2][ 0] );
  //digitalWrite( IN2, Paso[Steps2][ 1] );
  //digitalWrite( IN3, Paso[Steps2][ 2] );
  //digitalWrite( IN4, Paso[Steps2][ 3] );
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
  float h = dht_1.readHumidity(); // Lee la humedad del primer sensor.
  // float h2 = dht_2.readHumidity(); // Lee la humedad del segundo sensor.
  // float h3 = dht_3.readHumidity(); // Lee la humedad del tercer sensor.
  float t = dht_1.readTemperature(); // Lee la temperatura del primer sensor.
  // float t2 = dht_2.readTemperature(); // Lee la temperatura del segundo sensor.
  // float t3 = dht_3.readTemperature(); // Lee la temperatura del tercer sensor.
  //float h = (h1 + h2 + h3) / 3;
  //float t = (t1 + t2 + t3) / 3;

  Serial.println(t);
  Serial.println(h);
  Serial.println("CACA");

  // Serial.println(h);
  // Serial.println(t);
  /*
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
  */
}
/*
   Terminan los codigos de DHT22
*/
/*
   Comienzan los codigos para luminocidad
*/
void leerLums() {
  //ilum = ((long)(1024-V)*ResOscu*10)/((long)ResLight*ResCalib*V); // Usar si LDR entre GND y A0
  //ilum = ((long)V*ResOscu*10)/((long)ResLight*ResCalib*(1024-V)); // Usar si LDR entre A0 y Vcc (como en el esquema anterior)
  ilum = analogRead(LDRPin);
  Serial.println(ilum);
  delay(1000);
  //ilum2 = analogRead(LDRPin2);
  //ilum = (ilum + ilum2) / 2;
}
/*
   Terminan los codigos para luminocidad
*/

/*
   Comienzan los codigos para regar y fertilizar.
*/
void regar() {
  /*
    digitalWrite(AguaPIN, HIGH);
    delay(4000);
    digitalWrite(AguaPIN, LOW);
    delay(200);
  */
}

void fertilizar() {
  digitalWrite(FertPIN, LOW);
  delay(4000);
  digitalWrite(FertPIN, HIGH);
  delay(200);
}
/*
   Terminan los codigos de rogar y fertilizar.
*/
/*
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\r') continue;
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      comando += inChar;
    }
  }
}
*/

void leerLM() {
  int input = analogRead(LM35_PIN);    // Obtengo el valor sensado por el LM35
  float mv  = (1100 / 1024.0) * input; // Convierto el valor leido a mV (ahora el "tope" es de 1100mV)
  float cel = mv / 10;                 // Convierto los mV leidos a grados celsius
  Serial.println(cel);
  delay(1000);
}

void comandos() {
  Serial.println("Dame un comando");
  comando = Serial.readString();
}


