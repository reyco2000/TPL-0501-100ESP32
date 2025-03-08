#include <SPI.h>

#define CS_PIN 10  // Chip Select pin for TPL0501

void setup() {
    Serial.begin(115200);
    
    // Initialize SPI
    SPI.begin(12, -1, 4, CS_PIN);  // SCLK=12, MISO=-1 (not used), MOSI=4, CS=10
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);  // Set CS high (inactive)

    Serial.println("TPL0501 SPI Initialized.");
}

void writePot(uint8_t value) {
    digitalWrite(CS_PIN, LOW);  // Select the TPL0501
    SPI.transfer(value);        // Send resistance value (0-255)
    digitalWrite(CS_PIN, HIGH); // Deselect the TPL0501
}

void loop() {
    Serial.println("Sweeping potentiometer values...");
    
    for (uint8_t i = 0; i <= 255; i += 5) {  // Increase resistance in steps
        writePot(i);
        Serial.print("Wiper set to: ");
        Serial.println(i);
        delay(4000);
    }
    
    for (uint8_t i = 255; i > 0; i -= 5) {  // Decrease resistance in steps
        writePot(i);
        Serial.print("Wiper set to: ");
        Serial.println(i);
        delay(4000);
    }
}
