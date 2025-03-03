#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

// Definir los pines de control
int pin_motor_a_forward = 6;
int pin_motor_b_forward = 5;
int pin_motor_a_1 = 7;
int pin_motor_a_2 = 8;
int pin_motor_b_1 = 12;
int pin_motor_b_2 = 13;

const int pinTone = 10;

SoftwareSerial huskySerial(12, 13);  // RX, TX; estos son los parametros para arduino, las huskylens se conectan al inverso
HUSKYLENS huskylens;

//SoftwareSerial bluetooth(3, 2); // RX, TX (puerto serial para Bluetooth)

int objectWidthThreshold = 50;  // Umbral de tamaño mínimo para un objeto derribado
int objectHeightThreshold = 50; // Umbral de tamaño mínimo para un objeto derribado
byte baseMotorSpeed = 200;
byte leftSpeed = 0;
byte rightSpeed = 0;

void setup() {
  Play3Char("not");
  Serial.begin(115200);
  //bluetooth.begin(9600);
  huskySerial.begin(9600);

  pinMode(pinTone, OUTPUT);
  // Configurar pines de los motores
  pinMode(pin_motor_a_forward, OUTPUT);
  pinMode(pin_motor_b_forward, OUTPUT);
  pinMode(pin_motor_a_1, OUTPUT);
  pinMode(pin_motor_a_2, OUTPUT);
  pinMode(pin_motor_b_1, OUTPUT);
  pinMode(pin_motor_b_2, OUTPUT);
  digitalWrite(pin_motor_a_1, HIGH);
  digitalWrite(pin_motor_a_2, LOW);
  digitalWrite(pin_motor_b_1, LOW);  //cambio de sentido para que se dirija con las baterias al frente y el arduino detras
  digitalWrite(pin_motor_b_2, HIGH);

  // Iniciar HuskyLens
  while (!huskylens.begin(huskySerial)) {
    Serial.println(F("Fail com. Huskylens"));
    delay(300);
  }

  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Establecer algoritmo de seguimiento de objetos
  
  Play3Char("set");
}


void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) {
    searchForNextObject();
    Serial.println(F("No block or arrow appears on the screen!"));
	}
    else {        
        while (huskylens.available()) {
            HUSKYLENSResult result = huskylens.read();
            moveTowardsObject(result);
            Serial.println("Detction, going for it");
            
            // Comprobar si el robot está lo suficientemente cerca del objeto
			if (isCloseEnough(result)) {
				//knockDownObject();
				Serial.println("Objeto cercano, impacto marcado.");
				}
			}
        }    
}



void moveTowardsObject(HUSKYLENSResult result) {
    // Coordenadas del centro del objeto
    int xCenter = result.xCenter; // Rango: 0 a 319
    //int yCenter = result.yCenter; // Rango: 0 a 239
    //int width = result.width;     // Ancho del objeto
    //int height = result.height;   // Alto del objeto


    // Corrección proporcional basada en la posición horizontal (xCenter)
    // Centro horizontal de la pantalla (320 / 2)
    int errorX = xCenter - 160; // Error respecto al centro
    //int proportionalSpeed = map(abs(errorX), 0, 160, 0, 255); // Mapear el error a un rango de velocidad
    //proportionalSpeed = constrain(proportionalSpeed, 0, 255); // Limitar la velocidad

    // Movimiento proporcional
    if (abs(errorX) > 10) { // Objeto a la izquierda del centro
        // Girar a la izquierda: motor A más lento, motor B a velocidad normal
        leftSpeed = constrain(baseMotorSpeed + errorX, 0, 255);
        rightSpeed = constrain(baseMotorSpeed - errorX, 0, 255);
        //analogWrite(pin_motor_a_forward, verticalSpeed - proportionalSpeed);
        //analogWrite(pin_motor_b_forward, verticalSpeed);
        move();
    }
    else { // Objeto centrado
        // Mover hacia adelante
        leftSpeed = baseMotorSpeed;
        rightSpeed = baseMotorSpeed;
        
        move();
    }
}




bool isCloseEnough(HUSKYLENSResult result) {
  // Usamos las dimensiones del objeto (width y height) y las coordenadas para determinar si está cerca
  int width = result.width;
  int height = result.height;

  // Verificar si el objeto es lo suficientemente grande y está lo suficientemente cerca
  if (width > objectWidthThreshold && height > objectHeightThreshold) {
    Serial.print(F("Objeto derribable detectado: Ancho = "));
    Serial.print(width);
    Serial.print(F(", Alto = "));
    Serial.println(height);
    
    return true;  // El objeto es suficientemente grande y cerca
  }
  
  return false;
}

void knockDownObject() {
  // Ejecutar la maniobra para derribar el objeto
  Serial.println("Impactando el objeto y derribándolo.");
  // Detener los motores un momento tras el impacto
  stopMotors();
  delay(500);  // Simulación de impacto
}

void searchForNextObject() {
  // Maniobra de búsqueda: puede ser un movimiento en círculo o barrido.
  Serial.println("Buscando el siguiente objeto...");
  moveInCircle();  // O puedes usar otro patrón de búsqueda, como avanzar y girar a intervalos.
}

void moveForward() {
  analogWrite(pin_motor_a_forward, 255);  // Máxima velocidad
  analogWrite(pin_motor_b_forward, 255);  // Máxima velocidad
}

void move(){
  analogWrite(pin_motor_a_forward, leftSpeed);  // Máxima velocidad
  analogWrite(pin_motor_b_forward, rightSpeed);  // Máxima velocidad		
}	

void stopMotors() {
  
  analogWrite(pin_motor_a_forward, 0);
  analogWrite(pin_motor_b_forward, 0);
}

void moveInCircle() {
    
    analogWrite(pin_motor_a_forward, 100);  // Velocidad reducida para el motor A
    analogWrite(pin_motor_b_forward, 0);  // Velocidad máxima para el motor B
}
