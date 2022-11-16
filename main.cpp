#include <Arduino.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int pinservo1 = 2;
int pinservo2 = 3;
int pinservo3 = 4;
int pinservo4 = 5;
int pinservo5 = 6;

// Config
#define ENABLE true
int Sensores[5] = {A0, A1, A2, A3, A4}; // Entradas donde esta conectado el sensor. El primero debe ser el menique, el segundo el anular, etc.. hasta terminar en el pulgar (orden de mano izquierda)
float EST_NORMAL = 0.0; // Resistencia que entrega cuando el sensor no esta flexionado
float EST_DOBLADO = 4755.0; // Resistencia que entrega cuando el sensor esta completamente flexionado
float MAX_DEGREES = 180.0; // Grados maximos a girar
float V3 = 3.355; // Voltaje exacto que entrega en la salida 3.3v el Arduino
float Res = 10000.0; // La resistencia que se usa para el divisor de voltaje

void setup() {
  servo1.attach(pinservo1, 610, 2550);
  servo2.attach(pinservo2, 670, 2540);
  servo3.attach(pinservo3, 660, 2600);
  servo4.attach(pinservo4, 660, 2600);
  servo5.attach(pinservo5, 660, 2600);
  pinMode(pinservo1, OUTPUT);
  pinMode(pinservo2, OUTPUT);
  pinMode(pinservo3, OUTPUT);
  pinMode(pinservo4, OUTPUT);
  pinMode(pinservo5, OUTPUT);

  pinMode(Sensores[0], INPUT);
  pinMode(Sensores[1], INPUT);
  pinMode(Sensores[2], INPUT);
  pinMode(Sensores[3], INPUT);
  pinMode(Sensores[4], INPUT);

  Serial.begin(9600);
}

void loop() {
  int s1 = analogRead(Sensores[0]);
  float v_s1 = s1 * V3 / 1023.0;
  float r_s1 = Res * (V3 / v_s1 - 1.0);
  float angle_s1 = map(r_s1, EST_NORMAL, EST_DOBLADO, 0, MAX_DEGREES);

  int s2 = analogRead(Sensores[1]);
  float v_s2 = s2 * V3 / 1023.0;
  float r_s2 = Res * (V3 / v_s2 - 1.0);
  float angle_s2 = map(r_s2, EST_NORMAL, EST_DOBLADO, 0, MAX_DEGREES);

  int s3 = analogRead(Sensores[2]);
  float v_s3 = s3 * V3 / 1023.0;
  float r_s3 = Res * (V3 / v_s3 - 1.0);
  float angle_s3 = map(r_s3, EST_NORMAL, EST_DOBLADO, 0, MAX_DEGREES);

  int s4 = analogRead(Sensores[3]);
  float v_s4 = s4 * V3 / 1023.0;
  float r_s4 = Res * (V3 / v_s4 - 1.0);
  float angle_s4 = map(r_s4, EST_NORMAL, EST_DOBLADO, 0, MAX_DEGREES);

  int s5 = analogRead(Sensores[4]);
  float v_s5 = s5 * V3 / 1023.0;
  float r_s5 = Res * (V3 / v_s5 - 1.0);
  float angle_s5 = map(r_s5, EST_NORMAL, EST_DOBLADO, 0, MAX_DEGREES);

  #if ENABLE == true
  if(angle_s1 >= 0 && angle_s1 <= MAX_DEGREES)
    servo4.write(angle_s1); // Menique
  
  if(angle_s2 >= 0 && angle_s2 <= MAX_DEGREES)
    servo3.write(angle_s2); // Anular
  
  if(angle_s3 >= 0 && angle_s3 <= MAX_DEGREES)
    servo2.write(angle_s3); // Corazon
  
  if(angle_s4 >= 0 && angle_s4 <= MAX_DEGREES)
    servo1.write(angle_s4); // indice
  
  if(angle_s5 >= 0 && angle_s5 <= MAX_DEGREES)
    servo5.write(angle_s5); // pulgar
  #endif

  Serial.print("Menique: ");
  Serial.print(r_s1);
  Serial.print(" ohms, ");
  Serial.print(angle_s1);
  Serial.println("grados.");

  Serial.print("Anular: ");
  Serial.print(r_s2);
  Serial.print(" ohms, ");
  Serial.print(angle_s2);
  Serial.println("grados.");

  Serial.print("Corazon: ");
  Serial.print(r_s3);
  Serial.print(" ohms, ");
  Serial.print(angle_s3);
  Serial.println("grados.");

  Serial.print("Indice: ");
  Serial.print(r_s4);
  Serial.print(" ohms, ");
  Serial.print(angle_s4);
  Serial.println("grados.");

  Serial.print("Pulgar: ");
  Serial.print(r_s5);
  Serial.print(" ohms, ");
  Serial.print(angle_s5);
  Serial.println("grados.");
}