#include <LiquidCrystal.h>

// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Component pins
const int LM35_PIN = A0;
const int LED_PIN = 8;
const int BUZZER_PIN = 9;

// Temperature limit
const float TEMP_LIMIT = 30.0;

void setup()
{
    // Set output pins
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Start LCD
    lcd.begin(16, 2);

    // Start Serial Monitor
    Serial.begin(9600);

    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    lcd.setCursor(0, 1);
    lcd.print("Monitoring...");

    delay(2000);
    lcd.clear();
}

void loop()
{
    // Read LM35
    int sensorValue = analogRead(LM35_PIN);

    // Convert ADC value to voltage
    float voltage = sensorValue * (5.0 / 1023.0);

    // LM35: 10 mV = 1 degree Celsius
    float temperature = voltage * 100.0;

    // Display temperature
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print((char)223);
    lcd.print("C   ");

    // Check temperature
    if (temperature >= TEMP_LIMIT)
    {
        // High temperature
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);

        lcd.setCursor(0, 1);
        lcd.print("HIGH TEMP!     ");

        Serial.println("WARNING: High Temperature!");
    }
    else
    {
        // Normal temperature
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);

        lcd.setCursor(0, 1);
        lcd.print("NORMAL         ");

        Serial.println("Temperature Normal");
    }

    // Display on Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    delay(1000);
}