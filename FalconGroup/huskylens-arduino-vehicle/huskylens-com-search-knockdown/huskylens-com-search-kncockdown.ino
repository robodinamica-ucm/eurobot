#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(12, 13); // RX, TX

const int pinTone = 8;
int pin_motor_a_forward = 9;
int pin_motor_b_forward = 10;
int pin_motor_a_1 = 4;
int pin_motor_a_2 = 5;
int pin_motor_b_1 = 6;
int pin_motor_b_2 = 7;

byte baseMotorSpeed = 80;
byte leftSpeed = 0;
byte rightSpeed = 0;

bool objectDetected = false; // Indica si se ha detectado un objeto

int circleDirection = 1;
int lastDetectedDirection = -circleDirection; // 1 para cuando giramos a izquierda por lo que se encuentra a la derecha, -1 para cuando se encuentra a la izquierda (última dirección de giro)
//lo inicializamos para que corriga la inercia the circleDirection; una vez que objectDetected == true, cambiamos lastDetectedDirection segun el ultimo impulso de los motores antes de perder el objetivo

void setup() {
    pinMode(pin_motor_a_forward, OUTPUT);
    pinMode(pin_motor_b_forward, OUTPUT);
    pinMode(pin_motor_a_1, OUTPUT);
    pinMode(pin_motor_a_2, OUTPUT);
    pinMode(pin_motor_b_1, OUTPUT);
    pinMode(pin_motor_b_2, OUTPUT);
    pinMode(pinTone, OUTPUT);

    digitalWrite(pin_motor_a_1, LOW);
    digitalWrite(pin_motor_a_2, HIGH);
    digitalWrite(pin_motor_b_1, HIGH); // Cambio de sentido para el motor A
    digitalWrite(pin_motor_b_2, LOW);
    
    Play3Char("not");
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial)) {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    Play3Char("set");
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); // Cambiar al algoritmo de seguimiento de objetos
}

void loop() {
    if (!huskylens.request()) {
        Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    } else if (!huskylens.isLearned()) {
        Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    } else if (!huskylens.available()) {
        // No se detecta ningún objeto
        if (objectDetected) {
            // Si antes había un objeto, realizar una maniobra lenta en el sentido opuesto
            slowReverseSearch();
        } else {
            // Si no se ha detectado ningún objeto, buscar rápidamente
            searchForNextObject();
        }
    } else {
        // Objeto detectado
        objectDetected = true; //en este momento cada vez que perdamos el objetivo volveremos a buscarlo con slowReverseSearch
        //slowReverseSearch debe actuar en sentido contrario al ultimo impulso de los motores en move.
        //una vez que hayamos alcanzado el objetivo, ejecutamos knockdown() {objectDetected = false}
        HUSKYLENSResult result = huskylens.read();
        moveTowardsObject(result);
        if (leftSpeed > rightSpeed){lastDetectedDirection = 1;} else {lastDetectedDirection = -1;} //Evaluamos cual es la direccion en la que esta nuestro objetivo segun la potencia de los motores antes de perderlo
    }
}

void moveTowardsObject(HUSKYLENSResult result) {
    int xCenter = result.xCenter; // Rango: 0 a 319
    int errorX = 3 * (xCenter - 160); // Error respecto al centro

    // Control proporcional
    leftSpeed = constrain(baseMotorSpeed + errorX, 0, 255);
    rightSpeed = constrain(baseMotorSpeed - errorX, 0, 255);

    // Mover los motores
    move();

    // Mostrar información de depuración
    Serial.print("xCenter: ");
    Serial.print(xCenter);
    Serial.print(", errorX: ");
    Serial.print(errorX);
    Serial.print(", leftSpeed: ");
    Serial.print(leftSpeed);
    Serial.print(", rightSpeed: ");
    Serial.println(rightSpeed);
}

void searchForNextObject() {
    Serial.println("Buscando el siguiente objeto...");
    moveInCircle();
}


void slowReverseSearch() {
    Serial.println("Objeto perdido, realizando búsqueda lenta en sentido opuesto...");
    
    
    
    if (lastDetectedDirection == 1) {
        // Girar a la izquierda (sentido opuesto al último giro)
        leftSpeed = 80; // Motor A adelante
		rightSpeed =0;
    Serial.print("(lastDetectedDirection == 1) ");        
    
    } else {        
        leftSpeed = 0; 
		rightSpeed = 80; // Motor B go
    Serial.print("(lastDetectedDirection == 0) ");
    }
    move();
    //stopMotors();
}
 

void moveInCircle() {
    Serial.println("circle");
    if (circleDirection == 1) {
        leftSpeed = 100;
		rightSpeed =0;
    } else {
        leftSpeed = 0;
		rightSpeed = 100;
    }
    move();
}

void stopMotors() {
	leftSpeed = 0;
	rightSpeed = 0;
    move();
}

void move() {
    analogWrite(pin_motor_a_forward, leftSpeed);
    analogWrite(pin_motor_b_forward, rightSpeed);
    Serial.print("leftSpeed: ");
    Serial.print(leftSpeed);
    Serial.print(", rightSpeed: ");
    Serial.println(rightSpeed);
}
