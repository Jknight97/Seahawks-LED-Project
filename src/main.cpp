#include <Arduino.h>
#include <U8g2lib.h>
#include <FastLED.h>
#include <WiFi.h>

#define WIFI_NETWORK "TESTFIBER"            // Wifi network name of FIBER NETWORK BOX (must be connected to wherever DHCP is handled I guess)
#define WIFI_PASSWORD "J09R10K97"           // Wifi password of FIBER NETWORK BOX (must be connected to wherever DHCP is handled I guess)
#define FASTLED_INTERNAL
#define WIFI_TIMEOUT 20000                  // Time in milliseconds, sets a hard time on how long arduino is allowed to attempt to establish a wifi connection
#define OLED_CLOCK 15
#define OLED_DATA 4
#define OLED_RESET 16
#define NUM_LEDS 60
#define LED_PIN 21                          // Data line pin being used




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

// Handles Wifi connection
void connectToWifi(){
    
    Serial.print("Connecting to wifi");
    WiFi.mode(WIFI_STA);                                // When connectting to an existing wifi network, must be set to STA (station), as opposed to AP (access point)
    WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);            // AP can be used to allow arduino to establish it's own network

    unsigned long startAttemptTime = millis();          // millis() keeps track of arduino up-time, used to enforce our hard-coded timeout
    bool bLED = 0;
    while ((WiFi.status() != WL_CONNECTED) && ((millis() - startAttemptTime) < WIFI_TIMEOUT)){
        
        bLED = !bLED;                                                // Blinks white led for visual confirmation of the attempt to establish a wifi connection
        digitalWrite(LED_BUILTIN, bLED);                             // ^
        Serial.print(".");
        delay(100);
    }

    if (WiFi.status() != WL_CONNECTED){

        int NUM_NETWORKS = WiFi.scanNetworks(false, true, false, 300, 153);
        Serial.println(" Failed!");
        Serial.println(WiFi.status());
        Serial.print(NUM_NETWORKS);
        Serial.println(" networks found");
        
        for (int i = 0; i < NUM_NETWORKS; i++){

            Serial.println(WiFi.SSID(i));
        }
        
        ESP.restart();                                             // Restarts Arduino board
    }
    else{
        digitalWrite(LED_BUILTIN, 1);                              // Turns white led on for visual confirmation of wifi connection
        Serial.println(" Connected!");
        Serial.println(WiFi.localIP());

        int NUM_NETWORKS = WiFi.scanNetworks(false, true, false, 300, 153);
        Serial.printf("%d networks found\n", NUM_NETWORKS);
        
        
        for (int i = 1; i < NUM_NETWORKS + 1; i++){

            Serial.printf("%d: %s\n", i, WiFi.SSID(i).c_str());
        }
    }
}

int DKScore;
int SeahawksScore;

// Checks stats of game for score updates
bool checkGameStats(){

    bool arr[2];

    //getter method for game stat increases
    //keep track of DK TD stat and seahawks score

    //if (seahawks score increases){
        //if (dk.stat increases){

            //arr[0] = true;
            //arr[1] = true;
        //}
        //else{

            //arr[0] = false;
            //arr[1] = true;
        //}
    //}

}

int getDKScoreJSON(){

    //get JSON information of DK, return touchdowns
}

int getSeattleScoreJSON(){

    //get JSON information of Seattle, return current score
}

bool isDK(){

    return false;
}

bool isSeahawks(){

    return true;
}

// LED Show distinctly for any seahawks score
void seahawksScore(){

    for (int i = 1; i < NUM_LEDS + 1; i++){
            
        if (i % 2 == 0){

            g_LEDs[i] = CRGB::Green;
        }
        else {

            g_LEDs[i] = CRGB::Blue;
        }
    }

}

// LED Show distinctly for DK TD
void dkTD(){

    for (int i = 1; i < NUM_LEDS + 1; i++){
            
        if (i % 2 == 0){

            g_LEDs[i] = CRGB::Red;
        }
        else {

            g_LEDs[i] = CRGB::Red;
        }
    }
}

void setup(){
    WiFi.disconnect(true);
    pinMode(LED_BUILTIN, OUTPUT);

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

    double fps = 0;

    //Forever loop  
    for(;;){
        
        double dStart = millis() / 1000.0;

        g_OLED.clearBuffer();
        g_OLED.setCursor(0, g_lineHeight);
        g_OLED.printf("FPS: %.1lf", fps);
        g_OLED.sendBuffer();

        if (isSeahawks() == true && isDK() == true){

            dkTD();
            FastLED.show();
        }
        else if (isSeahawks() == true && isDK() == false){

            seahawksScore();
            FastLED.show();
        }

        double dEnd = millis() / 1000.0;
        fps = FramesPerSecond(dEnd - dStart);
    }
}