#include "HUSKYLENS.h"

HUSKYLENS huskylens;

void setup() {
    delay(2000);
    Serial.begin(115200);    // Monitor serie en PC
    Serial1.begin(9600);     // Comunicación con HuskyLens en UART1 (Mega 2560)
    
    while (!huskylens.begin(Serial1)) {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); //Switch the algorithm to object tracking.
}

void loop() {
    if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if (!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else {
        Serial.println(F("###########"));
        while (huskylens.available()) {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
        }    
    }
}

void printResult(HUSKYLENSResult result) {
    if (result.command == COMMAND_RETURN_BLOCK) {
        Serial.println(String() + F("Block: xCenter=") + result.xCenter + F(", yCenter=") + result.yCenter +
                        F(", width=") + result.width + F(", height=") + result.height + F(", ID=") + result.ID);
    } 
    else if (result.command == COMMAND_RETURN_ARROW) {
        Serial.println(String() + F("Arrow: xOrigin=") + result.xOrigin + F(", yOrigin=") + result.yOrigin +
                        F(", xTarget=") + result.xTarget + F(", yTarget=") + result.yTarget + F(", ID=") + result.ID);
    } 
    else {
        Serial.println("Object unknown!");
    }
}
