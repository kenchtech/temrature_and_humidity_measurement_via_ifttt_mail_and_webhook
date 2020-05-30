//Edited by chinua 

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor  //should be installed


#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 5     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
//WiFi details
const char* ssid = "     ";//wifi name or SSID
const char* password = "    ";// WIFI or SSID password
const char* host = "maker.ifttt.com";

void setup() {
    Serial.begin(115200);
    Serial.println(F("DHTxx test!"));
  dht.begin();
  delay(1000);

    Serial.println("Email from Node Mcu");
    delay(100);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  

            



}
void loop() {
  // put your main code here, to run repeatedly:
 // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  WiFiClient client; 
           const int httpPort = 80;  
            if (!client.connect(host, httpPort)) {  
                  Serial.println("connection failed");  
            return;} 
          //if(Serial.available()){
            
            //char a=Serial.read();
            
            //if (a=='y'){
    
          
                    String url = "/trigger/Temperature_alarm/with/key/p6FTqbEsTpK1b9fsdNehaY8DPUwzrBPCd8cC4b00PW1"; 

          
                    Serial.print("Requesting URL: ");
                    Serial.println(url);
                 
                     client.print(String("GET ") + url + String("?value1=") + t + String("?value2=") + h + " HTTP/1.1\r\n" + 
                                    "Host: " + host + "\r\n" + 
                                           "Connection: close\r\n\r\n");    
            //                        }  
//}
  //else{
    //        Serial.println("Correct character not pressed.Try again");    
      //    }
          
          delay(10000);
          }
