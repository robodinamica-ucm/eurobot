#define IN1_FL 4
#define IN2_FL 5
#define IN1_FR 10
#define IN2_FR 11
#define IN1_RL 6
#define IN2_RL 7
#define IN1_RR 13
#define IN2_RR 12
//
const int pinTone = 53;
const int trigPin = 47;
const int echoPin = 49;

// las unidades estan en cgs

unsigned long lastMeasureTime = 0;
float currentDistance = 0;
const int distanceCheckInterval = 100; // ms
const float safetyDistance = 10.0;

void setup() {
  pinMode(IN1_FL, OUTPUT); pinMode(IN2_FL, OUTPUT);
  pinMode(IN1_FR, OUTPUT); pinMode(IN2_FR, OUTPUT);
  pinMode(IN1_RL, OUTPUT); pinMode(IN2_RL, OUTPUT);
  pinMode(IN1_RR, OUTPUT); pinMode(IN2_RR, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinTone, OUTPUT);

  Play3Char("set");
  Serial.begin(9600);
}

// ---- Movimiento de motores ----
void moveForward(int speed) {
  Serial.println("forward");
  analogWrite(IN1_FL, speed); digitalWrite(IN2_FL, LOW);
  analogWrite(IN1_FR, speed); digitalWrite(IN2_FR, LOW);
  analogWrite(IN1_RL, speed); digitalWrite(IN2_RL, LOW);
  analogWrite(IN1_RR, speed); digitalWrite(IN2_RR, LOW);
}

void moveBackward(int speed) {
  digitalWrite(IN1_FL, LOW); analogWrite(IN2_FL, speed);
  digitalWrite(IN1_FR, LOW); analogWrite(IN2_FR, speed);
  digitalWrite(IN1_RL, LOW); analogWrite(IN2_RL, speed);
  digitalWrite(IN1_RR, LOW); analogWrite(IN2_RR, speed);
}

void moveRight(int speed) {
  analogWrite(IN1_FL, (int)(speed / 1.5)); digitalWrite(IN2_FL, LOW);
  digitalWrite(IN1_FR, LOW); analogWrite(IN2_FR, (int)(speed / 1.5));
  digitalWrite(IN1_RL, LOW); analogWrite(IN2_RL, speed);
  analogWrite(IN1_RR, speed); digitalWrite(IN2_RR, LOW);
}

void moveLeft(int speed) {
  Serial.println("left");
  digitalWrite(IN1_FL, LOW); analogWrite(IN2_FL, (int)(speed / 1.5));
  analogWrite(IN1_FR, (int)(speed / 1.5)); digitalWrite(IN2_FR, LOW);
  analogWrite(IN1_RL, speed); digitalWrite(IN2_RL, LOW);
  digitalWrite(IN1_RR, LOW); analogWrite(IN2_RR, speed);
}

void rotateRight(int speed) {
  Serial.println("rotate");
  analogWrite(IN1_FL, speed); digitalWrite(IN2_FL, LOW);
  digitalWrite(IN1_FR, LOW); analogWrite(IN2_FR, speed);
  analogWrite(IN1_RL, speed); digitalWrite(IN2_RL, LOW);
  digitalWrite(IN1_RR, LOW); analogWrite(IN2_RR, speed);
}

void rotateLeft(int speed) {
  digitalWrite(IN1_FL, LOW); analogWrite(IN2_FL, speed);
  analogWrite(IN1_FR, speed); digitalWrite(IN2_FR, LOW);
  digitalWrite(IN1_RL, LOW); analogWrite(IN2_RL, speed);
  analogWrite(IN1_RR, speed); digitalWrite(IN2_RR, LOW);
}

