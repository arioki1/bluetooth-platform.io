#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);
String inputBluetooth = "";
bool isLedOn = false;
bool processed = true;

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
    if (mySerial.available()) {
        inputBluetooth = mySerial.readString();
        processed = false;
    } else {
        processed = true;
    };

    if (inputBluetooth == "LED_OFF") {
        digitalWrite(LED_BUILTIN, LOW);
        isLedOn = false;
    }
    if (inputBluetooth == "LED_ON") {
        digitalWrite(LED_BUILTIN, HIGH);
        isLedOn = true;
    }
    if (inputBluetooth == "LED_STATUS" && !processed) {
        String status = "LED_STATUS: ";

        if (isLedOn) {
            status += "ON";
        } else {
            status += "OFF";
        }

        uint8_t *pointer = (uint8_t *) status.c_str();
        int length = status.length();
        mySerial.write(pointer, length);
    }

}