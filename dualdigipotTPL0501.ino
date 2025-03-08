//////////////////////////////////////////////////////////////////
// Reinaldo Torres  
// Email: reyco2000@gmail.com  
// Released as open source  
//  
// YouTube: https://www.youtube.com/@ChipShift  
// GitHub:  https://github.com/reyco2000  
//  
// Description:  
// Sample code to connect 2 TPL0501 digital potentiometes to an ESP32S3
//  
// 3-8-2025
//////////////////////////////////////////////////////////////////
#include <SPI.h>

// Define Chip Select (CS) pins for both potentiometers
#define CS_POT1 10  // Potentiometer 1 CS pin
#define CS_POT2 11  // Potentiometer 2 CS pin

void setup() {
    Serial.begin(115200);
    
    // Initialize SPI (SCLK=12, MOSI=4)
    SPI.begin(12, -1, 4, CS_POT1);  
    SPI.begin(12, -1, 4, CS_POT2);  

    pinMode(CS_POT1, OUTPUT);
    pinMode(CS_POT2, OUTPUT);
    
    digitalWrite(CS_POT1, HIGH); // Deselect Pot 1
    digitalWrite(CS_POT2, HIGH); // Deselect Pot 2

    Serial.println("Dual TPL0501 SPI Initialized.");
}

// Function to write value (0-255) to a specific potentiometer
void writePot(uint8_t cs_pin, uint8_t value) {
    digitalWrite(cs_pin, LOW);  // Select the potentiometer
    SPI.transfer(value);        // Send resistance value
    digitalWrite(cs_pin, HIGH); // Deselect the potentiometer
}

void loop() {
    Serial.println("Sweeping potentiometer values...");
    
    for (uint8_t i = 0; i <= 255; i += 5) {  
        writePot(CS_POT1, i);
        writePot(CS_POT2, 255 - i);  // Opposite direction
        
        Serial.print("Pot 1 set to: ");
        Serial.print(i);
        Serial.print(" | Pot 2 set to: ");
        Serial.println(255 - i);
        
        delay(3000);
    }
    
    for (uint8_t i = 255; i > 0; i -= 5) {  
        writePot(CS_POT1, i);
        writePot(CS_POT2, 255 - i);
        
        Serial.print("Pot 1 set to: ");
        Serial.print(i);
        Serial.print(" | Pot 2 set to: ");
        Serial.println(255 - i);
        
        delay(3000);
    }
}
