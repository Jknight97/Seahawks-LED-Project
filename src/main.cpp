#include <Arduino.h>
#include <U8g2lib.h>
#include <FastLED.h>
#include <WiFi.h>

#define WIFI_NETWORK "NETGEAR24-5G"            // Wifi network name
#define WIFI_PASSWORD "quietbird321"           // Wifi password
#define WIFI_TIMEOUT_MS 20000                  // Time in milliseconds, sets a hard time on how long arduino is allowed to attempt to establish a wifi connection
#define FASTLED_INTERNAL
#define OLED_CLOCK 15
#define OLED_DATA   4
#define OLED_RESET 16
#define NUM_LEDS   60
#define LED_PIN    21                          // Data line pin being used




/**
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
 * NO GO PAST THIS POINT CAUSE PASSWORD AND SHIT
*/

CRGB g_LEDs[NUM_LEDS] = {0};
U8G2_SSD1306_128X64_NONAME_F_HW_I2C g_OLED(U8G2_R2, OLED_RESET, OLED_CLOCK, OLED_DATA);
int g_lineHeight = 0;

double FramesPerSecond(double seconds){
    
    static double framesPerSecond;
    framesPerSecond = (framesPerSecond * .9) + (1.0 / seconds * 0.1);
    return framesPerSecond;
}

void connectToWifi(){
    Serial.print("Connecting to wifi");
    WiFi.mode(WIFI_STA);                                // When connectting to an existing wifi network, must be set to STA (station), as opposed to AP (access point)
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);            // AP can be used to allow arduino to establish it's own network

    unsigned long startAttemptTime = millis();          // millis() keeps track of arduino up-time, used to enforce our hard-coded timeout

    while ((WiFi.status() != WL_CONNECTED) && ((millis() - startAttemptTime) < WIFI_TIMEOUT_MS)){
        
        //pinMode(LED_BUILTIN, 1);
        Serial.print(".");
        delay(100);
        //pinMode(LED_BUILTIN, 0);
    }

    if (WiFi.status() != WL_CONNECTED){

        int NUM_NETWORKS = WiFi.scanNetworks();
        Serial.println(" Failed!");
        
        Serial.print(NUM_NETWORKS);
        Serial.println(" networks found");
        
        for (int i = 0; i < NUM_NETWORKS; i++){

            Serial.println(WiFi.SSID(i));
        }
        
        //ESP.restart();
    }
    else{
        
        pinMode(LED_BUILTIN, 1);
        Serial.print(" Connected!");
        Serial.println(WiFi.localIP());
    }
}

void setup(){
    
    pinMode(LED_PIN, OUTPUT);
    
    Serial.begin(9600);
    connectToWifi();

    while (!Serial) { }
    Serial.println("ESP32 Startup");

    g_OLED.begin();
    g_OLED.clear();
    g_OLED.setFont(u8g2_font_profont15_tf);
    g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();

    FastLED.addLeds<WS2812B, LED_PIN, GRB>(g_LEDs, NUM_LEDS);
    FastLED.setBrightness(16);
}

void loop() {

    bool bLED = 0;
    double fps = 0;

    //Forever loop  
    for(;;){
        bLED = !bLED;
        digitalWrite(LED_BUILTIN, bLED);

        double dStart = millis() / 1000.0;

        g_OLED.clearBuffer();
        g_OLED.setCursor(0, g_lineHeight);
        g_OLED.printf("FPS: %.1lf", fps);
        g_OLED.sendBuffer();

        for (int i = 1; i < NUM_LEDS + 1; i++){
            
            if (i % 2 == 0){

                g_LEDs[i] = CRGB::BlueViolet;
            }
            else {

                g_LEDs[i] = CRGB::BlueViolet;
            }
        }
        
        FastLED.show();

        double dEnd = millis() / 1000.0;
        fps = FramesPerSecond(dEnd - dStart);
    }
}