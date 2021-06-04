
/*  
 *   WeedPot
 *   PM Project 2021
 *   Radulescu Florin 333CC
 *   
 *   Documentation: 
 *   https://ocw.cs.pub.ro/courses/pm/prj2021/abirlica/weedpot
 *   
 */

/*** Start of the Global section ***/

  /*** Start of Imported Libraries section ***/
  
    #include <SoftwareSerial.h>
    #include <ThingSpeak.h>  
    #include <ESP8266WiFi.h>

  /*** End of Imported Libraries section ***/

  /*** Start of Constants section ***/

   // Names to the used pins
                                    
    const int soilMoisturePin = 8;      // Digital pin soil moisture sensor is connected to
    const int ambientalLightPin = A3;   // Analog pin ambiental ligth sensor is connected to
    const int waterLevelPin = A5;       // Analog pin water level sensor is connected to
    const int sensorSwitchPin = 7;      // Digital pin used to control the sensors
    const int WiFiTxPin = 3;            // Digital pin the TX of the Wi-Fi module is connected to
    const int WiFiRxPin = 2;            // Digital pin the RX of the Wi-Fi module is connected to
    const int ArduinoLedPin = 13;       // Pin used for debug connected to the Arduino's LED

    // Strings used for connecting to the personal data channel on the ThingsSpeak platform
  
    unsigned long myChannelNumber = "1397512";
    const char * myWriteAPIKey = "KT88QENXE27TD5MO";
    const char * myReadAPIKey = "P8IX2PMGTM8CO7HE";

  /*** End of Constants section ***/

  /*** Start of Variables section ***/

    // Strings used for connecting to Wi-Fi -- To be changed based on location
    
    char ssid[] = "UPCF3F966F";         // Personal network SSID (name)
    char pass[] = "bQ7zpyUxt6df";       // Personal network password
    int keyIndex = 0;                   // Personal network key index number (needed only for WEP)
  
    // Global temporary values
  
    int waterLevelValue = 0;            // Stores the value read from the waterlevel sensor
    int soilMoistureValue = 0;          // Stores the value read from the soil moisture sensor
    int ambientalLightValue = 0;        // Stores the value read from the ambiental ligth sensor
    int httpCode = 0;                   // Stores the results of Http Requests or Http Responses

  /*** End of Variables section ***/

  /*** Other global prequisites ***/
    
    SoftwareSerial ESPserial(WiFiRxPin, WiFiTxPin);        // Sets the serial communication to ESP module
    WiFiClient client;                  // Local client for the Http session with the ThingSpeak platform

/*** End of the Global section ***/

void setup() {
  
  // Setup code, runs once:

    // Set the serial communication with the ESP module
    
    ESPserial.begin(9600);

    // Set the pin modes for the configuration

    pinMode(soilMoisturePin, INPUT);
    pinMode(ambientalLightPin, INPUT);
    pinMode(waterLevelPin, INPUT);
    pinMode(sensorSwitchPin, OUTPUT);
    pinMode(ArduinoLedPin, OUTPUT);

    // Set the Wi-Fi session

    WiFi.mode(WIFI_STA);
    ThingSpeak.begin(client);

    // Flash the LED on the Arduino to confirm the code
                                                                  
    for (int i=0; i <= 4; i++){                                
        digitalWrite(ArduinoLedPin, HIGH);
        delay(300);
        digitalWrite(ArduinoLedPin, LOW);
        delay(300);
    }
    delay(2000);
    
}

void loop() {
  
  // Main code, runs repeatedly:

    // Actively connects to Wi-Fi
    
    WiFi.begin(ssid, pass);
    delay(5000);

    // If the connection fails 5 times, sleep for 2 minutes before trying again

    if (WiFi.status() != WL_CONNECTED) {
        int wifi_connection_attempts = 0;
        while (WiFi.status() != WL_CONNECTED) {
            wifi_connection_attempts++;
            if (wifi_connection_attempts == 5) { 
                ESP.deepSleep(120e6);            
            }
            WiFi.begin(ssid, pass);
            delay(5000);
        }
    }    

    // At this point the Wi-Fi connection should have been established
    // Set up the alimentation for the sensors
    
    digitalWrite(sensorSwitchPin, HIGH); 

    // Read the values from the sensors and print them on the serial monitor
    
    // Check ambiental light level
  
    ambientalLightValue = analogRead(ambientalLightPin);      
    Serial.print("Ambiental light value: ");                  
    Serial.println(ambientalLightValue);

    // Check water level
    
    waterLevelValue = analogRead(waterLevelPin);              
    Serial.print("Water level value: ");                      
    Serial.println(waterLevelValue);

    // Check soil moisture
  
    soilMoistureValue = digitalRead(soilMoisturePin);
    Serial.print("Soil moisture value: ");
    Serial.print(soilMoistureValue);
    Serial.println("('0' = soil is too dry; '1' = soil is moist enough;)");

    // Stop the alimentation for the sensors to save power

    digitalWrite(sensorSwitchPin, LOW);         

    // Send data to ThingSpeak
  
    httpCode = ThingSpeak.setField(1, ambientalLightValue);
    httpCode = ThingSpeak.setField(2, waterLevelValue);
    httpCode = ThingSpeak.setField(3, soilMoistureValue);
    httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(16000);

    // Enter Deep Sleep for 10 minutes
  
    ESP.deepSleep(600e6);

}