void stopMotors() {
  digitalWrite(IN1_FL, LOW); digitalWrite(IN2_FL, LOW);
  digitalWrite(IN1_FR, LOW); digitalWrite(IN2_FR, LOW);
  digitalWrite(IN1_RL, LOW); digitalWrite(IN2_RL, LOW);
  digitalWrite(IN1_RR, LOW); digitalWrite(IN2_RR, LOW);
}
//direction == 0, esta a la izquierda por lo que usamos moveLeft, direction == 1 => esta a la derecha
void pushStructure(bool direction){
  Serial.println("push");
  float halfStructureWidth = 20.0; 
  if(direction == 0){
    while(currentDistance > 50.0){
      updateDistance();
      moveLeft(100);
    }
    delay(10*halfStructureWidth); //continuamos moviendonos hasta llegar a la mitad
  }
  if(direction == 1){
    while(currentDistance > 50.0){
      updateDistance();
      moveRight(100);
    }
    delay(10*halfStructureWidth); //continuamos moviendonos hasta llegar a la mitad
  }
}

void moveForwardToApproach(float haltRange){
    currentDistance = haltRange + 1; //nos aseguramos de que el movimiento no va a quedar anulado por una medida anterior
    while(currentDistance > haltRange){
        updateDistance();
        moveForward(160);
    }        
}
// ---- Medición no bloqueante ----
void updateDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    //long duration = pulseIn(echoPin, HIGH, 25000); // 25 ms max timeout
    long duration = pulseIn(echoPin, HIGH); // 25 ms max timeout
    currentDistance = duration * 0.0343 / 2;

    Serial.print("Distance: ");
    Serial.println(currentDistance);

    lastMeasureTime = millis();
}


void accelerateSafely(void (*movement)(int), int maxSpeed, float targetDistance) { // en cm

  int speed = 80;

  unsigned long lastUpdate = 0;
  unsigned long lastDistanceCheck = 0;
  unsigned long lastIntegrationTime = millis();

  const int accelDelay = 50;
  const int distanceInterval = 50;

  float distanceTraveled = 0.0; // en cm
  const float speedToCMsFactor = 0.33; // calibrar // cm/s por unidad de "speed", debes calibrarlo
  //initial guess: 255 aprox 1 m/s = 100 cm/s speedToCMsFactor = 100/255 = 0.392
 

  updateDistance(); // Medición inicial

  while (true) {
    unsigned long currentMillis = millis();

    // Chequeo periódico de distancia al obstáculo
    if (currentMillis - lastDistanceCheck >= distanceInterval) {
      updateDistance();
      lastDistanceCheck = currentMillis;

      if (currentDistance < safetyDistance) {
        Play3Char("te");
        stopMotors();
        break;
      }
    }

    // Integración de la distancia recorrida
    float deltaTime = (currentMillis - lastIntegrationTime) / 1000.0; // segundos
    distanceTraveled += speed * speedToCMsFactor * deltaTime;
    lastIntegrationTime = currentMillis;

    if (distanceTraveled >= targetDistance) {
      stopMotors();
      break;
    }

    // Aceleración progresiva hasta maxSpeed
    if (speed < maxSpeed && (currentMillis - lastUpdate >= accelDelay)) {
      movement(speed);
      speed += 5;
      lastUpdate = currentMillis;
    } else if (speed >= maxSpeed) {
      movement(maxSpeed);
    }
  }
}

// ---- Loop principal ----
void loop() {
  accelerateSafely(moveForward, 160, 50);
  accelerateSafely(rotateRight, 160, 29); //estimacion para 90 grados a la derecha
  moveForwardToApproach(65);
  accelerateSafely(rotateRight, 160, 29);
  accelerateSafely(moveForward, 255, 30); //empujamos max potencia
  accelerateSafely(moveBackward, 160, 20);
  accelerateSafely(rotateLeft, 160, 26.4); //estimacion para 90 grados a la izquierda
  moveForwardToApproach(20);
  accelerateSafely(rotateLeft, 160, 26.4); //estimacion para 90 grados a la izquierda
  moveForwardToApproach(15); //aqui tenemos que aplicar la logica para la correccion de trayectoria e ir recto
}
