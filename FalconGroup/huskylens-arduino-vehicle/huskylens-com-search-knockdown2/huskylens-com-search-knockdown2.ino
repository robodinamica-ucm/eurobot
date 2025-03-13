#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(12, 13); // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);

const int pinTone = 8;
int pin_motor_a_forward = 9;
int pin_motor_b_forward = 10;

int pin_motor_a_1 = 4;
int pin_motor_a_2 = 5;
int pin_motor_b_1 = 6;
int pin_motor_b_2 = 7;

byte baseMotorSpeed = 200;
byte leftSpeed = 0;
byte rightSpeed = 0;

void setup() {
    //need to use pwm pins
    pinMode(pin_motor_a_forward, OUTPUT);
    pinMode(pin_motor_b_forward, OUTPUT);
  
    pinMode(pin_motor_a_1, OUTPUT);
    pinMode(pin_motor_a_2, OUTPUT);
    pinMode(pin_motor_b_1, OUTPUT);
    pinMode(pin_motor_b_2, OUTPUT);
    pinMode(pinTone, OUTPUT);

    digitalWrite(pin_motor_a_1, LOW);
    digitalWrite(pin_motor_a_2, HIGH);
    digitalWrite(pin_motor_b_1, HIGH); //cambio de sentido para que el motor A que se encuentra a la izq gire en antihorario(13/03/2025)
    digitalWrite(pin_motor_b_2, LOW);
    
    Play3Char("not");
    Serial.begin(115200);
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); //Switch the algorithm to object tracking.
    Play3Char("set");
}


//void loop() {
//    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
//    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
//    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
//    else
//    {
//        Serial.println(F("###########"));
//        while (huskylens.available())
//        {
//            HUSKYLENSResult result = huskylens.read();
//            printResult(result);
//        }    
//    }
//}

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
//      if (isCloseEnough(result)) {
//        //knockDownObject();
//        Serial.println("Objeto cercano, impacto marcado.");
//        }
      }
        }    
}

void moveTowardsObject(HUSKYLENSResult result) {
    // Coordenadas del centro del objeto
    int xCenter = result.xCenter; // Rango: 0 a 319
    int errorX = xCenter - 160; // Error respecto al centro

    // Movimiento proporcional
    if (abs(errorX) > 10) { // Objeto a la izquierda del centro
        leftSpeed = constrain(baseMotorSpeed + errorX, 0, 255);
        rightSpeed = constrain(baseMotorSpeed - errorX, 0, 255);
        move();
    }
    else { // Objeto centrado
        leftSpeed = baseMotorSpeed;
        rightSpeed = baseMotorSpeed;
        move();
    }
}

void searchForNextObject() {
  // Maniobra de búsqueda: puede ser un movimiento en círculo o barrido.
  Serial.println("Buscando el siguiente objeto...");
  moveInCircle();  // O puedes usar otro patrón de búsqueda, como avanzar y girar a intervalos.
}

void move() {
  // Escribir las velocidades en los motores

  // Imprimir los valores de las velocidades en el monitor serial
  analogWrite(pin_motor_a_forward, leftSpeed);
  analogWrite(pin_motor_b_forward, rightSpeed);
  Serial.print("leftSpeed: ");
  Serial.print(leftSpeed);
  Serial.print(", rightSpeed: ");
  Serial.println(rightSpeed);
}

void moveInCircle() {
  //Play7Char("circle");
  Serial.println("circle");
  analogWrite(pin_motor_a_forward, 120);  // Velocidad reducida para el motor A
  analogWrite(pin_motor_b_forward, 80);  // Velocidad máxima para el motor B
}


void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}
